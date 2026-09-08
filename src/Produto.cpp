#include "Produto.hpp"

Produto::Produto() : id(0), preco(0.0), qtd(0) {}

Produto::Produto(int id, std::string nome, double preco, int qtd, std::string categoria, std::string marca, std::string condicao) {
    this->id = id;
    this->nome = nome;
    this->preco = preco;
    this->qtd = qtd;
    this->categoria = categoria;
    this->marca = marca;
    this->condicao = condicao;
}
