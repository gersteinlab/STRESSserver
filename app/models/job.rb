class Job < ActiveRecord::Base
	has_attached_file :PDB_file
  validates_attachment :PDB_file, content_type: { content_type: "chemical/x-pdb" }
  validates :PDB_file, :attachment_presence => true, :on => :create

  has_attached_file :BL_result
  validates_attachment_file_name :BL_result, :matches => [/dat\Z/]

  has_attached_file :GN_result
  validates_attachment_file_name :GN_result, :matches => [/txt\Z/]

  # only works for uploaded files - to save local file, @job.BL_result = local_file
  def save_attachment(attribute_name, input_file, input_file_name)
    temp_file = File.new(input_file_name, "wb")
    temp_file.write(input_file.read)
    self.send(attribute_name+'=',temp_file)
    File.delete(temp_file.path)
  end


end
