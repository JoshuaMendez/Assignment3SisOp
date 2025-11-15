set terminal wxt persist size 1200,800
set title "Movimiento del cabezal en Disk Scheduling"
set xlabel "Número de peticiones"
set ylabel "Cilindro"

plot "fcfs.dat"  using 1:2 with lines lw 2 lc rgb "red"   title "FCFS", \
     "scan.dat"  using 1:2 with lines lw 2 lc rgb "green" title "SCAN", \
     "cscan.dat" using 1:2 with lines lw 2 lc rgb "blue"  title "C-SCAN"
