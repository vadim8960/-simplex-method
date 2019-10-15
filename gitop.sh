#!/bin/bash

rm *.gch 
rm a.out
git add .
git commit -m "$1"
git pull
git push