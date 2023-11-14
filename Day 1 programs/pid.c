#include<stdio.h>
#include<unistd.h>
int main(){
	pid_t process_id=getpid();
	printf("The process ID is: %d\n", process_id);
	return 0;
}
