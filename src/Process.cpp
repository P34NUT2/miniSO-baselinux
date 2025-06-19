#include "Process.h"
#include <iostream>
#include <unistd.h> // Esta libreria sirve para poner sleep etc 

//cosntructor de la clase
Process::Process(int pid, const std::string& name, int totalTime)
    : pid(pid), name(name), totalTime(totalTime), remainingTime(totalTime) {}


void Process::execute(int quantum) 
{
    int execTime = (remainingTime < quantum) ? remainingTime : quantum;//preferi dejarlo asi por que es una solucion mas elegante 
    //toma la primera condifcion si es true
    //esto es igual a 
    //int execTime;
    //if (remainingTime < quantum) {
       // execTime = remainingTime;
    //} else {
       // execTime = quantum;
    //}

    std::cout << "Running process " << name << " for " << execTime << " seconds..." << std::endl;
    sleep(execTime);
    remainingTime -= execTime;
}

bool Process::isFinished() const 
{
    return remainingTime <= 0;//aca amigos devuelve true si es menor a 0 osea ya termino el proceso
}

void Process::display() const 
{
    std::cout << "Proceso [" << name << "] PID: " << pid
              << " | Tiempo Restante: " << remainingTime << " Segundos" << std::endl;
}

//metodos mas avanzados para el promedio y eso
int Process::getRemainingTime() const 
{
    return remainingTime;
}
void Process::setArrivalTime(int t) {
    arrivalTime = t;
}

void Process::setStartTime(int t) 
{
    if (startTime == -1) // Only set the first time esto se hace por que ocupamos tener una variable incializada y no moleste despues
        startTime = t;// este if nos evita que el reloj no se guarde cada vez que queira si no sola la priemera vez 
}

void Process::setFinishTime(int t) 
{
    finishTime = t;
}

int Process::getResponseTime() const 
{
    return startTime - arrivalTime;
}

int Process::getWaitingTime() const 
{
    //se resta para saber cuanto tiempo estuvo en el sistema
    int turnaround = finishTime - arrivalTime;//tiempo total que pasó desde que el proceso llegó hasta que terminó
    return turnaround - totalTime;
}

float Process::getPenalty() const 
{
    int turnaround = finishTime - arrivalTime;//una vez mas usamos el tiempo en el sistema o que uso la cpu
    return (float)turnaround / totalTime;
}

std::string Process::getName()
{
    return name;
}
