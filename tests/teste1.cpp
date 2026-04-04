#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include "../src/Veiculo.h"
#include "../src/TabelaHash.h"
#include "../src/GeradorDePlacas.h"
#include "../src/CarregarCSVParaTabela.h"

int main() {
    // Inicializa uma semente aleatoria
    srand(time(NULL));

    // Este vetor contem todos as capacidades que testaremos na tabela hash
    // primeiro testaremos uma tabela de mil veiculos, depois 5 mil e assim
    // por diante
    std::vector<int> tamanhos_teste = {
        1000,       // 1 mil
        5000,       // 5 mil
        10000,      // 10 mil
        25000,      // 25 mil
        50000,      // 50 mil
        75000,      // 75 mil
        100000,     // 100 mil
        250000,     // 250 mil
        500000,     // 500 mil
        750000,     // 750 mil
        1000000,    // 1 milhao
        1500000,    // 1.5 milhoes
        2000000,    // 2 milhoes
        3000000,    // 3 mihloes
        4000000,    // 4 mihloes
        5000000     // 5 milhoes
    };

    std::cout << "\nIniciando testes com a tabela hash de veiculos...\n";

    for (int quantidade_de_veiculos : tamanhos_teste) {
        std::string nome_arquivo = "banco_" + std::to_string(quantidade_de_veiculos) + ".csv";

        // Primeiro, chama a funcao para gerar um banco de dados em csv com
        // (quantidade_de_veiculos) veiculos
        GerarBancoDeDadosCSV(quantidade_de_veiculos, nome_arquivo);

        // Segundo, cria uma tabela hash
        // Por padrao do projeto, todas as tabelas hash comecam com 10007 buckets
        TabelaHash tabela(10007);

        // Terceiro, guardamos em um vetor todas as placas que serao utilizadas
        // para testar a eficiencia da tabela hash
        // quanto mais veiculos tiver o csv, maior sera o vetor de veiculos
        std::vector<std::string> placas_de_teste;
        CarregarCSVParaTabela(nome_arquivo, tabela, placas_de_teste);

        // Quarto, iniciamos o cronometro
        auto inicio = std::chrono::high_resolution_clock::now();

        int repeticoes = 10000;
        int encontrados_sucesso = 0; // Mede quantos veiculos foram encontrados na consulta da tabela hash

        for (int i = 0; i < repeticoes; i++) {
            // Pegamos uma placa diferente do vetor de placas de teste
            std::string placa_da_vez = placas_de_teste[i % placas_de_teste.size()];

            Veiculo* encontrado = tabela.BuscarVeiculo(placa_da_vez);

            if (encontrado != nullptr) {
                encontrados_sucesso++;
            }
        }

        // Para o cronômetro
        auto fim = std::chrono::high_resolution_clock::now();
        // =======================================================

        // Quinto, calculamos o tempo gasto em nanossegundos
        auto duracao_total = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio).count();

        // Divide o tempo total pelas 10.000 repetições para ter o tempo exato de UMA única busca
        auto tempo_medio_por_busca = duracao_total / repeticoes;

        // Sexto, imprime o resultado do teste atual
        std::cout << "Quantidade de veículos: " << quantidade_de_veiculos << ","
        << " Tempo médio por busca: "<< tempo_medio_por_busca << " nanossegundos"
        << "\n" << std::endl;

        if (encontrados_sucesso == 0) std::cout << "";
    }

    return 0;
}