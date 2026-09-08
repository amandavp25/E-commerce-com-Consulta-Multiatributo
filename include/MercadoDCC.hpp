#ifndef MERCADO_DCC_HPP
#define MERCADO_DCC_HPP

#include "Usuario.hpp"
#include "Produto.hpp"
#include "Compra.hpp"
#include "Reposicao.hpp"
#include "Vector.hpp"
#include "StringIntVectorMap.hpp"
#include "IntIntVectorMap.hpp"
#include "ItemQtd.hpp"

// Classe principal que gerencia o estado e as regras de negócio do sistema
class MercadoDCC {
private:
    // Vetores para armazenar as entidades sequencialmente por ID
    Vector<Usuario> usuarios;
    Vector<Produto> produtos;
    Vector<Compra> compras;
    Vector<Reposicao> reposicoes;

    // Índices invertidos de buscas de Usuário
    StringIntVectorMap indice_usuario_nome;
    IntIntVectorMap    indice_usuario_idade;
    StringIntVectorMap indice_usuario_cidade;
    StringIntVectorMap indice_usuario_estado;
    StringIntVectorMap indice_usuario_nacionalidade;
    IntIntVectorMap    indice_usuario_id;

    // Índices invertidos de buscas de Produto
    StringIntVectorMap indice_produto_nome;
    StringIntVectorMap indice_produto_categoria;
    StringIntVectorMap indice_produto_marca;
    StringIntVectorMap indice_produto_condicao;
    IntIntVectorMap    indice_produto_id;

    // Índices invertidos de buscas de Compra
    IntIntVectorMap indice_compra_id;
    IntIntVectorMap indice_compra_timestamp;
    IntIntVectorMap indice_compra_id_usuario;
    IntIntVectorMap indice_compra_id_produto;

    // Índices invertidos de buscas de Reposição
    IntIntVectorMap indice_reposicao_id;
    IntIntVectorMap indice_reposicao_timestamp;
    IntIntVectorMap indice_reposicao_id_produto;

    // Históricos: cada posição representa um usuário ou produto e armazena os IDs com quantidades
    Vector<Vector<ItemQtd>> historico_usuario;
    Vector<Vector<ItemQtd>> historico_produto;

    // Funções auxiliares internas
    void adicionar_ao_historico(Vector<ItemQtd>& historico, int id, int qtd);
    Vector<int> intersecao(const Vector<int>& a, const Vector<int>& b) const;
    Vector<int> uniao(const Vector<int>& a, const Vector<int>& b) const;
    Vector<int> diferenca(const Vector<int>& a, const Vector<int>& b) const;
    Vector<int> avaliar_expressao(const Vector<std::string>& tokens, int tipo_entidade);

public:
    MercadoDCC();
    
    // Métodos de cadastro
    void cadastrar_usuario(const std::string& nome, int idade, const std::string& cidade, const std::string& estado, const std::string& nacionalidade);
    void cadastrar_produto(const std::string& nome, double preco, int qtd_inicial, const std::string& categoria, const std::string& marca, const std::string& condicao);
    
    // Métodos de registro de movimentação de estoque
    void registrar_reposicao(int timestamp, const Vector<ItemQtd>& itens);
    void registrar_compra(int timestamp, int id_usuario, const Vector<ItemQtd>& itens);

    // Métodos de consulta multiatributo com operadores lógicos
    void consultar_usuarios(const Vector<std::string>& tokens);
    void consultar_produtos(const Vector<std::string>& tokens);
    void consultar_compras(const Vector<std::string>& tokens);
    void consultar_reposicoes(const Vector<std::string>& tokens);
};

#endif
