class AddAttachmentGnResultToJobs < ActiveRecord::Migration
  def self.up
    change_table :jobs do |t|
      t.attachment :GN_result
    end
  end

  def self.down
    remove_attachment :jobs, :GN_result
  end
end
