starver SL18b
# infile=/star/data20/reco/production_pAu200_2015/ReversedFullField/P16id.SL18b/2015/140/16140009/st_physics_16140009_raw_1000022.picoDst.root
# infile=/star/data25/reco/production_pAu200_2015/ReversedFullField/P17id.SL18b/2015/128/16128022/st_ssdmb_16128022_raw_1000025.picoDst.root
# infile=/star/data19/reco/AuAu_200_production_mid_2014/ReversedFullField/P17id.SL18b/2014/116/15116033/st_physics_15116033_raw_5500031.picoDst.root
infile=/star/data25/reco/production_pAu200_2015/ReversedFullField/P17id.SL18b/2015/129/16129008/st_ssdmb_16129008_raw_5000043.picoDst.root
listdir=/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/picoQA/list
badtfile=$listdir/BadTowers_Comb.08.02.list
badrfile=$listdir/bad_run_list.list
root4star -q -b ./EventTrees.C\(-1,\"$infile\",\"test\",\"$badtfile\",\"$badrfile\",1\)
