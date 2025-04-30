#!/bin/bash




for i in $(seq 1 90); do
    arg3=$((i * 4))
    ./bresenham 22 40 "$arg3"

    sleep 0.2


done
