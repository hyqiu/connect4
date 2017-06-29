
#include "Connect4.h"
#include "Start.h"

// We include this mathematical package because we need to make operations on the graphic surfaces implemented by SDL.
#include <cmath>

// Define the dimensions of the window

const int WIDTH = 700;
const int HEIGHT = 600;

// Define MIN_VALUE and MAX_VALUE for the AI part

int const MIN_VALUE = -10000;
int const MAX_VALUE = 10000;

///////////////////////////////**************************************/////////////////////////////////////
///////////////////////////////    The First part : basic settings   /////////////////////////////////////
///////////////////////////////**************************************/////////////////////////////////////


//  We initialize our class objects

Connect4_AI::Connect4_AI(int ID, int dpth){
    
    Running = 1; // Running is a dummy variable to exit the while loop when interacting with the SDL functions linked to events.
    
    red = NULL; // We initialize our sprites to NULL (they will be loaded with OnInit later on).
    yellow = NULL;
    empty = NULL;
    
    for (int i = 0; i<6; i++) {
        for (int j=0; j<7; j++) {
            Grid[i][j] = Empty;
        }
    }
    
    Winner = None;
    
    // ID is to link the Start Menu to this particular constructor.
    
    if (ID == 0) {
        Firstplayer = player1;
    }
    
    else{
        Firstplayer = bot;
    }
    
    Currentplayer = Firstplayer;
    
    // We define the "Tile portfolio" for each player; they will be useful for the AI.
    
    if (Firstplayer == bot) {
        Bot_Tile = Red;
        P1_Tile = Yellow;
        
        MaximizerTile = Bot_Tile;
        MinimizerTile = P1_Tile;
        CurrentTile = Bot_Tile;
    }
    
    else{
        P1_Tile = Red;
        Bot_Tile = Yellow;
        
        MaximizerTile = P1_Tile;
        MinimizerTile = Bot_Tile;
        CurrentTile = P1_Tile;
    }
    
    // Depth is a typical essential data for the AI in our game : it determines the depth of computation during the game, i.e. "how far the computer goes to foresee the future moves".
    
    // In our case, we chose one ladder per difficulty level.
    
    depth = dpth;
}

