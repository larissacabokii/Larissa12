#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        /* Este é o processo filho. */   
        
        printf("O processo filho");

        exit(0);
    } else {
        /* Este é o processo pai. Dorme por um minuto. */
          printf("O processo pai vai dormir");
        sleep(60);
          printf("O processo pai encerrou");
    }
    return 0;
}