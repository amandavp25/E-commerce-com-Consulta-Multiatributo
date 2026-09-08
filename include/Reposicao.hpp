#ifndef REPOSICAO_HPP
#define REPOSICAO_HPP

#include "Vector.hpp"
#include "ItemQtd.hpp"

struct Reposicao {
    int id;
    int timestamp;
    Vector<ItemQtd> produtos;

    Reposicao();
    Reposicao(int id, int timestamp, const Vector<ItemQtd>& produtos);
};

#endif