bool Connect4_AI::OnInit(){
    
    ///// This function aims at loading the sprites and returns false if the directories are false, so please check them well before running !!!!
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((Surf_Display = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if ((empty = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/emptyboard.bmp")) == NULL) {
        return false;
    }
    
    if ((red = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/boardred.bmp")) == NULL) {
        return false;
    }
    
    if ((yellow = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/boardyellow.bmp")) == NULL) {
        return false;
    }
    
    if ((redh = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redh.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowh = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowh.bmp")) == NULL) {
        return false;
    }

    if ((redv = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redv.bmp")) == NULL) {
        return false;
    }

    if ((yellowv = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowv.bmp")) == NULL) {
        return false;
    }
    
    if ((redad = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/redad.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowad = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowad.bmp")) == NULL) {
        return false;
    }

    if ((reddd = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/reddd.bmp")) == NULL) {
        return false;
    }
    
    if ((yellowdd = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/yellowdd.bmp")) == NULL) {
        return false;
    }
    
    if ((gameover = CSurface::OnLoad("W:/Projets/Puissance4/Newsprites/GameOver.bmp")) == NULL) {
        return false;
    }
    
    // Transparent is a classical function to return a transparent background for each sprite.
    
    CSurface::Transparent(red, 255, 0, 255);
    CSurface::Transparent(redh, 255, 0, 255);
    CSurface::Transparent(redv, 255, 0, 255);
    CSurface::Transparent(redad, 255, 0, 255);
    CSurface::Transparent(reddd, 255, 0, 255);
    CSurface::Transparent(yellow, 255, 0, 255);
    CSurface::Transparent(yellowh, 255, 0, 255);
    CSurface::Transparent(yellowv, 255, 0, 255);
    CSurface::Transparent(yellowad, 255, 0, 255);
    CSurface::Transparent(yellowdd, 255, 0, 255);
    CSurface::Transparent(gameover, 255, 0, 255);
    
    backmain.x = 93;
    backmain.y = 505;
    backmain.w = 167;
    backmain.h = 15;
    
    quit.x = 502;
    quit.y = 506;
    quit.w = 74;
    quit.h = 15;
    
    // Reset is a function to "blit" (= paste) the empty spots of a Connect 4 game board.
    
    Reset();
    
    return true;
}

///// Here is the Reset function

void Connect4_AI::Reset(){
    
    // We divide the WIDTH and HEIGHT by their respective number of spots. We chose to restrict ourselves to a classical 6x7 Connect 4 Game.
    
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y = i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x = j;
            SDL_BlitSurface(empty,NULL,Surf_Display,&r);
        }
    }
    
}

///// SetCell "plays" a turn at a specific "address", for the player identified by a certain type.

void Connect4_AI::SetCell(int RowID, int ColID, Connect4_AI::Tiles Type){
    if(RowID<0 || RowID>5 || ColID <0 || ColID > 7) return;
    
    Grid[RowID][ColID]=Type;
}

///// EraseCell erases the spot whose address is in the arguments. It is mostly useful for the AI implementation.

void Connect4_AI::EraseCell(int RowID, int ColID){
    Grid[RowID][ColID] = Empty;
}

///// checkmouse is a function that takes the coordinates of the mouse on the surface and deduces the column in which the turn is played. Then checkmouse implements a SetCell.

void Connect4_AI::checkmouse(SDL_MouseButtonEvent *mouse){
    
    float mousex = mouse->x;
    
    int colID = floor(mousex/100);
    
    if (IsColFull(colID) == true) {
        return;
    }
    
    int rowID = RowforPlay(colID);
    
    SetCell(rowID,colID, CurrentTile);
}

///// The following boolean functions aim at checking if there are winning combinations on the board, resp. for horizontal, vertical, Ascending Diagonal (AD) and Descending Diagonal (DD).

bool Connect4_AI::HorizontalWin(Connect4_AI::Tiles tab[6][7]){
    int start;
    bool hwon = false;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                hwon = true;
                break;
            }
        }
    }
    
    return hwon;
}

bool Connect4_AI::VerticalWin(Connect4_AI::Tiles tab[6][7]){
    int start;
    bool vwon = false;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                vwon = true;
                break;
            }
        }
    }
    
    return vwon;
    
}

bool Connect4_AI::ADWin(Connect4_AI::Tiles tab[6][7]){
    
    int start;
    bool adwon = false;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                adwon = true;
                break;
            }
        }
    }
    return adwon;
}

bool Connect4_AI::DDWin(Connect4_AI::Tiles tab[6][7]){
    int start;
    bool ddwon = false;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                ddwon = true;
            }
        }
    }
    return ddwon;
}


///// The following functions make the blitting when there are winning combinations on the board. They blit a sprite with a black band on it.

void Connect4_AI::MarkHorizontal(Connect4_AI::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redh;
                    tab[i][start+1] = Redh;
                    tab[i][start+2] = Redh;
                    tab[i][start+3] = Redh;
                }
                
                else{
                    tab[i][start] = Yellowh;
                    tab[i][start+1] = Yellowh;
                    tab[i][start+2] = Yellowh;
                    tab[i][start+3] = Yellowh;
                }
                break;
            }
        }
    }
}

void Connect4_AI::MarkVertical(Connect4_AI::Tiles tab[6][7]){
    int start;
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                
                if (tab[start][j] == Red) {
                    
                    tab[start][j] = Redv;
                    tab[start+1][j] = Redv;
                    tab[start+2][j] = Redv;
                    tab[start+3][j] = Redv;
                }
                
                else{
                    tab[start][j] = Yellowv;
                    tab[start+1][j] = Yellowv;
                    tab[start+2][j] = Yellowv;
                    tab[start+3][j] = Yellowv;
                }
                break;
            }
        }
    }
}

void Connect4_AI::MarkAD(Connect4_AI::Tiles tab[6][7]){
    int start;
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Redad;
                    tab[i-1][start+1] = Redad;
                    tab[i-2][start+2] = Redad;
                    tab[i-3][start+3] = Redad;
                }
                
                else{
                    tab[i][start] = Yellowad;
                    tab[i-1][start+1] = Yellowad;
                    tab[i-2][start+2] = Yellowad;
                    tab[i-3][start+3] = Yellowad;
                }
                break;
            }
        }
    }
    
}

