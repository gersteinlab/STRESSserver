class JobsController < ApplicationController

  #before_action :redirect_to_archived_result_if_available, only: :create

  def new
    @job = Job.new
    @job.BL_needed = true
    @job.GN_needed = true
  end

  def create
    @job = Job.new
    save_uploaded_PDB_file_if_uploaded
    fetch_and_save_PDB_file_if_PDB_id_specified
    save_other_fields
    if @job.save && @job.PDB_file
      @job.PDB_file.copy_to_local_file(:original, @job.uuid)
      pdb_size = `grep "^ATOM" #{@job.uuid} | awk '{if ($3=="CA") print $0}' | wc -l`.to_i
      `rm -f #{@job.uuid}`
      if pdb_size > 1300
        @job.destroy
        @size = pdb_size
        render "new"
      else
        add_job_to_queue
        redirect_to job_url(@job.uuid)
      end
    else
      @invalid = true
      render 'new'
    end
  end

  def search
    @job = Job.find_by(uuid: params[:job_id].strip)
    if @job
      render action: 'show'
    else
      @not_found = true
      @job = Job.new
      @job.BL_needed = true
      @job.GN_needed = true
      render 'new'
    end
  end


  def show
    @job = Job.find_by(uuid: params[:id])
  end


  def download
    @job = Job.find_by(uuid: params[:uuid])
    attachment = params[:attachment]
    send_file(Paperclip.io_adapters.for(@job.send(attachment)).path, 
              :type => @job.send(attachment+'_content_type'), 
              :disposition => "attachment", 
              :filename => @job.send(attachment+'_file_name'))
  end


  private

    #params[:job][:GN_needed] will be "0" or "1"
    #but @job.GN_needed is false or true
    def redirect_to_archived_result_if_available

      if params[:job][:PDB_id]
        @job = Job.find_by(PDB_id: params[:job][:PDB_id].upcase,
                           GN_needed: params[:job][:GN_needed] == "1" ? true : false,
                           BL_needed: params[:job][:BL_needed] == "1" ? true : false)
        if @job
          redirect_to @job
        end
      end
    end

    def add_job_to_queue
      sqs = AWS::SQS::Client.new()
      queue_name = 'allostericweb'
      queue_url = sqs.get_queue_url(
        queue_name: queue_name
      ).queue_url
      # sqs.set_queue_attributes(
      #   queue_url: queue_url,
      #   attributes: { "VisibilityTimeout" => "43200" }
      # )
      sqs.send_message(
        queue_url: queue_url,
        message_body: "#{@job.uuid}"
        # message_body: %Q[{ "job_id": "#{@job.uuid}" }]
      )
    end

    def save_uploaded_PDB_file_if_uploaded
      if params[:job][:PDB_file]
        input_file = params[:job][:PDB_file]
        input_file_name = input_file.original_filename
        @job.save_attachment('PDB_file',input_file,input_file_name)
      end
    end

    def fetch_and_save_PDB_file_if_PDB_id_specified
      if params[:job][:PDB_id]
        begin
          @job.PDB_id = params[:job][:PDB_id].upcase
          input_file_name = @job.PDB_id + '.pdb1' # Try biological assembly first 
          input_file = open(URI.parse('http://www.rcsb.org/pdb/files/' + input_file_name))
          @job.save_attachment('PDB_file',input_file,input_file_name)
        rescue OpenURI::HTTPError => ex
    		  # probably redudant
    		  if (ex.io.status[0] == "404")
      			begin 
      			  input_file_name = @job.PDB_id + '.pdb'
      			  input_file = open(URI.parse('http://www.rcsb.org/pdb/files/' + input_file_name))
      			  @job.save_attachment('PDB_file',input_file, input_file_name)
      			rescue OpenURI::HTTPError => ex
      			end
    		  end
        end
      end
    end


    def save_other_fields
      @job.uuid = SecureRandom.uuid
      @job.email = params[:job][:email]
      @job.BL_needed = params[:job][:BL_needed]
      @job.GN_needed = params[:job][:GN_needed]
      @job.exitstatus = -1
    end

end
