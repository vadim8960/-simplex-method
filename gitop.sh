#!/bin/bash

if [ -n "$1" ]
then
rm *.gch 
rm a.out
git add .
git commit -m "$*"
git pull
git push
else
echo "Enter commit message. "
fi