void Connect4_AI::MarkDD(Connect4_AI::Tiles tab[6][7]){
    int start;
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                if (tab[i][start] == Red) {
                    tab[i][start] = Reddd;
                    tab[i+1][start+1] = Reddd;
                    tab[i+2][start+2] = Reddd;
                    tab[i+3][start+3] = Reddd;
                }
                
                else{
                    tab[i][start] = Yellowdd;
                    tab[i+1][start+1] = Yellowdd;
                    tab[i+2][start+2] = Yellowdd;
                    tab[i+3][start+3] = Yellowdd;
                }
                break;
            }
        }
    }
}

///// IsGameWon is a boolean function that checks if there are winning combinations overall. Also, it updates the winner identity.

bool Connect4_AI::IsGameWon(Connect4_AI::Tiles tab[6][7]){
    int start;
    bool won = false;
    
    ///// HORIZONTAL
    
    for (int i = 0; i< 6; i++){
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty)){
                won = true;
                
                if (tab[i][start] == Bot_Tile) {
                    Winner = bot;
                    
                }
                
                else{
                    Winner = player1;
                    
                }
                
                break;
            }
        }
    }
    
    ////// VERTICAL
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 3; start++){
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j] && tab[start+2][j] == tab[start+3][j]) && (tab[start][j] != Empty)) {
                won = true;
                
                if (tab[start][j] == Bot_Tile) {
                    Winner = bot;
                }
                
                else{
                    Winner = player1;
                }
                break;
            }
        }
    }
    
    ///// Ascending diagonal
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2] && tab [i-2][start+2] == tab [i-3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Bot_Tile) {
                    Winner = bot;
                }
                
                else{
                    Winner = player1;
                }
                break;
            }
        }
    }
    
    ///// Descending diagonal
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2] && tab [i+2][start+2] == tab [i+3][start+3]) && (tab[i][start] !=Empty)){
                won = true;
                if (tab[i][start] == Bot_Tile) {
                    Winner= bot;
                }
                
                else{
                    Winner = player1;
                }
                break;
            }
        }
    }
    
    return won;
}

///// IsBoardFull is another boolean that checks if the board is full or not.

bool Connect4_AI::IsBoardFull(Connect4_AI::Tiles tab[6][7]){
    bool res = true;
    
    for (int j = 0; j<7; j++) {
        if (tab[0][j] == Empty) {
            res = false;
            break;
        }
    }
    
    return res;
};

///// IsGameOver is the combination of the previous two boolean functions.

bool Connect4_AI::IsGameOver(Connect4_AI::Tiles tab[6][7]){
    if (IsGameWon(tab) == true || IsBoardFull(tab) == true) {
        return true;
    }
    
    else{
        return false;
    }
};

///// OnExecute is the Core of our Game Execution. It implements the Events management that serves us to make the game moves, mostly.

