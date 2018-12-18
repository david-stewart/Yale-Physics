#!/usr/local/Cellar/python@2/2.7.15_1/bin/python

"""find where the center division lies relative to 0.5"""

def where_in_int (n) -> float :
    div = 1./n
    i_left = 0.5 // div
    # print (i_left)
    return 0.5 - (0.5 - i_left*div) / div

for i in range(3,40):
    print(' i: ', i, ' ' ,where_in_int(i) )
