#!/usr/bin/python
""" Script run from main directory to resubmit jobs that didn't finish correctly

command line parameter: [name] in  "root/ln_[name]"
"""
from glob import glob
from sys import exit, argv
from os import path
from subprocess import call

#----------------------------------
# Find the session used to resubmit
#----------------------------------
if len(argv) < 2:
    print 'fatal error: requires one commnad line argument: [name] in  "root/ln_[name]"'
    exit(2)

ln_dir = 'root/ln_%s'%argv[1]

skip_files = []
for i in argv[2:]:
	skip_files.append(i)

if not path.exists(ln_dir):
    print 'fatal error, dir %s does not exist'%ln_dir
    exit(2)

names = []
for x in glob('%s/*.root'%ln_dir):
    val = x.split('/')[-1].split('_')[0]
    if val not in names:
        names.append(val)

if len(names) != 1:
    print 'fatal error: more than one root name in directory'
    exit(2)

name = names[0]
session_file = '%s.session.xml'%name

if not path.exists(session_file):
    print 'fatal: session file "%s" is not present'
    exit(2)

#-------------------------------
# Find the name of the root file
#-------------------------------
resub_vals = []
for f in open('%s/readme.md'%ln_dir,'r').readlines():
    if f.count('_') != 1:
        continue
    prefix, number = f.strip().split('_')
    # print "%s %s"%(prefix, name)
    if prefix == name:
        # print 'a'
        if number in skip_files:
             print 'skipping: %s'%number
        else:
             resub_vals.append(number)

# star-submit -r 1,2,3,5 DDD9CFB586F4139E8D14C6.session.xml    //Resubmit jobs 1,2,3, and 5

cmd = ['star-submit','-r',','.join(resub_vals),session_file]
# cmd = ' '.join(cmd)
print cmd
call (cmd)

