#include "Apresentacao.h"
#include "Game.h"

Apresentacao::Apresentacao(){
   posy = 0;
}

Apresentacao::~Apresentacao(){
   release();
}

void Apresentacao::release(){
   stop_midi();
   destroy_bitmap(menu);
   destroy_bitmap(seta);
}

void Apresentacao::inicializa(){
   underScene = load_bitmap("../imgs/StartGame.bmp",NULL);
   menu = load_bitmap("../imgs/menu.bmp",NULL);
   seta = load_bitmap("../imgs/seta.bmp",NULL);
   fundoMusical = load_midi("../musicas/startMusic.mid");
   mudaSeta     = load_wav("../musicas/cursor.wav");
   decisao      = load_wav("../musicas/decisao.wav");
   play_midi(fundoMusical,1);
   posy = 0;
}

void Apresentacao::execute(){
   if (key[KEY_UP]) {posy = (4 + posy - 1)%4;play_sample(mudaSeta,255,90,1000,0);}
   else if (key[KEY_DOWN]) {posy = (posy + 1)%4;play_sample(mudaSeta,255,90,1000,0);}
   else if (key[KEY_ENTER]) {
      switch(posy){
         case 0: play_sample(decisao,255,90,1000,0);rest(300);clear_keybuf();prGame->setCena(1);break;
         case 3: play_sample(decisao,255,90,1000,0);rest(300);clear_keybuf();prGame->setEstado(Game::ENDED);break;
         default : break;
      }
   }
}

void Apresentacao::update(){
   blit(underScene,backbuffer,0,0,(TELAW-underScene->w)/2,(TELAH - underScene->h)/2,underScene->w,underScene->h);
   draw_sprite(backbuffer,menu,100+(TELAW-menu->w)/2,20+(TELAH - menu->h)/2);
   draw_sprite(backbuffer,seta,60+(TELAW-menu->w)/2,20+(TELAH - menu->h)/2 + (4*46 + posy*46)%(4*46));
}
