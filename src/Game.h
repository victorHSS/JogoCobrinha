#ifndef _GAME_H_
#define _GAME_H_

#include "Global.h"
#include "vector"
#include "Cenario.h"
#include "Apresentacao.h"
#include "NormalGame.h"

class Game: public Object{
   vector <Cenario*> cenas;
   int numCenaAtual;
public:
   enum ESTADO{
      RUN,
      ENDED
   };
private:
   ESTADO estado;
public:
    Game();
    ~Game();   
    void inicializa();
    void execute();
    void update();
    void release();  
    void loop(); 
    void addCena(Cenario *cena);
    void setCena(int numCena);
    void setEstado(ESTADO estado);
    void init();
    void deinit();
};

#endif
