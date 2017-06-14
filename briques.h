#ifndef BRIQUES_H_INCLUDED
#define BRIQUES_H_INCLUDED
#include "SdlFont.h"
#include "raquettes.h"
#include "balle.h"

void initBriques(brique *TabBriq,int niveau);
void renderBriques(game *myGame,brique *TabBriq,SDL_Texture **TabTexture);



#endif // BRIQUES_H_INCLUDED
