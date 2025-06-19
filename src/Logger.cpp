#include "Logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>

void logEvent(const std::string& message) {
    std::ofstream log("logs/system.csv", std::ios::app); // ← CSV ahora

    if (log.is_open()) {
        std::time_t now = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&now);

        // Formato CSV: fecha,hora,mensaje
        log << std::put_time(timeinfo, "%Y-%m-%d") << ","
            << std::put_time(timeinfo, "%H:%M:%S") << ","
            << "\"" << message << "\"" << std::endl;

        log.close();
    }
}