#include <sys/syscall.h>


long syscall(long number, ...);


void _start(){
	char str[4000];
	int flag = syscall(SYS_read, 0, str, 4000);
	while (flag > 0){
		syscall(SYS_write, 1, str, flag);
		flag = syscall(SYS_read, 0, str, flag);
	}
	syscall(SYS_exit);
}
