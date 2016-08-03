class AddAttachmentPdbFileToJobs < ActiveRecord::Migration
  def self.up
    change_table :jobs do |t|
      t.attachment :PDB_file
    end
  end

  def self.down
    remove_attachment :jobs, :PDB_file
  end
end
