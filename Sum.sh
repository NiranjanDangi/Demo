#!/bin/bash

if [ -z "$1" ]; then
    echo "Please provide a number as a command-line argument."
    exit 1
fi


number=$1

sum=0


while [ $number -gt 0 ]; do
    digit=$((number % 10))
    
    sum=$((sum + digit))
    
    number=$((number / 10))
done

echo "The sum of the digits is: $sum"


