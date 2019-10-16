#!/bin/bash

if [ -n "$1" ]
then
	rm *.gch 2>> /dev/null
	rm a.out 2>> /dev/null
	git add .
	git commit -m "$*"
	git pull
	git push
else
	echo "Enter commit message. "
fi
