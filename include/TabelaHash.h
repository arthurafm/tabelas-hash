#ifndef TABELASHASH_H
#define TABELASHASH_H

#include <vector>
#include <list>

#include "../include/Registro.h"

typedef struct
{
    std::string chave;
    Registro* registro;
    bool ocupado;
} Elemento;

class TabelaHash_EndAberto
{
    public: // elementos que podem ser acessados externamente

        TabelaHash_EndAberto(unsigned int m); // construtor
        ~TabelaHash_EndAberto(); // destrutor

        bool insereEABL(std::string chave, Registro* reg);
        Registro* buscaEABL(std::string chave);

        bool insereDoubleHashing(std::string chave, Registro* reg);
        Registro* buscaDoubleHashing(std::string chave);

        int colisoesOcorridas();

    private: // elementos que somente podem ser acessados dentro da classe

        unsigned int M;
        std::vector<Elemento> tabela;
        int totalColisoes;
};

class TabelaHash_EndFechado
{
    public: // elementos que podem ser acessados externamente

        TabelaHash_EndFechado(unsigned int m, unsigned int t=5); // construtor
        ~TabelaHash_EndFechado(); // destrutor

        bool insereChaining(std::string chave, Registro* reg);
        Registro* buscaChaining(std::string chave);

        bool insereBuckets(std::string chave, Registro* reg);
        Registro* buscaBuckets(std::string chave);

        int colisoesOcorridas();

    private: // elementos que somente podem ser acessados dentro da classe

        unsigned int M;
        std::vector<std::list<Elemento> > tabelaChaining;

        unsigned int TamanhoBucket;
        std::vector<std::vector<Elemento> > tabelaBuckets;
        std::vector<Elemento> overflow;

        int totalColisoes;
};

#endif // TABELAHASH_H
