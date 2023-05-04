#!/bin/bash

set -e

# Create a temporary file to store the filtered CSV data
temp_csv="$(mktemp)"

# Filter the CSV data to only include the name of the benchmark and the time
# Convert scientific notation to decimal notation
awk -F, 'NF >= 3 && $1 ~ /^"BM/ {printf "%s,%f\n", $1, $3}' | sed 's/_/ /g' | sed 's/BM .. //g'> "${temp_csv}"
# awk -F, 'NF >= 3 && $1 ~ /^"BM/ {printf "%f,%s\n", $3, $1}' | sed 's/_/ /g' > "${temp_csv}"

num_lines=$(wc -l < "${temp_csv}")
if [[ ${num_lines} == 0 ]]; then exit 1; fi
# Create the gnuplot script to generate the graph
gnuplot_script="$(mktemp)"
# cat > "${gnuplot_script}" << EOL
# set terminal pngcairo size 1280,720 enhanced font 'Verdana,15'
# set output '${1}/bench.png'
# set boxwidth 0.1
# set style fill solid
# set grid x
# set xlabel 'Benchmark'
# set ylabel 'Aeg (ns)'
# set title '$(echo ${1} | sed "s/_/ /g")'
# set xtics rotate by -45
# set datafile separator ","
# plot '${temp_csv}' using 2:xtic(1) with boxes notitle
# EOL

cat > "${gnuplot_script}" << EOL
set terminal pngcairo size 720,500 font 'Verdana,12:italic'
set output '${1}/bench.png'
set boxwidth 0.5
set style fill solid
set grid y
set ylabel 'Aeg (ns)'
# set xlabel 'Benchmark'
set title '$(echo ${1} | sed "s/_/ /g")'
set xtics rotate by -45
set datafile separator ","
set lmargin 10
set rmargin 8
set tmargin 2
set bmargin 10
plot '${temp_csv}' using 2:xtic(1) with boxes notitle
EOL

# Generate the graph using gnuplot
gnuplot "${gnuplot_script}"

# Remove temporary files
rm "${temp_csv}" "${gnuplot_script}"

echo "Generated ${1}/bench.png"