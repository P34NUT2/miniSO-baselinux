#include "Scheduler.h"
#include <iostream>

Scheduler::Scheduler(int quantum) : quantum(quantum) {}//el cosntructor

void Scheduler::addProcess(Process* process) 
{
    processQueue.push(process);//mete el proceso a la cola
}

void Scheduler::run() 
{
    int currentTime = 0;// este seria como el reloj 

    //estos de aca son para sacar el promedio y penalizaciones obvio los iniclizamos por buenas practicas
    int totalResponse = 0;
    int totalWaiting = 0;
    float totalPenalty = 0.0;
    int completed = 0;


    while (!processQueue.empty())
    {
        Process* current = processQueue.front();
        processQueue.pop();
    
        // Guarda tiempo de primera ejecución
        current->setStartTime(currentTime);

        current->display();
    
        int remaining = current->getRemainingTime();
        int execTime = (remaining < quantum) ? remaining : quantum;//para que se le rerste el quntum pero si es uno solo se ejecute esa vez
    
        current->execute(execTime);   // corre el proceso
        currentTime += execTime;      // avanza el tiempo
    
        if (!current->isFinished()) 
        {
            processQueue.push(current);
        } else 
        {
            current->setFinishTime(currentTime);
            std::cout << "\n===============================\n";
            std::cout << "Proceso: " << current->getName() << " Completado :)." <<std::endl;
            //std::cout << "   Proceso Completado :).\n";
            std::cout << "   Tiempo de respuesta: " << current->getResponseTime() << "s\n";
            std::cout << "   Tiempo de espera: " << current->getWaitingTime() << "s\n";
            std::cout << "   Penalizacion: " << current->getPenalty() << "\n";
            std::cout << "===============================\n" << std::endl;

            //para los promedios 
            totalResponse += current->getResponseTime();
            totalWaiting  += current->getWaitingTime();
            totalPenalty  += current->getPenalty();
            completed++;// este de aca marca cuantos procesos se hacen para sacar el promedio

        }
    }
    
    std::cout << "\n========== Promedios ==========\n";
    std::cout << "Promedio de tiempo de respuesta: " << (float)totalResponse / completed << "s\n";
    std::cout << "Promedio de tiempo de espera : " << (float)totalWaiting / completed << "s\n";
    std::cout << "Promedio de penalizacion: " << totalPenalty / completed << "\n" << std::endl;

}
