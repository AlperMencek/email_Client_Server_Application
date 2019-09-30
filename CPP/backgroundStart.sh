#!/bin/sh
echo "syntax: ./startBackground.sh command with args"
echo "eg: ./startBackground.sh ./bin/calculateRPCServer 8080"
INVOKE="$@"
echo "starting with: nohup $INVOKE >> $LOG_PATH 2>> $ERROR_PATH < /dev/null &"
nohup $INVOKE > log.txt 2> logerrors.txt < /dev/null &
PID=$!
echo $PID > logpid.txt
