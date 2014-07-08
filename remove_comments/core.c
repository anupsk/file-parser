#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

//Macros
#define NEWLINE '\n'
#define SLASH '/'
#define STAR '*'

int read_from_file(char* file_read, char* buf){
	int total_bytes = 0;
	int fp = -1;
	int fd_read = open(file_read, O_RDONLY);
	if(-1 == fd_read){
		printf("\nError opening file. errno:%d, strerror:%s\n", errno, strerror(errno));
		return -1;
	}
	while(fp != 0){
		fp = read(fd_read, buf + total_bytes, 1);
		if(fp == -1){
			printf("\nread failed. errno:%d;  strerror:%s", errno, strerror(errno));
			return -1;
		}
		total_bytes++;   //ret=0 at EOF
	}
	return (total_bytes - 1);
}

int write_to_newfile(char* write_path, char *buf, int valid_bytes){
	int nbytes = 0;	
	int fd_write = open(write_path, O_RDWR | O_CREAT, 0666);
	if(-1 == fd_write){
		printf("failed to open new path\n");
		return -1;
	}
	nbytes = write(fd_write, buf, valid_bytes);
	if(nbytes != valid_bytes){
		printf("error during new file write\n");
		return -1;
	}
}


char* create_newpath(char* old_filename){
	char *ret = old_filename;
	int len = strlen(old_filename);
	len = len-2;
	ret[len+0] = '_';
	ret[len+1] = 'r';
	ret[len+2] = 'c';
	ret[len+3] = '.';
	ret[len+4] = 'c';
	ret[len+5] = '\0';
	return ret;	
}
int remove_comments(char *str){
	int store_pos = 0;
	int current_pos = 0;
	int len = strlen(str);
	for(current_pos=0; current_pos<len; current_pos++){
		if(str[current_pos] == SLASH && str[current_pos+1] == STAR){ //checking start of C style comment.
			current_pos += 2;
			while(!(str[current_pos] == STAR && str[current_pos+1] == SLASH)){ //checking end of C style comment.
				current_pos++;
			}
			current_pos += 2;
		}else if(str[current_pos] == SLASH && str[current_pos+1] == SLASH){ //checking start of C++ style comment.
			current_pos += 2;
			while(!((str[current_pos] == NEWLINE) || (str[current_pos] == '\0'))){ //checking end of C style comment.
				current_pos++;
			}
		}
		str[store_pos] = str[current_pos];
		store_pos++;
	}
	str[store_pos] = '\0';
	return (len-strlen(str));
}

