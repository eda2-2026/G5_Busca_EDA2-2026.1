#include "Veiculo.h"
#inclde "ArvoreBinaria.h"
#include <string>
#include <iostrem>

#include "ArvoreBinaria.h"

class TabelaHash {
private:
    ArvoreBinaria** tabela_hash;
    int capacidade;
    int qtd_de_veiculos;

public:

    TabelaHash(int tamanho_fixo) {
        this->capacidade = tamanho_fixo;
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
        int id_veiculo_na_tabela = FuncaoHash(veiculo->GetPlaca());

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
            tabela_hash[id_veiculo_na_tabela].BuscarVeiculo(placa) != nullptr) {

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
};
