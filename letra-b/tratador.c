#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){

	int temp, val;
	int sem1, sem2;
	struct sembuf P,V;
	P.sem_num=0;
	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;

	if ((sem1 = semget(100, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}

	if ((sem2 = semget(200, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}
	
	
	//Inicia semáforo com 1 (Último parâmetro)
	if (semctl(sem1, 0, SETVAL, 0) == -1) {
		perror("Erro ao inicializar semáforo");
		exit(0);
	}

	if (semctl(sem2, 0, SETVAL, 0) == -1) {
		perror("Erro ao inicializar semáforo");
		exit(0);
	}
	
	//Pega e imprime o valor do semáforo
	if ( ( val = semctl(sem1, 0, GETVAL, 1)) == -1) {
		perror("Erro ao pegar valor do semáforo");
		exit(0);
	}

	if ( ( val = semctl(sem2, 0, GETVAL, 1)) == -1) {
		perror("Erro ao pegar valor do semáforo");
		exit(0);
	}
	
	

	for(;;){
		printf("\nDigite o valor da temperatura:");
		scanf("%d", &temp);
		if (temp < 25){
			semop(sem1, &V, 1);
		}
		else{
			semop(sem2, &V, 1);
		}
	}

	

}
