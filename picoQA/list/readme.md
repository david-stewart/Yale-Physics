#purpose
get_file_list.pl -keys path,filename -cond events!=0,production=P17id,filetype~picoDst,collision=pAu200,runnumber[]16125033-16159025,year=2015,available=1,storage!=hpss,sanity=1 -limit 0 -delim \/ > pico_P17id.list


Tue Nov  6 14:21:18 EST 2018

I just noticed that teh above call for P17id is only for ssdmd. So... I should
be using the reconstruction for the P16id (which is the `st_physics` stream)

get_file_list.pl -keys path,filename -cond events!=0,production=P16id,filetype~picoDst,collision=pAu200,runnumber[]16125033-16159025,year=2015,available=1,storage!=hpss,sanity=1 -limit 0 -delim \/ > pico_P16id.list
