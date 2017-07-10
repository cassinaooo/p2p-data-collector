#!/bin/bash
while  [ true ]; do
  ps cax | grep sender > /dev/null
  if [ $? -ne 0 ]; then
    echo "Process is not running." | tee -a logs/sender.log &
    echo "Cleaning up and restarting." | tee -a logs/sender.log &
    rm -rf files/*.tar.gz

    if [ -f files/to_send/SUCCESS ]; then
        echo "Last transfer successful, preparing for next time" | tee -a logs/sender.log &
        #rm -rf files/to_send/*
    else
        echo "Last transfer did not end correctly, preparing for retry" | tee -a logs/sender.log &
    fi
    date +"%T" | tee -a logs/sender.log
    ./bin/sender | tee -a logs/sender.log &
    echo "running ..." | tee -a logs/sender.log &
  fi
done
