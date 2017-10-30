#include <sys/syscall.h>
#include <stdio.h>

#define sys_log710a2017as1 355

long foncTestAS1 (void){
	return (long) syscall(sys_log710a2017as1);
};

main(){
	printf("Le code de retour du nouvel appel systeme est : %d\n", foncTestAS1());
	return 0;
}

