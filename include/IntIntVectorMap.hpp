#ifndef INT_INT_VECTOR_MAP_HPP
#define INT_INT_VECTOR_MAP_HPP

#include "Vector.hpp"

// Tabela Hash que mapeia uma chave (inteiro) para um vetor de inteiros
class IntIntVectorMap {
private:
    // Nó da lista encadeada para tratar colisões
    struct No {
        int chave;
        Vector<int> valor;
        No* proximo;
        No(int k);
    };

    No** tabela;         // Array de ponteiros para os Nós
    int capacidade;      // Tamanho atual da tabela hash
    int tamanho_atual;   // Quantidade de chaves únicas armazenadas

    // Calcula o índice da tabela para um número inteiro
    int funcaoHash(int chave) const;
    
    // Aumenta a capacidade da tabela hash para reduzir o número de colisões
    void redimensionar();

public:
    IntIntVectorMap();
    ~IntIntVectorMap();

    // Obtém o vetor associado à chave. Cria se não existir.
    Vector<int>& obter(int chave);
    
    // Busca um vetor pela chave. Retorna verdadeiro se existir.
    bool encontrar(int chave, Vector<int>*& valor_saida);
};

#endif
