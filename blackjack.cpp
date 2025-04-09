#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

//uses strings but also can use ints (10 for face cards)
vector<string> deck = {
    "2","3","4","5","6","7","8","9","10",
    "J","Q","K","A",
    "2","3","4","5","6","7","8","9","10",
    "J","Q","K","A",
    "2","3","4","5","6","7","8","9","10",
    "J","Q","K","A",
    "2","3","4","5","6","7","8","9","10",
    "J","Q","K","A"
};

//string to number
int cardValue(string card) {
    if (card == "J" || card == "Q" || card == "K") return 10;
    if (card == "A") return 11; //ace is initially an 11
    return atoi(card.c_str()); //ascii to integer for 2-10
}

// Calculates the value of a hand, adjusting Aces from 11 → 1 as needed for soft or hard hands
int handValue(const vector<string>& hand) {
    int total = 0;
    int aces = 0; //aces counter

    for (int i = 0; i < hand.size(); ++i) {
        int val = cardValue(hand[i]);
        total += val;
        if (hand[i] == "A") aces++;
    }

    //convert 'soft' hands to hard hands if over 21
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    return total;
}
//checks to see if there are no aces. If so, just calculate card values 
bool isHard(const vector<string>& hand) {
    int total = 0, aces = 0;
    for (int i = 0; i < hand.size(); ++i) {
        int val = cardValue(hand[i]);
        total += val;
        if (hand[i] == "A") aces++;
    }
    return !(aces > 0 && total <= 21); //if aces and < 21 ... true before flipping with '!'
}

//draws cards from both decks.
string drawCard(bool infinite, vector<string>& gameDeck) {
    if (infinite) {
        int index = rand() % deck.size();
        return deck[index];
    } else {
        int index = rand() % gameDeck.size();
        string card = gameDeck[index];
        gameDeck.erase(gameDeck.begin() + index); //remove card that was drawn
        return card;
    }
}

// Policies are booleans to determine if the simulated player needs to hit or stick depending on the policy
// For example in policy if the hand is less than 17 then you boolean return true meaning you need to 'hit'

// Policy 1: Stick on 17 or higher
bool policy1(const vector<string>& hand) {
    return handValue(hand) < 17;
}

// Policy 2: Stick if 17+ and hard hand, else hit unless 21
bool policy2(const vector<string>& hand) {
    int val = handValue(hand);
    if (val == 21) return false;
    if (val >= 17 && isHard(hand)) return false;
    return true;
}

// Policy 3: Always stick
bool policy3(const vector<string>& hand) {
    return false; // always stick
}

// Policy 4: Custom - hit under 15
bool policy4(const vector<string>& hand) {
    return handValue(hand) < 15; // custom policy
}

// Policy 5: Custom aggressive - hit under 19
bool policy5(const vector<string>& hand) {
    return handValue(hand) < 19; // custom aggressive
}

// Simulates one game of Blackjack with the given policy and deck type
// Returns: 1 = win, 0 = draw, -1 = loss 
// Not yet looped
int simulateGame(bool (*policy)(const vector<string>&), bool infiniteDeck) {
    vector<string> gameDeck = deck; 
    //player and dealer hands
    vector<string> player = { drawCard(infiniteDeck, gameDeck), drawCard(infiniteDeck, gameDeck) };
    vector<string> dealer = { drawCard(infiniteDeck, gameDeck), drawCard(infiniteDeck, gameDeck) };

    //While policy is true meaning the player still needs to hit
    while (policy(player)) {
        player.push_back(drawCard(infiniteDeck, gameDeck));
        if (handValue(player) > 21) return -1; // player busts
    }

    // Rules for dealer play till 17 or bust
    while (handValue(dealer) < 17) {
        dealer.push_back(drawCard(infiniteDeck, gameDeck));
    }


    int p = handValue(player);
    int d = handValue(dealer);

    if (d > 21 || p > d) return 1; //player win or dealer loses
    if (p == d) return 0;         // Draw
    return -1;                   //  Player Loss
}

//Monte Carlo simulations with win/loss/draw percentages 
void evaluatePolicy(string name, bool (*policy)(const vector<string>&), int runs = 100000) { //size that never changes and is only used here. Easier to declare here because of that
    int infWins = 0, infLosses = 0, infDraws = 0;
    int deckWins = 0, deckLosses = 0, deckDraws = 0;

    for (int i = 0; i < runs; ++i) {
        //result for infite deck
        int res1 = simulateGame(policy, true); // simulateGame(policy, bool infinite deck)
        if (res1 == 1) infWins++;
        else if (res1 == -1) infLosses++;
        else infDraws++;

        //result when discarding drawn cards from deck
        int res2 = simulateGame(policy, false);
        if (res2 == 1) deckWins++;
        else if (res2 == -1) deckLosses++;
        else deckDraws++;
    }

    // Helper to print win/loss/draw as percentages
    // Needed [&] because it can access and modify variables from the outer scope
    // so if you have a loop or function where the number of wins, losses, or draws is updated dynamically,
    // the lambda can print the current values.
    auto printStats = [&](int wins, int losses, int draws) {
        double winRate = 100.0 * wins / runs;
        double drawRate = 100.0 * draws / runs;
        double lossRate = 100.0 - winRate - drawRate;
        cout << "    Win Rate:  " << winRate << "%\n";
        cout << "    Loss Rate: " << lossRate << "%\n";
        cout << "    Draw Rate: " << drawRate << "%\n";
    };

    // Code to help with policy and deck identity
    cout << "Policy: " << name << endl;
    cout << "  Infinite Deck:\n";
    printStats(infWins, infLosses, infDraws);
    cout << "  Single Deck:\n";
    printStats(deckWins, deckLosses, deckDraws);
    cout << "--------------------------" << endl;
}

int main() {
    srand(time(NULL)); // Sets random seed can change to an int if want to test specific seed (ex. srand(1234))

    evaluatePolicy("Policy 1: Stick on 17+", policy1);
    evaluatePolicy("Policy 2: Stick on Hard 17+", policy2);
    evaluatePolicy("Policy 3: Always Stick", policy3);
    evaluatePolicy("Policy 4: Hit under 15", policy4);
    evaluatePolicy("Policy 5: Hit under 19 (aggressive)", policy5);

    return 0;
}
