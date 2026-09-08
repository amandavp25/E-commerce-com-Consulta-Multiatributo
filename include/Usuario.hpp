#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

struct Usuario {
    int id;
    std::string nome;
    int idade;
    std::string cidade;
    std::string estado;
    std::string nacionalidade;

    Usuario();
    Usuario(int id, std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade);
};

#endif
