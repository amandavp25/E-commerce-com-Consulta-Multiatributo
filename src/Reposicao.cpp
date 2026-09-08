#include "Reposicao.hpp"

Reposicao::Reposicao() : id(0), timestamp(0) {}

Reposicao::Reposicao(int id, int timestamp, const Vector<ItemQtd>& produtos) {
    this->id = id;
    this->timestamp = timestamp;
    this->produtos = produtos;
}
