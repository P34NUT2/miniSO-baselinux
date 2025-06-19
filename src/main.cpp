#include "utils.h"//funciones generales oh animaciones como la ruedecita
#include "Scheduler.h"
#include "Process.h"
#include "users.h"
#include "Logger.h"
#include "ProcessManager.h"
#include "filesystem.h"

//bibliotecas
#include <iostream>
#include <signal.h>//para los prcesos 

//////DECLARACION DE FUNCIONES///////
void showHelp();
void tryProcess();
void clearScreen();
User UserDefault();//funcion para que se logue por defecto y obvio pasa una structure
void RealProcess();
void ShowAuthors();


int main() {
    User ActualUser = UserDefault();//creo una struct useranme para que se logue como default y pueda moverse en el SO obvio con restricciones
    FileSystem fs;

    std::string input;

    bool OpenFirstTime = true;
    //OJO la razon por la que la hago en if else es por que no jala en forma de string y comandos en switch recordemos que el string es un arreglo
    while (true) {

        if (OpenFirstTime == true || input == "help") 
        {
            showHelp();//aca solo se va abrir si es la primera vez si abre el SO o si ponen el input
        }
        
        if (ActualUser.role == "root") {
            std::cout << ActualUser.username << "@UPSYSTEM ~";
            fs.pwd();  // imprime ruta actual
            std::cout << "#";
        }
        else {
            std::cout << ActualUser.username << "@UPSYSTEM ~";
            fs.pwd();  // imprime ruta actual
            std::cout << "$";
        }
        //std::cout << ActualUser.username <<"@UPSYSTEM ~>>";
        //std::getline(std::cin, input);  // lee strings con espacios
        std::cin >> input;

        if (input == "cpu") 
        {   
            std::cout << R"(
░█▀▀░█▀█░█░█
░█░░░█▀▀░█░█
░▀▀▀░▀░░░▀▀▀
            )" << std::endl;
            loadingAnimation("Un momento ", 20, 60);
            std::cout << std::endl;
            tryProcess();
        }
        //solo es de prueba se cambiara a futuro
       else if (input == "2") 
        {
            std::cout << std::endl << "  limpiar pantalla: clear"<< std::endl;
            std::cout << "  Apagar equipo: poweroff"<< std::endl << std::endl;
        }
        //para los proceesos reales no simulados de la CPU
        else if (input == "process") 
        {
            RealProcess();
        }
        //apagar equipo oh salir del programa
        else if (input == "poweroff" || input == "p") 
        {
            loadingAnimation("Apagando el equipo", 20, 60);
            std::cout << "Hasta luego :) " << std::endl;
            break;
        }
        //para limpiar la terminal
        else if (input == "clear") 
        {
            clearScreen();
        }
        ///este solo es para simular los enter y que no ponga comando error 
        //else if (input == "") 
        //{
            //std::cout << "";
        //}
        else if (input == "9") 
        {
            std::cout << std::endl << "  modulo de desarrollador para probar cosas"<< std::endl << std::endl;
            std::cout << "Starting simulation...\n";
            loadingAnimation("probando", 20, 100);  // nombre, ciclos, velocidad
        }
        //funcion para ver quein esta logueado
        else if (input == "whoami") 
        {
            if (ActualUser.username == "default")
            {
                std::cout << "Aun no estas logueado, estas como default con permisos reducido" << std::endl;
            }else
            {
                std::cout << "Estas logueado con el usuario: " << ActualUser.username << std::endl;
            }
            
        }
        //para agregar usuarios esto va al csv
        else if (input == "useradd" || input == "adduser") 
        {
            CreateUser();
        }
        //para iniciar sesion 
        else if (input == "login") 
        {
            if (StartSecion(ActualUser)) //recordemos amigos que esta funcion devuelve un bool true oh false
            {
                loadingAnimation("Entrando al usuario actual", 20, 60);  // nombre, ciclos, velocidad
            }else
            {
                //para no cometer bugs ponemos el usuario en default de nuevo por que no se pudo inicair secion
                ActualUser = UserDefault();
            }
            
        }
        //para salir de la sesion y te pone en default
        else if (input == "logout") 
        {
            std::cout << "Saliendo de : " << ActualUser.username << " Adios amigo :)" <<std::endl;
            loadingAnimation("Saliendo", 20, 100);  // nombre, ciclos, velocidad
            logEvent("El usuario: " + ActualUser.username + "Cerro secion correctamente" );
            ActualUser = UserDefault();
        }
        //muestra los creditos
        else if (input == "authors" || input == "auth") 
        {
            ShowAuthors();
        }
        else if (input == "easteregg" || input == "msf" || input == "EasterEgg") 
        {
            clearScreen();
            showEasterEgg();
        }
        else if (input == "mkdir") {
            std::string name;
            std::cin >> name;
            fs.mkdir(name, ActualUser);
        }
        else if (input == "touch") {
            std::string name;
            std::cin >> name;
            fs.touch(name, ActualUser);
        }
        else if (input == "ls") {
            fs.ls();
        }
        else if (input == "cd") {
            std::string name;
            std::cin >> name;
            fs.cd(name);
        }
        else if (input == "pwd") {
            fs.pwd();
        }
        else if (input == "chmod") {
            std::string name, perms;
            std::cin >> name >> perms;
            fs.chmod(name, perms, ActualUser);
        }
        else if (input == "cat") {
            std::string name;
            std::cin >> name;
            fs.cat(name, ActualUser);
        }
        else if (input == "echo") {
            std::string name;
            std::cin >> name;
            std::cin.ignore(); // limpiar salto de línea pendiente
            std::string text;
            std::cout << "Texto a escribir: ";
            std::getline(std::cin, text);
            fs.echo(name, text, ActualUser);
        }
        else 
        {
            std::cout << "Comando desconocido intente de nuevo." << std::endl;
        }

        OpenFirstTime = false;
    }

    return 0;
}


