#ifndef VSSS_H
#define VSSS_H
#include "Robot.h"
#include <iostream>

class vsss:public Robot
{
    private:
        Estado posicaoDaBola;
        bool comunicacao;
        char funcao;
        velRoda v;
        int alfa;//angulo da reta que liga o robo e a bola
    public:
        vsss(float,int,Estado,bool,char,velRoda);
        void setCominicacao(bool c) { comunicacao=c; }; //true para comunicacao conectada e false para comunicacao desconectada
        void setFuncao(char f) { funcao=f; }; //"A" para atacante, "Z" para zagueiro e "G" para goleiro
        void setV(velRoda vel) { v=vel; };
        void setAlfa(Estado,Estado);
        void getComunicacao();
        string getFuncao();
        velRoda getV() { return v; };
        void setPosicaoDaBola(Estado);
        Estado getPosicaoDaBola() { return posicaoDaBola; };
        int getAlfa() { return alfa; };
        void girar(bool);
        void ajustarPosicao(Estado);
        void andarAteABola(Estado,Estado);
        void GOL(Estado, Estado);
        void ZAG(Estado, Estado);
        void ATK(Estado, Estado);

};

#endif // VSSS_H
