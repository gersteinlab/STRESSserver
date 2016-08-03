class WorkerMailer < ApplicationMailer

    default from: "stress@gersteinlab.org"  

    def notification(job)
        @job = job
        @url = 'http://stress.molmovdb.org/jobs/' + @job.uuid
        mail(:to => @job.email, :subject => "[STRESS] Your job result is ready")
    end
end
