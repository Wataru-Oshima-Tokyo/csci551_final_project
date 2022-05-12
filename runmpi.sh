#!/bin/bash
# Counting total number of arguments

# echo "Total number of arguments: $#"

# Reading argument values individually
# echo "First argument value : $1"
# echo "Second argument value : $2"
# echo "Third argument value : $3"
# for argval in "$@"
# do
#        echo -n "$argval "
# done
_arg=100
re='^[0-9]+$'
program=$1
VAR=$2
mpirun -n 16 -ppn 8 -f c1_hosts.wataru ./$program $VAR
# read VAR
# if [[$VAR =~ $re]] then
#     $_arg = $VAR
#     echo ''
# fi

