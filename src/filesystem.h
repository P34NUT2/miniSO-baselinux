#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include "users.h"

struct Node {
    std::string name;
    bool isDirectory;
    Node* parent;
    std::vector<Node*> children;

    // contenido en caso de no ser directorio
    std::string content;


    std::string owner;
    std::string permissions; // "rw", "rwx", etc.

    Node(std::string name, bool isDir, std::string owner, std::string perms, Node* parent = nullptr);
};

class FileSystem {
private:
    Node* root;
    Node* current;

    void printPath(Node* node);
    bool exists(const std::string& name);
    Node* find(const std::string& name);

   

public:
    FileSystem();

    std::string getPath(Node*);

    void mkdir(const std::string& name, const User& user);

    void touch(const std::string& name, const User& user);
    void cat(const std::string& name, const User& user);   // leer archivo
    void echo(const std::string& name, const std::string& text, const User& user);  // escribir en archivo

    void ls();
    void cd(const std::string& name);
    void pwd();

    void chmod(const std::string& name, const std::string& perms, const User& user);
};

#endif