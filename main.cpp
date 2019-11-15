#include <iostream>
#include "Robot.h"
#include "VSSS.h"

using namespace std;

int main()
{
    char p;
    Estado r,b,centroidATK,centroidDEF,centroidMEI; //Estado � struct
    centroidATK.x=160;
    centroidATK.y=65;
    centroidDEF.x=10;
    centroidDEF.y=65;
    centroidMEI.x=85;
    centroidMEI.y=65;
    velRoda vel; //velRoda � struct
    vel.Esquerda=50;// "vel" � usado para definir as velocidades das rodas
    vel.Direita=50;

    cout<<"______________________________________________________________________"<<endl<<endl;
    cout<<"Posicao inicial da bola ->  X: ";
    cin>>b.x;
    cout<<"                            Y: ";
    cin>>b.y;
    cout<<"______________________________________________________________________"<<endl<<endl;


    cout<<"______________________________________________________________________"<<endl<<endl;
    cout<<"Posicao inicial do robo ->  X: ";
    cin>>r.x;
    cout<<"                            Y: ";
    cin>>r.y;
    cout<<"      Theta(de 0 a 360 graus): ";
    cin>>r.theta;


    cout<<"Funcao do robo -> ";
    cin>>p;
    cout<<"______________________________________________________________________"<<endl<<endl;

    vsss habib(100,2,r,true,p,vel);//n�vel bateria (de 0 a 100) | numero de motores | r: struct Estado com a posi��o inicial do rob� | conex�o da comunica��o | fun��o | velocidade
    habib.setPosicaoDaBola(b);

    cout<<"______________________________________________________________________"<<endl<<endl;

    if (p=='A')
    {
        habib.ATK(r,b);
        habib.andarAteABola(r,centroidATK);
    }
    else
    {
        if(p=='Z')
        {
            habib.ZAG(r,b);
            habib.andarAteABola(r,centroidMEI);

        }
        else
        {
            if(p=='G')
            {
                if(r.x!=10){
                habib.andarAteABola(r,centroidDEF);
                }

                habib.GOL(r,b);

            }
            else
            {
                cout<<"Posicao do Robo nao reconhecida"<<endl;
            }
        }
    }

    cout<<"______________________________________________________________________"<<endl<<endl;
    cout<<"Orientacao final-> Theta:"<<habib.getOrientacao().theta<<"  X:"<<habib.getOrientacao().x<<" unidades  Y:"<<habib.getOrientacao().y<<" unidades"<<endl;
    return 0;
}
