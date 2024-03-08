#ifndef _PLACAR_H_
#define _PLACAR_H_

#include "Object.h"
#include "Global.h"
#include <string>
#include <cstring>

class Placar: public Object{
   int pontos;
   int passos;
   string strPontos;
   string strPassos;
   BITMAP *numeros;
   BITMAP *fruta;
   bool temFruta;
public:
   Placar();
   ~Placar();
   void inicializa();
   void setPontos(int pontos);
   void update();
   void strToImg(const char *str, int x, int y);
   void setFruta(BITMAP *fruta, int passos);
   bool isFruta();
   void decrementa();
   void pegou();
   string intToStr(int num);
   void release();
};

#endif
