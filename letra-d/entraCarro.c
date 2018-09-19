#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	int sem;
	struct sembuf P,V;

	P.sem_num=0;
	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;

	if ((sem = semget(100, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget");
        exit(0);
	}

    puts("O carro %d chegou!", getpid());	
    semop(sem, &P, 1);
    puts("O carro %d estacionou!", getpid());
}