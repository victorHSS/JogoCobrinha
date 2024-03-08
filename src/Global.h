/*
 *      Este arquivo cabeçalho contém todas as definições globais
 *      para o uso de todos os outros arquivos.
 *
 *      By equipe de desenvolvimento.
 *
 *      Todos os direitos reservados.
 */


#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <allegro.h>
#include <cstdlib>

/* 
 *  Definição da largura espaço disponível para o jogo 
 */

#ifndef TELAW
#define TELAW 640
#endif

#ifndef TELAH
#define TELAH 480
#endif

#ifndef TAMQUADRO
#define TAMQUADRO 20
#endif

#ifndef TAMSCORE
#define TAMSCORE (TELAW - TELAH - 1*TAMQUADRO) 
#endif

#ifndef MAXX
#define MAXX ((TELAW - TAMSCORE)/TAMQUADRO)
#endif

#ifndef MAXY
#define MAXY ((TELAH - 2*TAMQUADRO)/TAMQUADRO)
#endif

#ifndef MINX
#define MINX 1
#endif

#ifndef MINY
#define MINY 2
#endif

using namespace std;

/* 
 *  Ponteiro do backbuffer 
 */

extern BITMAP *backbuffer; 
extern volatile int tempo;

#endif
