#include "CSurface.h"
#include <math.h>

CSurface::CSurface(){
    
}

// Renvoyer une image "optimis�e"

SDL_Surface* CSurface::OnLoad(char* File){
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;
    
    if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }
    
    Surf_Return = SDL_DisplayFormat(Surf_Temp); // Display le temporaire
    SDL_FreeSurface(Surf_Temp); // Lib�rer l'espace
    
    return Surf_Return;
}

// Fonction pour ajouter une image

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y){
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_BlitSurface(Surf_Src,NULL,Surf_Dest,&DestR);
    
    return true;
}

// Fonction pour ajouter une image en sp�cifiant la hauteur et la largeur

bool CSurface::OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y, int X2, int Y2, int W, int H){
    
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_Rect SrcR;
    
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;
    
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, & DestR);
    
    return true;
}

///// Juste pour rendre l'arri�re plan transparent (inutile � vrai dire)

bool CSurface::Transparent(SDL_Surface *Surf_Dest, int R, int G, int B){
    
    if (Surf_Dest == NULL) {
        return false;
    }
    
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
    
    return true;
    
}
