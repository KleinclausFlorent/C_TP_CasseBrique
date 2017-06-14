#include "briques.h"
//Initialisation de l'ensemble des briques
//BUT : Donner une position et une couleur à chaque briqe et initialiser la variable visible
//ENTREE : Le tableau de brique et la variable de niveau ( On ne modifie pas la dispostion des briques pour chaque niveau mais on pourrait l'ajouter dans une version ultérieure)
//SORTIE : le tableau de brique avec toutes les briques initialisée
void initBriques(brique *TabBriq,int niveau){
    int i,rm;
    if (niveau>=0) {//1024/64=16
        for (i=0; i<NOMBRE_LIGNE*NOMBRE_BRIQ; i++){
            rm=rand();
            if (rm%4==0){
                TabBriq[i].Sx=0;
                TabBriq[i].Sy=0;

            } else if (rm%4==1){
                TabBriq[i].Sx=64;
                TabBriq[i].Sy=0;
            } else if (rm%4==2){
                TabBriq[i].Sx=0;
                TabBriq[i].Sy=24;
            } else if (rm%4==3){
                TabBriq[i].Sx=64;
                TabBriq[i].Sy=24;
            }
            TabBriq[i].Destx=(i%16)*64;
            TabBriq[i].Desty=((int)i/16)*24;
            TabBriq[i].h=24;
            TabBriq[i].w=64;
            TabBriq[i].visible=1;
        }
    }
}

//Affichage de l'ensemble des briques
//BUT : Affiche les briques visibles à la position voulues
//ENTREE : Le tableau de brique , la fenêtre et la texture des briques
//SORTIE : les briques dans la fenêtre
void renderBriques(game *myGame,brique *TabBriq,SDL_Texture **TabTexture){
    SDL_Rect rectangleSource;
    SDL_Rect rectangleDest;
    int i;
    myGame->g_ptexture = TabTexture[2];

    if(myGame->g_ptexture){
        for (i=0; i<NOMBRE_LIGNE*NOMBRE_BRIQ; i++){
            if (TabBriq[i].visible==1){
                rectangleSource.x=TabBriq[i].Sx;//debut x
                rectangleSource.y=TabBriq[i].Sy;//debut y
                rectangleSource.w=TabBriq[i].w; //Largeur
                rectangleSource.h=TabBriq[i].h; //Hauteur
                SDL_QueryTexture(myGame->g_ptexture,NULL,NULL,NULL,NULL);

                //Définition du rectangle dest pour dessiner Bitmap
                rectangleDest.x=TabBriq[i].Destx;//debut x
                rectangleDest.y=TabBriq[i].Desty;//debut y
                rectangleDest.w=TabBriq[i].w; //Largeur
                rectangleDest.h=TabBriq[i].h; //Hauteur

                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,&rectangleSource,&rectangleDest);
            }

        }

    }

    else{
            fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
    }

}

