
#include "Start.h"
#include "Csurface.h"


StartMenu::StartMenu() {
    Background = NULL;
    HumanvBot = NULL;
    HumanvHuman = NULL;
    Level = NULL;
    Menu_Display = NULL;
    Quit = NULL;
    MenuRuns = 1;
    
}

int StartMenu::showmenu(){
    
    if(MenuInit() == false){
        return -1;
    }
    
    int x = 0, y = 0;
    
    SDL_Event event;
    
    while (MenuRuns == 1) {
        
        SDL_WaitEvent(&event);
        
        if (event.type == SDL_MOUSEMOTION) {
            x = event.motion.x;
            y = event.motion.y;
            
            bool arcade =(x>posArcade.x) && (x< (posArcade.x+posArcade.w)) && (y>posArcade.y) && (y<(posArcade.y + posArcade.h));
            
            bool humans = (x>pos2.x) && (x< (pos2.x+pos2.w)) && (y>pos2.y) && (y<(pos2.y + pos2.h));
            
            bool instructions = (x>posLevel.x) && (x< (posLevel.x+posLevel.w)) && (y>posLevel.y) && (y<(posLevel.y + posLevel.h));
            
            bool quits = (x>posQuit.x) && (x< (posQuit.x+posQuit.w)) && (y>posQuit.y) && (y<(posQuit.y + posQuit.h));
            
            if (arcade == true) {
                CSurface::OnDraw(Menu_Display, HumanvBot, 0, 0);
                SDL_Flip(Menu_Display);
            }
            
            else if (humans == true) {
                CSurface::OnDraw(Menu_Display, HumanvHuman, 0, 0);
                SDL_Flip(Menu_Display);
            }
            
            else if (instructions == true) {
                CSurface::OnDraw(Menu_Display, Level, 0, 0);
                SDL_Flip(Menu_Display);
            }
            
            else if (quits == true) {
                CSurface::OnDraw(Menu_Display, Quit, 0, 0);
                SDL_Flip(Menu_Display);
            }
            
            else{
                CSurface::OnDraw(Menu_Display, Background, 0, 0);
                SDL_Flip(Menu_Display);
            }
        }
        
        if (event.type==SDL_MOUSEBUTTONDOWN) {
            x = event.motion.x;
            y = event.motion.y;
            
            bool arcade =(x>posArcade.x) && (x< (posArcade.x+posArcade.w)) && (y>posArcade.y) && (y<(posArcade.y + posArcade.h));
            
            bool humans = (x>pos2.x) && (x< (pos2.x+pos2.w)) && (y>pos2.y) && (y<(pos2.y + pos2.h));
            
            bool instructions = (x>posLevel.x) && (x< (posLevel.x+posLevel.w)) && (y>posLevel.y) && (y<(posLevel.y + posLevel.h));
            
            bool quits = (x>posQuit.x) && (x< (posQuit.x+posQuit.w)) && (y>posQuit.y) && (y<(posQuit.y + posQuit.h));

        
            if (arcade == true) {
                
                // Il faut que ça mène au menu des difficultés.
                CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                SDL_Flip(Menu_Display);
                
                int diffrun = 1;
                
                while (diffrun ==1) {
                    
                    SDL_WaitEvent(&event);
                    
                    if (event.type == SDL_KEYDOWN) {
                        switch (event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                diffrun = 0;
                                MenuRuns = 0;
                                break;
                        }

                    }
                    
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        x = event.motion.x;
                        y = event.motion.y;
                        
                        bool fit1 = (x>poslvl1.x) && (x< (poslvl1.x+poslvl1.w)) && (y>poslvl1.y) && (y<(poslvl1.y + poslvl1.h));
                        
                        bool fit2 = (x>poslvl2.x) && (x< (poslvl2.x+poslvl2.w)) && (y>poslvl2.y) && (y<(poslvl2.y + poslvl2.h));
                        
                        bool fit3 = (x>poslvl3.x) && (x< (poslvl3.x+poslvl3.w)) && (y>poslvl3.y) && (y<(poslvl3.y + poslvl3.h));
                        
                        bool fit4 = (x>poslvl4.x) && (x< (poslvl4.x+poslvl4.w)) && (y>poslvl4.y) && (y<(poslvl4.y + poslvl4.h));
                        
                        bool fit5 = (x>poslvl5.x) && (x< (poslvl5.x+poslvl5.w)) && (y>poslvl5.y) && (y<(poslvl5.y + poslvl5.h));
                        
                        bool fit6 = (x>poslvl6.x) && (x< (poslvl6.x+poslvl6.w)) && (y>poslvl6.y) && (y<(poslvl6.y + poslvl6.h));
                        
                        bool fitback = (x>posback.x) && (x< (posback.x+posback.w)) && (y>posback.y) && (y<(posback.y + posback.h));
                        
                        
                        if (fit1 == true) {
                            
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);
                            SDL_Flip(Menu_Display);
                            
                            int choicerun = 1;  /// Loop to get the choice of the player
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 1);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 1);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;

                                    }


                                }
                            }
                            
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fit2 == true) {
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);
                            SDL_Flip(Menu_Display);
                            int choicerun = 1;
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 2);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 2);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;
                                        
                                    }
                                }
                            }
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fit3 == true) {
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);

                            SDL_Flip(Menu_Display);
                            
                            int choicerun = 1;
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 3);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 3);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;
                                        
                                    }
                                    
                                    
                                }
                            }
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fit4 == true) {
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);
                            
                            SDL_Flip(Menu_Display);
                            
                            int choicerun = 1;
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 4);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 4);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;
                                        
                                    }
                                    
                                    
                                }
                            }
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fit5 == true) {
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);
                            
                            SDL_Flip(Menu_Display);
                            
                            int choicerun = 1;
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 5);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 5);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;
                                        
                                    }
                                    
                                    
                                }
                            }
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fit6 == true) {
                            SDL_FreeSurface(Menu_Display);
                            
                            Menu_Display = SDL_SetVideoMode(640, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            
                            CSurface::OnDraw(Menu_Display, OneTwo, 0, 0);
                            
                            SDL_Flip(Menu_Display);
                            
                            int choicerun = 1;
                            
                            while (choicerun == 1){
                                SDL_WaitEvent(&event);
                                if (event.type==SDL_MOUSEBUTTONDOWN){
                                    x = event.motion.x;
                                    y = event.motion.y;
                                    bool first =(x>PosP1.x) && (x< (PosP1.x+PosP1.w)) && (y>PosP1.y) && (y<(PosP1.y + PosP1.h));
                                    
                                    bool second = (x>PosP2.x) && (x< (PosP2.x+PosP2.w)) && (y>PosP2.y) && (y<(PosP2.y + PosP2.h));
                                    
                                    bool back = (x>PosbacktoD.x) && (x< (PosbacktoD.x+PosbacktoD.w)) && (y>PosbacktoD.y) && (y<(PosbacktoD.y + PosbacktoD.h));
                                    
                                    if (first == true){
                                        Connect4_AI MyGame (0, 6);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (second == true){
                                        Connect4_AI MyGame (1, 6);
                                        MyGame.OnExecute();
                                        choicerun = 0;
                                    }
                                    
                                    else if (back == true){
                                        SDL_FreeSurface(Menu_Display);
                                        
                                        Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        
                                        CSurface::OnDraw(Menu_Display, Difficulty, 0, 0);
                                        choicerun = 0;
                                        
                                    }
                                }
                            }
                            diffrun = 0;
                            MenuRuns = 0;
                        }
                        
                        else if (fitback == true){
                            // Je reviens au menu principal
                            CSurface::OnDraw(Menu_Display, Background, 0, 0);
                            SDL_Flip(Menu_Display);
                            diffrun = 0;
                            MenuRuns = 1;
                        }
                        
                        else{
                            MenuRuns = 1;
                        }
                        
                    }
                    
                }
            }
            
            else if (humans == true){
                TwoPlayers OurGame;
                
                OurGame.OnExecute();
                
                MenuRuns = 0;
            }
            
            else if (instructions == true){
                // Connect4_AIeler la page des consignes
                MenuRuns = 0;
            }
            
            else if (quits == true){
                MenuRuns = 0;
            }
        }

        if (event.type == SDL_QUIT) {
            MenuRuns = 0;
        }
    }
    
    OnCleanup();
    
