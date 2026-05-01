#!/bin/bash

ARCH=$$.ar
if [[ $# -lt 3 ]] 
then
    echo "usage $0 server port file1 [file2 ...]"
    exit 1
fi
SERVER=$1
PORT=$2
shift; shift
ARGS=$*
ar rc $ARCH $ARGS
nc -q1 $SERVER $PORT < $ARCH
rm -f $ARCH

