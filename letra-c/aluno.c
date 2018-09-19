#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	
    int *biscoitos;
	int idMem;
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
	
	//Se liga a uma área de memória compartilhada existente
	if ((idMem = shmget(100, sizeof(int), 0666)) == -1) {
		perror("Erro no shmget") ;
		exit(0) ;
	}
	
	// acoplamento do processo a zona de memória
	biscoitos = (int *)shmat(idMem, 0, 0);

	//printf("%d", *biscoitos);
	
	for(;;){
		if(*biscoitos == 0){
			puts("\nAcabaram os biscoitos");
			semop(sem2, &V, 1);
			sleep(1);
		}
		else{
			semop(sem1, &V, 1);
			// representa a retirada de um biscoito da bandeija
			puts("\nRetirei um biscoito");
			*biscoitos = *biscoitos - 1;
			printf("Biscoitos Restantes: %d\n", *biscoitos);
			//sleep(1);
			semop(sem1, &P, 1);
		}		
		sleep(1);
	}
}
