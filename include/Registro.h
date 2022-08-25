#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <ostream>
#include <vector>

enum POSICAO { GOL, ZAG, LESQ, LDIR, VOL, MESQ, MCEN, MDIR, MOFE, PESQ, PDIR, SEGATA, CA};

class Registro
{
    public: // elementos que podem ser acessados externamente

        Registro(std::string str); // construtor

        ~Registro(); // destrutor

        std::string getNome();
        std::string getNacionalidade();
        std::string getClube();
        POSICAO getPosicao();
        int getIdade();
        float getValor();

        // sobrecarrega operador de escrita para permitir impressao via streams (i.e. std::cout << registro)
        friend std::ostream& operator<<(std::ostream& os, const Registro& reg);

    private: // elementos que somente podem ser acessados dentro da classe

        std::string nome;
        std::string nacionalidade;
        std::string clube;
        POSICAO posicao;
        float valor;
        int idade;
};

#endif // REGISTRO_H
