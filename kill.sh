#!/bin/bash

for pid in $(pgrep -u gby python3); do
    echo "Killing process $pid (python3) for user gaobingyu"
    kill -9 $pid
done

echo "All python3 processes for user gaobingyu have been terminated."

