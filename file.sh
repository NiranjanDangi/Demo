#!/bin/bash


check_file() {
    if [ -z "$1" ]; then
        echo "Usage: $0 <filename>"
        exit 1
    fi

    filename="$1"

    if [ -e "$filename" ]; then
        echo "File: $filename"
        echo "File Type:"
        file "$filename"
        echo "Permissions:"
        ls -l "$filename" | awk '{print $1 " " $3 " " $4}'
    else
        echo "File does not exist."
    fi
}


echo "Enter the filename:"
read filename


check_file "$filename"