#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;


//deck with each face card counting as a 10
//TODO: Add in aces for either a 1 or 11
const int deckSize = 52;
int hand = 0;

int deck[deckSize] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 

//simple function to draw a card from deck
int hit() {
    // Generate a random index for array
    int index = rand() % deckSize;
    if (deck[index] == 1 && hand <=10){
        cout << "added 11" << endl;    //for testing
        hand += 11;
        return deck[index];
    } else if(deck[index]==1) {
        cout << "added 1" << endl;    //for testing
        hand += 1;
        return deck[index];
    }
    cout << "added " << deck[index] << endl;    //for testing
    hand += deck[index];
    return deck[index];
}

int startingHand(){
    hit();
    hit();
    return hand;
}

int main(){
    srand(time(NULL));      //random time seed

    startingHand();
    cout << "hand:" << hand;
    

    /*for(int i = 0; i < 10; i++){
        int h = hit();
        cout << h << endl;
    }*/

return 0;
}