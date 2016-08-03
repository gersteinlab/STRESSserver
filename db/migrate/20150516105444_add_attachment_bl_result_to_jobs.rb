class AddAttachmentBlResultToJobs < ActiveRecord::Migration
  def self.up
    change_table :jobs do |t|
      t.attachment :BL_result
    end
  end

  def self.down
    remove_attachment :jobs, :BL_result
  end
end
