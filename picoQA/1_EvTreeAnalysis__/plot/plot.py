#!/usr/bin/python
#!/usr/local/Cellar/python@2/2.7.15_1/bin/python

# !/usr/local/Cellar/python/3.7.1/bin/python3
import matplotlib.pyplot as plt
import numpy as np
from ROOT import TH1F, TCanvas

def getRunIds(file_name):
    runIds = []
    for x in open(file_name).readlines():
        X = x.split()
        if not X: continue
        if X[0] == ':':
            if int(X[1]) == 0: continue
        else: 
            continue

        if int(X[1]) not in runIds:
            runIds.append(int(X[1]))

    rval = dict()
    i = 0

    for x in runIds:
        rval[i] = x
        i += 1
    return rval

class stat_line:
    mean = 0
    min  = 0
    max  = 0
    std  = 0
    stdmean = 0
    nEntries = 0
    def __init__(self, arr):
        self.mean = float(arr[5])
        self.max  = float(arr[4])
        self.min  = float(arr[3])
        self.std  = float(arr[6])
        self.std_mean = float(arr[7])
        self.nEntries = int(arr[8])

def collect_y_vals(file_name, keyword_name):
    vals = dict()
    val_0line = 0
    for line in open(file_name).readlines():
        words = line.split()
        if not words: continue
        if not words[0] == ':':
            continue
        if words[2] == keyword_name:
            if words[1] == '00000000':
                val_0line = stat_line(words)
            else:
                vals[int(words[1])] = stat_line(words)
    return vals, val_0line

def plot_hgram(file_name, entry_name, nbins = 40):
    runIds = getRunIds(file_name)
    stats, stats0  = collect_y_vals(file_name, entry_name)

    x = runIds.keys();
    x.sort();
    y = [ stats[runIds[i]].mean for i in x ]

    print 'z'
    # x_hgram = np.arange(stats0.min, stats0.max, 1)
    # y_hgram, stuf = np.histogram(y, bins=50)
    # plt.hist(np.histogram(y_hgram, x_hgram))
    # plt.show()

    # c1 = TCanvas("c1")
    hgram = TH1F("hgram",";;",80, 0, 80);
    keys = stats.keys()
    keys.sort()

    k0 = []
    for key in keys:
        k0.append(stats[key].mean)
        # print "%i %f"%(key, stats[key].mean)

    k1 = [ stats[key].mean for key in keys ]

    print k0 == k1


    for x in k1:
        hgram.Fill(x)
        print x
    # hgram.Draw()
    # c1.Show()
    # c1.SaveAs("a.pdf")
    

    plt.hist(k1, np.arange(10,40,1))
    plt.yscale('log')
    plt.xaxi
    plt.show()

    exit("done")




    print "a"
    print y_hgram
    print "b"
    print stuf

    
    
plot_hgram("P16.log","nPrimaryTracks")

# runIds = getRunIds("P16.log")
# stats  = collect_y_vals("P16.log", "nPrimaryTracks")

# x = runIds.keys()
# y = [ stats[runIds[i]].mean for i in x ]
# y = [x.mean for x in stats.values()]
# for i in x:
    # y.append(stats[runIds[i]].mean)

# z = [ stats[runIds[i]].mean for i in x ]

# print y == z

# print x
# print y

# i = 0
# keys = stats.keys()
# keys.sort()
# for index in keys:
#     if (i > 10) : break
#     i += 1
#     print ("%i  %f (%f-%f) means (%f, %f) :: %i"%(index, 
#         stats[index].mean, 
#         stats[index].min,
#         stats[index].max,
#         stats[index].std_mean,
#         stats[index].std,
#         stats[index].nEntries))

# print "Size of dict: %i"%len(runIds.keys())
# print "Size of dict: %i"%len(stats.keys())




# for x in a.keys():
    # print "  %10i : |%9i|"%(x, a[x])

# plt.plot(x,y)
# plt.show()
# plt.plot([1,2,3,4])
# plt.ylabel('some numbers')
# plt.show()

