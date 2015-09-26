class AddGnOptionToJobs < ActiveRecord::Migration
  def change
    add_column :jobs, :GN_needed, :boolean
  end
end
