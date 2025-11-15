set terminal wxt persist size 900,600
set title "Comparación de rendimiento (Movimiento total del cabezal)"
set style data histograms
set style fill solid 1.0
set ylabel "Distancia total recorrida"

plot "performance.dat" using 2:xtic(1) title ""
