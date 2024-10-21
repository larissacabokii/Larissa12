#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    /* Alocar o segmento de memória compartilhada */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    // Acoplar o segmento de memória compartilhada
    shared_memory = (char*) shmat(segment_id, NULL, 0);

    int pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // Processo filho
        // Esperar o pai escrever
        // (Neste exemplo simples, o filho apenas espera o pai terminar)
        wait(NULL);

        // Ler a string da memória compartilhada e imprimir
        printf("Filho leu: %s\n", shared_memory);
    } else { // Processo pai
        // Escrever uma string na memória compartilhada
        sprintf(shared_memory, "Olá do pai!");

        // Esperar o filho terminar antes de liberar a memória
        wait(NULL);
    }

    // Desacoplar e desalocar a memória compartilhada
    shmdt(shared_memory);
    shmctl(segment_id, IPC_RMID, 0);

    return 0;  
}