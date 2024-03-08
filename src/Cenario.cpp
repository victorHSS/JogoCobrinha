#include "Cenario.h"

Cenario::Cenario(){
   underScene = NULL;
   fundoMusical = NULL;
}

Cenario::~Cenario(){
   release();
}

void Cenario::release(){
   destroy_bitmap(underScene);
}

void Cenario::update(){
   blit(backbuffer,underScene,0,0,0,0,underScene->w,underScene->h);
}
