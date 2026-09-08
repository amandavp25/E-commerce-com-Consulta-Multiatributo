#include "IntIntVectorMap.hpp"

IntIntVectorMap::No::No(int k) : chave(k), proximo(nullptr) {}

IntIntVectorMap::IntIntVectorMap() : capacidade(101), tamanho_atual(0) {
    tabela = new No*[capacidade];
    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;
}

IntIntVectorMap::~IntIntVectorMap() {
    for (int i = 0; i < capacidade; i++) {
        No* atual = tabela[i];
        while (atual != nullptr) {
            No* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }
    delete[] tabela;
}

int IntIntVectorMap::funcaoHash(int chave) const {
    // Garante que o índice hash seja positivo
    return (chave >= 0 ? chave : -chave) % capacidade;
}

void IntIntVectorMap::redimensionar() {
    int capacidade_antiga = capacidade;
    No** tabela_antiga = tabela;
    
    capacidade *= 2;
    tabela = new No*[capacidade];
    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;

    for (int i = 0; i < capacidade_antiga; i++) {
        No* atual = tabela_antiga[i];
        while (atual != nullptr) {
            No* proximo = atual->proximo;
            int h = funcaoHash(atual->chave);
            atual->proximo = tabela[h];
            tabela[h] = atual;
            atual = proximo;
        }
    }
    delete[] tabela_antiga;
}

Vector<int>& IntIntVectorMap::obter(int chave) {
    int h = funcaoHash(chave);
    No* atual = tabela[h];
    
    while (atual != nullptr) {
        if (atual->chave == chave) {
            return atual->valor;
        }
        atual = atual->proximo;
    }
    
    if (tamanho_atual >= capacidade) {
        redimensionar();
        h = funcaoHash(chave);
    }
    
    No* novo_no = new No(chave);
    novo_no->proximo = tabela[h];
    tabela[h] = novo_no;
    tamanho_atual++;
    
    return novo_no->valor;
}

bool IntIntVectorMap::encontrar(int chave, Vector<int>*& valor_saida) {
    int h = funcaoHash(chave);
    No* atual = tabela[h];
    
    while (atual != nullptr) {
        if (atual->chave == chave) {
            valor_saida = &(atual->valor);
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}
