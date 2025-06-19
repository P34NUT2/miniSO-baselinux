#ifndef PROCESS_H //define clases y evita errores 
#define PROCESS_H
//aca definimos la estructura oh calse de procesos 

#include <string>

class Process {
private:
    int pid;
    std::string name;
    int totalTime;
    int remainingTime;
    int arrivalTime;     // tiempo en que el proceso entra al sistema
    int startTime = -1;  // first time it gets CPU (initially -1 = not started)
    int finishTime = -1; // when it finishes


public:
    //Este de aca es el constructor de la clase y definimos en el cpp
    Process(int pid, const std::string& name, int totalTime);
    
    //estos de aca son metodos basicos 
    void execute(int quantum);
    bool isFinished() const;
    void display() const;
    int getRemainingTime() const;
    std::string getName();

    //metodos que uso para poder scar promedios y tiempo de distancias
    void setArrivalTime(int t);
    void setStartTime(int t);
    void setFinishTime(int t);
    int getResponseTime() const;
    int getWaitingTime() const;
    float getPenalty() const;


};

#endif
