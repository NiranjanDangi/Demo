#!/bin/bash


check_palindrome() {
    input="$1"
    reversed=$(echo "$input" | rev)

    if [ "$input" = "$reversed" ]; then
        echo "$input is a palindrome."
    else
        echo "$input is not a palindrome."
    fi
}


echo "Enter a string:"
read string


check_palindrome "$string"