// By: Yasser JEMLI //--05-05-2023

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if(argc != 2) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}

	printf(" ************* Communication via les pipes anonymes ************* \n");
	printf(" Proc courant : PID = %d et PPID = %d ----- \n", getpid(), getppid());
	printf(" Proc courant : je vais créer un pipe anonyme via l'appel système pipe() \n");
	int fd[2];
	int ret = pipe(fd); // Appel système de création de tube anonyme
	if(ret == -1) {
		perror("TUBE");
		exit(EXIT_FAILURE);
	}

	// Création d'un processus fils
	pid_t val = fork();
	if(val == -1) {
		perror("FORK");
		exit(EXIT_FAILURE);
	}

	if(val == 0) {
		// FILS
		close(fd[0]);
		if(write(fd[1], argv[1], strlen(argv[1])) == -1) {
			perror("wr");
			exit(EXIT_FAILURE);
			}

		printf("\t\t FILS : je viens d'envoyer un message à mon père et je termine dans 5 sec\n");
		sleep(5);
	}
	else {
		// PERE
		printf("PERE : j'attends la terminaison du proc FILS \n");
		wait(NULL);
		close(fd[1]);
		char BUFFER[10];
		int nbOctectLu;
		memset(BUFFER, 0, sizeof(BUFFER)); // Initialisation du tampon avec des zéros
		nbOctectLu = read(fd[0], BUFFER, sizeof(BUFFER) - 1);
		if(nbOctectLu == -1) {
			perror("Rd");
			exit(EXIT_FAILURE);
		}
		BUFFER[nbOctectLu] = '\0';
		printf("Pere : je viens de recevoir le message --> %s \n", BUFFER);
	}

	return 0;
}

