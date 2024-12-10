#!/bin/sh

LEAK_CHECK='valgrind --log-file=/dev/null --leak-check=full --show-leak-kinds=all ./miniRT'

#get all .rt files in scenes
FILES=($(ls -1 scenes/*.rt))

#make sure executable is up to date
make >/dev/null

for file in "${FILES[@]}"
do
	#run valgrind for the file from FILES, if there's leaks, output
	if ! ${LEAK_CHECK} ${file} >/dev/null; then
		echo ERROR ${file}
	fi
done
