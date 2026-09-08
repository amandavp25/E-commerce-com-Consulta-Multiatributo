#include "ItemQtd.hpp"

ItemQtd::ItemQtd() : id(0), qtd(0) {}

ItemQtd::ItemQtd(int id, int qtd) {
    this->id = id;
    this->qtd = qtd;
}
