#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    if (argc != 7)
    {
        printf("Erreur : mauvais nombre d'arguments --> %s [arg1] [opt1] [arg2] [opt2] [arg3] [opt3]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Processus courant : je vais exécuter la commande : %s %s | %s %s | %s %s\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);  // Table de descripteurs de fichiers : STDIN // STDOUT // STDERR // fd[0] // fd[1]

    }

  if (fork()) 
  { 
   
    if (fork()) // pid_t val = fork(); if(val)

    {
        // Processus père
        if (fork())
        {
            // Processus père
            close(fd[0]);
            close(fd[1]);
            printf("Père : Je vais attendre la terminaison de mes processus fils\n");
            while (wait(NULL) > 0);
            printf("Père : Je vais quitter l'application\n");
            exit(EXIT_SUCCESS);
        }
      
    // Processus fils 3 (wc -l)
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            execlp(argv[5], argv[5], argv[6], NULL);
            perror("Erreur lors de l'exécution de la commande wc -l");
            exit(EXIT_FAILURE);
            
    
}
   
    
       // Processus fils 2 (tee teefich.txt)
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp(argv[3], argv[3], argv[4], NULL);
        perror("Erreur lors de l'exécution de la commande tee teefich.txt");
        exit(EXIT_FAILURE);
  

 
  
            }
            
          // Processus fils 1 (ps axl)
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execlp(argv[1], argv[1], argv[2], NULL);
    perror("Erreur lors de l'exécution de la commande ps axl");
    exit(EXIT_FAILURE);  
   
     }
