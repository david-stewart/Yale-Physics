#!/usr/bin/python
from subprocess import call

for x in ((5,7,160), (7,9,80), (9,11,40), (11,15,60), (15,25,20), (25,35, 80), (35,45,8)):
    call (['star-submit-template','-template', 'xml/pythia6_template.xml',
        '-entities', 'min=%.1f,max=%.1f,nEvents=%i,seed=-1'%(x[0],x[1],x[2]*1000)])
