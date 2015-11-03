#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#define SYSCALL 325

int main(void){
	char *buf [20];
	memcpy(buf, "Wha gwan", strlen("Wha gwan") + 1);
	syscall(SYSCALL, buf, 10);
	printf("kernel said %s\n", buf);
	return 0;
}
