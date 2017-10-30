#include <sys/syscall.h>
#include <stdio.h>
#include "./procdata.h"

#define sys_log710a2017as2 356

char* getStringState(const long state){
	if(state < 0){
		return "unrunnable";
	} else if (state == 0){
		return "runnable";
	} else {
		return "stopped";
	}
}

long foncTestAS2 (void){
	struct procdata pudata;
	long returnCode = (long) syscall(sys_log710a2017as2, &pudata);	
	
	printf("STATE      : %s \n", getStringState(pudata.state));
	printf("PID        : %d \n", pudata.pid);
	printf("PARENT PID : %d \n", pudata.parent_pid);
	printf("UID        : %d \n", pudata.uid);
	printf("COMMANDE   : %s \n", pudata.comm);

	return returnCode;
};

main(){
	printf("Le code de retour du nouvel appel systeme est : %li\n", foncTestAS2());
	return 0;
}

