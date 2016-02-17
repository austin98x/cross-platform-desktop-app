#!/bin/bash

# copy shared library and it's symbolic links
# $1 the *.so file
# $2 destination copy to

function copy_so()
{
	so_file=$1
	dest_dir=$2

	if [ ! -d "$dest_dir" ] ; then
		mkdir -p "$dest_dir"
	fi

	base_name=`basename $so_file`
	real_file=`readlink -f $so_file`

	files=(`ls ${so_file}*`)

	real_dir=`dirname $real_file`
	if [ $real_dir != "`dirname $so_file`" ] ; then
		files+=(`ls $real_dir/${base_name}*`)
	fi

	cp -a "$real_file" "$dest_dir"

	cd "$dest_dir"
	base_name=`basename $real_file`
	for file in ${files[@]} ; do
		if [ -L $file ] ; then
			ln -fs $base_name `basename $file`
		fi
	done
}

copy_so $@
