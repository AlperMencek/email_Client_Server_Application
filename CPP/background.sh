#!/bin/sh
echo "syntax: ./startStopResetBackground [start|stop|restart] command with args"
echo "such as: ./startStopResetBackground start java -jar lib/echoserver.jar 8080"
echo "remove ./log/command.txt to reset the command to start the server"
CMMD=$1
shift
LOG_PATH=./log/log.txt
ERROR_PATH=./log/error.txt
PID_PATH_NAME=./log/pid.txt
START_COMMAND_FILE=./log/command.txt
case $CMMD in
    start)
        if [ ! -f $PID_PATH_NAME ]; then
            if [ -f $START_COMMAND_FILE ]; then
                INVOKE=$(cat $START_COMMAND_FILE);
            else
                INVOKE="$@"
                echo $INVOKE > $START_COMMAND_FILE
            fi
            echo "starting with: nohup $INVOKE >> $LOG_PATH 2>> $ERROR_PATH < /dev/null &"
            nohup $INVOKE >> $LOG_PATH 2>> $ERROR_PATH < /dev/null &
            echo $! > $PID_PATH_NAME
        else
            echo "Service is already running, $PID_PATH_NAME exists ..."
        fi
    ;;
    stop)
        if [ -f $PID_PATH_NAME ]; then
            PID=$(cat $PID_PATH_NAME);
            echo "$Stopping process with PID $PID ..."
            kill -9 $PID;
            echo "Stopped ..."
            rm $PID_PATH_NAME
        else
            echo "Service is not running, can't find PID file: $PID_PATH_NAME ..."
        fi
    ;;
    restart)
        if [ -f $PID_PATH_NAME ]; then
            PID=$(cat $PID_PATH_NAME);
            echo "$Stopping process with PID $PID ...";
            kill -9 $PID;
            echo "$Stopped ...";
            rm $PID_PATH_NAME
            if [ -f $START_COMMAND_FILE ]; then
                INVOKE=$(cat $START_COMMAND_FILE);
            else
                INVOKE="$@"
                echo $INVOKE > $START_COMMAND_FILE
            fi
            echo "starting with: nohup $INVOKE >> $LOG_PATH 2>> $ERROR_PATH < /dev/null &"
            nohup $INVOKE >> $LOG_PATH 2>> $ERROR_PATH < /dev/null &
            echo $! > $PID_PATH_NAME
        else
            echo "$Service is not running,  can't find PID file: $PID_PATH_NAME ..."
        fi
    ;;
esac 
exit 0
