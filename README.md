file-parser
===========
This project contains source files which parse the .C files.
Parsing involves removing C and C++ style comments from the .C files.

/*
*  This program removes all the C and C++ style comments from the given input C file.
*  New file will be created in the same directory with "_rc" appended to the original file path.
*  Original file path is provided as input to this program.
*  example: ./rc test.c -> In this case all C/C++ comments will be removed from file test.c and new file test_rc.c will be created
*  
*  Limitations/TODO as of now:
*  -only .c files can be provided as input
*  -directory cannot be provided as input
*  -no option to replace existing file
*/
