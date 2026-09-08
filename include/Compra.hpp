#ifndef COMPRA_HPP
#define COMPRA_HPP

#include "Vector.hpp"
#include "ItemQtd.hpp"

struct Compra {
    int id;
    int timestamp;
    int id_usuario;
    Vector<ItemQtd> produtos;

    Compra();
    Compra(int id, int timestamp, int id_usuario, const Vector<ItemQtd>& produtos);
};

#endif
