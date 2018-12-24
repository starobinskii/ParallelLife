#!/bin/bash

runParallelLife(){
    meshSize=$1

    for k in $(seq 1 4); do
        echo "Started with N_proc = ${k}"
        mpiexec -n ${k} parallelLife.out --runs=10 --mesh-size=${meshSize} > ./Results/${meshSize}_${k}.time
        echo "Finished"
        echo ""
    done
}

# clean
rm -f *.time ./Results/*.time
rm life.png

# calculate
for i in {240,480,720,960,1200,1440,1680,1920}; do
    runParallelLife ${i}
    echo "" > ${i}p.time
    for j in $(seq 1 4); do
        result=$(cat ./Results/${i}_${j}.time | awk '{print $3}' | tr -d 'ms' | paste -sd+ - | awk '{print "(" $1 ")/10"}' | bc -liq)
        echo "${j} ${result}" >> ${i}p.time
    done
done

# plot
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
         "1200p.time" using 1:2 title "Mesh = 1200", \ 
         "1440p.time" using 1:2 title "Mesh = 1440", \ 
         "1680p.time" using 1:2 title "Mesh = 1680", \ 
         "1920p.time" using 1:2 title "Mesh = 1920"
EOD