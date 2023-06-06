#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX 2000

void* Tha()
{
int i ;


for(i=1;i<=MAX; i++)
	printf("A");
printf("TH A : Fin du thread  \n");

pthread_exit(NULL);
}

void* Thc()
{
int i ;


for(i=1;i<=3200; i++)
        printf("C");
printf("TH C : Fin du thread  \n");

pthread_exit(NULL);
}


void* Thb()
{
int i ;

pthread_t tid3;
// int a = 1, b=2;

if(pthread_create(&tid3,NULL, Thc, NULL)==-1)
{perror("THR");exit(EXIT_FAILURE);}



for(i=1;i<=2535; i++)
        printf("B");
pthread_join(tid3,NULL);

printf("TH B : Fin du thread  \n");

pthread_exit(NULL);
}


int main()
{
printf("thread principal : je vais demander à l'os de créer deux threads \n");

pthread_t tid1,tid2;  


if(pthread_create(&tid1,NULL, Tha,NULL )==-1)
{perror("THR");exit(EXIT_FAILURE);}

if(pthread_create(&tid2,NULL, Thb,NULL )==-1)
{perror("THR");exit(EXIT_FAILURE);}

// Bloquer le thread principal en attente de la terminaison des autres threads
printf("Thread Principal : je vais attendre les autres threads du même proc courant \n"); 
pthread_join(tid1,NULL);
pthread_join(tid2, NULL);

printf("Thread Principal : ------------- FIN --------------- \n");

return 0;
}
