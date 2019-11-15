#include "Robot.h"
#include <math.h>
#include <iostream>

Robot::Robot()
{
    numeroMotores=0;
    numeroSensores=0;
    bateria=0;
    orientacao.x=0;
    orientacao.y=0;
    orientacao.theta=0;
}

void Robot::Locomocao(velRoda v)
{
    if((v.Esquerda>0)&&(v.Direita>0))
    {
        cout<<"Robo andando para frente."<<endl;
    }
    if((v.Esquerda<0)&&(v.Direita<0))
    {
        cout<<"Robo andando para tras."<<endl;
    }
    if(v.Esquerda>v.Direita)
    {
        cout<<"Robo fazendo curva pra direita."<<endl;
    }
    if(v.Esquerda<v.Direita)
    {
        cout<<"Robo fazendo curva para esquerda."<<endl;
    }
}

