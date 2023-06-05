#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


// By : Yasser JEMLI //--05-05-2023 

int main ( int argc , char* argv[]) 
{

// Table de descripteurs des fichiers : STDIN // STDOUT //STDERR 
if ( argc != 5) { printf("Erreur : manque d'args --> %s [arg1][opt1] [arg2][opt2] \n" , argv[0]);
exit(EXIT_FAILURE);}

printf ("Proc Courant : je vais donner le resultat %s %s | %s %s \n " , argv[1],argv[2],argv[3],argv[4]);

int fd[2];

if (pipe(fd)==-1){ perror("PIPE"); exit(EXIT_FAILURE);}
//Table  de descripteurs des fichiers : STDIN //STDOUT //STDERR // fd[0] // fd[1]

if ( fork())// pid_t val ; val = fork  ; if val §=0 // 
	{ // PERE 
		if (fork()) 
				{//PERE 
					close(fd[0]);
					close(fd[1]);
					printf (" PERE : je vais attendre la termination de mes proc fils \n");
					while (wait(NULL)>0) ;// PERE : Attend tous les fils 
					printf("PERE : je vais Quitter l'application \n ");
}
//FILS  2
close(fd[1]);
dup2(fd[0], 0); // dup2(fd[0], STDIN-FILENO);
close(fd[0]);

execlp(argv[3],argv[3],argv[4], NULL);
perror("REC");
exit(EXIT_FAILURE);
}
// FILS NUM 1
close(fd[0]);
dup2(fd[1], STDOUT_FILENO); // dup2(fd[1],1);
close(fd[1]);


execlp(argv[1],argv[1],argv[2], NULL);
perror("REC");
exit(EXIT_FAILURE);

return 0 ; 
}