/////////////////////////FUNCIONES//////////////////////////////
void showHelp() 
{
    std::cout << R"(
██╗   ██╗██████╗      ██████╗ ██████╗ ███████╗██████╗  █████╗ ████████╗██╗ ██████╗ ███╗   ██╗    
██║   ██║██╔══██╗    ██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║    
██║   ██║██████╔╝    ██║   ██║██████╔╝█████╗  ██████╔╝███████║   ██║   ██║██║   ██║██╔██╗ ██║    
██║   ██║██╔═══╝     ██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗██╔══██║   ██║   ██║██║   ██║██║╚██╗██║    
╚██████╔╝██║         ╚██████╔╝██║     ███████╗██║  ██║██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║    
 ╚═════╝ ╚═╝          ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝    
                                                                                                 
███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗                                            
██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║                                            
███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║                                            
╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║                                            
███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║                                            
╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝                                                                                                                            
    )" << std::endl;                                       
                                                                                                 
    std::cout << R"(
    Este sistema simula un entorno básico inspirado en un sistema operativo Linux.
    Contiene módulos funcionales para:
    - Gestión de procesos (simulada y real con fork/exec/wait),
    - Planificación de CPU (con FIFO y Round Robin),
    - Sistema de archivos (simulado con permisos y estructura jerárquica),
    - Control de acceso por usuarios (login/logout y privilegios),
    - Entrada y salida simuladas (logs e impresora virtual).

    Por esta razón, se imitan comandos comunes como `clear`, `poweroff`, `useradd`, etc.

    >> Comandos disponibles:

        cpu         → Ejecuta el simulador de planificación Round Robin y muestra métricas.
        process     → Ejecuta gestión real de procesos con fork(), exec() y señales.
        login       → Inicia sesión con un usuario registrado en el sistema.
        logout      → Cierra la sesión actual y vuelve al usuario por defecto.
        useradd     → Crea un nuevo usuario y lo guarda en el archivo de usuarios.
        whoami      → Muestra el nombre del usuario actualmente logueado.
        clear       → Limpia la pantalla de la consola.
        poweroff    → Apaga el sistema (termina el programa).
        help        → Muestra este menú de ayuda.
        authors     → Muestra los nombres de los creadores del proyecto.

    >> Comandos de sistema de archivos(OJO para usar los coamandos pones mkdir por ejemplo enter y lo demas):

        mkdir <dir>         → Crea una carpeta en el directorio actual.
        touch <archivo>     → Crea un archivo nuevo.
        ls                  → Lista archivos y carpetas del directorio actual.
        cd <ruta>           → Cambia de directorio.
        pwd                 → Muestra la ruta actual.
        chmod <archivo> <permisos> → Cambia los permisos de un archivo (ej: rwx).
        cat <archivo>       → Muestra el contenido de un archivo.
        echo <archivo>      → Escribe texto dentro de un archivo (si tienes permisos).

    *NOTA:* Este menú aparece automáticamente al iniciar por primera vez o al usar el comando `help`.

)" << std::endl;

    
    
}

void tryProcess()
{
    //ojo medidas en segundos
    Scheduler rrScheduler(2); // quantum = 2 

    //el proces id es un id y supongamos que un tiempo de llegada o activacion
    Process* p1 = new Process(1, "P1", 4);//para crearlos va el orden ID, string(identificador), tiempo de ejecucion
    p1->setArrivalTime(0);

    Process* p2 = new Process(2, "P2", 5);
    p2->setArrivalTime(1);

    Process* p3 = new Process(3, "P3", 4);
    p3->setArrivalTime(2);

    Process* p4 = new Process(4, "P4", 3);
    p4->setArrivalTime(3);

    Process* p5 = new Process(5, "P4", 2);
    p5->setArrivalTime(4);

    rrScheduler.addProcess(p1);
    rrScheduler.addProcess(p2);
    rrScheduler.addProcess(p3);
    rrScheduler.addProcess(p4);
    rrScheduler.addProcess(p5);

    rrScheduler.run();
}

