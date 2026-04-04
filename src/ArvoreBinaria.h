#pragma once
#include <string>
#include "NoArvore.h"
#include "Veiculo.h"



class ArvoreBinaria {
public:
    NoArvore* raiz;

    ArvoreBinaria() {
        raiz = nullptr;
    }

    // ── Inserir ──────────────────────────────────────────────────────────

    void InserirVeiculo(Veiculo* veiculo) {
        NoArvore* novo_no = new NoArvore(veiculo);

        // Árvore vazia: o novo nó vira a raiz
        if (raiz == nullptr) {
            raiz = novo_no;
            return;
        }

        // Caminha pela árvore até achar uma posição vazia
        NoArvore* atual = raiz;
        while (true) {
            if (veiculo->placa < atual->veiculo->placa) {
                if (atual->filho_esquerdo == nullptr) {
                    atual->filho_esquerdo = novo_no;
                    return;
                }
                atual = atual->filho_esquerdo;

            } else if (veiculo->placa > atual->veiculo->placa) {
                if (atual->filho_direito == nullptr) {
                    atual->filho_direito = novo_no;
                    return;
                }
                atual = atual->filho_direito;

            } else {
                // Placa duplicada, ignora
                return;
            }
        }
    }

    // ── Buscar ───────────────────────────────────────────────────────────

    Veiculo* BuscarVeiculo(std::string placa) {
        NoArvore* atual = raiz;

        while (atual != nullptr) {
            if (placa == atual->veiculo->placa) {
                return atual->veiculo;        // Encontrou!

            } else if (placa < atual->veiculo->placa) {
                atual = atual->filho_esquerdo;

            } else {
                atual = atual->filho_direito;
            }
        }

        return nullptr; // Não encontrou
    }

    // ── Deletar ──────────────────────────────────────────────────────────

    void DeletarVeiculo(std::string placa) {
        NoArvore* pai   = nullptr;
        NoArvore* atual = raiz;

        // Passo 1: encontra o nó e guarda seu pai
        while (atual != nullptr && atual->veiculo->placa != placa) {
            pai = atual;
            if (placa < atual->veiculo->placa)
                atual = atual->filho_esquerdo;
            else
                atual = atual->filho_direito;
        }

        if (atual == nullptr) return; // Placa não encontrada

        // Passo 2: o nó tem dois filhos →
        // substitui pelo sucessor (menor nó da subárvore direita)
        if (atual->filho_esquerdo != nullptr && atual->filho_direito != nullptr) {
            NoArvore* pai_sucessor = atual;
            NoArvore* sucessor     = atual->filho_direito;

            while (sucessor->filho_esquerdo != nullptr) {
                pai_sucessor = sucessor;
                sucessor     = sucessor->filho_esquerdo;
            }

            // Copia o veículo do sucessor para o nó atual e
            // redireciona o problema para deletar o sucessor
            atual->veiculo = sucessor->veiculo;
            atual          = sucessor;
            pai            = pai_sucessor;
        }

        // Passo 3: agora o nó tem 0 ou 1 filho — caso simples
        NoArvore* filho = nullptr;
        if (atual->filho_esquerdo != nullptr)
            filho = atual->filho_esquerdo;
        else
            filho = atual->filho_direito;

        if (pai == nullptr) {
            raiz = filho;        // Estava deletando a raiz
        } else if (pai->filho_esquerdo == atual) {
            pai->filho_esquerdo = filho;
        } else {
            pai->filho_direito = filho;
        }

        delete atual;
    }
};