#include "MercadoDCC.hpp"
#include <iostream>
#include <iomanip>

MercadoDCC::MercadoDCC() {}

// Faz a interseção entre dois conjuntos de IDs que já estão ordenados de forma crescente
Vector<int> MercadoDCC::intersecao(const Vector<int>& conjunto_a, const Vector<int>& conjunto_b) const {
    Vector<int> resultado;
    int i = 0, j = 0;
    while (i < conjunto_a.tamanho() && j < conjunto_b.tamanho()) {
        if (conjunto_a[i] < conjunto_b[j]) {
            i++;
        } else if (conjunto_a[i] > conjunto_b[j]) {
            j++;
        } else {
            resultado.adicionar(conjunto_a[i]);
            i++;
            j++;
        }
    }
    return resultado;
}

// Mantém o histórico ordenado por ID de forma a facilitar na hora de exibir
void MercadoDCC::adicionar_ao_historico(Vector<ItemQtd>& historico, int id, int qtd) {
    for (int i = 0; i < historico.tamanho(); ++i) {
        if (historico[i].id == id) {
            historico[i].qtd += qtd;
            return;
        } else if (historico[i].id > id) {
            // Empurra os elementos pra frente e insere o novo ID
            historico.adicionar({0, 0});
            for (int j = historico.tamanho() - 1; j > i; --j) {
                historico[j] = historico[j-1];
            }
            historico[i] = {id, qtd};
            return;
        }
    }
    historico.adicionar({id, qtd});
}

void MercadoDCC::cadastrar_usuario(const std::string& nome, int idade, const std::string& cidade, const std::string& estado, const std::string& nacionalidade) {
    int id = usuarios.tamanho();
    usuarios.adicionar(Usuario(id, nome, idade, cidade, estado, nacionalidade));
    historico_usuario.adicionar(Vector<ItemQtd>());

    // Salva o ID do usuário recém-criado em todos os índices invertidos correspondentes
    indice_usuario_id.obter(id).adicionar(id);
    indice_usuario_nome.obter(nome).adicionar(id);
    indice_usuario_idade.obter(idade).adicionar(id);
    indice_usuario_cidade.obter(cidade).adicionar(id);
    indice_usuario_estado.obter(estado).adicionar(id);
    indice_usuario_nacionalidade.obter(nacionalidade).adicionar(id);

    std::cout << "U " << id << "\n";
}

void MercadoDCC::cadastrar_produto(const std::string& nome, double preco, int qtd_inicial, const std::string& categoria, const std::string& marca, const std::string& condicao) {
    int id = produtos.tamanho();
    produtos.adicionar(Produto(id, nome, preco, qtd_inicial, categoria, marca, condicao));
    historico_produto.adicionar(Vector<ItemQtd>());

    indice_produto_id.obter(id).adicionar(id);
    indice_produto_nome.obter(nome).adicionar(id);
    indice_produto_categoria.obter(categoria).adicionar(id);
    indice_produto_marca.obter(marca).adicionar(id);
    indice_produto_condicao.obter(condicao).adicionar(id);

    std::cout << "P " << id << "\n";
}

void MercadoDCC::registrar_reposicao(int timestamp, const Vector<ItemQtd>& itens) {
    int id = reposicoes.tamanho();
    reposicoes.adicionar(Reposicao(id, timestamp, itens));

    indice_reposicao_id.obter(id).adicionar(id);
    indice_reposicao_timestamp.obter(timestamp).adicionar(id);
    
    // Atualiza o estoque de cada produto reposto
    for (int i = 0; i < itens.tamanho(); ++i) {
        indice_reposicao_id_produto.obter(itens[i].id).adicionar(id);
        produtos[itens[i].id].qtd += itens[i].qtd;
    }

    std::cout << "R " << id << "\n";
}

