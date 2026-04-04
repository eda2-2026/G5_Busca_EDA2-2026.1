#pragma once
#include "Veiculo.h"

class NoArvore {
public:
    NoArvore* filho_direito;
    NoArvore* filho_esquerdo;
    Veiculo*  veiculo;

    NoArvore(Veiculo* v) {
        this->veiculo        = v;
        this->filho_direito  = nullptr;
        this->filho_esquerdo = nullptr;
    }
};