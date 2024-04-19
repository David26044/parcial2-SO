#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10000

long double factorial(int num) {
    long double temp = 1;
    while (num > 0) {
        temp *= num;
        num--;
    }
    return temp;
}

// Estructura de un proceso
typedef struct {
    int id;
    int fact;
} Process;

// Cola de prioridad de procesos
typedef struct {
    Process *queue[MAX_PROCESSES];
    int size;
} PriorityQueue;

// Inicializar una cola de prioridad
void initializePriorityQueue(PriorityQueue *pq) {
    pq->size = 0;
}

// Verificar si la cola de prioridad está vacía
int isPriorityQueueEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Añadir un proceso a la cola de prioridad
void enqueue(PriorityQueue *pq, Process *process) {
    if (pq->size == MAX_PROCESSES) {
        printf("La cola de prioridad está llena\n");
        exit(EXIT_FAILURE);
    }

    int i = pq->size;
    while (i > 0 && pq->queue[(i - 1) / 2]->fact < process->fact) {
        pq->queue[i] = pq->queue[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->queue[i] = process;
    pq->size++;
}

// Eliminar un proceso de la cola de prioridad
Process *dequeue(PriorityQueue *pq) {
    if (isPriorityQueueEmpty(pq)) {
        printf("La cola de prioridad está vacía\n");
        exit(EXIT_FAILURE);
    }

    Process *maxProcess = pq->queue[0];
    Process *lastProcess = pq->queue[pq->size - 1];
    pq->size--;

    int i = 0;
    int child;
    while (2 * i + 1 < pq->size) {
        child = 2 * i + 1;
        if (child != pq->size - 1 && pq->queue[child + 1]->fact > pq->queue[child]->fact) {
            child++;
        }
        if (lastProcess->fact >= pq->queue[child]->fact) {
            break;
        }
        pq->queue[i] = pq->queue[child];
        i = child;
    }
    pq->queue[i] = lastProcess;

    return maxProcess;
}

// Función principal
int main() {
    printf("Prueba en C \n");
    clock_t ini, fin;
    double tiempo;

    ini = clock();
    // Inicializar la cola de prioridad
    PriorityQueue pq;
    initializePriorityQueue(&pq);
    
    Process* processes[MAX_PROCESSES];

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        Process *temp = malloc(sizeof(Process));
        temp->id = i;
        temp->fact = 500;
        processes[i] = temp;
    }

    // Añadir los procesos a la cola de prioridad
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        enqueue(&pq, processes[i]);
    }
    

    // Simular la ejecución de procesos
    printf("Ejecutando procesos de la cola de prioridad:\n");
    long double res;
    while (!isPriorityQueueEmpty(&pq)) {
        Process *current_process = dequeue(&pq);
        printf("Proceso %d en ejecución\n", current_process->id);
        // Aquí iría la lógica para ejecutar el proceso
        res = factorial(current_process->fact);
        printf("Factorial de: %d = %.0Lf\n", current_process->fact, res);
    }

    // Liberar memoria
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        free(processes[i]);
    }
    fin = clock();
    tiempo = (double)(fin - ini) / CLOCKS_PER_SEC;
    printf("El programa tardó %.4f segundos en ejecutarse\n", tiempo);

    return 0;
}
