class AddIndexToJobs < ActiveRecord::Migration
  def change
    add_index :jobs, :PDB_id
  end
end
