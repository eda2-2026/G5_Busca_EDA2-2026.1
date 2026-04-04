#pragma once
#include "Veiculo.h"
#include "ArvoreBinaria.h"
#include "AuxCalculoDePrimos.h"
#include <string>
#include <vector>
#include <iostream>

class TabelaHash {
private:
    ArvoreBinaria** tabela_hash;
    int capacidade;
    int qtd_de_veiculos;

public:

    TabelaHash(int tamanho_fixo) {
        this->capacidade = ProximoPrimo(tamanho_fixo);
        this->qtd_de_veiculos = 0;
        this->tabela_hash = new ArvoreBinaria*[capacidade];

        // Inicializa todos os buckets como vazios
        for (int i = 0; i < capacidade; i++) {
            tabela_hash[i] = nullptr;
        }
    }

    ~TabelaHash() {
        // Primeiro deleta as arvores que foram criadas
        for (int i = 0; i < capacidade; i++) {
            if (tabela_hash[i] != nullptr) {
                delete tabela_hash[i];
            }
        }
        // Depois deleta o array principal
        delete[] tabela_hash;
    }

    int FuncaoHash(std::string placa) {
        /// Utiliza polynomial rolling hash para calcular os valores

        long long valor_hash = 0;
        int p = 31; // Utiliza um numero primo para aumentar a "aleatoriedadde" dos valores de saida

        for (int i = 0; i < 7; i++) {
            valor_hash = (valor_hash * p + placa[i]) % capacidade;
        }

        return valor_hash;
    }

    void InserirVeiculo(Veiculo *veiculo) {

        // Se o fator de carga da tabela for maior que 75%, e aplicada
        // uma funcao que dobra o tamanho da tabela hash e calcula
        // as novas posicoes dos carros nos buckets
        if (CalcularFatorDeCarga() > 0.75) {
            RedimensionarTabela();
        }

        int id_veiculo_na_tabela = FuncaoHash(veiculo->placa);

        // Se o bucket for vazio ele cria uma arvore
        if (tabela_hash[id_veiculo_na_tabela] == nullptr) {
            tabela_hash[id_veiculo_na_tabela] = new ArvoreBinaria();
        }

        tabela_hash[id_veiculo_na_tabela]->InserirVeiculo(veiculo);
        qtd_de_veiculos++;

    }

    void DeletarVeiculo(std::string placa) {
        int id_veiculo_na_tabela = FuncaoHash(placa);

        // Verifica se existe uma arvore naquele indice e se existe um veiculo la dentro
        if (tabela_hash[id_veiculo_na_tabela] != nullptr &&
            tabela_hash[id_veiculo_na_tabela]->BuscarVeiculo(placa) != nullptr) {

            tabela_hash[id_veiculo_na_tabela]->DeletarVeiculo(placa);
            qtd_de_veiculos--;
            printf("Veículo de placa %s deletado com sucesso.\n", placa.c_str());
        } else {
            printf("Não existe veículo de placa %s no banco de dados.\n", placa.c_str());
        }
    }

    Veiculo* BuscarVeiculo(std::string placa) {
        int id_veiculo_na_tabela = FuncaoHash(placa);

        if (tabela_hash[id_veiculo_na_tabela] != nullptr) {

            // Retorna o que a arvore encontrar
            return tabela_hash[id_veiculo_na_tabela]->BuscarVeiculo(placa);
        } else {
            printf("Não existe veículo de placa %s no banco de dados.\n", placa.c_str());
            return nullptr;
        }

    }

    float CalcularFatorDeCarga() {
        // E utilizado o cast float para evitar qye a divisao de zero
        float fator_de_carga = (float) qtd_de_veiculos / capacidade;
        return fator_de_carga;
    }

    void RedimensionarTabela() {
        int nova_capacidade = ProximoPrimo(capacidade * 2);

        // Primeiro, a funcao coloca todos os veiculos da tabela hash em um vetor
        std::vector<Veiculo*> todos_veiculos;
        for (int i = 0; i < capacidade; i++) {
            if (tabela_hash[i] != nullptr) {
                // Pega todos os veiculos que estao armazenados em um
                // bucket especifico e adiciona em um vetor temporario
                std::vector<Veiculo*> veiculos_da_arvore = tabela_hash[i]->ObterTodosOsVeiculos();

                // insere os veiculos do vetor temporario no vetor geral
                todos_veiculos.insert(todos_veiculos.end(), veiculos_da_arvore.begin(), veiculos_da_arvore.end());
            }
        }

        // Segundo, limpa da memoria a tabela hash antiga
        for (int i = 0; i < capacidade; i++) {
            if (tabela_hash[i] != nullptr) {
                delete tabela_hash[i];
            }
        }
        delete[] tabela_hash;

        // Terceiro, atualiza as configuracoes da nova tabela hash
        this->capacidade = nova_capacidade;
        this->qtd_de_veiculos = 0; // Por enquanto zero, ele ja sera calculado automaticamente ao inserir os veiculos pela funcao InserirVeiculo
        this->tabela_hash = new ArvoreBinaria*[nova_capacidade];

        for (int i = 0; i < nova_capacidade; i++) {
            tabela_hash[i] = nullptr;
        }

        // Quarto, insere os veiculos da antiga tabela hash, os que estavam no
        // vetor, na nova tabela hash em novas posicoes seguindo a nova
        // funcao hash
        for (Veiculo* v : todos_veiculos) {
            InserirVeiculo(v);
        }

        std::cout << "-> Redimensionamento da tabela hash. Tabela cresceu para " << nova_capacidade << " posicoes." << std::endl;
    }
};
