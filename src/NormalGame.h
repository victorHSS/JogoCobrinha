#ifndef _NORMALGAME_H_
#define _NORMALGAME_H_

#include "Cenario.h"
#include "Cobra.h"
#include "Fruta.h"
#include "Placar.h"
#include "string"

class NormalGame: public Cenario{
   Cobra *cobra;
   Fruta *maca;
   Fruta *frutas;
   Placar *placar;
   SAMPLE *pegaFruta;
   SAMPLE *perdeFruta;
   SAMPLE *morreu;
   MIDI *endGame;
   BITMAP *gameOver;
   BITMAP *start;
   BITMAP *pausado;
   int  numMacaComida;
   int  totalMaca;
   int  passos;
   bool isFruta;
   enum ESTADO{
      START,  
      JOGANDO,
      PAUSADO,
      GAMEOVER
   };
   ESTADO estado;
public:
   NormalGame();
   ~NormalGame();
   void inicializa();
   void execute();
   void update();
   void release();
   bool contato(Fruta *fruta);
   void normal();
   void end();
   string sortFruta();
};

#endif