void clearScreen() 
{
    std::cout << "\033[2J\033[H"; // Limpia terminal ANSI
}

//logica para el login default 
User UserDefault() 
{
    User STRUCT;
    STRUCT.username = "default";
    STRUCT.passwordHash = "0000"; // valor simbólico, no se usa para login
    STRUCT.role = "normal";       // restringido

    return STRUCT;
}

void RealProcess()
{
    ProcessManager pm;
    std::string choice;
    bool openFirstTime = true;

    while (true) {
        
        if (openFirstTime)
        {
            std::cout << R"(
░█▀▀░█▀▀░█▀▀░▀█▀░▀█▀░█▀█░█▀█░░░█▀▄░█▀▀░░░█▀█░█▀▄░█▀█░█▀▀░█▀▀░█▀▀░█▀█░█▀▀░░░█▀▄░█▀▀░█▀█░█░░░█▀▀░█▀▀
░█░█░█▀▀░▀▀█░░█░░░█░░█░█░█░█░░░█░█░█▀▀░░░█▀▀░█▀▄░█░█░█░░░█▀▀░▀▀█░█░█░▀▀█░░░█▀▄░█▀▀░█▀█░█░░░█▀▀░▀▀█
░▀▀▀░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░░░▀▀░░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░░░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀
                        )" << std::endl;
        }
        
        openFirstTime = false;

        std::cout << std::endl << "1. Crear proceso hijo\n";
        std::cout << "2. Pausar (SIGSTOP)\n";
        std::cout << "3. Reanudar (SIGCONT)\n";
        std::cout << "4. Terminar (SIGKILL)\n";
        std::cout << "5. Esperar hijos\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << ">> ";
        std::getline(std::cin, choice);

        // Validar que solo entre si es un dígito
        if (choice.length() != 1 || !isdigit(choice[0])) {
            std::cout << "Opción inválida\n";
            continue;
        }

        int option = std::stoi(choice);

        switch (option) {
            case 1: {
                std::string programa;
                std::cout << "\n----------------------------------\n";
                std::cout << "Ingrese el nombre del programa a ejecutar (ej. ls): ";
                std::getline(std::cin, programa);
                std::cout << ">> Ejecutando: " << programa << "\n";
                std::cout << "----------------------------------\n\n";
                pm.createChildProcess(programa);
                std::cout << "\n----------------------------------\n";
                std::cout << ">> Proceso finalizado o en ejecución.\n";
                std::cout << "----------------------------------\n\n";
                break;
            }
            case 2:
                pm.sendSignalToChild(SIGSTOP);
                break;
            case 3:
                pm.sendSignalToChild(SIGCONT);
                break;
            case 4:
                pm.sendSignalToChild(SIGKILL);
                break;
            case 5:
                pm.waitForChildren();
                break;
            case 0:
                return;  // salir de la función
            default:
                std::cout << "Opción inválida\n";
                break;
        }
    }
}

void ShowAuthors()
{
    std::cout << R"(
                                             
   (               )    )                
   )\       (   ( /( ( /(       (        
((((_)(    ))\  )\()))\())  (   )(   (   
 )\ _ )\  /((_)(_))/((_)\   )\ (()\  )\  
 (_)_\(_)(_))( | |_ | |(_) ((_) ((_)((_) 
  / _ \  | || ||  _|| ' \ / _ \| '_|(_-< 
 /_/ \_\  \_,_| \__||_||_|\___/|_|  /__/ 
                                         

                 _              _   __      __    
     /\         | |            (_)  \ \    / /    
    /  \   _ __ | |_ ___  _ __  _  __\ \  / /     
   / /\ \ | '_ \| __/ _ \| '_ \| |/ _ \ \/ /      
  / ____ \| | | | || (_) | | | | | (_) \  /       
 /_/____\_\_| |_|\__\___/|_| |_|_|\___(_)/  _____ 
 |  ____|         (_) (_)                  / ____|
 | |__   _ __ ___  _| |_  __ _ _ __   ___ | |  __ 
 |  __| | '_ ` _ \| | | |/ _` | '_ \ / _ \| | |_ |
 | |____| | | | | | | | | (_| | | | | (_) | |__| |
 |______|_| |_| |_|_|_|_|\__,_|_| |_|\___(_)_____|
  _____      _     _        _____                 
 |  __ \    | |   | |      / ____|                
 | |__) |_ _| |__ | | ___ | |                     
 |  ___/ _` | '_ \| |/ _ \| |                     
 | |  | (_| | |_) | | (_) | |____                 
 |_|   \__,_|_.__/|_|\___(_)_____|                
                                                  
                                                  


    )"<< std::endl;
}