int Connect4_AI::OnExecute(){
    
    // OnInit check
    
    if(OnInit() == false){
        return -1;
    }
    
    // We define an event
    
    SDL_Event Event;
    
    // watchdog is a variable that prevents the "capriciousness" of the MouseButton.
    // We'd like that a "Left click" in MouseButtonDown event represents the player making the move, and the MouseButtonUp event represents the AI making the move. However, we don't want the AI making the move before the player does. So if the program enters the undesired event, watchdog stays at 0.
    
    int watchdog = 0;
    
    if (Firstplayer == bot) {
        
        if (depth < 4) {
            
            int col = rand()% 7;
            
            int row = RowforPlay(col);
            
            SetCell(row, col, Bot_Tile);
            
        }
        
        else{
        
            int row = RowforPlay(3);
            SetCell(row, 3, Bot_Tile);
        }
        
    }
    
    while(Running ==1) {
        
        // We wait for the player to make an event
        
        SDL_WaitEvent(&Event);
        
        switch (Event.type) {
                
            case SDL_QUIT:
                Running = 0;
                break;
                
                // Pressing Esc can make you break.
                
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                
                if (Event.button.button == SDL_BUTTON_LEFT) {
                    
                    // We update watchdog.
                    
                    watchdog = 1;
                    
                    // We check if the Game is over; if so we break.
                    
                    if (IsGameOver(Grid) == true) {
                        Running = 0;
                        break;
                    }
                    
                    Currentplayer = player1;
                    CurrentTile = P1_Tile;
                    
                    checkmouse(&Event.button);
                    
                    if (IsGameWon(Grid) == true) {
                        if (HorizontalWin(Grid) == true) {
                            MarkHorizontal(Grid);
                        }
                        
                        if (VerticalWin(Grid) == true) {
                            MarkVertical(Grid);
                        }
                        
                        if (ADWin(Grid) == true) {
                            MarkAD(Grid);
                        }
                        
                        if (DDWin(Grid) == true) {
                            MarkDD(Grid);
                        }
                    }
                }
                break;
            
            case SDL_MOUSEBUTTONUP:
                
                if (Event.button.button == SDL_BUTTON_LEFT){
                    if (watchdog == 0) {
                        Running = 1;
                        break;
                    }
                    
                    if (IsGameOver(Grid) == true) {
                        Running = 0;
                        break;
                    }
                    
                    Currentplayer = bot;
                    CurrentTile = Bot_Tile;
                    
                    botplays(depth, CurrentTile);
                    
                    if (IsGameWon(Grid) == true) {
                        if (HorizontalWin(Grid) == true) {
                            MarkHorizontal(Grid);
                        };
                        
                        if (VerticalWin(Grid) == true) {
                            MarkVertical(Grid);
                        };
                        
                        if (ADWin(Grid) == true) {
                            MarkAD(Grid);
                        };
                        
                        if (DDWin(Grid) == true) {
                            MarkDD(Grid);
                        };
                    }
                }
                break;
        }

        OnRender();
    }
    
    OnCleanup();
    OnExit();
    
    return 0;
}


///////////////////////////////**************************************/////////////////////////////////////
///////////////////////////////   Second part : Setting up the AI      ///////////////////////////////////
///////////////////////////////**************************************/////////////////////////////////////


// RowforPlay returns the row number of the selected column.

int Connect4_AI::RowforPlay(int ColID){
    
    int row;
    
    for (int i=5; i>=0; i--) {
        if (Grid[i][ColID] == Empty) {
            row = i;
            break;
        }
    }
    return row;
}

// IsColFull checks if the argument column is full.

bool Connect4_AI::IsColFull(int ColID){
    
    if (Grid[0][ColID] != Empty) {
        return true;
    }
    
    else{
        return false;
    }
}

// Classic Maximum and Minimum functions.

int Connect4_AI::Maximum(int a, int b){
    if (a <=b) {
        return b;
    }
    
    else {
        return a;
    }
}

int Connect4_AI::Minimum(int a, int b){
    if (a >=b) {
        return b;
    }
    
    else {
        return a;
    }
}

// CheckThrees is a function that checks for a player the number of 3-series combinations in the game. The more 3-series combos the player has, the higher the score.

