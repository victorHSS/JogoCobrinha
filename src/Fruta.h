#ifndef _FRUTA_H_
#define _FRUTA_H_

#include "Global.h"
#include "Object.h"
#include "string"

class Fruta: public Object{
   BITMAP *fruta;
   int posx,posy;
   bool comida;
   bool escondida;
public:
   Fruta(const char *type);
   ~Fruta();
   void inicializa();
   void sort();
   bool samePlace(Fruta &fruit);
   int  getx() const;
   int  gety() const;
   void setFruta(const char *type);
   BITMAP *getFruta();
   void esconde();
   void update();
private:
   void release();
};

#endif
