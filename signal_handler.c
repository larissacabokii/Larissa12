#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigterm(int sig) {
    printf("SIGTERM recebido: %d\n", sig);
    exit(0);
}

int main() {
    signal(SIGTERM, handle_sigterm);
    while (1) {
        printf("Trabalhando...\n");
        sleep(1);
    }
    return 0;
}