void MercadoDCC::registrar_compra(int timestamp, int id_usuario, const Vector<ItemQtd>& itens) {
    // Validação da compra: verifica estoques e se o usuário existe
    bool compra_valida = true;
    for (int i = 0; i < itens.tamanho(); ++i) {
        if (itens[i].id >= produtos.tamanho() || produtos[itens[i].id].qtd < itens[i].qtd) {
            compra_valida = false;
            break;
        }
    }
    if (id_usuario >= usuarios.tamanho()) {
        compra_valida = false;
    }

    // Retorna erro se a compra for inválida
    if (!compra_valida) {
        std::cout << "C INV\n";
        return;
    }

    // Se válida, processa a compra
    int id = compras.tamanho();
    compras.adicionar(Compra(id, timestamp, id_usuario, itens));

    indice_compra_id.obter(id).adicionar(id);
    indice_compra_timestamp.obter(timestamp).adicionar(id);
    indice_compra_id_usuario.obter(id_usuario).adicionar(id);

    for (int i = 0; i < itens.tamanho(); ++i) {
        produtos[itens[i].id].qtd -= itens[i].qtd;
        indice_compra_id_produto.obter(itens[i].id).adicionar(id);

        adicionar_ao_historico(historico_usuario[id_usuario], itens[i].id, itens[i].qtd);
        adicionar_ao_historico(historico_produto[itens[i].id], id_usuario, itens[i].qtd);
    }

    std::cout << "C " << id << "\n";
}

Vector<int> MercadoDCC::uniao(const Vector<int>& a, const Vector<int>& b) const {
    Vector<int> resultado;
    int i = 0, j = 0;
    while (i < a.tamanho() && j < b.tamanho()) {
        if (a[i] < b[j]) {
            resultado.adicionar(a[i++]);
        } else if (a[i] > b[j]) {
            resultado.adicionar(b[j++]);
        } else {
            resultado.adicionar(a[i]);
            i++; j++;
        }
    }
    while (i < a.tamanho()) resultado.adicionar(a[i++]);
    while (j < b.tamanho()) resultado.adicionar(b[j++]);
    return resultado;
}

Vector<int> MercadoDCC::diferenca(const Vector<int>& a, const Vector<int>& b) const {
    Vector<int> resultado;
    int i = 0, j = 0;
    while (i < a.tamanho() && j < b.tamanho()) {
        if (a[i] < b[j]) {
            resultado.adicionar(a[i++]);
        } else if (a[i] > b[j]) {
            j++;
        } else {
            i++; j++;
        }
    }
    while (i < a.tamanho()) resultado.adicionar(a[i++]);
    return resultado;
}

