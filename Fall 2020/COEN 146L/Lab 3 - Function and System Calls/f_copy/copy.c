/*
Name: Ruchir Mehta
Date: October 12, 2020
Title: Lab 3 Part 1
Description: Copy a binary/text file to another file using function calls
*/

// To compile an run
// gcc -o copy copy.c -std=c99
// ./copy
// Either copy from remote server "copyTo.jpg" or display using terminal

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *sc, *destination;
    char myChar;

    // have to use "rb" for non-text files
    sc = fopen("reach.jpg", "rb");
    fputs("This is an image from the video game Halo Reach", sc);
    // error checking
    if (sc == NULL)
    {
        perror("Error opening the source file");
        return(-1);
    }

    fseek(sc, 0, SEEK_END);
    int len = ftell(sc);

    // use wb to make file of zero length to allow for writing
    destination = fopen("copyTo.jpg", "wb");
    // error checking
    if (destination == NULL)
    {
        perror("Error opening the destination file");
        return(-1);
    }

    // Put source file back to beginning
    fseek(sc, 0, SEEK_SET);

    for (int i = 0; i < len; i++)
    {
        // function that gets individual char
        myChar = fgetc(sc);

        // write char to the destination file
        fputc(myChar, destination);
    }

    // close up shop
    close(sc);
    close(destination);

    return 0;

}