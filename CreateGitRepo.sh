#!/bin/bash

if [ "$#" -ne 1 ];
then
	echo "Illegal Number of parameters"
	echo "Please enter the name of the repo you wish to create"
	exit
fi

curl -u 'jandrewmc' https://api.github.com/user/repos -d '{"name":"'$@'"}'
