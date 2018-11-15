#!/usr/bin/bash
for i in {1..20}
do 
    star-submit-template -template xml/P17_template.xml -entities n=$i,k=20
done
