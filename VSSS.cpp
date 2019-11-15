#include "Robot.h"
#include "VSSS.h"
#include <math.h>
#include <iostream>

vsss::vsss(float n,int m, Estado r, bool c, char f, velRoda vel)
{
    bateria = n;
    numeroMotores = m;
    orientacao = r;
    comunicacao = c;
    funcao = f;
    v = vel;
}

void vsss::getComunicacao()
{
    cout<<"Counicacao: ";
    if(comunicacao)
    {
        cout<<"conectada."<<endl;
    }
    else
    {
        cout<<"desconectada."<<endl;
    }
}
string vsss::getFuncao()
{
    if(funcao=='A')
    {
        return " atacante.";
    }
    if(funcao=='Z')
    {
        return " zagueiro.";
    }
    if(funcao=='G')
    {
        return " goleiro.";
    }
    else
    {
        return " invalida.";
    }
}

void vsss::setPosicaoDaBola(Estado b)//recebe a posição escolhida pelo usuario e altera a posição da variável na classe
{
    posicaoDaBola.x=b.x;
    posicaoDaBola.y=b.y;
}

void vsss::setAlfa(Estado r, Estado b)//recebe r(orientação atual do robô) e b(posição inicial da bola) e altera o valor de alfa(angulo que o robô precisa estar virado para estar direcionado para a bola)
{
    float x=((atan((b.y-r.y)/(b.x-r.x)))*180/3.14159265359);
    if(b.x<r.x)// segundo quadrante e terceiro quadrante
    {
        alfa=round(x)+180;
    }
    else if(b.y>=r.y) // primeiro quadrante
    {
        alfa=round(x);
    }
    else // quarto quadrante
    {
        alfa=round(x)+360;
    }
}

void vsss::girar(bool j)//j=true girar no sentido anti-horário ou j=false para girar no sentido horário
{
    velRoda g;
    if(j)
    {
        g.Direita=100;
        g.Esquerda=-100;
        setV(g);
        cout<<"Robo girando no sentido anti-horario."<<endl;
        cout<<"Velocidade roda esquerda: "<<getV().Esquerda<<"\tVelocidade roda direita: "<<getV().Direita<<endl;
    }
    else
    {
        g.Direita=-100;
        g.Esquerda=100;
        setV(g);
        cout<<"Robo girando no sentido horario."<<endl;
        cout<<"Velocidade roda esquerda: "<<getV().Esquerda<<"\tVelocidade roda direita: "<<getV().Direita<<endl;
    }
}

void vsss::ajustarPosicao(Estado orientacao)//recebe orientação atual do robo e chama a função girar escolhendo o sentido de rotação comparando a posição ideal (alfa) e a posição atual do robô (orientacao.theta)
{
    while(orientacao.theta!=alfa)
    {

        if(alfa>orientacao.theta)
        {
            if((alfa-orientacao.theta)<=180)
            {
                girar(true);
                orientacao.theta++;
            }
            else
            {
                orientacao.theta--;
                girar(false);
            }
        }
        else
        {
            if((orientacao.theta-alfa)<=180)
            {
                girar(false);
                orientacao.theta--;
            }
            else
            {
                girar(true);
                orientacao.theta++;
            }
        }
        if(orientacao.theta<0)//ajuste para theta não ficar negativo
        {
            orientacao.theta=orientacao.theta+360;
        }
        else if(orientacao.theta>=360)//ajuste para theta não ficar maior que 360 graus
        {
            orientacao.theta=orientacao.theta-360;
        }
        cout<<"Novo theta: "<<orientacao.theta<<endl;
    }
    setOrientacao(orientacao);//atualiza a variável orientacao do robô depois do ajuste já terminado
    cout<<"O robo esta direcionado para a meta."<<endl;
}

void vsss::andarAteABola(Estado r,Estado b)//recebe a posição atual do robô e a posição da bola
{
    float x=sqrt(((b.x-r.x)*(b.x-r.x))+((b.y-r.y)*(b.y-r.y)));
    int d=round(x);//distância entre o robô e a bola

    if(d!=0)
    {
        setAlfa(r,b);//chama a função que vai calcular o angulo ideal (alfa)
        cout<<"Alfa= "<<getAlfa()<<endl;
        ajustarPosicao(r);//chama a função que vai ajustar o angulo theta atual do robô para o angulo ideal alfa
    }

    while(d!=0)//faz o robô andar até que a distancia entre ele e a bola seja nula (e exibe o tipo de movimento na tela)
    {
        cout<<"O robo esta a "<<d<<" unidades da meta."<<endl;
        velRoda v;
        v.Direita=100;
        v.Esquerda=100;
        Locomocao(v);
        d--;
    }
    Estado u;//u é uma variável auxiliar usada para atualizar a posição do robô colocando ele nos mesmos x e y da bola (já que a distancia entre os dois chegou a zero)
    u.x=b.x;
    u.y=b.y;
    u.theta=getOrientacao().theta;//u.theta é definido como o angulo original da orientação para que o theta do robô seja mantido
    setOrientacao(u);//atualiza a orientação depois de ter andado até a bola

    cout<<"O robo chegou a meta estabelecida!"<<endl;
}

void vsss::GOL(Estado r, Estado b)
{
    Estado metagol;
    metagol.x=10;
    metagol.y=b.y;
    if((b.y==r.y)&&(b.x==r.x)){
       girar(true);
    }
    else{
    if(b.y>85)
    {
        metagol.y=85;
    }
    else
    {
        if(b.y<45)
        {
            metagol.y=45;
        }
    }
    andarAteABola(r,metagol);
}
}

void vsss::ZAG(Estado r, Estado b)
{
    Estado metazag;
    if(b.x<85)
    {
        metazag.x=b.x;
        metazag.y=b.y;
    }
    else
    {
        if(b.x>=85)
        {
            metazag.x=r.x;
            metazag.y=b.y;
        }
    }
    andarAteABola(r,metazag);

}

void vsss::ATK(Estado r, Estado b)
{
    Estado metaatk;
    if(b.x<85)
    {
        metaatk.x=r.x;
        metaatk.y=b.y;
    }
    else
    {
        if(b.x>=85)
        {
            metaatk.x=b.x;
            metaatk.y=b.y;
        }
    }
    andarAteABola(r,metaatk);

}

