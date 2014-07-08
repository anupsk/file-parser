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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include "./core.h"

int process_regular_file(char* reg_file, char** newfile){
	struct stat file_stat;
	stat(reg_file, &file_stat);
	char *str = (char*)malloc((long long)file_stat.st_size);
	if(str == NULL){
		printf("memory allocation fail!\n");
		return -1;
	}
	int total_bytes   = read_from_file(reg_file, str);
	if(-1 == total_bytes)
		return -1;

	int invalid_bytes = remove_comments(str);
	*newfile  	 = create_newpath(reg_file);
	int valid_bytes   = write_to_newfile(*newfile, str, (total_bytes-invalid_bytes));
	if(-1 == valid_bytes)
		return -1;
	return 0;
}


int main(int argc, char** argv){
	if(argc != 2){
		printf("\nwrong usage!!");
		printf("\nUSAGE: rc <valid path>");
		exit(1);
	}
	struct stat file_stat;	
	if(-1 == stat(argv[1], &file_stat)) {
		printf("Failed to get file stats. errno:%d, strerror:%s\n", errno, strerror(errno));	
		exit(1);
	}
	if(S_ISDIR(file_stat.st_mode)){
		printf("\ninput parameter: directory");
		exit(1);
		//TODO : process all .c files in this given directory.
	}else
		if(S_ISREG(file_stat.st_mode)){
			printf("\ninput parameter: regular file");
			char* newfile;
			if(-1 == process_regular_file((argv[1]), &newfile)){
				printf("\nFAILED to generate new file");
				exit(1);
			}
		printf("\nnew file generated: %s", newfile);
	}
	printf("\n---Done. \n");
	return 0;
}

