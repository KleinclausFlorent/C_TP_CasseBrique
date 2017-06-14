//Création des raquettes et gestion des événements liées aux raquettes
#ifndef RAQUETTES_H_INCLUDED
#define RAQUETTES_H_INCLUDED
#include "SdlFont.h"


void handleEvents(gameState *state,EtatRaquette *boo1,EtatPause *Pboo,int *niveau);
void MouvementRaquette(coordonnees *dep,EtatRaquette *boo1);
void renderRaquette1(game *myGame,coordonnees *dep,SDL_Texture **TabTexture);


#endif // RAQUETTES_H_INCLUDED
