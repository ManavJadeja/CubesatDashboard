#!/bin/bash

gcc lorenz.c -o lorenz.exe -lm && ./lorenz.exe &
sleep 0.2
gnuplot -persist <<-EOFMarker
  set xrange [-25:25]
  set yrange [-25:35]
  set zrange [-10:60]
  unset key
  set terminal wxt size 1000,800
  set size 1.1,1.2
  set xyplane 0
  load 'realtime.p'
EOFMarker
