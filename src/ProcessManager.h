#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <vector>
#include <string>

class ProcessManager {
public:
    void createChildProcess(const std::string& program);
    void sendSignalToChild(int signal);
    void waitForChildren();

private:
    std::vector<pid_t> childPIDs;
};

#endif
