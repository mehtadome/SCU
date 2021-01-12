# Name: Ruchir Mehta
# Date: 01/11/2021
# Title: Lab 1 - Scripting in Shell
# Description: This program displays path and user and then calculates
#              the area of a rectangle and circle

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$

# If user is ruchir, the rest of the program will run
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."

if [ $user = "ruchir" ]
then
    echo "Now you can proceed!"
else 
    echo "Check who logged in!"
    exit 1
fi 

# Calculate area of rectangle based on user input
response="Yes"
while [ $response != "No" ]
do
    echo "Enter height of rectangle: "
    read height
    echo "Enter width of rectangle: "
    read width 
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area"

    echo "Would you like to repeat for another rectangle [Yes/No]?"
    read response 

done

# Calculate area of circle based on user input
response1="Yes"
pi="3.1415"
while [ $response1 != "No" ]
do  
    echo "Enter radius of circle: "
    read radius
    radSquared=`expr $radius \* $radius`
    
    # Note: there cannot be spaces in multipliction due to bc being invoked
    area1=`scale=4; expr $pi\*$radSquared | bc`
    echo "The area of the circle is $area1"

    echo "Would you like to repeat for another circle [Yes/No]?"
    read response1

done
