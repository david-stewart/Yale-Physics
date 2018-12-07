#!/usr/bin/bash
for i in {1..40}
do 
    star-submit-template -template xml/P16_template.xml -entities n=$i,k=40
done
