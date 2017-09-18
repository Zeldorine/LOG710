#include <stdio.h>

int main(int argc, char **argv)
{
	consumeArgs(argc, argv);
    
    switch(pid=fork()){
        case -1:
            perror("An error occured during fork()");
            break;
        
        case 0 :
            childProcessFct();
            break;
            
        default:
            parentProcessFct();
            break;
    }
    
	return 0;
}

void childProcessFct(){
    
}

void parentProcessFct(){
    
}

char** consumeArgs(int argc, char** argv){
    
}