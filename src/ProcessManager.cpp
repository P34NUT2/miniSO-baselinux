#include "ProcessManager.h"
#include "Logger.h"  
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void ProcessManager::createChildProcess(const std::string& program) {
    pid_t pid = fork();

    if (pid == 0) {
        // Proceso hijo
        logEvent("Hijo ejecutando: " + program);
        std::cout << ">> [Hijo] PID: " << getpid() << " creado. Ejecutando " << program << std::endl;
        std::cout << "-------------------------------------\n";
        execlp(program.c_str(), program.c_str(), nullptr);
        std::cerr << ">> [Hijo] Error al ejecutar " << program << std::endl;
        logEvent("Error ejecutando: " + program);
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Proceso padre
        std::cout << ">> [Padre] Creado hijo con PID: " << pid << std::endl;
        logEvent("Padre creó proceso hijo con PID " + std::to_string(pid));
        childPIDs.push_back(pid);
    } else {
        std::cerr << ">> Error: no se pudo crear el proceso hijo" << std::endl;
        logEvent("Error al crear proceso hijo");
    }
}

void ProcessManager::waitForChildren() {
    int status;
    for (pid_t pid : childPIDs) {
        waitpid(pid, &status, 0);
        std::cout << "-------------------------------------\n";
        std::cout << ">> [Padre] Proceso hijo " << pid << " finalizó con estado: " << status << std::endl;
        logEvent("Padre esperó al hijo PID " + std::to_string(pid) + " con estado: " + std::to_string(status));
    }
    childPIDs.clear();
}

void ProcessManager::sendSignalToChild(int signal) {
    if (!childPIDs.empty()) {
        pid_t target = childPIDs.back(); // Tomamos el último hijo
        kill(target, signal);
        std::cout << ">> Señal " << signal << " enviada al proceso " << target << std::endl;
        logEvent("Señal " + std::to_string(signal) + " enviada al proceso hijo PID " + std::to_string(target));
    } else {
        std::cout << ">> No hay procesos hijos activos" << std::endl;
        logEvent("Intento de enviar señal fallido: no hay hijos activos");
    }
}