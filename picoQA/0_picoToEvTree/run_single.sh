starver SL18b
infile=/star/data25/reco/production_pAu200_2015/ReversedFullField/P17id.SL18b/2015/128/16128022/st_ssdmb_16128022_raw_1000025.picoDst.root
root4star -q -b ./basicRunQA.C\(1000,\"$infile\",\"test\",1\)
