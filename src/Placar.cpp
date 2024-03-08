#include "Placar.h"

Placar::Placar(){
   pontos = 0;
   strPontos = "0000";
   strPassos = "";
   passos = 0;
   temFruta = false;
}
Placar::~Placar(){
   release();
}

void Placar::inicializa(){
   numeros = load_bitmap("imgs/numeros2.bmp",NULL);
}

void Placar::setPontos(int pontos){
   this->pontos+=pontos;
   strPontos = intToStr(this->pontos);//converter
}

void Placar::release(){
   destroy_bitmap(numeros);
}

void Placar::strToImg(const char *str, int x, int y){
   int largNum = numeros->w/10;
   for (int i=0;*(str+i);i++){ 
       char num = *(str+i) - '0';
       int posx = num%10;
       masked_blit(numeros,backbuffer,posx*largNum, 0 ,x+i*largNum,y,largNum,numeros->h);
   }
}

void Placar::setFruta(BITMAP *fruta, int passos){
   temFruta = true;  
   this->fruta = fruta;
   this->passos = passos;
   this->strPassos = passos;
}

bool Placar::isFruta(){return temFruta;}

void Placar::decrementa(){passos--;if (passos<0) temFruta=false;strPassos = intToStr(passos);}

void Placar::update(){
   strToImg(strPontos.c_str(),(MAXX+2)*TAMQUADRO,2*TAMQUADRO);
   if (temFruta) {
      draw_sprite(backbuffer,fruta,(MAXX+3)*TAMQUADRO,13*TAMQUADRO-20);
      strToImg(strPassos.c_str(),(MAXX+2)*TAMQUADRO,14*TAMQUADRO);
   }
}

string Placar::intToStr(int num){
   int resto;
   string numStr = "";
   do{
       resto = num%10;
       num = num/10;
       numStr = " " + numStr;
       numStr[0] = ('0' + resto);
   }while(num!=0);
   while(numStr.length()<4) numStr = '0' + numStr;
   return numStr;
}

void Placar::pegou(){
   temFruta = false;
}
