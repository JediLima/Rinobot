#ifndef _ROBOT_H_
#define _ROBOT_H_
//
#include <iostream>
using namespace std;
struct Estado
{
  float x,y;
  int theta;
};
struct velRoda
{
    float Esquerda, Direita;
};
class Robot
{
  protected:
    int numeroMotores;
    int numeroSensores;
    float bateria;
    Estado orientacao;

  public:
    Robot();
    int getNumeroMotores() { return numeroMotores; };
    int getNumeroSensores() { return numeroSensores; };
    int getNivelBateria() { return bateria; };
    Estado getOrientacao() { return orientacao; };
    void setOrientacao(Estado r) { orientacao=r; };
    void setNivelBateria(float b) { bateria=b; };
    void setNumeroMotores(int m) { numeroMotores=m; };
    void setNumeroSensores(int s) { numeroSensores=s; };
    void Locomocao(velRoda);
};
#endif


