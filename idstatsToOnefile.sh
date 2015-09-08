#!/bin/bash
#This script merge all count file in the folder into one 
#usage: bash idstateTooneFile.sh foldername
cd $1
FILE=$(ls| sort -n |head -1)
cd ..
echo Genome > Genome.txt
cat $1/$FILE | cut -f1 -s >> Genome.txt

for x in $1/*.txt;
do echo ${x##*$1/} > $x.col.txt;
cat $x | cut -f3 -s >> $x.col.txt;
done

paste Genome.txt $1/*.col.txt > counts.txt
rm $1/*.col.txt
rm Genome.txt