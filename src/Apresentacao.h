#ifndef _APRESENTACAO_H_
#define _APRESENTACAO_H_

#include "Cenario.h"

class Apresentacao: public Cenario{
   BITMAP *menu;
   BITMAP *seta;
   SAMPLE *mudaSeta; 
   SAMPLE *decisao;
   int posy;
public:
   Apresentacao();
   ~Apresentacao();
   void inicializa();
   void execute();
   void update();
   void release();
};

#endif
