#!/bin/bash


bubble_sort() {
    local array=("$@")
    local n=${#array[@]}
    local temp

    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [ "${array[j]}" -gt "${array[j+1]}" ]; then
                # Swap array[j] and array[j+1]
                temp=${array[j]}
                array[j]=${array[j+1]}
                array[j+1]=$temp
            fi
        done
    done

    echo "Sorted array: ${array[@]}"
}


echo "Enter numbers separated by spaces:"
read -a numbers


bubble_sort "${numbers[@]}"
