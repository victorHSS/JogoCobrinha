#ifndef _COBRA_H
#define _COBRA_H

#include "Global.h"
#include "Object.h"

class Cobra: public Object{
   int tam;
   enum direcao{
      ESQUERDA,
      DIREITA,
      CIMA,
      BAIXO
   };
   struct corpo{
      int posx;
      int posy;
      direcao dir;
      corpo *prox;
      corpo *ant;   
   };
   corpo *pCabeca,*pRabo;
   direcao dir;
   BITMAP *bRaboEsquerda, *bRaboDireita,*bRaboCima, *bRaboBaixo;
   BITMAP *bCorpoHorizontal, *bCorpoVertical;
   BITMAP *bCabecaDireita, *bCabecaEsquerda, *bCabecaCima, *bCabecaBaixo;
   BITMAP *bCorpoCurvaBD, *bCorpoCurvaCE, *bCorpoCurvaDC, *bCorpoCurvaEB;
public:
   Cobra();
   ~Cobra();    
   void inicializa(int tam, int posx, int posy);
   void execute();
   void update();
   void esquerda();
   void direita();
   void cima();
   void baixo();
   bool contatoCabeca(int posx, int posy);
   bool contatoCorpo(int posx, int posy);
   bool selfShock();
   void comeFruta(); 
private:
   void release();     
   void cresce();
};
#endif
