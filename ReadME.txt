EMPLOYEE DATABASE
------------------
A simple C program which takes in a txt file of Employees and adds them to a an array of structures, sorts it and performs various operations on them.

Project Description
-------------------
This program is built using 3 C files. 
	1. readfile.h		- Declares the functions used to read the text file
	2. readfile.c		- Defines the function used to read the text file
	3. workerDB.c		- Contains the main function to run the program and other supporting functions for the various operations to be perfomed on the database

Source codes are included in the repository, for reference.

How to RUN (on a windows OS through the Command Line)
----------------------------
1. Download the 3 files into the computer, along with the input.txt file
2. Navigate to the downloaded file directory in the file explorer
3. Open Command prompt through the address bar of the folder
4. Enter in the command line : gcc -o workerDB workerDB.c readfile.c
5. Next enter : workerDB input.txt
6. Perform the required operations
7. Close the command prompt when finished

Credits
-------
This project was developed as part of the SP-Lab2 assignment of the course CS402 at the Illinois Institue of Technology, under guidance from Professor Virgil Bistriceanu and Teaching Assistant Aashesh Kumar.
