#!/bin/bash
while  [ true ]; do
  ps cax | grep receiver > /dev/null
  if [ $? -ne 0 ]; then
    echo "Process is not running." | tee -a logs/receiver.log
    echo "Restarting receiver" | tee -a logs/receiver.log
    date +"%T" | tee -a logs/receiver.log
    ./bin/receiver | tee -a logs/receiver.log &
  fi
done
