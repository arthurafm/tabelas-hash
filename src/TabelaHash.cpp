#include "../include/TabelaHash.h"

#include <iostream>

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

TabelaHash_EndAberto::TabelaHash_EndAberto(unsigned int m):
M(m)
{
    tabela.resize(M);
    for(unsigned int i=0;i<M;i++)
    {
        tabela[i].ocupado=false;
        tabela[i].registro=NULL;
    }

    totalColisoes=0;
}

TabelaHash_EndFechado::TabelaHash_EndFechado(unsigned int m, unsigned int t):
M(m), TamanhoBucket(t)
{
    tabelaChaining.resize(M);

    tabelaBuckets.resize(M);
    for(unsigned int i=0;i<M; i++)
        tabelaBuckets[i].resize(TamanhoBucket);

    totalColisoes=0;
}

TabelaHash_EndAberto::~TabelaHash_EndAberto()
{

}

TabelaHash_EndFechado::~TabelaHash_EndFechado()
{

}




////////////////////////////
/// ENDERECAMENTO ABERTO ///
////////////////////////////

bool TabelaHash_EndAberto::insereEABL(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento aberto com busca linear
    int e = -1, marca = -1;
    int endc = 0; // Endere�o inicial calculado
    // Fun��o hash para strings encontrada em Algorithms 4th Ed.
    for(unsigned int i = 0; i < chave.size(); i++){
        endc = (31 * endc + chave[i]) % tabela.size();
    }
    int end_l = endc;
    do{
        // Se a posi��o na tabela j� estiver ocupada
        if(tabela[end_l].ocupado == true){
            // Se a chave j� existir na tabela
            if(tabela[end_l].chave == chave){
                e = end_l;
                inseriu = true;
                break;
            }
            else{
                // Passa para o pr�ximo
                colisoes++;
                end_l++;
                if((unsigned int)end_l == tabela.size()){
                    end_l -= tabela.size();
                }
                if(end_l == endc){
                    break;
                }
            }
        }
        // Se a chave estiver livre
        else{
            if(marca == -1){
                marca = end_l;
                break;
            }
        }
    }while((end_l != endc) || (e == -1));

    // Posiciona na tabela
    if((e == -1) && (marca != -1)){
        tabela[marca].chave = chave;
        tabela[marca].ocupado = true;
        tabela[marca].registro = reg;
        inseriu = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndAberto::buscaEABL(std::string chave)
{
    Registro* r = NULL;

    int e = -1;
    int end_c = 0;
    // Calcula o hash
    for (unsigned int i = 0; i < chave.size(); i++)
        end_c = (31*end_c + chave[i]) % tabela.size();
    int end_l = end_c;
    do{
        // Procura a chave
        if (tabela[end_l].ocupado && tabela[end_l].chave == chave)
        {
            e = end_l;
            break;
        }
        // N�o achou
        else
        {
            // Busca linearmente
            end_l = end_l + 1;
            // Faz a tabela ser encadeada
            if((unsigned int)end_l == tabela.size()){
                end_l -= tabela.size();
            }
            // Se voltar pro in�cio, n�o h�
            if(end_l == end_c){
                break;
            }
        }
    } while (end_c != end_l || e == -1);
    // N�o achou
    if (e == -1)
        return NULL;
    // Achou
    else
    {
        r = tabela[e].registro;
        return r;
    }
}

bool TabelaHash_EndAberto::insereDoubleHashing(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    int e = -1, marca = -1, j = 0;
    int endc = 0; // Endere�o inicial calculado
    // Fun��o hash para strings encontrada em Algorithms 4th Ed.
    for(unsigned int i = 0; i < chave.size(); i++){
        endc = (31 * endc + chave[i]) % tabela.size();
    }
    int end_l = endc;
    do{
        // Se a posi��o na tabela j� estiver ocupada
        if(tabela[end_l].ocupado == true){
            // Se a chave j� existir na tabela
            if(tabela[end_l].chave == chave){
                e = end_l;
                inseriu = true;
                break;
            }
            else{
                // Passa para o pr�ximo
                colisoes++;
                j++;
                // Calcula novamente a fun��o hash
                for(unsigned int i = 0; i < chave.size(); i++){
                    end_l = (endc + 23 * j * end_l + chave[i]) % tabela.size();
                }
                if((unsigned int)end_l >= tabela.size()){
                    end_l -= tabela.size();
                }
                if((end_l == endc) && ((unsigned int)j > tabela.size())){
                    break;
                }
            }
        }
        // Se a chave estiver livre
        else{
            if(marca == -1){
                marca = end_l;
                break;
            }
        }
    }while((end_l != endc) || (e == -1));
    // Posiciona na tabela
    if((e == -1) && (marca != -1)){
        tabela[marca].chave = chave;
        tabela[marca].ocupado = true;
        tabela[marca].registro = reg;
        inseriu = true;
    }

    totalColisoes += colisoes;
    return inseriu;
}

Registro* TabelaHash_EndAberto::buscaDoubleHashing(std::string chave)
{
    Registro* r = NULL;

    int e = -1;
    int end_c = 0;
    int j = 0;
    // Calcula hash
    for (unsigned int i = 0; i < chave.size(); i++)
        end_c = (31*end_c + chave[i]) % tabela.size();
    int end_l = end_c;

    do{
        // Se encontrar a chave
        if (tabela[end_l].ocupado && tabela[end_l].chave == chave)
        {
            e = end_l;
            break;
        }
        else
        {
            j++;
            // Calcula novamente a fun��o hash
            for(unsigned int i = 0; i < chave.size(); i++){
                end_l = (end_c + 23 * j * end_l + chave[i]) % tabela.size();
            }
            if((unsigned int)end_l >= tabela.size()){
                end_l -= tabela.size();
            }
            if((end_l == end_c) && ((unsigned int)j > tabela.size())){
                break;
            }
        }
    } while ((end_c != end_l) || (e == -1));

    // N�o achou
    if (e == -1)
        return NULL;
    // Achou
    else
    {
        r = tabela[e].registro;
        return r;
    }
}

int TabelaHash_EndAberto::colisoesOcorridas()
{
    return totalColisoes;
}

/////////////////////////////
/// ENDERECAMENTO FECHADO ///
/////////////////////////////

bool TabelaHash_EndFechado::insereChaining(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento fechado com encadeamento (chaining)

    int e = -1;
    int endc = 0; // Endere�o inicial calculado
    // Cria��o de buffer para inser��o
    Elemento buffer;
    buffer.chave = chave;
    buffer.ocupado = true;
    buffer.registro = reg;
    // Fun��o hash para strings encontrada em Algorithms 4th Ed.
    for(unsigned int i = 0; i < chave.size(); i++){
        endc = (31 * endc + chave[i]) % tabelaChaining.size();
    }

    // Se a lista n�o for vazia
    if(tabelaChaining[endc].empty() == false){
        for(std::list<Elemento>::iterator it = tabelaChaining[endc].begin(); it != tabelaChaining[endc].end(); ++it){
            // Se encontrar o elemento a inserir, sai do la�o
            if(buffer.chave == it->chave){
                e = 0;
                break;
            }
            // Caso contr�rio, colidiu
            else{
                colisoes++;
            }
        }
    }
    //Se n�o tinha antes na lista, insere
    if(e == -1){
        tabelaChaining[endc].push_back(buffer);
    }

    // Sempre � inserido, uma vez que o tamanho das listas � indeterminado
    inseriu = true;
    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndFechado::buscaChaining(std::string chave)
{
    Registro* r = NULL;

    int end_c = 0;
    // Calcula o hash
    for (unsigned int i = 0; i < chave.size(); i++)
        end_c = (31*end_c + chave[i]) % tabelaChaining.size();

    int end_l = end_c;

    // Posi��o hash vazia
    if (tabelaChaining[end_l].empty())
    {
        return r;
    }
    else
    {
        std::list<Elemento>::iterator i = tabelaChaining[end_l].begin();
        if (i->chave == chave)
        {
            r = i->registro;
            return r;
        }
        // Leitura de elementos na lista
        while (i != tabelaChaining[end_l].end())
        {
            // Achou
            if (i->chave == chave)
            {
                r = i->registro;
                return r;
            }
            i++;
        }
    }
    return r;
}

bool TabelaHash_EndFechado::insereBuckets(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento fechado com blocos de tamanho fixo (buckets) e area de overflow

    unsigned int i;
    int endc = 0; // Endere�o inicial calculado
    // Cria��o de buffer para inser��o
    Elemento buffer;
    buffer.chave = chave;
    buffer.ocupado = true;
    buffer.registro = reg;
    // Fun��o hash para strings encontrada em Algorithms 4th Ed.
    for(unsigned int i = 0; i < chave.size(); i++){
        endc = (31 * endc + chave[i]) % tabelaBuckets.size();
    }

    // Se a lista n�o for vazia
    if(tabelaBuckets[endc][0].ocupado == true){
        for(i = 0; i < tabelaBuckets[endc].size(); i++){
            // J� est� inserido
            if(tabelaBuckets[endc][i].chave == buffer.chave){
                inseriu = true;
                break;
            }
            else{
                colisoes++;
                // Encontrou espa�o vazio antes do fim do bucket
                if(tabelaBuckets[endc][i].ocupado == false){
                    tabelaBuckets[endc][i] = buffer;
                    inseriu = true;
                    break;
                }
            }
        }
        // Se n�o houver espa�o no bucket, joga no overflow
        if(i == tabelaBuckets[endc].size()){
            overflow.push_back(buffer);
        }
    }
    // Se a lista for vazia
    else{
        tabelaBuckets[endc][0] = buffer;
        inseriu = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndFechado::buscaBuckets(std::string chave)
{
    Registro* r = NULL;

    int end_c = 0;
    // Calcula o hash
    for (unsigned int i = 0; i < chave.size(); i++)
        end_c = (31*end_c + chave[i]) % tabelaBuckets.size();

    int end_l = end_c;

    std::vector<Elemento>::iterator i = tabelaBuckets[end_l].begin();
    // Achou a chave
    if (i->chave == chave)
    {
        r = i->registro;
        return r;
    }
    // Enquanto nao chegar no fim
    while (i != tabelaBuckets[end_l].end())
    {
        // Achou a chave
        if (i->chave == chave)
        {
            r = i->registro;
            return r;
        }
        i++;
    }
    return r;
}

int TabelaHash_EndFechado::colisoesOcorridas()
{
    return totalColisoes;
}