//    SDL_Flip(Menu_Display);
    return 0;
    
}

bool StartMenu::MenuInit(){
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    if ((Menu_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if ((Background = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/MainMenu.bmp")) == NULL) {
        return false;
    }
    
    if ((HumanvBot = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/ModeArcade.bmp")) == NULL) {
        return false;
    }
    
    if ((HumanvHuman = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/DeuxJoueurs.bmp")) == NULL) {
        return false;
    }
    
    if ((Level = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/Niveau.bmp")) == NULL) {
        return false;
    }
    
    if ((Quit = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/quitter.bmp")) == NULL) {
        return false;
    }
    
    if ((Difficulty = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/LevelChoice.bmp")) == NULL) {
        return false;
    }
    
    if ((OneTwo = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/Choix.bmp")) == NULL) {
        return false;
    }
    
    CSurface::Transparent(Background, 255, 0, 255);
    CSurface::Transparent(HumanvBot, 255, 0, 255);
    CSurface::Transparent(HumanvHuman, 255, 0, 255);
    CSurface::Transparent(Level, 255, 0, 255);
    CSurface::Transparent(Quit, 255, 0, 255);
    CSurface::Transparent(Difficulty, 255, 0, 255);
    
    Reset();
    
    return true;

}

void StartMenu::Reset(){
    
    CSurface::OnDraw(Menu_Display, Background, 0, 0);
    
    posArcade.x = 150;
    posArcade.y = 100;
    posArcade.w = 165;
    posArcade.h=135;
    
    pos2.x = 315;
    pos2.y = 100;
    pos2.w= 165;
    pos2.h= 135;

    posLevel.x = 150;
    posLevel.y = 235;
    posLevel.w = 165;
    posLevel.h= 135;
    
    posQuit.x = 315;
    posQuit.y = 235;
    posQuit.w = 165;
    posQuit.h= 135;
    
    poslvl1.x = 71;
    poslvl1.y = 140;
    poslvl1.w = 88;
    poslvl1.h = 13;
    
    poslvl2.x = 71;
    poslvl2.y = 197;
    poslvl2.w = 88;
    poslvl2.h = 13;
    
    poslvl3.x = 71;
    poslvl3.y = 252;
    poslvl3.w = 88;
    poslvl3.h = 13;
    
    poslvl4.x = 71;
    poslvl4.y = 308;
    poslvl4.w = 88;
    poslvl4.h = 13;
    
    poslvl5.x = 71;
    poslvl5.y = 363;
    poslvl5.w = 88;
    poslvl5.h = 13;
    
    poslvl6.x = 71;
    poslvl6.y = 417;
    poslvl6.w = 88;
    poslvl6.h = 13;
    
    posback.x = 488;
    posback.y = 450;
    posback.w = 128;
    posback.h = 10;
    
    PosP1.x= 57;
    PosP1.y= 53;
    PosP1.w= 235;
    PosP1.h= 104;
    
    PosP2.x= 317;
    PosP2.y= 53;
    PosP2.w= 247;
    PosP2.h= 104;
    
    PosbacktoD.x = 567;
    PosbacktoD.y = 176;
    PosbacktoD.w = 50;
    PosbacktoD.h = 12;
    
    
}

void StartMenu::OnCleanup(){
    SDL_FreeSurface(Background);
    SDL_FreeSurface(HumanvHuman);
    SDL_FreeSurface(HumanvBot);
    SDL_FreeSurface(Quit);
    SDL_Quit();
}
