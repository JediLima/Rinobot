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

void vsss::setPosicaoDaBola(Estado b)//recebe a posi��o escolhida pelo usuario e altera a posi��o da vari�vel na classe
{
    posicaoDaBola.x=b.x;
    posicaoDaBola.y=b.y;
}

void vsss::setAlfa(Estado r, Estado b)//recebe r(orienta��o atual do rob�) e b(posi��o inicial da bola) e altera o valor de alfa(angulo que o rob� precisa estar virado para estar direcionado para a bola)
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

void vsss::girar(bool j)//j=true girar no sentido anti-hor�rio ou j=false para girar no sentido hor�rio
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

void vsss::ajustarPosicao(Estado orientacao)//recebe orienta��o atual do robo e chama a fun��o girar escolhendo o sentido de rota��o comparando a posi��o ideal (alfa) e a posi��o atual do rob� (orientacao.theta)
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
        if(orientacao.theta<0)//ajuste para theta n�o ficar negativo
        {
            orientacao.theta=orientacao.theta+360;
        }
        else if(orientacao.theta>=360)//ajuste para theta n�o ficar maior que 360 graus
        {
            orientacao.theta=orientacao.theta-360;
        }
        cout<<"Novo theta: "<<orientacao.theta<<endl;
    }
    setOrientacao(orientacao);//atualiza a vari�vel orientacao do rob� depois do ajuste j� terminado
    cout<<"O robo esta direcionado para a meta."<<endl;
}

void vsss::andarAteABola(Estado r,Estado b)//recebe a posi��o atual do rob� e a posi��o da bola
{
    float x=sqrt(((b.x-r.x)*(b.x-r.x))+((b.y-r.y)*(b.y-r.y)));
    int d=round(x);//dist�ncia entre o rob� e a bola

    if(d!=0)
    {
        setAlfa(r,b);//chama a fun��o que vai calcular o angulo ideal (alfa)
        cout<<"Alfa= "<<getAlfa()<<endl;
        ajustarPosicao(r);//chama a fun��o que vai ajustar o angulo theta atual do rob� para o angulo ideal alfa
    }

    while(d!=0)//faz o rob� andar at� que a distancia entre ele e a bola seja nula (e exibe o tipo de movimento na tela)
    {
        cout<<"O robo esta a "<<d<<" unidades da meta."<<endl;
        velRoda v;
        v.Direita=100;
        v.Esquerda=100;
        Locomocao(v);
        d--;
    }
    Estado u;//u � uma vari�vel auxiliar usada para atualizar a posi��o do rob� colocando ele nos mesmos x e y da bola (j� que a distancia entre os dois chegou a zero)
    u.x=b.x;
    u.y=b.y;
    u.theta=getOrientacao().theta;//u.theta � definido como o angulo original da orienta��o para que o theta do rob� seja mantido
    setOrientacao(u);//atualiza a orienta��o depois de ter andado at� a bola

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

