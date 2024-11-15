#!/bin/bash

# Function to calculate factorial without recursion
factorial_non_recursive() {
    local number=$1
    local result=1

    for ((i = 1; i <= number; i++)); do
        result=$((result * i))
    done

    echo "Factorial of $number (non-recursive) is: $result"
}

# Read a number from the user
echo "Enter a number to find its factorial (non-recursive):"
read number

# Call the non-recursive factorial function with the user-provided number
factorial_non_recursive $number
