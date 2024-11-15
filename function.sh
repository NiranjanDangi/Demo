#!/bin/bash


average() {
    echo "Enter numbers separated by spaces:"
    read -a numbers

    sum=0
    count=${#numbers[@]}

    for num in "${numbers[@]}"; do
        sum=$((sum + num))
    done

    avg=$(echo "scale=2; $sum / $count" | bc)
    echo "The average is: $avg"
}


max_number() {
    echo "Enter numbers separated by spaces:"
    read -a numbers

    max=${numbers[0]}

    for num in "${numbers[@]}"; do
        if [ $num -gt $max ]; then
            max=$num
        fi
    done

    echo "The maximum number is: $max"
}


min_number() {
    echo "Enter numbers separated by spaces:"
    read -a numbers

    min=${numbers[0]}

    for num in "${numbers[@]}"; do
        if [ $num -lt $min ]; then
            min=$num
        fi
    done

    echo "The minimum number is: $min"
}


echo "Choose an option:"
echo "1) Calculate average of given numbers"
echo "2) Find maximum number from given numbers"
echo "3) Find minimum number from given numbers"
read choice

case $choice in
    1)
        average
        ;;
    2)
        max_number
        ;;
    3)
        min_number
        ;;
    *)
        echo "Invalid option. Please select 1, 2, or 3."
        ;;
esac
