#ifndef VECTOR_HPP
#define VECTOR_HPP

// Estrutura de dados genérica para armazenar elementos dinamicamente
template <typename T>
class Vector {
private:
    T* dados;             // Ponteiro para o array armazenado na memória
    int capacidade;       // Capacidade total alocada no momento
    int tamanho_atual;    // Quantidade de elementos atualmente no vetor

    // Dobra a capacidade do vetor quando não há mais espaço
    void redimensionar() {
        capacidade = (capacidade == 0) ? 2 : capacidade * 2;
        T* novos_dados = new T[capacidade];
        for (int i = 0; i < tamanho_atual; i++) {
            novos_dados[i] = dados[i];
        }
        delete[] dados;
        dados = novos_dados;
    }

public:
    // Construtor padrão inicializa o vetor vazio
    Vector() {
        capacidade = 0;
        tamanho_atual = 0;
        dados = nullptr;
    }

    // Destrutor libera a memória alocada
    ~Vector() {
        if (dados != nullptr) {
            delete[] dados;
        }
    }
    
    // Construtor de cópia (necessário para passar o vetor por valor com segurança)
    Vector(const Vector& outro) {
        capacidade = outro.capacidade;
        tamanho_atual = outro.tamanho_atual;
        if (capacidade > 0) {
            dados = new T[capacidade];
            for (int i = 0; i < tamanho_atual; i++) {
                dados[i] = outro.dados[i];
            }
        } else {
            dados = nullptr;
        }
    }
    
    // Operador de atribuição (necessário para igualar dois vetores com segurança)
    Vector& operator=(const Vector& outro) {
        if (this != &outro) {
            delete[] dados;
            capacidade = outro.capacidade;
            tamanho_atual = outro.tamanho_atual;
            if (capacidade > 0) {
                dados = new T[capacidade];
                for (int i = 0; i < tamanho_atual; i++) {
                    dados[i] = outro.dados[i];
                }
            } else {
                dados = nullptr;
            }
        }
        return *this;
    }

    // Adiciona um novo elemento ao final do vetor
    void adicionar(const T& elemento) {
        if (tamanho_atual == capacidade) {
            redimensionar();
        }
        dados[tamanho_atual++] = elemento;
    }

    // Retorna a quantidade de elementos armazenados
    int tamanho() const {
        return tamanho_atual;
    }

    // Sobrecarga de operador para acessar elementos pelo índice (leitura/escrita)
    T& operator[](int indice) {
        return dados[indice];
    }

    // Sobrecarga de operador para acessar elementos pelo índice (somente leitura)
    const T& operator[](int indice) const {
        return dados[indice];
    }
};

#endif
