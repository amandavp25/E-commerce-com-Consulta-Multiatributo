#ifndef ITEM_QTD_HPP
#define ITEM_QTD_HPP

// Estrutura genérica para armazenar um identificador e uma quantidade
// Usada tanto para produtos em uma compra/reposição quanto para o histórico
struct ItemQtd {
    int id;
    int qtd;
    ItemQtd();
    ItemQtd(int id, int qtd);
};

#endif
