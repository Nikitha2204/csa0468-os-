#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	char name1[]="file1.txt";
	char name2[]="file2.txt";
	int source, dest;
	ssize_t bytesRead;
	char buffer[1024];
	source=open(name1, O_RDONLY);
	if(source==-1){
		perror("Erorr opening the file");
		exit(1);
	}
	dest=open(name2, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(dest==-1){
		perror("Error opening dest file");
		close(source);
		exit(1);
	}
	while((bytesRead=read(source,buffer,sizeof(buffer)))>0){
		if(write(dest,buffer,bytesRead)!=bytesRead){
			perror("Error writing to dest file");
			close(source);
			close(dest);
			exit(1);
		}
	}
	if(bytesRead==-1){
		perror("Error reading from source");
		close(source);
		close(dest);
		exit(1);
	}
	close(source);
	close(dest);
	printf("File copied successfully");
	return 0;
}
