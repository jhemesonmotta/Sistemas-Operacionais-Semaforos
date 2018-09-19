#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	
    int *biscoitos;
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

	for(;;){
        semop(sem1, &P, 1);
            if(*biscoitos == 0){
                // feito nessa estrutura para representar que é este aluno (que foi pegar o biscoito e não achou)
                //que liberou a cozinheira para encher a bandeija de novos biscoitos
                semop(sem2, &V, 1);
            }
            else{
                // representa a retirada de um biscoito da bandeija
                *biscoitos = *biscoitos - 1;
            }
        semop(sem1, &V, 1);
	}
}
