#include "Cobra.h"

Cobra::Cobra(){
   tam = 0;
   dir = DIREITA;
   pCabeca = pRabo = NULL;
   bCabecaDireita  = load_bitmap("../imgs/cobra/cabecaCobraDireita.bmp",NULL);
   bCabecaEsquerda = load_bitmap("../imgs/cobra/cabecaCobraEsquerda.bmp",NULL);
   bCabecaCima     = load_bitmap("../imgs/cobra/cabecaCobraCima.bmp",NULL);
   bCabecaBaixo    = load_bitmap("../imgs/cobra/cabecaCobraBaixo.bmp",NULL);
   bRaboEsquerda   = load_bitmap("../imgs/cobra/raboCobraEsquerda.bmp",NULL);
   bRaboDireita    = load_bitmap("../imgs/cobra/raboCobraDireita.bmp",NULL);
   bRaboCima       = load_bitmap("../imgs/cobra/raboCobraCima.bmp",NULL);
   bRaboBaixo      = load_bitmap("../imgs/cobra/raboCobraBaixo.bmp",NULL);
   bCorpoHorizontal= load_bitmap("../imgs/cobra/corpoCobraHorizontal.bmp",NULL);
   bCorpoVertical  = load_bitmap("../imgs/cobra/corpoCobraVertical.bmp",NULL);
   bCorpoCurvaBD   = load_bitmap("../imgs/cobra/corpoCobraCurvaBD.bmp",NULL);
   bCorpoCurvaCE   = load_bitmap("../imgs/cobra/corpoCobraCurvaCE.bmp",NULL);
   bCorpoCurvaDC   = load_bitmap("../imgs/cobra/corpoCobraCurvaDC.bmp",NULL);
   bCorpoCurvaEB   = load_bitmap("../imgs/cobra/corpoCobraCurvaEB.bmp",NULL);
   
}

Cobra::~Cobra(){
   release();
}

void Cobra::release(){
   delete pCabeca;
   delete pRabo;
   destroy_bitmap(bCabecaDireita);
   destroy_bitmap(bCabecaEsquerda);
   destroy_bitmap(bCabecaCima);
   destroy_bitmap(bCabecaBaixo);
   destroy_bitmap(bCorpoHorizontal);
   destroy_bitmap(bCorpoVertical);
   destroy_bitmap(bRaboEsquerda);
   destroy_bitmap(bRaboDireita);
   destroy_bitmap(bRaboCima);
   destroy_bitmap(bRaboBaixo);
   destroy_bitmap(bCorpoCurvaBD);
   destroy_bitmap(bCorpoCurvaCE);
   destroy_bitmap(bCorpoCurvaDC);
   destroy_bitmap(bCorpoCurvaEB);
}

void Cobra::inicializa(int tam, int posx, int posy){
   this->tam = tam;  
   corpo *temp = NULL;
   while (tam--){
      if (pCabeca==NULL) {
         pCabeca = new corpo;
         pCabeca->ant = NULL;
         pCabeca->prox = NULL;
         pCabeca->posx = MINX + ((MAXX-MINX)-tam)/2;//centralisar cobra
         pCabeca->dir = dir;
         pCabeca->posy = 3;
         temp = pCabeca;
      } else {
         temp->prox = new corpo;
         temp->prox->ant = temp;
         temp = temp->prox;
         temp->prox = NULL;
         temp->posx = temp->ant->posx-1;
         temp->posy = temp->ant->posy;
         temp->dir  = dir;
      }
   }
   pRabo = temp;
}

void Cobra::execute(){
   corpo *temp = pRabo;
   if (temp==NULL) return;
   while(temp->ant!=NULL){
      temp->posx = temp->ant->posx;
      temp->posy = temp->ant->posy;
      temp->dir  = temp->ant->dir;
      temp       = temp->ant;
   }
   switch (dir) {
      case DIREITA:  temp->posx = ((MAXX - MINX) + temp->posx + 1)%(MAXX-MINX); pCabeca->dir = DIREITA;  break;
      case ESQUERDA: temp->posx = ((MAXX - MINX) + temp->posx - 1)%(MAXX-MINX); pCabeca->dir = ESQUERDA; break;
      case CIMA:     temp->posy = ((MAXY - MINY) + temp->posy - 1)%(MAXY-MINY); pCabeca->dir = CIMA;     break;
      case BAIXO:    temp->posy = ((MAXY - MINY) + temp->posy + 1)%(MAXY-MINY); pCabeca->dir = BAIXO;    break;
   }
   
}

