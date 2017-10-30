#include <linux/types.h>
#include <unistd.h>

struct procdata {
	long state;		// Etat du processus
	pid_t pid;		// PID du processus
	pid_t parent_pid;	// PID du processus pere
	uid_t uid;		// ID de l'utilisateur du processus
	char comm[16];		// nom du programme (commande) ayant resulte en 				   ce processus
};
