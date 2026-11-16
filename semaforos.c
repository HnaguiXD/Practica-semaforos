#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo;

void* contar(void* arg) {
    int id_hilo = *(int*)arg;

    for (int i = 1; i <= 10000; i++) {
        if (i == 4000) {
            sem_wait(&semaforo);
            printf("\n>>> [HILO %d] ENTRANDO A SECCIÓN CRÍTICA (4000 - 6000) <<<\n", id_hilo);
        }

        printf("Hilo %d: %d\n", id_hilo, i);

        
        if (i == 6000) {
            printf(">>> [HILO %d] SALIENDO DE SECCIÓN CRÍTICA <<<\n\n", id_hilo);
            sem_post(&semaforo);
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilo1, hilo2;
    int id1 = 1, id2 = 2;

    if (sem_init(&semaforo, 0, 1) != 0) {
        perror("Error al inicializar el semáforo");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&hilo1, NULL, contar, &id1) != 0) {
        perror("Error al crear el hilo 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&hilo2, NULL, contar, &id2) != 0) {
        perror("Error al crear el hilo 2");
        exit(EXIT_FAILURE);
    }

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_destroy(&semaforo);

    printf("Ejecución finalizada correctamente.\n");
    return 0;
}
