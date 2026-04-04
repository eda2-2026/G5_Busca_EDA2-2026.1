#pragma once
#include <string>

class Veiculo {
public:
    std::string placa;
    std::string cor;
    int ano;

    Veiculo(std::string placa, std::string cor, int ano) {
        this->placa = placa;
        this->cor   = cor;
        this->ano   = ano;
    }
};