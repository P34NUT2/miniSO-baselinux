#ifndef AUTH_H
#define AUTH_H

#include <string>

//en  lugar de hacer una clase usamos un struct y con eso es como una mini base de datos
//por que stuct por que es mas simple y no ocupa logica ni metodos dificiles
struct User {
    std::string username;
    std::string passwordHash;
    std::string role;
};

bool CreateUser();
int simpleHash(std::string pass);
bool StartSecion(User &ActualUser);

void ListUsers(); // opcional para debug

#endif
