#!/bin/bash

export TIMEFORMAT=%E

LC_NUMERIC="en_US.UTF-8"
LF="$(time (./queue_lockfree) 2>&1 1>/dev/null)"
MT="$(time (./queue_mutex) 2>&1 1>/dev/null)"

echo "536644"
S=$(echo "scale=3; (($LF/ $MT) * 100) / 1" | bc) ; echo ${S%.*}
