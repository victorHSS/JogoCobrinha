#ifndef _CENARIO_H_
#define _CENARIO_H_

#include "Global.h"
#include "Object.h"

class Game;//protótipo

class Cenario: public Object{
public:
   BITMAP *underScene;    
   MIDI *fundoMusical;
   Game *prGame;
   Cenario();
   ~Cenario();
   virtual void inicializa() = 0;
   virtual void execute() = 0;
   virtual void update();
   void release();
};

#endif
