#include <iostream>
#include <string>
#include <sstream>
#include "MercadoDCC.hpp"
#include "Vector.hpp"
#include "ItemQtd.hpp"

int main() {
    // Otimização de I/O recomendada em C++
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string linha;
    MercadoDCC mercado;

    // Processa a entrada linha por linha
    while (std::getline(std::cin, linha)) {
        if (linha.empty()) continue;
        
        std::stringstream ss(linha);
        std::string comando;
        ss >> comando;

        // Comandos de cadastro e movimentação
        if (comando == "U") {
            std::string nome, cidade, estado, nacionalidade;
            int idade;
            ss >> nome >> idade >> cidade >> estado >> nacionalidade;
            mercado.cadastrar_usuario(nome, idade, cidade, estado, nacionalidade);
        } else if (comando == "P") {
            std::string nome, categoria, marca, condicao;
            double preco;
            int qtd_inicial;
            ss >> nome >> preco >> qtd_inicial >> categoria >> marca >> condicao;
            mercado.cadastrar_produto(nome, preco, qtd_inicial, categoria, marca, condicao);
        } else if (comando == "R") {
            int timestamp;
            ss >> timestamp;
            Vector<ItemQtd> itens;
            int id_p, qtd;
            // Lê todos os pares de produtos da linha atual e os insere ordenados por ID
            while (ss >> id_p >> qtd) {
                bool inserido = false;
                for (int i = 0; i < itens.tamanho(); ++i) {
                    if (itens[i].id > id_p) {
                        itens.adicionar({0, 0});
                        for (int j = itens.tamanho() - 1; j > i; --j) {
                            itens[j] = itens[j-1];
                        }
                        itens[i] = {id_p, qtd};
                        inserido = true;
                        break;
                    }
                }
                if (!inserido) itens.adicionar({id_p, qtd});
            }
            mercado.registrar_reposicao(timestamp, itens);
        } else if (comando == "C") {
            int timestamp, id_usuario;
            ss >> timestamp >> id_usuario;
            Vector<ItemQtd> itens;
            int id_p, qtd;
            // Lê todos os pares de produtos comprados e os insere ordenados por ID
            while (ss >> id_p >> qtd) {
                bool inserido = false;
                for (int i = 0; i < itens.tamanho(); ++i) {
                    if (itens[i].id > id_p) {
                        itens.adicionar({0, 0});
                        for (int j = itens.tamanho() - 1; j > i; --j) {
                            itens[j] = itens[j-1];
                        }
                        itens[i] = {id_p, qtd};
                        inserido = true;
                        break;
                    }
                }
                if (!inserido) itens.adicionar({id_p, qtd});
            }
            mercado.registrar_compra(timestamp, id_usuario, itens);
            
        // Comandos de consultas multiatributo
        } else if (comando == "LU" || comando == "LP" || comando == "LC" || comando == "LR") {
            Vector<std::string> tokens;
            std::string token;
            
            // Lê todos os tokens (atributos, valores e operadores booleanos)
            while (ss >> token) {
                tokens.adicionar(token);
            }
            
            if (comando == "LU") mercado.consultar_usuarios(tokens);
            else if (comando == "LP") mercado.consultar_produtos(tokens);
            else if (comando == "LC") mercado.consultar_compras(tokens);
            else if (comando == "LR") mercado.consultar_reposicoes(tokens);
        }
    }
    return 0;
}