Vector<int> MercadoDCC::avaliar_expressao(const Vector<std::string>& tokens, int tipo_entidade) {
    if (tokens.tamanho() == 0) return Vector<int>();

    Vector<int> universo;
    int max_id = 0;
    if (tipo_entidade == 0) max_id = usuarios.tamanho();
    else if (tipo_entidade == 1) max_id = produtos.tamanho();
    else if (tipo_entidade == 2) max_id = compras.tamanho();
    else if (tipo_entidade == 3) max_id = reposicoes.tamanho();

    for (int i = 0; i < max_id; ++i) universo.adicionar(i);

    Vector<int> resultado_final; // Para o OR
    bool primeiro_chunk = true;

    int i = 0;
    while (i < tokens.tamanho()) {
        Vector<int> resultado_chunk; // Para o AND
        bool primeiro_termo = true;

        while (i < tokens.tamanho() && tokens[i] != "OR") {
            if (tokens[i] == "AND") {
                i++;
                continue;
            }

            bool is_not = false;
            if (tokens[i] == "NOT") {
                is_not = true;
                i++;
            }

            if (i >= tokens.tamanho()) break;
            std::string atributo = tokens[i++];
            if (i >= tokens.tamanho()) break;
            std::string valor = tokens[i++];

            bool is_range = false;
            std::string valor2;
            if (atributo == "idade" || atributo == "preco" || atributo == "qtd" || atributo == "timestamp") {
                if (i < tokens.tamanho() && tokens[i] != "AND" && tokens[i] != "OR" && tokens[i] != "NOT") {
                    std::string n = tokens[i];
                    if (n != "id" && n != "nome" && n != "idade" && n != "cidade" && n != "estado" && n != "nacionalidade" &&
                        n != "preco" && n != "qtd" && n != "categoria" && n != "marca" && n != "condicao" &&
                        n != "timestamp" && n != "id_usuario" && n != "id_produto") {
                        valor2 = tokens[i++];
                        is_range = true;
                    }
                }
            }

            Vector<int> conjunto_atual;
            if (is_range) {
                if (atributo == "idade" && tipo_entidade == 0) {
                    int min_val = std::stoi(valor);
                    int max_val = std::stoi(valor2);
                    for (int k = 0; k < usuarios.tamanho(); ++k) {
                        if (usuarios[k].idade >= min_val && usuarios[k].idade <= max_val) conjunto_atual.adicionar(k);
                    }
                } else if (atributo == "preco" && tipo_entidade == 1) {
                    double min_val = std::stod(valor);
                    double max_val = std::stod(valor2);
                    for (int k = 0; k < produtos.tamanho(); ++k) {
                        if (produtos[k].preco >= min_val && produtos[k].preco <= max_val) conjunto_atual.adicionar(k);
                    }
                } else if (atributo == "qtd" && tipo_entidade == 1) {
                    int min_val = std::stoi(valor);
                    int max_val = std::stoi(valor2);
                    for (int k = 0; k < produtos.tamanho(); ++k) {
                        if (produtos[k].qtd >= min_val && produtos[k].qtd <= max_val) conjunto_atual.adicionar(k);
                    }
                } else if (atributo == "timestamp") {
                    int min_val = std::stoi(valor);
                    int max_val = std::stoi(valor2);
                    if (tipo_entidade == 2) {
                        for (int k = 0; k < compras.tamanho(); ++k) {
                            if (compras[k].timestamp >= min_val && compras[k].timestamp <= max_val) conjunto_atual.adicionar(k);
                        }
                    } else if (tipo_entidade == 3) {
                        for (int k = 0; k < reposicoes.tamanho(); ++k) {
                            if (reposicoes[k].timestamp >= min_val && reposicoes[k].timestamp <= max_val) conjunto_atual.adicionar(k);
                        }
                    }
                }
            } else {
                Vector<int>* conjunto_ptr = nullptr;
                if (tipo_entidade == 0) {
                    if (atributo == "id") indice_usuario_id.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "nome") indice_usuario_nome.encontrar(valor, conjunto_ptr);
                    else if (atributo == "idade") indice_usuario_idade.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "cidade") indice_usuario_cidade.encontrar(valor, conjunto_ptr);
                    else if (atributo == "estado") indice_usuario_estado.encontrar(valor, conjunto_ptr);
                    else if (atributo == "nacionalidade") indice_usuario_nacionalidade.encontrar(valor, conjunto_ptr);
                } else if (tipo_entidade == 1) {
                    if (atributo == "id") indice_produto_id.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "nome") indice_produto_nome.encontrar(valor, conjunto_ptr);
                    else if (atributo == "categoria") indice_produto_categoria.encontrar(valor, conjunto_ptr);
                    else if (atributo == "marca") indice_produto_marca.encontrar(valor, conjunto_ptr);
                    else if (atributo == "condicao") indice_produto_condicao.encontrar(valor, conjunto_ptr);
                } else if (tipo_entidade == 2) {
                    if (atributo == "id") indice_compra_id.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "timestamp") indice_compra_timestamp.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "id_usuario") indice_compra_id_usuario.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "id_produto") indice_compra_id_produto.encontrar(std::stoi(valor), conjunto_ptr);
                } else if (tipo_entidade == 3) {
                    if (atributo == "id") indice_reposicao_id.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "timestamp") indice_reposicao_timestamp.encontrar(std::stoi(valor), conjunto_ptr);
                    else if (atributo == "id_produto") indice_reposicao_id_produto.encontrar(std::stoi(valor), conjunto_ptr);
                }
                if (conjunto_ptr != nullptr) conjunto_atual = *conjunto_ptr;
            }

            if (is_not) {
                conjunto_atual = diferenca(universo, conjunto_atual);
            }

            if (primeiro_termo) {
                resultado_chunk = conjunto_atual;
                primeiro_termo = false;
            } else {
                resultado_chunk = intersecao(resultado_chunk, conjunto_atual);
            }
        }

        if (primeiro_chunk) {
            resultado_final = resultado_chunk;
            primeiro_chunk = false;
        } else {
            resultado_final = uniao(resultado_final, resultado_chunk);
        }

        if (i < tokens.tamanho() && tokens[i] == "OR") {
            i++;
        }
    }

    return resultado_final;
}

