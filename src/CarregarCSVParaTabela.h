#pragma once
#include <iostream>
#include <vector>
#include "Veiculo.h"
#include "TabelaHash.h"

void CarregarCSVParaTabela(std::string nome_arquivo, TabelaHash& tabela, std::vector<std::string>& alvos_de_busca) {
    std::ifstream arquivo(nome_arquivo);
    std::string linha, placa, cor, ano_str;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o CSV para leitura." << std::endl;
        return;
    }

    // Pula a primeira linha do arquivo csv, o cabecalho
    std::getline(arquivo, linha);

    int contador = 0;

    // Le linha a linha do arquivo csv
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::getline(ss, placa, ',');
        std::getline(ss, cor, ',');
        std::getline(ss, ano_str, ',');

        // Cria um veiculo e insere ele na tabela hash
        Veiculo* v = new Veiculo(placa, cor, std::stoi(ano_str));
        tabela.InserirVeiculo(v);

        // A cada 500 carros e salvo a placa de um carro para ser utilizada nos testes
        if (contador % 500 == 0) {
            alvos_de_busca.push_back(placa);
        }
        contador++;
    }
    arquivo.close();
}