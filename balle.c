#include "balle.h"
#include "briques.h"

//Gestion de la balle
//BUT : construction de la balle
//ENTREE : la fenêtre myGame et la balle
//SORTIE : Balle construite ( cercle)
void renderBalle(game *myGame,balle *bal1,SDL_Texture **TabTexture) {

        SDL_Rect rectangleSource;
        SDL_Rect rectangleDest;
        myGame->g_ptexture = TabTexture[0];

        if(myGame->g_ptexture){
            rectangleSource.x=0;//debut x
            rectangleSource.y=0;//debut y
            rectangleSource.w=SCREEN_WIDTH; //Largeur
            rectangleSource.h=SCREEN_HEIGHT; //Hauteur
            SDL_QueryTexture(myGame->g_ptexture,NULL,NULL,NULL,NULL);

            //Définition du rectangle dest pour dessiner Bitmap
            rectangleDest.x=bal1->x;//debut x
            rectangleDest.y=bal1->y;//debut y
            rectangleDest.w=bal1->r*2; //Largeur
            rectangleDest.h=bal1->r*2; //Hauteur

            SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,&rectangleSource,&rectangleDest);

        }

        else{
                fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
        }
}
//Gestion de la balle
//BUT : Calcul position balle + collision, gestion du score, vitesse de la balle
//ENTREE : la fenetre, la balle, les position des raquettes, les scores et l'enum pause
//SORTIE : la balle sa position, sa direction et le score

void jeu(game *myGame, balle *bal1,coordonnees *dep,int *scoreJ1,EtatPause *Pboo,brique *TabBriq,int *niveau){
    int i;
    int vide=0;
    //HAUT gauche
    if (bal1->d==1){
        bal1->x=bal1->x-1*(*niveau);
        bal1->y=bal1->y-1*(*niveau);
    }
    //HAUT droite
    if (bal1->d==2){
        bal1->x=bal1->x+1*(*niveau);
        bal1->y=bal1->y-1*(*niveau);
    }
    //BAS droit
    if (bal1->d==3){
        bal1->x=bal1->x+1*(*niveau);
        bal1->y=bal1->y+1*(*niveau);
    }
    //BAS gauche
    if (bal1->d==4){
        bal1->x=bal1->x-1*(*niveau);
        bal1->y=bal1->y+1*(*niveau);
    }
    //Rebond ecran haut
    if (bal1->y<=bal1->r){
        if (bal1->d==1){
            bal1->d=4;
        } else if (bal1->d==2){
            bal1->d=3;
        }
    }
    //Rebond ecran gauche
    if (bal1->x<=bal1->r){
        if (bal1->d==1){
            bal1->d=2;
        } else if (bal1->d==4){
            bal1->d=3;
        }
    }
    //Rebond ecran droit
    if (bal1->x>=SCREEN_WIDTH-bal1->r){
        if (bal1->d==2){
            bal1->d=1;
        } else if (bal1->d==3){
            bal1->d=4;
        }
    }
     //Sortie ecran bas
    if (bal1->y>SCREEN_HEIGHT){
        *Pboo=Pause;
        *scoreJ1=*scoreJ1/2;
        bal1->x=SCREEN_WIDTH/2-16;
        bal1->y=SCREEN_HEIGHT-64;
        dep->x=SCREEN_WIDTH/2-(64);
        dep->y=SCREEN_HEIGHT-32;
    }

    //Rebond Raquette
    if ((bal1->y>=SCREEN_HEIGHT-(dep->h+2*bal1->r))&&(bal1->y<=SCREEN_HEIGHT)&&(bal1->x>=dep->x)&&(bal1->x<=dep->x+dep->w))
    {
        if (bal1->d==4){
            bal1->d=1;
        } else if (bal1->d==3){
            bal1->d=2;
        }
    }
    //Rebond Briques
    for (i=0; i<NOMBRE_LIGNE*NOMBRE_BRIQ; i++){
            if (TabBriq[i].visible==1){
                    if (((TabBriq[i].Destx <= bal1->x)&&(bal1->x<=TabBriq[i].Destx+TabBriq[i].w)&&(TabBriq[i].Desty<= bal1->y)&&(bal1->y<=TabBriq[i].Desty+TabBriq[i].h))
                        ||((TabBriq[i].Destx <= bal1->x+2*bal1->r)&&(bal1->x+2*bal1->r<=TabBriq[i].Destx+TabBriq[i].w)&&(TabBriq[i].Desty<= bal1->y)&&(bal1->y<=TabBriq[i].Desty+TabBriq[i].h))
                        ||((TabBriq[i].Destx <= bal1->x+2*bal1->r)&&(bal1->x+2*bal1->r<=TabBriq[i].Destx+TabBriq[i].w)&&(TabBriq[i].Desty<= bal1->y+2*bal1->r)&&(bal1->y+2*bal1->r<=TabBriq[i].Desty+TabBriq[i].h))
                        ||((TabBriq[i].Destx <= bal1->x)&&(bal1->x<=TabBriq[i].Destx+TabBriq[i].w)&&(TabBriq[i].Desty<= bal1->y+2*bal1->r)&&(bal1->y+2*bal1->r<=TabBriq[i].Desty+TabBriq[i].h))){
                            *scoreJ1=*scoreJ1+1*(*niveau);
                            if (bal1->d==1){
                                bal1->d=4;

                            }
                            //HAUT droite
                            else if (bal1->d==2){
                                bal1->d=3;
                            }
                            //BAS droit
                             else if (bal1->d==3){
                                bal1->d=2;
                            }
                            //BAS gauche
                             else if (bal1->d==4){
                                bal1->d=1;
                            }
                            TabBriq[i].visible=0;
                    }
            }
    }

    //Plus de brique visible
    for (i=0; i<NOMBRE_LIGNE*NOMBRE_BRIQ; i++){
        if (TabBriq[i].visible==0)
            {
                vide = vide +1;
            }

    }
    if (vide>=NOMBRE_LIGNE*NOMBRE_BRIQ){
        initBriques(TabBriq,*niveau);
        *Pboo=Pause;
        *scoreJ1=*scoreJ1+100*(*niveau);
        *niveau=*niveau+1;
        bal1->x=SCREEN_WIDTH/2-16;
        bal1->y=SCREEN_HEIGHT-64;
        dep->x=SCREEN_WIDTH/2-(64);
        dep->y=SCREEN_HEIGHT-32;
    }
}
