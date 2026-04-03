#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

std::string GerarPlacaAleatoria() {
    std::string placa = "";

    // Gera tres letras aleatorias
    for (int i = 0; i < 3; i++) {
        placa += (char)('A' + rand() % 26);
    }

    // Gera um numero aleatorio
    placa += std::to_string(rand() % 10);

    // Gera uma letra aleatoria
    placa += (char)('A' + rand() % 26);

    // Gera dois numeros aleatorios
    placa += std::to_string(rand()%10);
    placa += std::to_string(rand()%10);

    return placa;
}

void GerarBancoDeDadosCSV(int quantidade_de_carros, std::string nome_do_arquivo) {
    stq::ofstream arquivo(nome_do_arquivo);

    if (!arquivo.is_open()) {
        std::cout << "Erro ao criar o arquivo CSV." << std::endl;
        return;
    }

    arquivo << "Placa,Cor,Ano\n";

    // Vetor com opcoes de cores para serem sorteadas
    std::vector<std::string> cores = {"Branco", "Preto", "Prata", "Cinza", "Vermelho", "Azul"};

    for (int i = 0; i < quantidade_de_carrosq; i++) {
        std::string placa = GerarPlacaAleatoria();
        std::string cor = cores[rand() % cores.size()];
        int ano = 1990 + (rand() % 37); // Sorteia um ano entre 1990 e 2026

        // Escreve a linha no formato: Placa,Cor,Ano
        arquivo << placa << "," << cor << "," << ano << "\n";
    }

    arquivo.close();
    std::cout << "Sucesso: " << nome_do_arquivo << " gerado com " << quantidade_de_carros << " veículos." << std::endl;
}

}

