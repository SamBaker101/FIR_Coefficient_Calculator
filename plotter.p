#Plot impulse response via gnuplot
set terminal png size 500,500

#Destination Address
set output 'data/impulse.png'

set title 'Impulse Response'
plot "data/impulse.txt"