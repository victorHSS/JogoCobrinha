#include "NormalGame.h"
#include "Game.h"

NormalGame::NormalGame(){
   cobra = NULL;
   maca = NULL;
   frutas = NULL;
   placar = NULL;
}

NormalGame::~NormalGame(){
   release();
}

void NormalGame::release(){
   delete cobra;
   delete maca;
   delete frutas;
   destroy_bitmap(gameOver);
   destroy_bitmap(start);
   destroy_bitmap(pausado);
   stop_midi();
}

void NormalGame::inicializa(){
   cobra = new Cobra();
   cobra->inicializa(3, 10,10);
   maca = new Fruta("maca");
   maca->inicializa();
   frutas = new Fruta((sortFruta()).c_str());
   frutas->inicializa();
   frutas->esconde();
   placar = new Placar();
   placar->inicializa();
   numMacaComida = -1;
   totalMaca     = 0;
   passos        = 0;
   isFruta       = false;
   estado = START;
   gameOver   = load_bitmap("imgs/gameOver.bmp",NULL);
   underScene = load_bitmap("imgs/underGame.bmp",NULL);
   start      = load_bitmap("imgs/pressStart.bmp",NULL);
   pausado    = load_bitmap("imgs/pausa.bmp",NULL);
   pegaFruta  = load_wav("musicas/pegaFruta.wav");
   perdeFruta = load_wav("musicas/perdeFruta.wav");
   morreu  = load_wav("musicas/morreu.wav");
   fundoMusical = load_midi("musicas/fundoNormalGame.mid");
   endGame = load_midi("musicas/gameOver.mid");
}

void NormalGame::execute(){
     switch (estado) {
        case START: if(keypressed()) estado = JOGANDO; play_midi(fundoMusical,1);break;   
        case JOGANDO: normal(); break;
        case PAUSADO: if (key[KEY_ENTER]) estado = JOGANDO; break;
        case GAMEOVER: {
           if (keypressed() && key[KEY_ENTER]){clear_keybuf();rest(200);prGame->setCena(0);} 
           break;
        }
     }
}

string NormalGame::sortFruta(){
   string sortF;    
   switch (rand()%8){
         case 0: sortF = "pera";break;
         case 1: sortF = "morango";break;
         case 2: sortF = "melancia";break;
         case 3: sortF = "banana";break;
         case 4: sortF = "uva";break;
         case 5: sortF = "laranja";break;
         case 6: sortF = "mamao";break;
         case 7: sortF = "abacaxi";break;
      }
   return sortF;
}

bool NormalGame::contato(Fruta *fruta){
   return cobra->contatoCabeca(fruta->getx(),fruta->gety()) || cobra->contatoCorpo(fruta->getx(),fruta->gety());
}

void NormalGame::normal(){
   if (key[KEY_LEFT])       cobra->esquerda();
   else if (key[KEY_RIGHT]) cobra->direita();
   else if (key[KEY_UP])    cobra->cima();
   else if (key[KEY_DOWN])  cobra->baixo();
   if (key[KEY_ENTER]) estado = PAUSADO;
   if (key[KEY_ESC]) {
      estado = GAMEOVER;
      stop_midi();
      play_midi(endGame,1);
   }
   cobra->execute();
   if (cobra->contatoCabeca(maca->getx(),maca->gety())){
      cobra->comeFruta();
      do {
         maca->sort();
      } while (contato(maca));
      placar->setPontos(10);
      numMacaComida = (numMacaComida + 1)%5;
      totalMaca++;
      play_sample(pegaFruta,255,90,1000,0);
   }
   
   if ((numMacaComida==4) && (!isFruta)){
      isFruta = true;
      passos  = 30;
      frutas->setFruta((sortFruta()).c_str());
      placar->setFruta(frutas->getFruta(), passos);
      do {
         frutas->sort();
      } while (contato(frutas));
   }
   
   if (isFruta) {
      if (cobra->contatoCabeca(frutas->getx(),frutas->gety())){
         cobra->comeFruta();                                           
         frutas->esconde();
         placar->setPontos(20);
         placar->pegou();
         isFruta = false;
         numMacaComida = -1;
         play_sample(pegaFruta,255,90,1000,0);
      }else {passos--;if (placar->isFruta()) placar->decrementa();}
      
      if (passos==0) {
        frutas->esconde();
        placar->pegou();
        play_sample(perdeFruta,255,90,1000,0);
        isFruta = false;
        numMacaComida = -1;
      }
       
   }
   
   if (cobra->selfShock()) {
      estado = GAMEOVER;
      stop_midi();
      play_sample(morreu,255,90,1000,0);
      play_midi(endGame,1);
   }
}


void NormalGame::update(){
   blit(underScene,backbuffer,0,0,0,0,underScene->w,underScene->h);
   maca->update();
   frutas->update();
   cobra->update();
   placar->update();
   if (estado==GAMEOVER) draw_sprite(backbuffer,gameOver,((TELAW-TAMSCORE)-gameOver->w)/2,(TELAH-gameOver->h)/2);
   else if(estado==START) draw_sprite(backbuffer,start,((TELAW-TAMSCORE)-start->w)/2,(TELAH-start->h)/2);
   else if(estado==PAUSADO) draw_sprite(backbuffer,pausado,((TELAW-TAMSCORE)-pausado->w)/2,(TELAH-pausado->h)/2);
}
