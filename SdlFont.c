#include "SdlFont.h"
//Initialisation gestion de la fenêtre et de la font


//BUT : Charger les images qui nous serviront de texture dans le tableau de texture
//ENTREE : la fenêtre et le tableau de texture
//SORTIE : le tableau de texture rempli
void loadTextures(game *myGame,SDL_Texture **TabTexture){
    SDL_Surface *Temp;
    Temp=IMG_Load("D:/ludus/2016-2017/Algo-C/TP_Casse-Brique/assets/ball.png");
    TabTexture[0] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,Temp);
    SDL_FreeSurface(Temp);
    Temp=IMG_Load("D:/ludus/2016-2017/Algo-C/TP_Casse-Brique/assets/paddle.png");
    TabTexture[1] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,Temp);
    SDL_FreeSurface(Temp);
    Temp=IMG_Load("D:/ludus/2016-2017/Algo-C/TP_Casse-Brique/assets/bricks.png");
    TabTexture[2] = SDL_CreateTextureFromSurface(myGame->g_pRenderer,Temp);
    SDL_FreeSurface(Temp);
}
//BUT : initialisation de la fenetre des raquettes de la balle et de la fonts
//ENTREE : bal, raquettes , fenetre , font
//SORTIE : tout est initialisé
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, font *mFont,coordonnees *dep, balle *bal1){


    //initialize SDL
    dep->x=SCREEN_WIDTH/2-(64);
    dep->y=SCREEN_HEIGHT-32;
    dep->w=128;
    dep->h=32;
    bal1->x=SCREEN_WIDTH/2-16;
    bal1->y=SCREEN_HEIGHT-64;
    bal1->r=16;
    bal1->d=1;
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);


            }


    }else{


        return 0;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    mFont->g_font=TTF_OpenFont("./assets/fonts/arial_narrow_7/arial_narrow_7.ttf",65);




    return 1;


}
//Gestion de l'affiche du texte
//BUT : affichage du score
//ENTREE : la fenêtre myGame et les scores
//SORTIE : Score afficher dans la page
void writeSDL(game *myGame,font mFont,int Text,int scoreJ1) {

        SDL_Color fontColor={255,0,0};
        char buffer[200];
        if (Text==0){
            int affichage=sprintf(buffer,"Score : %i        Appuyer sur Espace pour jouer",scoreJ1);
        }
        myGame->g_psurface=TTF_RenderText_Blended(mFont.g_font, buffer, fontColor);//Charge la police

        if(myGame->g_psurface){


                //Définition du rectangle dest pour blitter la chaine
                SDL_Rect rectangle;
                rectangle.x=SCREEN_WIDTH/2-300;//debut x
                rectangle.y=SCREEN_HEIGHT-300;//debut y
                rectangle.w=600; //Largeur
                rectangle.h=200; //Hauteur


                 myGame->g_ptexture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_psurface); // Préparation de la texture pour la chaine
                 SDL_FreeSurface(myGame->g_psurface); // Libération de la ressource occupée par le sprite

                 if(myGame->g_ptexture){

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&rectangle); // Copie du sprite grâce au SDL_Renderer
                        //SDL_RenderPresent(myGame->g_pRenderer); // Affichage
                 }
                 else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de creation surface pour chaine (%s)\n",SDL_GetError());
        }

}
//Gestion du delay
//BUT : imposer un delay pour le rafraichissement (PAS FONCTIONNEL)
//ENTREE : notre limit de rafraichissement
//SORTIE : vitesse régulée
void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();
    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(1);
    }
}


//BUT : Gestion de la destruction de la fenetre
//ENTREE : la fenêtre myGame et la font
//SORTIE : fermeture de la fenetre
void destroy(game *myGame,font *mFont,SDL_Texture **TabTexture){


    if(mFont->g_font!=NULL){
        TTF_CloseFont(mFont->g_font); /* Doit être avant TTF_Quit() */
        mFont->g_font=NULL;
    }

    //Destroy texture
    if(myGame->g_ptexture!=NULL)
            SDL_DestroyTexture(myGame->g_ptexture);
    if(TabTexture[0]!=NULL)
            SDL_DestroyTexture(TabTexture[0]);
    if(TabTexture[1]!=NULL)
            SDL_DestroyTexture(TabTexture[1]);
    if(TabTexture[2]!=NULL)
            SDL_DestroyTexture(TabTexture[2]);


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}