void MercadoDCC::consultar_usuarios(const Vector<std::string>& tokens) {
    if (tokens.tamanho() == 0) {
        std::cout << "LU VAZIO\n";
        return;
    }

    Vector<int> resultado = avaliar_expressao(tokens, 0);

    if (resultado.tamanho() == 0) {
        std::cout << "LU VAZIO\n";
        return;
    }

    for (int i = 0; i < resultado.tamanho(); ++i) {
        int id = resultado[i];
        const Usuario& u = usuarios[id];
        std::cout << "LU resultado_" << (i+1) << " usuario " << u.id << " " << u.nome << " " 
                  << u.idade << " " << u.cidade << " " << u.estado << " " << u.nacionalidade << "\n";
        
        const Vector<ItemQtd>& hist = historico_usuario[id];
        if (hist.tamanho() > 0) {
            for (int j = 0; j < hist.tamanho(); ++j) {
                std::cout << "produto_" << (j+1) << " " << hist[j].id << " " << hist[j].qtd << (j == hist.tamanho() - 1 ? "" : " ");
            }
            std::cout << "\n";
        }
    }
}

void MercadoDCC::consultar_produtos(const Vector<std::string>& tokens) {
    if (tokens.tamanho() == 0) {
        std::cout << "LP VAZIO\n";
        return;
    }

    Vector<int> resultado = avaliar_expressao(tokens, 1);

    if (resultado.tamanho() == 0) {
        std::cout << "LP VAZIO\n";
        return;
    }

    for (int i = 0; i < resultado.tamanho(); ++i) {
        int id = resultado[i];
        const Produto& p = produtos[id];
        std::cout << "LP resultado_" << (i+1) << " produto " << p.id << " " << p.nome << " ";
        std::cout << std::fixed << std::setprecision(2) << p.preco;
        std::cout << " " << p.qtd << " " << p.categoria << " " << p.marca << " " << p.condicao << "\n";
        
        const Vector<ItemQtd>& hist = historico_produto[id];
        if (hist.tamanho() > 0) {
            for (int j = 0; j < hist.tamanho(); ++j) {
                std::cout << "usuario_" << (j+1) << " " << hist[j].id << " " << hist[j].qtd << (j == hist.tamanho() - 1 ? "" : " ");
            }
            std::cout << "\n";
        }
    }
}

void MercadoDCC::consultar_compras(const Vector<std::string>& tokens) {
    if (tokens.tamanho() == 0) {
        std::cout << "LC VAZIO\n";
        return;
    }

    Vector<int> resultado = avaliar_expressao(tokens, 2);

    if (resultado.tamanho() == 0) {
        std::cout << "LC VAZIO\n";
        return;
    }

    for (int i = 0; i < resultado.tamanho(); ++i) {
        int id = resultado[i];
        const Compra& c = compras[id];
        std::cout << "LC resultado_" << (i+1) << " compra " << c.id << " timestamp " << c.timestamp << " usuario " << c.id_usuario << "\n";
        
        for (int j = 0; j < c.produtos.tamanho(); ++j) {
            std::cout << "produto_" << (j+1) << " " << c.produtos[j].id << " " << c.produtos[j].qtd << (j == c.produtos.tamanho() - 1 ? "" : " ");
        }
        std::cout << "\n";
    }
}

void MercadoDCC::consultar_reposicoes(const Vector<std::string>& tokens) {
    if (tokens.tamanho() == 0) {
        std::cout << "LR VAZIO\n";
        return;
    }

    Vector<int> resultado = avaliar_expressao(tokens, 3);

    if (resultado.tamanho() == 0) {
        std::cout << "LR VAZIO\n";
        return;
    }

    for (int i = 0; i < resultado.tamanho(); ++i) {
        int id = resultado[i];
        const Reposicao& r = reposicoes[id];
        std::cout << "LR resultado_" << (i+1) << " reposicao " << r.id << " timestamp " << r.timestamp << "\n";
        
        for (int j = 0; j < r.produtos.tamanho(); ++j) {
            std::cout << "produto_" << (j+1) << " " << r.produtos[j].id << " " << r.produtos[j].qtd << (j == r.produtos.tamanho() - 1 ? "" : " ");
        }
        std::cout << "\n";
    }
}
