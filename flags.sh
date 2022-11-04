#!/bin/bash


file="$1"
shift
echo  "" "$@" > ${file}.new
if report test -e "${file}" && report not cmp ${file}.new ${file} ; then
  report mv ${file}.new ${file}
else
  report rm -f "${file}.new"
fi
