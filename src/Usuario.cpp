#include "Usuario.hpp"

Usuario::Usuario() : id(0), idade(0) {}

Usuario::Usuario(int id, std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade) {
    this->id = id;
    this->nome = nome;
    this->idade = idade;
    this->cidade = cidade;
    this->estado = estado;
    this->nacionalidade = nacionalidade;
}
