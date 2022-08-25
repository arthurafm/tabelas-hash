#include "../include/Registro.h"

#include <iostream>
#include <sstream>

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Registro::Registro(std::string linha)
{
    std::vector<std::string> row;
    std::string word;

    std::istringstream iss(linha);
    while (getline(iss, word, '\t')) {
        row.push_back(word);
    }

    nome = row[0];

    posicao=GOL;

//    posicao = row[1];
    if(row[1].compare("Goleiro")==0)
        posicao = GOL;
    else if(row[1].compare("Zagueiro")==0)
        posicao = ZAG;
    else if(row[1].compare("Lateral Esq.")==0)
        posicao = LESQ;
    else if(row[1].compare("Lateral Dir.")==0)
        posicao = LDIR;
    else if(row[1].compare("Volante")==0)
        posicao = VOL;
    else if(row[1].compare("Meia Esquerda")==0)
        posicao = MESQ;
    else if(row[1].compare("Meia Central")==0)
        posicao = MCEN;
    else if(row[1].compare("Meia Direita")==0)
        posicao = MDIR;
    else if(row[1].compare("Meia Ofensivo")==0)
        posicao = MOFE;
    else if(row[1].compare("Ponta Esquerda")==0)
        posicao = PESQ;
    else if(row[1].compare("Ponta Direita")==0)
        posicao = PDIR;
     else if(row[1].compare("Seg. Atacante")==0)
        posicao = SEGATA;
    else if(row[1].compare("Centroavante")==0)
        posicao = CA;
    else
        std::cout << "AQUI";

    idade = std::stoi(row[2]);
    nacionalidade = row[3];
    clube = row[4];
    valor = std::stof(row[5]);
}

Registro::~Registro()
{
    //destrutor
}

/// GET

std::string Registro::getNome()
{
    return nome;
}

std::string Registro::getNacionalidade()
{
    return nacionalidade;
}

std::string Registro::getClube()
{
    return clube;
}

POSICAO Registro::getPosicao()
{
    return posicao;
}

int Registro::getIdade()
{
    return idade;
}

float Registro::getValor()
{
    return valor;
}

/// IMPRESSAO
std::vector<std::string> strPOSICAO = {"GOL", "ZAG", "LESQ", "LDIR", "VOL", "MESQ", "MCEN", "MDIR", "MOFE", "PESQ", "PDIR", "2ATA", "CA"};

std::ostream& operator<<(std::ostream& os, const Registro& reg)
{
    os << "-> " << reg.nome << " | " << strPOSICAO[reg.posicao] << " | clube: " << reg.clube << std::endl
    << "   idade: " << reg.idade << " | nac: " << reg.nacionalidade << " | valor " << reg.valor << " mi EUR";
    return os;
}
