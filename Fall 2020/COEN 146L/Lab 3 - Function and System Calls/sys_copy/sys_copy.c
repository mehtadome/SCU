/*
Name: Ruchir Mehta
Date: October 12, 2020
Title: Lab 3 Part 1
Description: Copy a binary/text file to another file using system calls
*/

// To compile and run:
// gcc -o sys sys_copy.c -std=c99
// ./sys
// vim copyTo.txt

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buffer;

    // O_RDWR mode for reading and writing 
    int sc = open("sup.txt", O_RDWR);
    // error checking
    if (sc == -1)
    {
        perror("Error opening source file.");
        return(-1);
    }

    // create file if one doesn't exit and write only
    // 0644 is some mode to specify read and write only (required)
    int destination = open("copyTo.txt",O_WRONLY | O_CREAT, 0644); 
    if (destination == -1)
    {
        perror("Error opening the destination file.");
        return (-1);
    }

    // read the source file and output to destination file
        // 0 indicates end of file
    

    // close up shop
    close(sc);
    close(destination);

    return 0;
}