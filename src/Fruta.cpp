#include "Fruta.h"

Fruta::Fruta(const char *type){
   fruta = NULL;
   setFruta(type);
   posx = posy = 0;
   comida = false;
   escondida = false;
}

Fruta::~Fruta(){
   release();
}

void Fruta::setFruta(const char *type){
   if (fruta!=NULL) destroy_bitmap(fruta);
   string local = "../imgs/frutas/";       
   local = (local + type) + ".bmp";   
   fruta = load_bitmap(local.c_str(),NULL);
}

void Fruta::release(){
   destroy_bitmap(fruta);
}

void Fruta::inicializa(){
   sort();
}

void Fruta::sort(){
   posx = MINX + (rand()%(MAXX-MINX));
   posy = MINY + (rand()%(MAXY-MINY));
   escondida = false;
}


void Fruta::update(){
   if (!escondida) draw_sprite(backbuffer,fruta,posx*TAMQUADRO + (TAMQUADRO - fruta->w)/2,posy*TAMQUADRO + (TAMQUADRO - fruta->h)/2);
}

bool Fruta::samePlace(Fruta &fruit){
   return ((fruit.posx == posx) && (fruit.posy==posy));
}

void Fruta::esconde(){
   posx = posy = 0;
   escondida = true;
}

int Fruta::getx() const{ return posx;}
int Fruta::gety() const{ return posy;}

BITMAP *Fruta::getFruta(){return fruta;}
