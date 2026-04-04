#include <iostream>
#include "Veiculo.h"
#include "ArvoreBinaria.h"

int main() {
    ArvoreBinaria arvore;

    // Cria alguns veículos
    Veiculo* v1 = new Veiculo("ABC1D23", "Vermelho", 2020);
    Veiculo* v2 = new Veiculo("XYZ9F99", "Azul",     2018);
    Veiculo* v3 = new Veiculo("DEF2G34", "Preto",    2022);

    // Testa inserção
    arvore.InserirVeiculo(v1);
    arvore.InserirVeiculo(v2);
    arvore.InserirVeiculo(v3);
    std::cout << "Veículos inseridos!" << std::endl;

    // Testa busca
    Veiculo* encontrado = arvore.BuscarVeiculo("DEF2G34");
    if (encontrado != nullptr)
        std::cout << "Encontrado: " << encontrado->placa << " - " << encontrado->cor << std::endl;
    else
        std::cout << "Veículo não encontrado." << std::endl;

    // Testa deleção
    arvore.DeletarVeiculo("DEF2G34");
    std::cout << "Veículo DEF2G34 deletado." << std::endl;

    // Tenta buscar o deletado
    encontrado = arvore.BuscarVeiculo("DEF2G34");
    if (encontrado != nullptr)
        std::cout << "Encontrado: " << encontrado->placa << std::endl;
    else
        std::cout << "Veículo não encontrado (deletado com sucesso)." << std::endl;

    return 0;
}