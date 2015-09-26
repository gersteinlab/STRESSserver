class AddBlOptionToJobs < ActiveRecord::Migration
  def change
    add_column :jobs, :BL_needed, :boolean
  end
end
