#include <iostream>
#include <stdio.h>
#include "SDL/SDL.h"
#include "Connect4.h"
#include <stdio.h>
#include <stdlib.h>
#include "Start.h"
#include <ctime>



int main(int argc,char*argv[]){
    
    srand(unsigned(time(0)));
    
    StartMenu start;
    return start.showmenu();
}
