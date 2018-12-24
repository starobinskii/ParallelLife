#!/bin/bash

for i in {240,480,720,960,1200, 1440, 1680, 1920}; do
    echo "" > ${i}p.time
    for j in $(seq 1 4); do
        result=$(cat ./Results/${i}_${j}.time | awk '{print $3}' | tr -d 'ms' | paste -sd+ - | awk '{print "(" $1 ")/10"}' | bc -liq)
        echo "${j} ${result}" >> ${i}p.time
    done
done

gnuplot << EOD
    set terminal png
    set output 'life.png'

    set xlabel "processes"

    set autoscale

    set ylabel "time, ms"

    set title "Parallel Life (Mushchak, Starobinskii)"
    set key reverse Left outside
    set grid

    set style data linespoints

    plot "240p.time" using 1:2 title "Mesh = 240", \
         "480p.time" using 1:2 title "Mesh = 480", \
         "720p.time" using 1:2 title "Mesh = 720", \
         "960p.time" using 1:2 title "Mesh = 960", \
         "1200p.time" using 1:2 title "Mesh = 1200" \ 
         "1440p.time" using 1:2 title "Mesh = 1440" \ 
         "1680p.time" using 1:2 title "Mesh = 1680" \ 
         "1920p.time" using 1:2 title "Mesh = 1920"
EOD