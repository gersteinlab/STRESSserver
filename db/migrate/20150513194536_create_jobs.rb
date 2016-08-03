class CreateJobs < ActiveRecord::Migration
  def change
    create_table :jobs do |t|
      t.string :PDB_id

      t.timestamps null: false
    end
  end
end
