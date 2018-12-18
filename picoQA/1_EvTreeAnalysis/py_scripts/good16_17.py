data_16 = [ int(x.strip()) for x in open('16_good_runs.list','r') if x.strip() ]
data_17 = [ int(x.strip()) for x in open('17_good_runs.list','r') if x.strip() ]


with open('good_16_and_17.list','w') as f:
    for x in (x for x in data_16 if x in data_17):
       f.write('%i\n'%x)
