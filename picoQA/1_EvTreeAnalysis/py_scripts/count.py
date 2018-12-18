from sys import argv, exit

# get the good and bad runs stats from [16/17]_[good/bad]_runs.list

good16 = []
bad16  = []
good17 = []
bad17  = []

good16 = set ( int(i) for i in open('16_good_runs.list','r') if i.strip())
good17 = set ( int(i) for i in open('17_good_runs.list','r') if i.strip())

bad16 = set ( int(i) for i in open('16_bad_runs.list','r') if i.strip())
bad17 = set ( int(i) for i in open('17_bad_runs.list','r') if i.strip())

def diffs(a,b):
    return {'a':len(a), 'a-only':len(a.difference(b)), 'b':len(b), 'b-only':len(b.difference(a))}

f_str = '{a:10} {a-only:10} {b:10} {b-only:10}'
print (f_str.format( **{'a':'P16id', 'a-only':'only P16id', 'b':'P17id', 'b-only':'only P17id'} ))
print (f_str.format(**diffs(good16.union(bad16), good17.union(bad17))))
print (f_str.format(**diffs(good16, good17)))
print (f_str.format(**diffs(bad16, bad17)))
print('done')
print('a independent: ' , len(good17), ' ' , len(bad17), ' ' , len(good17.intersection(bad17)))
print('a independent: ' , len(good16), ' ' , len(bad16), ' ' , len(good16.intersection(bad16)))
print('a independent: ' , len(good17), ' ' , len(good16), ' ' , len(good16.intersection(good17)))
exit(2)

print ('inter 16: ', len(good16.intersection(bad16)))
print ('inter 17: ', len(good16.intersection(bad16)))

print( len(good16), ' ' , len(bad16), ' ', len(good16)+len(bad16), ' ' , len(good16.union(bad16)))
exit(2)

for x in open('16_good_runs.list','r').readlines():
    # print( x)
    val = x.strip()
    if val:
        good16.append(val)

for x in open('16_bad_runs.list','r').readlines():
    # print( x)
    val = x.strip()
    if val:
        bad16.append(val)

for x in open('17_good_runs.list','r').readlines():
    # print( x)
    val = x.strip()
    if val:
        good17.append(val)

for x in open('17_bad_runs.list','r').readlines():
    # print( x)
    val = x.strip()
    if val:
        bad17.append(val)

n16 = len(good16)+len(bad16)
n16good = len(good16)
n17 = len(good17)+len(bad17)
n17good = len(good17)

def print_stat(a, b):
    print(len(a), len([x for x in a if x not in b]), len(b), len([x for x in b if x not in a]))

print_stat(good16 + bad16, good17 + bad17)
print_stat(good16, good17)
print_stat(bad16, bad17)

