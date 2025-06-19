============================================================
        Simulador de Sistema Operativo - Proyecto Final
============================================================

Autores: Antonio Villafaña, Emiliano Garcia y Pablo Eugenio Chavez
Materia: Sistemas Operativos  
Fecha: Mayo 2025  
Compilador: g++  
Sistema: Linux (recomendado Arch Linux, Ubuntu, Debian, etc.)

------------------------------------------------------------
1. DESCRIPCIÓN GENERAL
------------------------------------------------------------
Este proyecto simula un sistema operativo, incluyendo sus principales componentes como:

- Gestión de usuarios con login y permisos
- Gestión y planificación de procesos (con fork(), exec(), wait())
- Planificador FIFO y Round Robin
- Simulación de consola y comandos básicos
- Simulación de archivos con control de acceso (permisos)
- Entrada/salida simulada
- Registro de eventos en log (CSV)
- Interfaz estilo terminal con menú en español

Todos los componentes están integrados en un solo programa funcional y ejecutable desde consola.

------------------------------------------------------------
2. ESTRUCTURA DE ARCHIVOS
------------------------------------------------------------
El proyecto está organizado en archivos separados por módulos:

- main.cpp → Entrada principal y menú del sistema
- users.h/.cpp → Gestión de usuarios y autenticación
- Process.h/.cpp → Estructura de procesos
- Scheduler.h/.cpp → Planificación FIFO y Round Robin
- ProcessManager.h/.cpp → fork, exec, wait y señales
- utils.h/.cpp → Utilidades generales (carga, animaciones, consola)
- Logger.h/.cpp → Registro de logs en CSV
- Filesystem.h/.cpp → Sistema de archivos de usuarios
- logs/system.csv → Archivo generado con eventos del sistema

------------------------------------------------------------
3. REQUISITOS
------------------------------------------------------------
- Linux con compilador g++ instalado
- Terminal con permisos de ejecución
- Makefile (opcional) o compilación manual

------------------------------------------------------------
4. INSTRUCCIONES DE COMPILACIÓN
------------------------------------------------------------

Opción 1: Compilar todos los archivos con g++
------------------------------------------------------------
g++ -o so_sim main.cpp Process.cpp Scheduler.cpp users.cpp utils.cpp ProcessManager.cpp Logger.cpp

Opción 2: Usar Makefile (si está incluido)
------------------------------------------------------------
make

Esto genera un ejecutable llamado `so_sim`.

------------------------------------------------------------
5. INSTRUCCIONES DE EJECUCIÓN
------------------------------------------------------------
./so_sim

Al ejecutar, se mostrará el sistema con el menú de comandos disponibles.
Puedes iniciar sesión como 'root' u otros usuarios, crear procesos, ver planificación, y más.

------------------------------------------------------------
6. LOG DE EVENTOS
------------------------------------------------------------
Todos los eventos importantes (creación de procesos, accesos denegados, lecturas/escrituras)
se registran automáticamente en logs/system.csv.

------------------------------------------------------------
7. USUARIOS Y PERMISOS
------------------------------------------------------------
- Cada archivo simulado tiene un dueño y permisos.
- El usuario root tiene control total.
- Otros usuarios están limitados por sus permisos (lectura, escritura, ejecución).
- Se simula login con autenticación de usuario antes de acceder al sistema.
