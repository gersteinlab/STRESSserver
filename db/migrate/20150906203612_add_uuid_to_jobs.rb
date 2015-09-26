class AddUuidToJobs < ActiveRecord::Migration
  def change
    add_column :jobs, :uuid, :string
  end
end
