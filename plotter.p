#Plot impulse response via gnuplot
set terminal png size 500,500
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2

#Destination Address
set output 'data/impulse.png'

set title 'Impulse Response'
plot "data/impulse.txt" with lines linestyle 1


#Destination Address
set output 'data/freq.png'

set title 'Frequency Response'
plot "data/freq.txt" with lines linestyle 1