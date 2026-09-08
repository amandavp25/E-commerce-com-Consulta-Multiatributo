#include "StringIntVectorMap.hpp"

StringIntVectorMap::No::No(const std::string& k) : chave(k), proximo(nullptr) {}

StringIntVectorMap::StringIntVectorMap() : capacidade(101), tamanho_atual(0) {
    tabela = new No*[capacidade];
    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;
}

StringIntVectorMap::~StringIntVectorMap() {
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

int StringIntVectorMap::funcaoHash(const std::string& chave) const {
    unsigned long valor_hash = 5381;
    for (char c : chave) {
        valor_hash = ((valor_hash << 5) + valor_hash) + c; 
    }
    return valor_hash % capacidade;
}

void StringIntVectorMap::redimensionar() {
    int capacidade_antiga = capacidade;
    No** tabela_antiga = tabela;
    
    capacidade *= 2;
    tabela = new No*[capacidade];
    for (int i = 0; i < capacidade; i++) tabela[i] = nullptr;

    // Realoca todos os nós existentes na nova tabela com a capacidade ampliada
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

Vector<int>& StringIntVectorMap::obter(const std::string& chave) {
    int h = funcaoHash(chave);
    No* atual = tabela[h];
    
    // Procura a chave na lista encadeada (tratamento de colisão)
    while (atual != nullptr) {
        if (atual->chave == chave) {
            return atual->valor;
        }
        atual = atual->proximo;
    }
    
    // Se a tabela estiver muito cheia, redimensiona
    if (tamanho_atual >= capacidade) {
        redimensionar();
        h = funcaoHash(chave); // Recalcula o hash após o redimensionamento
    }
    
    // Cria um novo nó e adiciona no início da lista (encadeamento)
    No* novo_no = new No(chave);
    novo_no->proximo = tabela[h];
    tabela[h] = novo_no;
    tamanho_atual++;
    
    return novo_no->valor;
}

bool StringIntVectorMap::encontrar(const std::string& chave, Vector<int>*& valor_saida) {
    int h = funcaoHash(chave);
    No* atual = tabela[h];
    
    while (atual != nullptr) {
        if (atual->chave == chave) {
            valor_saida = &(atual->valor);
            return true;
        }
        atual = atual->proximo;
    }
    return false; // Retorna falso caso a chave não seja encontrada
}
