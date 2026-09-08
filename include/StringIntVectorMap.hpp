#ifndef STRING_INT_VECTOR_MAP_HPP
#define STRING_INT_VECTOR_MAP_HPP

#include <string>
#include "Vector.hpp"

// Tabela Hash que mapeia uma chave (string) para um vetor de inteiros
class StringIntVectorMap {
private:
    // Nó da lista encadeada para tratar colisões na Tabela Hash
    struct No {
        std::string chave;
        Vector<int> valor;
        No* proximo;
        No(const std::string& k);
    };

    No** tabela;         // Array de ponteiros para os Nós
    int capacidade;      // Tamanho atual da tabela hash
    int tamanho_atual;   // Quantidade de chaves únicas armazenadas

    // Calcula o índice da tabela para uma string usando o algoritmo djb2
    int funcaoHash(const std::string& chave) const;
    
    // Aumenta a capacidade da tabela hash para reduzir o número de colisões
    void redimensionar();

public:
    // Construtor inicializa a tabela com capacidade padrão
    StringIntVectorMap();
    
    // Destrutor limpa todos os nós para evitar vazamento de memória
    ~StringIntVectorMap();

    // Obtém o vetor de inteiros associado à chave. Se não existir, cria um novo nó.
    Vector<int>& obter(const std::string& chave);
    
    // Busca um vetor de inteiros pela chave. Retorna verdadeiro se existir.
    bool encontrar(const std::string& chave, Vector<int>*& valor_saida);
};

#endif
