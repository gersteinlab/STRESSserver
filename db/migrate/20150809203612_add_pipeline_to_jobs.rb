class AddPipelineToJobs < ActiveRecord::Migration
  def change
    add_column :jobs, :pipeline, :string
  end
end
