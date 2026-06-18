#!/bin/bash
MOD=100
RANDOM="${1:-20125}"
FILENAME="input.txt";
echo "10" > $FILENAME;
for ((i=0; i<10; i++)); do
    len_N=$((10 + RANDOM % 90));
    len_K=$(($len_N + RANDOM % 900));
    echo "$len_N $len_K" >> $FILENAME;
    for ((j=0; j<$len_N; j++)); do
        echo -n "$(( RANDOM % $MOD )) " >> $FILENAME
    done
    echo "" >> $FILENAME;
    for ((j=0; j<$len_K; j++)); do
        echo -n "$(( RANDOM % $MOD )) " >> $FILENAME
    done
    echo "" >> $FILENAME;
done
