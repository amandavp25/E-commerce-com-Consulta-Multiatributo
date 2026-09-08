#include "Compra.hpp"

Compra::Compra() : id(0), timestamp(0), id_usuario(0) {}

Compra::Compra(int id, int timestamp, int id_usuario, const Vector<ItemQtd>& produtos) {
    this->id = id;
    this->timestamp = timestamp;
    this->id_usuario = id_usuario;
    this->produtos = produtos;
}
