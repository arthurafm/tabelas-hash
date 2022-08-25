#include <iostream>
#include <fstream>

#include "include/Registro.h"
#include "include/TabelaHash.h"

#define DIV_CEIL(x,y) ((x/y) + (x%y!=0))

int main()
{
    std::cout << "LAB 3" << std::endl;

    std::vector<Registro> dados_entrada;
    std::string linha;

//    std::ifstream entrada("dataset.txt");  // Abre arquivo de entrada
    std::ifstream entrada("dataset-short.txt");  // Abre arquivo de entrada reduzido

    while (std::getline(entrada, linha))   // Le linha a linha
    {
        Registro reg(linha);         // Cria registro
        dados_entrada.push_back(reg);    // Coloca num vetor de registros
    }
    unsigned int N = dados_entrada.size();

    int M_EndA = 501;
    int M_EndF = 50;

    TabelaHash_EndAberto hash_buscalinear(M_EndA);
    TabelaHash_EndAberto hash_doublehashing(M_EndA);
    TabelaHash_EndFechado hash_chaining(M_EndF);
    TabelaHash_EndFechado hash_buckets(M_EndF, DIV_CEIL(N,M_EndF));
//    std::cout << "N " << N << " M " << M_EndF << " N/M " << DIV_CEIL(N,M_EndF) << std::endl;

    std::cout << "----------------------------------------------" <<std::endl;
    std::cout << "PARTE 1) INSERINDO ELEMENTOS NAS TABELAS HASH:" <<std::endl;

    for(unsigned int i=0; i<N; i++){
        bool sucesso;

        sucesso = hash_buscalinear.insereEABL(dados_entrada[i].getNome(),&dados_entrada[i]);
        std::cout << "Elemento (" << dados_entrada[i].getNome() << (sucesso?") inserido com sucesso":") NAO FOI inserido") << " na tabela Hash EABL" <<std::endl;

        sucesso = hash_doublehashing.insereDoubleHashing(dados_entrada[i].getNome(),&dados_entrada[i]);
        std::cout << "Elemento (" << dados_entrada[i].getNome() << (sucesso?") inserido com sucesso":") NAO FOI inserido") << " na tabela Hash EA Double Hashing" <<std::endl;

        sucesso = hash_chaining.insereChaining(dados_entrada[i].getNome(),&dados_entrada[i]);
        std::cout << "Elemento (" << dados_entrada[i].getNome() << (sucesso?") inserido com sucesso":") NAO FOI inserido") << " na tabela Hash EF Chaining" <<std::endl;


        sucesso = hash_buckets.insereBuckets(dados_entrada[i].getNome(),&dados_entrada[i]);
        std::cout << "Elemento (" << dados_entrada[i].getNome() << (sucesso?") inserido com sucesso":") NAO FOI inserido") << " na tabela Hash EF Buckets" <<std::endl;
    }
    std::cout << "Total de colisoes End Aberto BL: " << hash_buscalinear.colisoesOcorridas() << std::endl;
    std::cout << "Total de colisoes End Aberto DoubleHashing: " << hash_doublehashing.colisoesOcorridas() << std::endl;
    std::cout << "Total de colisoes End Fechado Chaining: " << hash_chaining.colisoesOcorridas() << std::endl;
    std::cout << "Total de colisoes End Fechado Buckets: " << hash_buckets.colisoesOcorridas() << std::endl;


    std::cout << "----------------------------------------------" <<std::endl;
    std::cout << "PARTE 2) REALIZANDO BUSCAS DE TODOS ELEMENTOS:" <<std::endl;

    for(unsigned int i=0; i<N; i++){
        Registro* r;



        r = hash_buscalinear.buscaEABL(dados_entrada[i].getNome());

        if(r==&dados_entrada[i])
            std::cout << "Encontrou registro (" << r->getNome() << ") na tabela Hash EABL" << std::endl;
        else
            std::cout << "NAO encontrou registro (" << dados_entrada[i].getNome() << ") na tabela Hash EABL" << std::endl;

        r = hash_doublehashing.buscaDoubleHashing(dados_entrada[i].getNome());
        if(r==&dados_entrada[i])
            std::cout << "Encontrou registro (" << r->getNome() << ") na tabela Hash EA Double Hashing" << std::endl;
        else
            std::cout << "NAO encontrou registro (" << dados_entrada[i].getNome() << ") na tabela Hash EA Double Hashing" << std::endl;

        r = hash_chaining.buscaChaining(dados_entrada[i].getNome());
        if(r==&dados_entrada[i])
            std::cout << "Encontrou registro (" << r->getNome() << ") na tabela Hash EF Chaining" << std::endl;
        else
            std::cout << "NAO encontrou registro (" << dados_entrada[i].getNome() << ") na tabela Hash EF Chaining" << std::endl;


        r = hash_buckets.buscaBuckets(dados_entrada[i].getNome());
        if(r==&dados_entrada[i])
            std::cout << "Encontrou registro (" << r->getNome() << ") na tabela Hash EF Buckets" << std::endl;
        else
            std::cout << "NAO encontrou registro (" << dados_entrada[i].getNome() << ") na tabela Hash EF Buckets" << std::endl;

    }

    std::cout << "---------------------------------------" <<std::endl;
    std::cout << "PARTE 3) REALIZANDO BUSCAS ESPECIFICAS:" <<std::endl;

    Registro *messi = hash_buscalinear.buscaEABL("Lionel Messi");
    Registro *cr7 = hash_doublehashing.buscaDoubleHashing("Cristiano Ronaldo");
    Registro *meninoNey = hash_chaining.buscaChaining("Neymar");
    Registro *lewa = hash_buckets.buscaBuckets("Robert Lewandowski");



    if(messi!=NULL)
        std::cout << "ACHOU: " << *messi << std::endl;
    else
        std::cout << "Nao achou Messi na Hash EABL" << std::endl;
    if(cr7!=NULL)
        std::cout << "ACHOU: " << *cr7 << std::endl;
    else
        std::cout << "Nao achou CR7 na Hash EA Double Hashing" << std::endl;

    if(meninoNey!=NULL)
        std::cout << "ACHOU: " << *meninoNey << std::endl;
    else
        std::cout << "Nao achou Neymar na Hash EF Chaining" << std::endl;
    if(lewa!=NULL)
        std::cout << "ACHOU: " << *lewa << std::endl;
    else
        std::cout << "Nao achou Lewandowski na Hash EF Buckets" << std::endl;

    return 0;
}
