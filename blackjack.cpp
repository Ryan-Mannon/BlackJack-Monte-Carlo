#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;


//deck with each face card counting as a 10
//TODO: 
//Add in aces for either a 1 or 11
//so far I have to where each ace counts as an 11. If the hand is greater than 21 then subtract 10 for each ace until hand is less than 21
const int deckSize = 52;
int pHand = 0;
int aceCounter = 0;
int dHand = 0;
int gameResult;     //0 for loss 1 for tie 2 for win
int score;

int deck[deckSize] = {11,11,11,11,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 

void aceCheck (){
    if(pHand > 21 && aceCounter > 0){
        pHand -= 10;
        aceCounter--;
    }
}

int result(){
    if (pHand > 21)
        return 0;
    if (pHand == dHand)
        return 1;
    if(dHand > 21)
        return 2;
    if(pHand > dHand)
        return 2;
    return -1;
}

//simple function to draw a card from deck
int hit() {
    // Generate a random index for array
    int index = rand() % deckSize;
    pHand += deck[index];
    if (deck[index] == 11 ){
        aceCounter++;
    }
    //cout << "added " << deck[index] << endl;    //for testing
    return deck[index];
}

int dHit() {
    // Generate a random index for array
    int index = rand() % deckSize;
    dHand += deck[index];
    if (deck[index] == 11 ){
        aceCounter++;
    }
    return deck[index];
}


int startingHand(){
    hit();
    hit();
    return pHand;
}


//Dealer will hit until they get 17 or above
int dealerHand(){
    while (dHand < 17){
        dHit();
    }
    return dHand;
}

int runPolicy(int policy, int gamesPlayed){
    gameResult = result();

    switch (gameResult)
    {
    case 0:
        score--;
        break;
    case 1:
        break;
    case 2:
        score++;
        break;
    default:
        break;
    }
    
    switch (policy)
    {
    case 1:
        for(int i = 0; i < gamesPlayed; i++){
            while(pHand < 17){
                startingHand();
                dealerHand();
                hit();
            }
        }
        break;
    
    default:
        break;
    }
    double winRate = score/gamesPlayed;
    cout << score;
    return winRate;
}

int main(){
    srand(time(NULL));      //random time seed

    //policy then games played
    cout << runPolicy(1,10);
    

return 0;
}