int Connect4_AI::CheckThrees(Connect4_AI::Tiles tab[6][7], Connect4_AI::PlayerT player){
    Tiles mark;
    int score =0;
    
    if (player == bot) {
        mark = Bot_Tile;
    }
    
    else{
        mark = P1_Tile;
    }
    
    int start;
    
    // Horizontal Threes. 3 cases : "xxx" / "xx x" / "x xx". Make sure that it's not a "dead end", i.e. that there are empty spots remaining right or lift of the series. For more information, please read the joined report.
    
    for (int i = 0; i<6; i++) {
        
        for (start = 0; start<5; start++) {
            
            if ((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+2]) && (tab[i][start] != Empty) && (tab[i][start - 1] == Empty || tab[i][start+3] == Empty)) {
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if((tab[i][start] == tab[i][start+2] && tab[i][start+2] == tab[i][start+3]) && (tab[i][start] != Empty) && (start<4) && tab[i][start+1] == Empty){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if((tab[i][start] == tab[i][start+1] && tab[i][start+1] == tab[i][start+3]) && (tab[i][start] != Empty) && (start<4) && tab[i][start+2] == Empty){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    // Vertical Threes. One case only, but make sure that there is nothing at the top of the 3-series.
    
    for (int j = 0; j< 7 ;j++){
        for (start = 0 ; start < 4; start++){
            
            if ((tab[start][j] == tab[start+1][j] && tab[start+1][j] == tab[start+2][j]) && (tab[start][j] != Empty) && (tab[start-1][j] == Empty)){
                
                if (tab[start][j] == mark){
                    score += 1;
                }
            }
        }
    }
    
    
    // Ascending diagonal Threes. Please check report for detailed information.

    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            
            if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-2][start+2]) && (tab[i][start] !=Empty) && (tab[i+1][start-1] == Empty || tab[i-3][start+3] == Empty) ){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if ((tab[i][start] == tab[i-1][start+1] && tab[i-1][start+1] == tab[i-3][start+3]) && (tab[i][start] !=Empty) && (start+3 < 7) && tab[i-2][start+2]==Empty){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if ((tab[i][start] == tab[i-2][start+2] && tab[i-2][start+2] == tab[i-3][start+3]) && (tab[i][start] !=Empty) && (start+3 < 7) && (tab[i-1][start+1]==Empty)){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    // Descending Diagonal Threes. More details in report.
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+2][start+2]) && (tab[i][start] !=Empty) && (tab[i+3][start+3] == Empty || tab[i-1][start-1] == Empty)){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if ((tab[i][start] == tab[i+1][start+1] && tab[i+1][start+1] == tab[i+3][start+3]) && (tab[i][start] !=Empty) && tab[i+2][start+2]==Empty){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
            
            else if ((tab[i][start] == tab[i+2][start+2] && tab[i+2][start+2] == tab[i+3][start+3]) && (tab[i][start] !=Empty) && tab[i+1][start+1]==Empty){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    return score;
}

// CheckThrees is a function that checks for a player the number of 2-series combinations in the game. The more 2-series combos the player has, the higher the score.

// NB : there can be more listed cases for the Ascending and Descending Diagonals; however since our game is limited in its dimensions so the chances that these situations happening are scarce.

int Connect4_AI::CheckTwos(Connect4_AI::Tiles tab[6][7], Connect4_AI::PlayerT player){
    Tiles mark;
    int score =0;
    
    if (player == bot) {
        mark = Bot_Tile;
    }
    
    else{
        mark = P1_Tile;
    }
    int start;
    
    // Horizontal : two aligned (condition : there is nothing on the immediate left or the immediate right; or separated by a blank.
    
    for (int i = 0; i<6; i++) {
        
        for (start = 0; start<7; start++) {
            
            if ((tab[i][start] == tab[i][start+1] && (tab[i][start] != Empty) && (tab[i][start - 1] == Empty || tab[i][start+2] == Empty))) {
                
                if (tab[i][start] == mark){
                    score += 1;
                }
                
            }
            
            //// Separated by one blank
            
            if ((tab[i][start] == tab[i][start+2] && (tab[i][start] != Empty) && (tab[i][start+1] == Empty))) {
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    // Vertical : one case. Two superposed at the condition that there is nothing immediately over the series of 2
    
    for (int j = 0; j< 7 ;j++){
        for (start = 1 ; start < 6; start++){
            
            if ((tab[start][j] == tab[start+1][j] && (tab[start][j] != 0)) && (tab[start-1][j] == Empty)){
                
                if (tab[start][j] == mark){
                    score += 1;
                }
            }
        }
    }
    
    // Ascending Diagonal.
    
    for (int i = 3; i< 6; i++) {
        for (start = 0; start < 4; start++){
            
            if ((tab[i][start] == tab[i-1][start+1] && (tab[i][start] !=Empty)) && (tab[i+1][start - 1] == Empty || tab[i-2][start+2] == Empty)){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    // Descending Diagonal.
    
    for (int i = 0; i< 3; i++) {
        for (start = 0; start < 4; start++){
            if ((tab[i][start] == tab[i+1][start+1] && (tab[i][start] !=Empty)
                 && (tab[i+2][start+2] == Empty || tab[i-1][start-1] == Empty))){
                
                if (tab[i][start] == mark){
                    score += 1;
                }
            }
        }
    }
    
    return score;
}

// Eval is the "Heuristic Evaluation" function. It returns MAX_VALUE if the player has a winning 4-combo; MIN_VALUE if the opponents does. Otherwise, the score is computed as the following :
//                                  10 * #Twos + 100 * #Threes.

int Connect4_AI::Eval(Connect4_AI::Tiles tab[6][7], PlayerT player){
    
    PlayerT opponent;
    
    if (player == player1) {
        opponent = bot;
    }
    
    else{
        opponent = player1;
    }
    
    int score = 0;
    int twosplayer;
    int threesplayer;
    int twosopponent;
    int threesopponent;
    
    if (IsGameWon(Grid)==true) {
        if (player == Winner) {
            score = MAX_VALUE;
        }
        
        else{
            score = MIN_VALUE;
        }
    }
    
    else{
        twosplayer = CheckTwos(Grid, player);
        threesplayer = CheckThrees(Grid, player);
        twosopponent = CheckTwos(Grid, opponent);
        threesopponent = CheckThrees(Grid, opponent);
        
        score = twosplayer * 10 + threesplayer * 100 - twosopponent * 10 - threesopponent * 100;
        
    }
    
    return score;
    
}

// We used Alpha_Beta algorithm to compute the best response function. It is an enhanced version of the recursive Minimax algorithm : it optimises the computation time. Please refer to the report for futher details.

int Connect4_AI::Alpha_Beta(Connect4_AI::Tiles tab[6][7], int depth, int alpha, int beta, Connect4_AI::PlayerT player){
    
    PlayerT opponent;
    PlayerT maxplayer = Firstplayer;
    
    if (player == player1) {
        opponent = bot;
    }
    
    else{
        opponent = player1;
    }
    
    int score = 0;
    
    /// We add a termination condition of the recursion : if GameOver or depth has reached 0.
    
    if (depth==0 || IsGameOver(tab)==true) {
        
        //// We distinguish the minimizing player and the maximizing player as their strategy is not the same, so they should return different results depending on their role.
        
        if (player !=maxplayer) {
            if (IsGameWon(tab)==true) {
                if (opponent == Winner) {
                    score = MAX_VALUE;
                }
                else{
                    score = MIN_VALUE;
                }
            }
            
            else    {
                score = Eval(Grid, opponent);
            }
        }
        
        else {
            if (IsGameWon(tab)==true) {
                if (opponent == Winner) {
                    score = MIN_VALUE;
                }
                else{
                    score = MAX_VALUE;
                }
            }
            
            else    {
                score = Eval(Grid, player);
            }
            
        }
        return score;
    }
    
    // The Firstplayer is always the maximizing player !
    
    if (player == maxplayer) {
        Tiles type = MaximizerTile;
        int val = MIN_VALUE;
        for (int colun=0; colun < 7; colun++) {
            if (IsColFull(colun) == false) {
                
                int row = RowforPlay(colun);
                
                SetCell(row, colun, type);
                
                val = Maximum(val, Alpha_Beta(Grid, depth - 1, alpha, beta, opponent));
                alpha = Maximum(alpha,val);
                
                EraseCell(row,colun);
                
                if (beta <= alpha) {
                    break;
                }
            }
        }
        
        return val;
    }
    
    else {
        Tiles type = MinimizerTile;
        int val = MAX_VALUE;
        for (int colun=0; colun < 7; colun++) {
            if (IsColFull(colun) == false) {
                
                int row = RowforPlay(colun);
                
                SetCell(row,colun,type);
                
                val = Minimum(val, Alpha_Beta(Grid, depth-1, alpha, beta, opponent));
                beta = Minimum(beta, val);
                
                EraseCell(row,colun);
                
                if (beta <= alpha) {
                    break;
                }
            }
        }
        
        return val;
    }
}


// MakeBotPlay returns the best column for which the computer has the better expectations. We use the Alpha_beta algorithm to implement it. NB : we initialized the column at 7, knowing the column index in our game stops at 6. Therefore, if the AI is indecise, we force it to pick a column where the column is not full.

int Connect4_AI::MakeBotPlay(Connect4_AI::Tiles tab[6][7], int depth, Connect4_AI::PlayerT player, Connect4_AI::Tiles type){
    
    int bestmax = MIN_VALUE;
    int bestmin = MAX_VALUE;
    int temp;
    int choice = 7;
    
    PlayerT opponent;
    PlayerT maxplayer = Firstplayer;
    
    if (player == player1) {
        opponent = bot;
    }
    
    else{
        opponent = player1;
    }
    
    for (int colun=0; colun < 7; colun++) {
        if (IsColFull(colun)==false) {
            
            int row = RowforPlay(colun);
            
            SetCell(row, colun, type);
            
            temp = Alpha_Beta(Grid, depth, MIN_VALUE, MAX_VALUE, opponent);
            
            if (player == maxplayer) {
                if (temp > bestmax) {
                    bestmax = temp;
                    choice = colun;
                }
            }
            
            else{
                if (temp < bestmin) {
                    bestmin = temp;
                    choice = colun;
                }
            }
            
            EraseCell(row,colun);
            
        }
    }
    
    /// To avoid any indecision ...
    
    if (choice == 7) {
        for(int l = 0; l < 6; l++){
            for (int j = 0; j<7; j++) {
                if (tab[l][j] == Empty) {
                    choice = j;
                    break;
                }
            }
        }
    }
    
    return choice;
}

// Botplays gathers the turn for the Bot.

void Connect4_AI::botplays(int depth, Connect4_AI::Tiles type){
    
    int Col = MakeBotPlay(Grid, depth, bot, type);
    
    int Row = RowforPlay(Col);
    
    SetCell(Row, Col, type);
}


///////////////////////////////**************************************/////////////////////////////////////
///////////////////////////////      Final part : SDL Details        /////////////////////////////////////
///////////////////////////////**************************************/////////////////////////////////////


// Rendering it all : we blit the corresponding sprites and we actualize it via SDL_Flip.

void Connect4_AI::OnRender(){
    
    CSurface::OnDraw(Surf_Display,empty,0,0);
    
    int w = WIDTH/7, h= HEIGHT/6, i, j, k, l;
    
    SDL_Rect r = {0};
    
//    SDL_BlitSurface(empty,NULL,Surf_Display,&r);
    
    for (k= 0, i=0; i<HEIGHT; i+=h,k++) {
        r.y=i;
        for (l=0,j=0; j<WIDTH; j+=w,l++) {
            r.x=j;
            
            if (Grid[k][l]==Red) {
                SDL_BlitSurface(red,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l]==Yellow){
                SDL_BlitSurface(yellow,NULL,Surf_Display,&r);
            }
            
            
            else if (Grid[k][l] == Redh){
                SDL_BlitSurface(redh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowh){
                SDL_BlitSurface(yellowh,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redv){
                SDL_BlitSurface(redv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowv){
                SDL_BlitSurface(yellowv,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Redad){
                SDL_BlitSurface(redad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowad){
                SDL_BlitSurface(yellowad,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Reddd){
                SDL_BlitSurface(reddd,NULL,Surf_Display,&r);
            }
            
            else if (Grid[k][l] == Yellowdd){
                SDL_BlitSurface(yellowdd,NULL,Surf_Display,&r);
            }
        }
    }
    
    SDL_Flip(Surf_Display);
    
}

// We end up clearing memory. 

void Connect4_AI::OnCleanup(){
    SDL_FreeSurface(Surf_Display);
    SDL_FreeSurface(red);
    SDL_FreeSurface(yellow);
    SDL_FreeSurface(redh);
    SDL_FreeSurface(redv);
    SDL_FreeSurface(redad);
    SDL_FreeSurface(reddd);
    SDL_FreeSurface(yellowv);
    SDL_FreeSurface(yellowh);
    SDL_FreeSurface(yellowad);
    SDL_FreeSurface(yellowdd);
}

void Connect4_AI::OnExit(){
    SDL_Quit();
}
