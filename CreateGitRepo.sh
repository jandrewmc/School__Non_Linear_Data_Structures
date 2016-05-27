#!/bin/bash

if [ "$#" -ne 3 ];
then
	echo "Illegal Number of parameters"
	echo "Please enter the user-name, visibility modifier, and repo name respectively"
	exit
fi
if [ "$2" = '-private' ]
then
	curl -u "$1" https://api.github.com/user/repos -d '{"name":"'$3'", "public":"false"}'
	exit
fi

if [ "$2" = '-public' ]
then
	curl -u "$1" https://api.github.com/user/repos -d '{"name":"'$3'", "public":"true"}'
	exit
fi
