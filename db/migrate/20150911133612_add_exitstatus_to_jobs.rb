class AddExitstatusToJobs < ActiveRecord::Migration
  def change
    add_column :jobs, :exitstatus, :integer
  end
end
