import time

MAX_PROCESSES = 10000

def factorial(num):
    temp = 1
    while num > 0:
        temp *= num
        num -= 1
    return temp

# Estructura de un proceso
class Process:
    def __init__(self, id, fact):
        self.id = id
        self.fact = fact

# Cola de prioridad de procesos
class PriorityQueue:
    def __init__(self):
        self.queue = [None] * MAX_PROCESSES
        self.size = 0

    # Verificar si la cola de prioridad está vacía
    def is_empty(self):
        return self.size == 0

    # Añadir un proceso a la cola de prioridad
    def enqueue(self, process):
        if self.size == MAX_PROCESSES:
            print("La cola de prioridad está llena")
            exit()

        i = self.size
        while i > 0 and self.queue[(i - 1) // 2].fact < process.fact:
            self.queue[i] = self.queue[(i - 1) // 2]
            i = (i - 1) // 2
        self.queue[i] = process
        self.size += 1


    # Eliminar un proceso de la cola de prioridad
    def dequeue(self):
        if self.is_empty():
            print("La cola de prioridad está vacía")
            exit()

        max_process = self.queue[0]
        last_process = self.queue[self.size - 1]
        self.size -= 1

        i = 0
        child = 0
        while 2 * i + 1 < self.size:
            child = 2 * i + 1
            if child != self.size - 1 and self.queue[child + 1].fact > self.queue[child].fact:
                child += 1
            if last_process.fact >= self.queue[child].fact:
                break
            self.queue[i] = self.queue[child]
            i = child
        self.queue[i] = last_process

        return max_process


# Registrar el tiempo de inicio de la ejecución del programa
print("Prueba en python")
start_time_total = time.time()
# Inicializar la cola de prioridad
pq = PriorityQueue()

processes = []  # Inicializa la lista vacía

for i in range(MAX_PROCESSES):
    processes.append(Process(i + 1, 500))


# Añadir los procesos a la cola de prioridad
for Process in processes:
    pq.enqueue(Process)

# Simular la ejecución de procesos
print("Ejecutando procesos de la cola de prioridad:")
while not pq.is_empty():
    current_process = pq.dequeue()
    print(f"Proceso {current_process.id} en ejecución")
    # Aquí iría la lógica para ejecutar el proceso
    res = factorial(current_process.fact)
    print("Factorial de: ", current_process.fact, " = ", res)

total_execution_time = time.time() - start_time_total
print("Tiempo total de ejecucion: ", total_execution_time)
