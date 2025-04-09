#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

//deck with each face card counting as a 10
//TODO: Add in aces for either a 1 or 11
const int deckSize = 52;

int deck[deckSize] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 

//simple function to draw two cards assuming infinite deck
int drawHand(){
    int hand = 0;
    hand += deck[rand()%52];
    hand += deck[rand()%52];
return hand;
}


int main(){

    int seed = 12345;
    srand(time(NULL));      //random time seed

    for(int i = 0; i < 10; i++){
        int h = drawHand();
        cout << h << endl;
    }

return 0;
}