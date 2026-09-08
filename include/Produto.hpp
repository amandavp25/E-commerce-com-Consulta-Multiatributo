#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

struct Produto {
    int id;
    std::string nome;
    double preco;
    int qtd;
    std::string categoria;
    std::string marca;
    std::string condicao;

    Produto();
    Produto(int id, std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao);
};

#endif
