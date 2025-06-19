#ifndef SCHEDULER_H
#define SCHEDULER_H
//aca es mas inportante creamos la clase o la unica clase de adeministrador esto se va encargar de mover los procesos 

#include <queue>//libreria para simular una cola FIFO se puede hacer con 
//vector pero este es mas natural
#include "Process.h"

class Scheduler {
private:
    std::queue<Process*> processQueue;//aca usamos la libreria para hacer una cola
    //ojo pasmos el objeto real osea con un pointer para trabajr con el objeto real, diferente a &(referencia)
    int quantum;

public:
    //Este de aca es el constructor de la clase  y lo definimos oh pasmos el parametro en el cpp
    Scheduler(int quantum);
    void addProcess(Process* process);
    void run();
};

#endif
