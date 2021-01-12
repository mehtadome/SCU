/*
Name: Ruchir Mehta
Date: October 5th, 2020
Title: Lab 2 Part 3: Finding response times
Description: Create a C program to computer various listed times
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RTT0 3
#define RTT1 20
#define RTT2 26
#define RTTHTTP 47
#define objects 6

int main() 
{
    // zero transmission time
    int zero_time = RTT0 + RTT1 + RTT2 + (2 * RTTHTTP);
    printf("Zero transmission time elapsed equals %d.\n", zero_time);

    // six objects w/ non-persistent HTTP and no parallel TCP connections
    int six_objs = zero_time + (2 * objects * RTTHTTP);
    print("Six objects with non-pers HTTP and no parallel TCP elapsed time equals %d.\n", six_objs);

    // non-persistent case
    int parallel_connects = 5;
    int non_per = zero_time + (2 * ceil(objects / parallel_connects) * RTTHTTP);
    printf("Parallel TCP connection and non-persistent time elapsed equals %d.\n", non_per);
    
    // persistent case
    int per = zero_time + (ceil(objects / parallel_connects) * RTTHTTP);
    printf("Parallel TCP connections and persistent time elapsed equals %d.\n", per);

}