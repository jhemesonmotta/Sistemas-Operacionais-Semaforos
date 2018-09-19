#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	int idMem;
	shmctl(idMem, IPC_RMID, NULL);
}
