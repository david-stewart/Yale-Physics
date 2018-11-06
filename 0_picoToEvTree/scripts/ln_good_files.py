#!/usr/bin/python

# run this file from kate/root/[name]
from glob import glob
import subprocess
from subprocess import call
from os import path
from os import getcwd
import os

# ln each file in root/[name] that has an We END in out/[name]

name = getcwd().split('/')[-1]
print 'my name: %s'%name

if not os.path.isdir('good_links'):
    os.mkdir('good_links')
else:
    call ("rm good_links/*", shell=True)

nbad = 0
ngood = 0

bad_alloc = []
no_WeEND  = []
for fname in glob("../../out/%s/*"%name):
    # check for endline in ../../out
    endline = subprocess.check_output(["tail","-n","1",fname])
    e_name = fname.split('/')[-1]
    b_no_WeEND = 'We END' not in endline

    # check for bad_alloc
    # print "grep bad_alloc ../../err/%s/%s"%(name, e_name)
    err = ""
    has_bad_alloc = False
    try:
        err = subprocess.check_output(["grep","bad_alloc","../../err/%s/%s"%(name, e_name)])
        if "bad_alloc" in err:
            has_bad_alloc = True
    except:
        pass

    if b_no_WeEND:
        no_WeEND.append(e_name) 
        print '"We END" not found in ../../out/%s: %s'%(name, e_name)
    if has_bad_alloc:
        bad_alloc.append(e_name)
        print ' bad_alloc error in ../../err/%s: %s'%(name, e_name)

    if b_no_WeEND or has_bad_alloc:
        nbad += 1
    else:
        call(['ln','%s.root'%e_name,'good_links/%s.root'%e_name])
        ngood += 1

fout = open('good_links/readme.md','w')
fout.write("Total files:  %i\n"%(ngood + nbad))
fout.write("n files good:  %i\n"%ngood)
fout.write("n files bad: %i\n"%nbad)

fout.write("  -- %i files with no 'We END':\n" % len(no_WeEND))
for L in no_WeEND:
    fout.write("  %s\n"%L)

fout.write("  -- %i files with 'bad_alloc':\n" % len(bad_alloc))
for L in bad_alloc:
    fout.write("  %s\n"%L)

fout.close()

for L in open('good_links/readme.md'):
    print L.strip()

# print "Total files:  %i"%(ngood + nbad)
# print "n files bad:  %i"%nbad
# print "n files good: %i"%ngood
# fout.write("  -- %i files with no 'We END':\n" % len(no_WeEND))
# for L in no_WeEnd:
#     fout.write("  %s\n"%L)

# fout.write("  -- %i files with no 'bad_alloc':\n" % len(bad_alloc))
# for L in bad_alloc:
#     fout.write("  %s\n"%L)

# if len(argv) == 1:
#     exit("error, need name of directory")

# name = argv[1]
# dname = "%s/good_ln"%name

# if path.isdir("
# print

# print 'hi'
