#include "Game.h"


void timer(){
   tempo++;
}

Game::Game(){
   numCenaAtual = 0;
}

Game::~Game(){
   release();
}

void Game::inicializa(){
   init();  
    //Timer
    tempo=0;
	LOCK_VARIABLE(tempo);
    LOCK_FUNCTION(timer);
    install_int(timer,100);
    //EndTimer
   srand(time(NULL));//botar no inicialise do game
   backbuffer = create_bitmap(TELAW,TELAH);
   Cenario *apresentacao = new Apresentacao();
   Cenario *normal       = new NormalGame();
   apresentacao->prGame  = this;
   normal->prGame        = this;
   addCena(apresentacao);
   addCena(normal);
   numCenaAtual = 0;
   estado = RUN;
}

void Game::execute(){

}

void Game::update(){

}

void Game::loop(){
   inicializa();  
   cenas[numCenaAtual]->inicializa();
   while(true){
      if (estado == RUN) {                                 
         cenas[numCenaAtual]->execute();
         cenas[numCenaAtual]->update();
         blit(backbuffer,screen,0,0,0,0,backbuffer->w,backbuffer->h);
         rest(100);
      } else {
         break;
      }
   }
}

void Game::release(){
   for (int i=0;i<cenas.size();i++){
      delete cenas[i];
   }
   cenas.clear();
   destroy_bitmap(backbuffer);
   deinit();
}

void Game::addCena(Cenario *cena){
   cenas.push_back(cena);
}

void Game::setCena(int numCena){
   cenas[numCenaAtual]->release();
   cenas[numCena]->inicializa();
   numCenaAtual = numCena;
}

void Game::init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELAW, TELAH, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
}

void Game::setEstado(ESTADO estado){
   this->estado = estado;
}

void Game::deinit() {
	clear_keybuf();
	allegro_exit();
}
