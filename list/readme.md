#purpose
This directory contains the run lists used for the QA process.


Command for 0_picoToEvTree

get_file_list.pl -keys path,filename -cond events!=0,production=P17id,filetype~picoDst,collision=pAu200,runnumber[]16125033-16159025,year=2015,available=1,storage!=hpss,sanity=1 -limit 0 -delim \/ > pico.list

