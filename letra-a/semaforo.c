#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){

	int *soma, x=3, y=3, val;
	int idMem, X; /* identificador da memória comum */
	int sem;
	struct sembuf P,V;
	P.sem_num=0;
	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;

	if ((sem = semget(IPC_PRIVATE, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}
	
	//Inicia semáforo com 1 (Último parâmetro)
	if (semctl(sem, 0, SETVAL, 1) == -1) {
		perror("Erro ao inicializar semáforo");
		exit(0);
	}
	
	//Pega e imprime o valor do semáforo
	if ( ( val = semctl(sem, 0, GETVAL, 1)) == -1) {
		perror("Erro ao pegar valor do semáforo");
		exit(0);
	}
	
	printf("\n pai: val= %d\n", val); //valor 1
	idMem = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666);

	if (idMem == -1) {
		perror("Erro no shmget") ;
		exit(0) ;
	}

	// acoplamento do processo a zona de memória
	soma = shmat(idMem, 0, 0);

	*soma = 10;

	printf("\nprimeira *soma = %d\n", *soma); //10

	if (fork()==0){
		semop(sem, &P, 1);
		//Pega e imprime o valor do semáforo
		if ( ( val = semctl(sem, 0, GETVAL, 1)) == -1) {
			perror("Erro ao pegar valor do semáforo");
			exit(0);
		}
		printf("\n f1: val= %d\n", val); //valor 1
		*soma = *soma + x + y;
		printf("\n\nNo filho1: soma = %d", *soma); puts(" "); //26
		semop(sem, &V, 1);
		exit(0);

	}

	if (fork()==0){
		semop(sem, &P, 1);
		//Pega e imprime o valor do semáforo
		if ( ( val = semctl(sem, 0, GETVAL, 1)) == -1) {
			perror("Erro ao pegar valor do semáforo");
			exit(0);
		}
		printf("\n f2: val= %d\n", val); //valor 1
		X = X + 5;
		*soma = *soma + 10;
		printf("\n\nNo filho2: soma = %d", *soma); puts(" "); //36
		semop(sem, &V, 1);
		exit(0);
	}

        wait(0); wait(0);
		//Pega e imprime o valor do semáforo
		if ( ( val = semctl(sem, 0, GETVAL, 1)) == -1) {
			perror("Erro ao pegar valor do semáforo");
			exit(0);
		}
		printf("\n pai: val= %d\n", val); //valor 1
	*soma = *soma + 10;
	printf("\n\nNo pai: soma última = %d", *soma); puts(" "); //20

	//Apaga a área de memória

	shmctl(idMem, IPC_RMID, NULL);
}

