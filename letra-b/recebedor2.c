#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	
	int sem2;
	struct sembuf P,V;
	P.sem_num=0;

	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;

	if ((sem2 = semget(200, 1, 0666)) == -1){
		perror("Erro do semget"); exit(0);
	}


	for(;;){
		semop(sem2, &P, 1);
		puts("Temperatura Alta");	

	}
}
