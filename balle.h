#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED
#include "SdlFont.h"
#include "raquettes.h"

void renderBalle(game *myGame,balle *bal1,SDL_Texture **TabTexture);
void jeu(game *myGame, balle *bal1,coordonnees *dep,int *scoreJ1,EtatPause *Pboo,brique *TabBriq,int *niveau);


#endif // BALLE_H_INCLUDED
