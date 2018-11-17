Allosteric Web
=============
Repo for website of an allosteric project in Gersten lab

All code from DC in code folder

## Note about potential security vulnerability
The current version of this server has a security vulnerability. This vulnerability, which is in the rack module, has been classified by GitHub as a moderate severity security vulnerability. More information can be found here:
https://nvd.nist.gov/vuln/detail/CVE-2018-16471
and here:
https://nvd.nist.gov/vuln/detail/CVE-2015-3225

## Tasks
- [x] Allow users to upload files
- [x] Allow users to give PDB ID and then fetch files from PDB
- [x] Let users select which module they want to run (BL or/and GN)
- [x] Run two programs and report results
  - [x] Pipeline all programs using bash (Shantao) 
  - [x] Install & configure MMTK on an AWS instance (Richard)
- [x] Email notification for users after the job is done
- [x] Archive finished results in SQL database, automatically query
- [x] Fix GN module
- [N] Batch processing (user can submit multiple PDB ids or upload multiple PDB files and retrieve all the results in one zip file)
- [x] Random job id
- [N] Delete user submitted PDB files and results after 1 week
- [N] Prepopulate database with selected PDB IDs and results
- [ ] Front end design, descriptions, instructions, email content, etc.
- [N] Progress indicator
- [ ] Quick mode?
- [ ] Docker image
- [ ] Make code available: BL/GN, server code, sample data & output, docker image
- [ ] Database flat file showing all results: Bulk paper results and accumulated results
- [ ] Documentation
- [N] Caps to prevent overuse
- [N] DNS naming
- [N] Visualization (optional)?
- [D] Fix autoscaling
- [ ] Web server setup packaging and distribution

## Implementation Notes
- Paperclip used to manage PDB file attachments
- Validations for user-uploaded PDB files and user-specified PDB ids
- Run `pipeline_BL [INPUTPDB]` to execute BL module and `pipeline_GN [INPUTPD]`
  - But in order to remove MMTK dependency, pass `fnm_10` as the 2nd param 
  - GN Module not working now...I need to ask DC about the weird VMD dependency and python script (Shantao)
  - `pipeline_BL.sh` writes output files to the current working directory


## AWS Notes
- 1 web server tier for processing HTTP requests, 1 worker tier for processing background jobs. Auto-scaling enabled.
- 1 RDS database and 1 S3 bucket for cloud-based storage. Allows both tiers to share data.
- RDS t2.micro: max_connections is 26
