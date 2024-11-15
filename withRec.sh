#!/bin/bash

# Function to calculate factorial with recursion
factorial_recursive() {
    local number=$1

    if [ $number -le 1 ]; then
        echo 1
    else
        local temp=$((number - 1))
        local result=$(factorial_recursive $temp)
        echo $((number * result))
    fi
}

# Read a number from the user
echo "Enter a number to find its factorial (recursive):"
read number

# Call the recursive factorial function and print the result
result=$(factorial_recursive $number)
echo "Factorial of $number (recursive) is: $result"
