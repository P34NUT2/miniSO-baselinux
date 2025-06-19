#include "filesystem.h"
#include "Logger.h"
#include <iostream>

using namespace std;

Node::Node(std::string name, bool isDir, std::string owner, std::string perms, Node* parent)
    : name(name), isDirectory(isDir), owner(owner), permissions(perms), parent(parent), content("") {}

FileSystem::FileSystem() {
    root = new Node("/", true, "root", "rwx");
    current = root;
}

bool FileSystem::exists(const string& name) {
    return find(name) != nullptr;
}

Node* FileSystem::find(const string& name) {
    for (auto child : current->children) {
        if (child->name == name) return child;
    }
    return nullptr;
}

void FileSystem::mkdir(const string& name, const User& user) {
    std::string path = getPath(current);

    if (exists(name)) {
        cout << "Ya existe ese nombre.\n";
        return;
    }
    current->children.push_back(new Node(name, true, user.username, "rwx", current));


    logEvent("El usuario " + user.username + " Ha creado un directorio nuevo con nombre " + name + " ubicado en " + path);
}

void FileSystem::cat(const std::string& name, const User& user) {
    std::string path = getPath(current);

    Node* file = find(name);

    if (!file || file->isDirectory) {
        std::cout << "Archivo no encontrado o es un directorio.\n";
        return;
    }

    if ((file->owner == user.username && file->permissions.find('r') != std::string::npos) ||
        (file->owner != user.username && file->permissions.find('r') != std::string::npos && user.role == "root")) {
        std::cout << file->content << "\n";
        logEvent("El usuario " + user.username + " ha leido el archivo " + name + " ubicado en " + path);
    }
    else {
        std::cout << "Permiso denegado para leer.\n";
        logEvent("El usuario " + user.username + " ha INTENTADO leer el archivo " + name + " ubicado en " + path + " pero NO TIENE PERMISOS");
    }

    
    
}

void FileSystem::echo(const std::string& name, const std::string& text, const User& user) {
    std::string path = getPath(current);
    Node* file = find(name);

    if (!file || file->isDirectory) {
        std::cout << "Archivo no encontrado o es un directorio.\n";
        return;
    }

    if ((file->owner == user.username && file->permissions.find('w') != std::string::npos) ||
        (file->owner != user.username && file->permissions.find('w') != std::string::npos && user.role == "root")) {
        file->content = text;
        std::cout << "Contenido escrito.\n";

        logEvent("El usuario " + user.username + " ha escrito lo siguiente en el archivo " + name + " ubicado en " + path + ": " + text);
    }
    else {
        std::cout << "Permiso denegado para escribir.\n";
        logEvent("El usuario " + user.username + " ha INTENTADO escribir en el archivo " + name + " ubicado en " + path + " pero NO TIENE PERMISOS");
    }
}

void FileSystem::touch(const string& name, const User& user) {
    std::string path = getPath(current);
    if (exists(name)) {
        cout << "Ya existe ese nombre.\n";
        return;
    }
    current->children.push_back(new Node(name, false, user.username, "rw", current));
    logEvent("El usuario " + user.username + " ha creado el archivo de texto " + name + " ubicado en " + path);
}

void FileSystem::ls() {
    for (auto child : current->children) {
        cout << (child->isDirectory ? "[DIR] " : "      ")
             << child->name << " ("
             << child->owner << ", "
             << child->permissions << ")\n";
    }
}

void FileSystem::cd(const string& name) {
    if (name == "..") {
        if (current->parent != nullptr)
            current = current->parent;
    } else {
        Node* dir = find(name);
        if (dir && dir->isDirectory)
            current = dir;
        else
            cout << "Directorio no encontrado.\n";
    }
}

void FileSystem::pwd() {

    printPath(current);
}

void FileSystem::chmod(const std::string& name, const std::string& perms, const User& user) {
    std::string path = getPath(current);
    Node* node = find(name);
    if (!node) {
        cout << "Archivo no encontrado.\n";
        return;
    }

    if (node->owner != user.username && user.role != "root") {
        cout << "Permiso denegado.\n";
        logEvent("El usuario " + user.username + " ha INTENTADO modificar los permisos del archivo " + name + " ubicado en " + path + " pero NO TIENE PERMISOS");
        return;
    }


    logEvent("El usuario " + user.username + " ha modificado los permisos del archivo " + name + " ubicado en " + path + ": " + node->permissions + " > " + perms);
    node->permissions = perms;
    cout << "Permisos cambiados a: " << perms << "\n";
    
}

void FileSystem::printPath(Node* node) {
    if (node == nullptr) return;
    if (node->parent != nullptr) printPath(node->parent);
    if (node->name != "/") cout << "/" << node->name;
    else cout << "/";
}

std::string FileSystem::getPath(Node* node) {
    if (node == nullptr) return "";
    if (node->parent != nullptr) getPath(node->parent);
    if (node->name != "/") {
        return "/" + node->name;
    }
    else{
        return "/";
    }

}