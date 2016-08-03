class WorkersController < ApplicationController

  skip_before_filter :verify_authenticity_token

  def sqsd
    queue_url='https://sqs.us-west-2.amazonaws.com/244108043468/allostericweb'
    poller = Aws::SQS::QueuePoller.new(queue_url)

    if Dir.exist?("/var/app/current/working")
      render :nothing => true, :status => :processing
    end

    poller.poll do |msg|
      Dir.mkdir("/var/app/current/working")
      job_id = msg.body
      @job = Job.find_by(uuid: job_id)
      temp_dir_name = "/var/app/current/processing_temp_files_#{job_id}/"
      pdb_id = @job.PDB_file.path.gsub(/.pdb1/, '').gsub(/.pdb/, '').gsub(/.*\//, '')
      pdb_file = temp_dir_name+pdb_id
      log_tag = "[#{job_id}]"

      pipeline_location = '/var/app/current/code/pipeline_both.sh'

      if Dir.exist?(temp_dir_name)
        # unexpected error occurred while processing messages,
        # log it, and skip delete so it can be re-processed later
        throw :skip_delete
        logger.info("#{log_tag} Already processing")
        # render :nothing => true, :status => :processing   #status code 102

      else

        Dir.mkdir(temp_dir_name)

        @job.PDB_file.copy_to_local_file(:original, pdb_file)

        logger.info("#{log_tag} running pipeline")
        `sh #{pipeline_location} #{pdb_file} #{temp_dir_name} #{job_id} #{@job.BL_needed} #{@job.GN_needed} > #{temp_dir_name}/bashlog`
        exitstatus = $?.exitstatus
        @job.exitstatus = exitstatus
        @job.save
        logger.info("#{log_tag} Pipeline finished. Exit status: #{exitstatus}")

        # BL pipeline successful?
        if @job.BL_needed 
          if exitstatus | 0b10000 == 0b10000
            my_BL_result_file_name = temp_dir_name+pdb_id+'__SURFACE_CRITICAL_residues.dat'
            my_BL_result_file = open(my_BL_result_file_name, "r") 
            @job.BL_result = my_BL_result_file
            @job.save
            my_BL_result_file.close
            logger.info("#{log_tag} pipeline_BL succeeded: attached #{my_BL_result_file_name} to job #{job_id}")
          else
            #error handling
            logger.info("#{log_tag} pipeline_BL failed with error code #{exitstatus}")
          end
        else
          logger.info("#{log_tag} skipped BL pipeline")
        end

        # GN pipeline successful?
        if @job.GN_needed
          if exitstatus | 0b01100 == 0b01100
            my_GN_result_file_name = temp_dir_name+pdb_id+'__INTERIOR_CRITICAL_residues.txt'
            my_GN_result_file = open(my_GN_result_file_name, "r") 
            @job.GN_result = my_GN_result_file
            @job.save
            my_GN_result_file.close
            logger.info("#{log_tag} pipeline_GN succeeded: attached #{my_GN_result_file_name} to job #{job_id}")
          else
            #error handling
            logger.info("#{log_tag} pipeline_GN failed with error code #{exitstatus}")
          end
        else
          logger.info("#{log_tag} skipped GN pipeline")
        end

        #system("rm -rf #{temp_dir_name}")
        send_email_notification_if_requested
        system("rm -rf /var/app/current/working")
        head :ok

      end  
    end

  end

  # def process_job
  #   Dir.mkdir("/var/app/current/working")
  #   job_id = params[:job_id]
  #   @job = Job.find_by(uuid: job_id)
  #   temp_dir_name = "/var/app/current/processing_temp_files_#{job_id}/"
  #   pdb_id = @job.PDB_file.path.gsub(/.pdb1/, '').gsub(/.pdb/, '').gsub(/.*\//, '')
  #   pdb_file = temp_dir_name+pdb_id
  #   log_tag = "[#{job_id}]"

  #   pipeline_location = '/var/app/current/code/pipeline_both.sh'

  #   if Dir.exist?(temp_dir_name)
  #     logger.info("#{log_tag} Already processing")
  #     render :nothing => true, :status => :processing   #status code 102

  #   else

  #     Dir.mkdir(temp_dir_name)

  #     @job.PDB_file.copy_to_local_file(:original, pdb_file)

  #     logger.info("#{log_tag} running pipeline")
  #     `sh #{pipeline_location} #{pdb_file} #{temp_dir_name} #{job_id} #{@job.BL_needed} #{@job.GN_needed} > #{temp_dir_name}/bashlog`
  #     exitstatus = $?.exitstatus
  #     @job.exitstatus = exitstatus
  #     @job.save
  #     logger.info("#{log_tag} Pipeline finished. Exit status: #{exitstatus}")

  #     # BL pipeline successful?
  #     if @job.BL_needed 
  #       if exitstatus | 0b10000 == 0b10000
  #         my_BL_result_file_name = temp_dir_name+pdb_id+'__SURFACE_CRITICAL_residues.dat'
  #         my_BL_result_file = open(my_BL_result_file_name, "r") 
  #         @job.BL_result = my_BL_result_file
  #         @job.save
  #         my_BL_result_file.close
  #         logger.info("#{log_tag} pipeline_BL succeeded: attached #{my_BL_result_file_name} to job #{job_id}")
  #       else
  #         #error handling
  #         logger.info("#{log_tag} pipeline_BL failed with error code #{exitstatus}")
  #       end
  #     else
  #       logger.info("#{log_tag} skipped BL pipeline")
  #     end

  #     # GN pipeline successful?
  #     if @job.GN_needed
  #       if exitstatus | 0b01100 == 0b01100
  #         my_GN_result_file_name = temp_dir_name+pdb_id+'__INTERIOR_CRITICAL_residues.txt'
  #         my_GN_result_file = open(my_GN_result_file_name, "r") 
  #         @job.GN_result = my_GN_result_file
  #         @job.save
  #         my_GN_result_file.close
  #         logger.info("#{log_tag} pipeline_GN succeeded: attached #{my_GN_result_file_name} to job #{job_id}")
  #       else
  #         #error handling
  #         logger.info("#{log_tag} pipeline_GN failed with error code #{exitstatus}")
  #       end
  #     else
  #       logger.info("#{log_tag} skipped GN pipeline")
  #     end

  #     #system("rm -rf #{temp_dir_name}")
  #     send_email_notification_if_requested
  #     system("rm -rf /var/app/current/working")
  #     head :ok

  #   end
    
  # end
  


  private

    def send_email_notification_if_requested
      if @job.email.length > 0
        # ses = AWS::SimpleEmailService.new(:region => 'us-west-2')
        # ses.send_email(
        #   :subject => '[STRESS] Your job result is ready',
        #   :from => 'richard.w.chang@yale.edu',
        #   :to => @job.email,
        #   :body_text => 'Please http://stress.molmovdb.org/jobs/' + @job.uuid,
        #   :body_html => 'http://stress.molmovdb.org/jobs/' + @job.uuid)
        WorkerMailer.notification(@job).deliver_now
      end
    end

end
