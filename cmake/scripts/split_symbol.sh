#!/bin/bash

# split code and debug symbols
# save debug symbols to subdir named symbols

set -e

OBJCOPY_BIN=objcopy
STRIP_BIN=strip

function split_symbol()
{
	fname="$1"

	if [ ! -f $fname ]; then 
		echo "$fname" does not exists! > /dev/stderr
		exit 1
	fi

	if [ -h $fname ]; then
		fname=`readlink $fname`
	fi

	md5=`md5sum $fname | sed 's/\s.*$//'`
	# clean old symbols
	rm -f .debug/$fname.*
	${OBJCOPY_BIN} --only-keep-debug $fname .debug/$fname.$md5
	${STRIP_BIN} $fname
	${OBJCOPY_BIN} --add-gnu-debuglink=.debug/$fname.$md5 $fname
}

function usage()
{
	echo "Usage: $1 -o objcopy_bin -s strip_binfile [file...]"
}

function main()
{
	if [[ $# -eq 0 ]]; then
		usage $0
		exit 0
	fi

	while getopts o:s: flag; do
		case $flag in
			o)
				OBJCOPY_BIN=$OPTARG
				;;
			s)
				STRIP_BIN=$OPTARG
				;;
			*)
				usage $0
				;;
		esac
	done

	shift $(($OPTIND - 1))

	if [ ! -d symbols ]; then
		mkdir symbols -p
	fi
	if [ ! -d .debug ]; then
		ln -sf symbols .debug
	fi
	
	for i in $@; do
		split_symbol $i
	done
}

main $@