void Cobra::update(){
   corpo *temp = pCabeca;
   BITMAP *tempBit = NULL;
   while(temp!=NULL) {           
      if (temp == pCabeca) {
         switch(temp->dir){
            case DIREITA:  tempBit = bCabecaDireita;break;
            case ESQUERDA: tempBit = bCabecaEsquerda;break;
            case CIMA:     tempBit = bCabecaCima;break;
            case BAIXO:    tempBit = bCabecaBaixo;break;
         }      
      }
      else if (temp == pRabo) { 
           switch(temp->ant->dir){
              case DIREITA:  tempBit = bRaboDireita;break;
              case ESQUERDA: tempBit = bRaboEsquerda;break;
              case CIMA:     tempBit = bRaboCima;break;
              case BAIXO:    tempBit = bRaboBaixo;break;
           } 
      }
      else {
         if ((temp->ant->dir == temp->dir)) {
            if (temp->ant->dir==ESQUERDA || temp->ant->dir==DIREITA) tempBit = bCorpoHorizontal;
            else tempBit = bCorpoVertical;
         } else {
            if (((temp->ant->dir == ESQUERDA && temp->dir == CIMA) || (temp->ant->dir == BAIXO && temp->dir == DIREITA))) tempBit = bCorpoCurvaEB;
            else if (((temp->ant->dir == BAIXO && temp->dir == ESQUERDA) || (temp->ant->dir == DIREITA && temp->dir == CIMA)) ) tempBit = bCorpoCurvaBD;
            else if (((temp->ant->dir == CIMA && temp->dir == ESQUERDA) || (temp->ant->dir == DIREITA && temp->dir == BAIXO))) tempBit = bCorpoCurvaDC;
            else if (((temp->ant->dir == ESQUERDA && temp->dir == BAIXO) || (temp->ant->dir == CIMA && temp->dir == DIREITA))) tempBit = bCorpoCurvaCE;
         }
      }
      draw_sprite(backbuffer, tempBit,(MINX + temp->posx)*TAMQUADRO, (MINY + temp->posy)*TAMQUADRO);
      temp = temp->prox;
   }
}

void Cobra::direita(){
   if (dir!=ESQUERDA) dir = DIREITA;
}

void Cobra::esquerda(){
   if (dir!=DIREITA) dir = ESQUERDA;
}

void Cobra::cima(){
   if (dir!=BAIXO) dir = CIMA;
}

void Cobra::baixo(){
   if (dir!=CIMA) dir = BAIXO;
}

void Cobra::comeFruta(){
   cresce();
}

void Cobra::cresce(){
   pRabo->prox = new corpo;
   pRabo->prox->ant = pRabo;
   pRabo = pRabo->prox;
   pRabo->prox = NULL;
   pRabo->posx = pRabo->ant->posx; 
   pRabo->posy = pRabo->ant->posy;
   tam++;
}

bool Cobra::contatoCabeca(int posx, int posy){//rever//lembrar que eh a posicao relativa ao quadro(TAMQUADRO)
   return ((this->pCabeca->posx + MINX == posx) && (this->pCabeca->posy + MINY == posy));
}

bool Cobra::contatoCorpo(int posx, int posy){
   corpo *temp = pRabo;
   while (temp!=pCabeca){
      if ((temp->posx + MINX == posx) && (temp->posy + MINY == posy)) return true;   
      temp = temp->ant;
   }
   return false;
}


bool Cobra::selfShock(){
   return (contatoCorpo(pCabeca->posx+MINX,pCabeca->posy+MINY));
}

