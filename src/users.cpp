#include "users.h"
#include "Logger.h"  
#include <iostream>
#include <fstream>
#include <sstream>

int simpleHash(std::string pass) 
{
    int hash = 0;

    for (size_t i = 0; i < pass.size(); i++) //uso size_t por que segun yo es para lista vectores etc;
    {
        hash += (int)pass[i]; // suma de valores ASCII Osea las hashea conforme a ascii 
        //un algoritmo muy simple y debil pero funciona en una demostracion por ejemplo
        //contra: abc, a=97, b= 98 y c=99 entonces se suman todos estos valores y da 224
    }
    return hash;
}

bool CreateUser() 
{
    std::string username, password, role, aux;
    bool end = true;

    std::cout << R"(
░█▀▀░█▀▄░█▀▀░█▀█░█▀▀░▀█▀░█▀█░█▀█░░░█▀▄░█▀▀░░░█░█░█▀▀░█░█░█▀█░█▀▄░▀█▀░█▀█░█▀▀
░█░░░█▀▄░█▀▀░█▀█░█░░░░█░░█░█░█░█░░░█░█░█▀▀░░░█░█░▀▀█░█░█░█▀█░█▀▄░░█░░█░█░▀▀█
░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀▀░░▀▀▀░░░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀▀▀
    )" <<std::endl;
    std::cout << "Nombre de usuario: ";
    std::cin >> username;

    std::cout << "Contraseña: ";
    while (end == true)
    {
        std::cin >> aux;
        std::cout << "Confirma la Contraseña: ";
        std::cin >> password;

        if (aux == password)
        {
            std::cout << std::endl << "Contraseña establecida para: " << username << std::endl;
            end = false;

        }else
        {
            std::cout << "La Contraseñas no coinciden vuelvelo a intentar" << std::endl;
            std::cout << "Para cancelar oprime 2 si no quieres cancelar oprime cualquier numero: ";
            int input = 0;
            std::cin >> input;

            if (input == 2)
            {
                return false;
            }
            
        }
        
    }
    

    std::cout << "Rol (root/normal): ";
    std::cin >> role;

    // Guardar en CSV //ojo aca en c++ se crea asi el archivo si no existe o se abre en modo escritura 
    std::ofstream file("data/users.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir usuarios.csv\n";
        logEvent("Error critico, nose puede abrir la base de datos para crear usuario");
        return false;
    }

    file << username << "," << simpleHash(password) << "," << role << std::endl;
    file.close();

    std::cout << "Usuario creado con éxito." << std::endl;
    logEvent("El usuario " + username + " creado exitosamente");
    return true;
}


bool StartSecion(User &ActualUser) 
{
    std::string inputUser, inputPass;
    std::cout << R"(
░█░░░█▀█░█▀▀░▀█▀░█▀█
░█░░░█░█░█░█░░█░░█░█
░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀
    )" << std::endl;
    std::cout << "Usuario: ";
    std::cin >> inputUser;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Ingrese la Contraseña " << i +1 << "er intento: "; 
        std::cin >> inputPass;

        std::ifstream file("data/users.csv");
        if (!file.is_open()) 
        {
            std::cerr << "Error: no se pudo abrir usuarios.csv\n";
            logEvent("Error critico, nose puede abrir la base de datos para iniciar secion");
            return false;
        }

        std::string linea;
        while (std::getline(file, linea)) //linea entera en string
        {
            std::stringstream ss(linea);
            std::string username, passHash, role;

            std::getline(ss, username, ',');//con esto le y separa los atos por comas
            std::getline(ss, passHash, ',');
            std::getline(ss, role, ',');

            if (username == inputUser && std::to_string(simpleHash(inputPass)) == passHash) 
            {
                ActualUser.username = username;
                ActualUser.passwordHash = passHash;
                ActualUser.role = role;
                std::cout << "Bienvenido, " << username << " (" << role << ")" << std::endl;
                logEvent("El usuario: " + username + " se logeo correctamente");
                return true;
            }
        }

        std::cout << "Usuario o contraseña incorrectos.\n";
        logEvent("El usuario: " + inputUser + "no existe o no fallo la Contraseña");
        return false;
    }
    return false; //esto solo para que el compilador no ande molestando con warning en return dentro del ciclo
}
