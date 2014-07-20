// A text-based Blackjack game.
//
// Author: Christos Samaras
//
// Rules and assumptions:
//     There is 1 dealer.
//     There is only 1 player.
//     The dealing shoe contains 1 standard 52-card deck.
//     A Blackjack game consists of 1 or more rounds.
//     The deck is shuffled between each round.
//     The player starts with 100 chips.
//     The player must bet at least 1 chip each hand.
//     There is no limit to maximum bet.
//     Side bets are not allowed.
//     Doubling down, splitting, and surrendering are not supported.
//     The dealer should hit until his hand value is 17 or greater.
//     The dealer must stand on soft-17.
//     Two aces count as 12.
//     All wins are paid out at 1:1 (i.e., equal to the bet).

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <exception>

class CustomExceptionWithErrorMessage: public std::exception {
private:
    std::string errorMessage;

public:
    CustomExceptionWithErrorMessage(std::string message) {
        errorMessage = message;
    }

    ~CustomExceptionWithErrorMessage() throw() {}

    virtual const char* what() const throw() {
        return errorMessage.c_str();
    }
};

enum CardRank {
    Ace = 0,
    Two = 1,
    Three = 2,
    Four = 3,
    Five = 4,
    Six = 5,
    Seven = 6,
    Eight = 7,
    Nine = 8,
    Ten = 9,
    Jack = 10,
    Queen = 11,
    King = 12
};

enum CardSuit {
    Spades = 0,
    Hearts = 1,
    Diamonds = 2,
    Clubs = 3
};

class Card {
private:
    CardRank cardRank;
    CardSuit cardSuit;
    int cardValue;

    int computeCardValue() {
        int cardValue = 0;
        switch(cardRank) {
            case Ace:
                cardValue = 1;
                break;
            case Two:
                cardValue = 2;
                break;
            case Three:
                cardValue = 3;
                break;
            case Four:
                cardValue = 4;
                break;
            case Five:
                cardValue = 5;
                break;
            case Six:
                cardValue = 6;
                break;
            case Seven:
                cardValue = 7;
                break;
            case Eight:
                cardValue = 8;
                break;
            case Nine:
                cardValue = 9;
                break;
            case Ten:
                cardValue = 10;
                break;
            case Jack:
                cardValue = 10;
                break;
            case Queen:
                cardValue = 10;
                break;
            case King:
                cardValue = 10;
                break;
            default:
                throw CustomExceptionWithErrorMessage("Error: card rank is not identified.");
                break;
        }
        return cardValue;
    }

public:
    Card(CardRank rank, CardSuit suit) {
        cardRank = rank;
        cardSuit = suit;
        cardValue = computeCardValue();
    }

    CardRank getCardRank() {
        return cardRank;
    }

    CardSuit getCardSuit() {
        return cardSuit;
    }

    int getCardValue() {
        return cardValue;
    }

    // example: "Ace of Hearts"
    std::string getCardInTextFormat() {
        std::string rankInText = getCardRankInTextFormat();
        std::string suitInText = getCardSuitInTextFormat();
        std::string cardInText = rankInText + " of " + suitInText;
        return cardInText;
    }

    std::string getCardRankInTextFormat() {
        std::string rankInText = "";
        switch(cardRank) {
            case Ace:
                rankInText = "Ace";
                break;
            case Two:
                rankInText = "2";
                break;
            case Three:
                rankInText = "3";
                break;
            case Four:
                rankInText = "4";
                break;
            case Five:
                rankInText = "5";
                break;
            case Six:
                rankInText = "6";
                break;
            case Seven:
                rankInText = "7";
                break;
            case Eight:
                rankInText = "8";
                break;
            case Nine:
                rankInText = "9";
                break;
            case Ten:
                rankInText = "10";
                break;
            case Jack:
                rankInText = "Jack";
                break;
            case Queen:
                rankInText = "Queen";
                break;
            case King:
                rankInText = "King";
                break;
            default:
                throw CustomExceptionWithErrorMessage("Error: card rank is not identified.");
                break;
        }
        return rankInText;
    }

    std::string getCardSuitInTextFormat() {
        std::string suitInText = "";
        switch(cardSuit) {
            case Spades:
                suitInText = "Spades";
                break;
            case Hearts:
                suitInText = "Hearts";
                break;
            case Diamonds:
                suitInText = "Diamonds";
                break;
            case Clubs:
                suitInText = "Clubs";
                break;
            default:
                throw CustomExceptionWithErrorMessage("Error: card suit is not identified.");
                break;
        }
        return suitInText;
    }

    bool isAce() {
        if (cardRank == Ace) {
            return true;
        } else {
            return false;
        }
    }
};

class BlackjackPresenter {
private:
    std::string appendTrailingCharacterS(int quantity) {
        std::string trailingCharacterS = ""; // singular number ("s" character is not appended)
        if (quantity > 1) {
            trailingCharacterS = "s"; // plural number ("s" character is appended)
        }
        return trailingCharacterS;
    }

public:
    void displayWelcomeMessage() {
        std::cout << std::endl;
        std::cout << "Welcome to Blackjack! Enjoy your play." << std::endl;
        std::cout << std::endl;
    }

    void displayGoodbyeMessage() {
        std::cout << std::endl;
        std::cout << "We hope you had a great time and to see you again soon!" << std::endl;
        std::cout << std::endl;
    }

    void announceStartOfRound() {
        std::cout << std::endl;
        std::cout << "A new Blackjack round begins." << std::endl;
        std::cout << std::endl;
    }

    void announceEndOfRound() {
        std::cout << "Current Blackjack round is over." << std::endl;
        std::cout << std::endl;
    }

    void displayPlayerAvailableChipsToBetWith(int playerChipsToPlay) {
        std::string trailingCharacterS = appendTrailingCharacterS(playerChipsToPlay);
        std::cout << "You have " << playerChipsToPlay << " chip" << trailingCharacterS << " to bet with." << std::endl;
    }

    int askPlayerToBetChips(int minimumBet, int maximumBet) {
        int playerBetInChips = 0;
        std::cout << "Place your bet please (minimum bet is 1):  ";
        while (!(std::cin >> playerBetInChips) || playerBetInChips < minimumBet || playerBetInChips > maximumBet) {
            std::cout << "Please try to bet again. Your bet should be a number between 1 and up to your available chips:  ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string trailingCharacterS = appendTrailingCharacterS(playerBetInChips);
        std::cout << "Your bet is " << playerBetInChips << " chip" << trailingCharacterS << "." << std::endl;
        return playerBetInChips;
    }

    void displayPlayerHand(std::string playerHandInTextFormat) {
        std::cout << "Your hand contains:  " << playerHandInTextFormat << std::endl;
    }

    void displayPlayerHandValue(int playerHandValue) {
        std::cout << "Your hand value is:  " << playerHandValue << std::endl;
    }

    void displayDealerHand(std::string dealerHandInTextFormat) {
        std::cout << "Dealer's hand contains:  " << dealerHandInTextFormat << std::endl;
    }

    void displayDealerHandValue(int dealerHandValue) {
        std::cout << "Dealer's hand value is:  " << dealerHandValue << std::endl;
    }

    void announceSecondCardOfDealerIsHidden() {
        std::cout << "Dealer's second card remains hidden." << std::endl;
    }

    bool askPlayerForAdditionalCard() {
        std::cout << "Would you like 1 more card (y/n)?  ";
        std::string playerResponse = "";
        getline(std::cin, playerResponse);
        transform(playerResponse.begin(), playerResponse.end(), playerResponse.begin(), ::tolower);
        while (!(playerResponse == "y") && !(playerResponse == "yes") && !(playerResponse == "n") && !(playerResponse == "no")) {
            std::cout << "Would you like 1 more card (y/n)? Please type 'y' or 'n' (without the quotes):  ";
            getline(std::cin, playerResponse);
            transform(playerResponse.begin(), playerResponse.end(), playerResponse.begin(), ::tolower);
        }
        bool playerWantsToGetOneAdditionalCard = false;
        if (playerResponse == "y" || playerResponse == "yes") {
            playerWantsToGetOneAdditionalCard = true;
        }
        if (playerResponse == "n" || playerResponse == "no") {
            playerWantsToGetOneAdditionalCard = false;
        }
        return playerWantsToGetOneAdditionalCard;
    }

    void announcePlayerWins() {
        std::cout << "You win." << std::endl;
    }

    void announcePlayerPushes() {
        std::cout << "You push." << std::endl;
    }

    void announcePlayerLoses() {
        std::cout << "You lose." << std::endl;
    }

    void displayPlayerCurrentNumberOfChips(int currentNumberOfChips) {
        std::cout << "Your current number of chips is " << currentNumberOfChips << "." << std::endl;
    }

    void displayRegretMessageNoChips() {
        std::cout << "Sorry but you have no more chips to bet with." << std::endl;
    }

    bool askPlayerToPlayNewRound() {
        std::cout << "Would you like to play another round (y/n)?  ";
        std::string playerResponse = "";
        getline(std::cin, playerResponse);
        transform(playerResponse.begin(), playerResponse.end(), playerResponse.begin(), ::tolower);
        while (!(playerResponse == "y") && !(playerResponse == "yes") && !(playerResponse == "n") && !(playerResponse == "no")) {
            std::cout << "Would you like to play another round (y/n)? Please type 'y' or 'n' (without the quotes):  ";
            getline(std::cin, playerResponse);
            transform(playerResponse.begin(), playerResponse.end(), playerResponse.begin(), ::tolower);
        }
        bool playerWantsToPlayNewRound = false;
        if (playerResponse == "y" || playerResponse == "yes") {
            playerWantsToPlayNewRound = true;
        }
        if (playerResponse == "n" || playerResponse == "no") {
            playerWantsToPlayNewRound = false;
        }
        return playerWantsToPlayNewRound;
    }
};

class Hand {
private:
    std::vector<Card*> cardsInHand;

    bool handContainsAce() {
        if (isHandEmpty()) {
            return false;
        }
        bool aceExists = false;
        for (int handIndex = 0; handIndex < cardsInHand.size(); handIndex++) {
            Card* currentCard = cardsInHand[handIndex];
            if (currentCard->isAce()) {
                aceExists = true;
            }
        }
        return aceExists;
    }

public:
    ~Hand() {
        if (!isHandEmpty()) {
            clearHand();
        }
    }

    bool isHandEmpty() {
        return cardsInHand.empty();
    }

    int getNumberOfCardsInHand() {
        return cardsInHand.size();
    }

    int getHandValue() {
        if (isHandEmpty()) {
            return 0;
        }
        int handValue = 0;
        for (int handIndex = 0; handIndex < cardsInHand.size(); handIndex++) {
            handValue += cardsInHand[handIndex]->getCardValue();
        }
        if (handContainsAce() && handValue <= 11) {
            handValue += 10; // Two aces count as 12.
        }
        return handValue;
    }

    std::string getHandInTextFormat() {
        if (isHandEmpty()) {
            return "";
        }
        std::string handInTextFormat = "";
        for (int handIndex = 0; handIndex < cardsInHand.size(); handIndex++) {
            Card* currentCard = cardsInHand[handIndex];
            handInTextFormat += currentCard->getCardInTextFormat();
            handInTextFormat += " | ";
        }
        return handInTextFormat;
    }

    void addCardToHand(Card* newCard) {
        cardsInHand.push_back(newCard);
    }

    // The cards in hand are discarded.
    void clearHand() {
        if (isHandEmpty()) {
            return;
        }
        for (int handIndex = 0; handIndex < cardsInHand.size(); handIndex++) {
            delete cardsInHand[handIndex];
            cardsInHand[handIndex] = nullptr;
        }
        cardsInHand.clear();
    }
};

class Dealer {
private:
    Hand dealerHand;

public:
    int getHandValue() {
        return dealerHand.getHandValue();
    }

    std::string getHandInTextFormat() {
        return dealerHand.getHandInTextFormat();
    }

    bool handValueIsAtLeast17() {
        int dealerHandValue = getHandValue();
        if (dealerHandValue >= 17) {
            return true;
        } else {
            return false;
        }
    }

    void isHitting(Card* newCard) {
        dealerHand.addCardToHand(newCard);
    }

    bool isBusted() {
        if (dealerHand.getHandValue() > 21) {
            return true;
        } else {
            return false;
        }
    }

    // The cards in hand are discarded.
    void clearHand() {
        dealerHand.clearHand();
    }
};

class Player {
private:
    Hand playerHand;
    int chipsToPlay;
    int chipsInBettingBox;
    static const int minimumBet = 1; // The player should bet at least 1 chip.

public:
    Player() {
        chipsToPlay = 0;
        buyChips(100); // The player starts with 100 chips.
        chipsInBettingBox = 0;
    }

    int getHandValue() {
        return playerHand.getHandValue();
    }

    std::string getHandInTextFormat() {
        return playerHand.getHandInTextFormat();
    }

    void buyChips(int newChips) {
        chipsToPlay += newChips;
    }

    int getCurrentNumberOfChipsToPlay() {
        return chipsToPlay;
    }

    bool hasAvailableChipsToPlay() {
        if (chipsToPlay >= 1) {
            return true;
        } else {
            return false;
        }
    }

    void isBetting(int chipsToBet) {
        if (chipsToBet > getCurrentNumberOfChipsToPlay()) {
            throw CustomExceptionWithErrorMessage("Error: player is trying to bet more than their available chips.");
        }
        if (chipsToBet < getMinimumBet()) {
            throw CustomExceptionWithErrorMessage("Error: player is trying to bet less than the minimum bet of 1 chip.");
        }
        chipsToPlay -= chipsToBet;
        chipsInBettingBox += chipsToBet;
    }

    int getMinimumBet() {
        return minimumBet;
    }

    void isHitting(Card* newCard) {
        playerHand.addCardToHand(newCard);
    }

    bool isBusted() {
        if (playerHand.getHandValue() > 21) {
            return true;
        } else {
            return false;
        }
    }

    bool hasBlackjack() {
        if (playerHand.getHandValue() == 21) {
            return true;
        } else {
            return false;
        }
    }

    void wins() {
        int chipsWon = chipsInBettingBox; // All wins are paid out at 1:1.
        chipsToPlay += chipsInBettingBox + chipsWon;
        chipsInBettingBox = 0;
    }

    void pushes() {
        chipsToPlay += chipsInBettingBox; // Bet is returned (without adjustment) to the player.
        chipsInBettingBox = 0;
    }

    void loses() {
        chipsInBettingBox = 0; // Bet is lost (i.e., taken by the dealer).
    }

    // The cards in hand are discarded.
    void clearHand() {
        playerHand.clearHand();
    }
};

class Deck {
private:
    std::vector<Card*> cardsInDeck;
    static const int totalNumberOfCardsInCompleteDeck = 52;

    void createOrderedCardsOfSuit(CardSuit suit) {
        for (int rankInIntegerFormat = Ace; rankInIntegerFormat <= King; rankInIntegerFormat++) {
            CardRank rank = static_cast<CardRank>(rankInIntegerFormat);
            try {
                Card* newCard = new Card(rank, suit);
                cardsInDeck.push_back(newCard);
            }
            catch (const std::bad_alloc& e) {
                throw CustomExceptionWithErrorMessage("Error: the system is unable to satisfy request for memory.");
            }
        }
    }

public:
    Deck() {
        cardsInDeck.reserve(52);
        createOrderedDeck();
    }

    ~Deck() {
        clearDeck();
    }

    // Discard cards (if any) in deck and create an ordered deck of cards.
    void createOrderedDeck() {
        clearDeck();
        createOrderedCardsOfSuit(Spades);
        createOrderedCardsOfSuit(Hearts);
        createOrderedCardsOfSuit(Diamonds);
        createOrderedCardsOfSuit(Clubs);
    }

    // The deck of cards is discarded.
    void clearDeck() {
        if (isDeckEmpty()) {
            return;
        }
        for (int deckIndex = 0; deckIndex < getCurrentNumberOfCardsInDeck(); deckIndex++) {
            delete cardsInDeck[deckIndex];
            cardsInDeck[deckIndex] = nullptr;
        }
        cardsInDeck.clear();
    }

    bool isDeckEmpty() {
        return cardsInDeck.empty();
    }

    int getCurrentNumberOfCardsInDeck() {
        return cardsInDeck.size();
    }

    void shuffleDeck() {
        if (!isDeckEmpty()) {
            random_shuffle(cardsInDeck.begin(), cardsInDeck.end());
        }
    }

    Card* drawCardfromDeck() {
        if (isDeckEmpty()) {
            throw CustomExceptionWithErrorMessage("Error: cannot draw card from an empty deck.");
        } else {
            Card* removedCard = cardsInDeck.back();
            cardsInDeck.pop_back();
            return removedCard;
        }
    }

    void displayCardsInDeckInTextFormat() {
        int currentNumberOfCardsInDeck = getCurrentNumberOfCardsInDeck();
        std::string trailingCharacterS = ""; // singular number ("s" character is not appended)
        if (currentNumberOfCardsInDeck > 1) {
            trailingCharacterS = "s"; // plural number ("s" character is appended)
        }
        std::cout << "The deck contains " << currentNumberOfCardsInDeck << " card" << trailingCharacterS << "." << std::endl;
        if (isDeckEmpty()) {
            return;
        } else {
            for (int deckIndex = 0; deckIndex < currentNumberOfCardsInDeck; deckIndex++) {
                std::cout << cardsInDeck[deckIndex]->getCardInTextFormat() << std::endl;
            }
        }
    }
};

class BlackjackGame {
private:
    Dealer dealer;
    Player player;
    Deck deck;
    BlackjackPresenter blackjackPresenter;

    void gameStarts() {
        blackjackPresenter.displayWelcomeMessage();
    }

    void gameEnds() {
        blackjackPresenter.displayGoodbyeMessage();
    }

    // Algorithm for a Blackjack round:
    //     Place shuffled deck into dealing shoe
    //     Player bets
    //     Deal 2 cards to player
    //     Display player's initial cards (i.e., 2 cards)
    //     Deal 2 cards to dealer
    //     Display dealer's first card
    //     Hide dealer's second card (called the hole card)
    //     Deal additional cards to player
    //     If player busts
    //         Player loses
    //         Blackjack round is over
    //     Display dealer's second card (namely, the hole card)
    //     Deal additional cards to dealer
    //     If dealer busts
    //         Player wins
    //         Blackjack round is over
    //     If player's hand value is greater than dealer's hand value
    //         Player wins
    //         Blackjack round is over
    //     If player's hand value is less than dealer's hand value
    //         Player loses
    //         Blackjack round is over
    //     If player's hand value equals dealer's hand value
    //         Player pushes
    //         Blackjack round is over
    //     Discard all cards (namely, player's hand, dealer's hand, and dealing shoe)

    void roundStarts() {
        blackjackPresenter.announceStartOfRound();
        placeShuffledDeckIntoDealingShoe();
        playerPlacesBet();
        dealCardToPlayer(); // player's 1st card
        dealCardToPlayer(); // player's 2nd card
        displayPlayerHandContents();
        dealCardToDealer(); // dealer's 1st card
        displayDealerHandContents();
        dealCardToDealer(); // dealer's 2nd card (namely, the hole card)
        hideTheHoleCardFromPlayer(); // The hole card remains hidden.
        dealAdditionalCardsToPlayer();
        if (playerIsBusted()) {
            playerLoses();
            return;
        }
        displayDealerHandContents(); // Reveal the hole card.
        dealAdditionalCardsToDealer();
        if (dealerIsBusted()) {
            playerWins();
            return;
        }
        if (playerHandValueGreaterThanDealerHandValue()) {
            playerWins();
            return;
        }
        if (playerHandValueLessThanDealerHandValue()) {
            playerLoses();
            return;
        }
        if (playerHandValueIsEqualToDealerHandValue()) {
            playerPushes();
            return;
        }
    }

    void roundEnds() {
        blackjackPresenter.announceEndOfRound();
        discardAllCardsFromTable();
    }

    void placeShuffledDeckIntoDealingShoe() {
        clearDeck();
        getOrderedDeck();
        shuffleDeck();
    }

    void clearDeck() {
        deck.clearDeck();
    }

    // Ordered deck needs to be shuffled before use.
    void getOrderedDeck() {
        deck.createOrderedDeck();
    }

    void shuffleDeck() {
        deck.shuffleDeck();
    }

    bool isDeckEmpty() {
        return deck.isDeckEmpty();
    }

    void playerPlacesBet() {
        int playerCurrentNumberOfChipsToPlay = getPlayerCurrentNumberOfChipsToPlay();
        blackjackPresenter.displayPlayerAvailableChipsToBetWith(playerCurrentNumberOfChipsToPlay);
        int minimumBet = 1; // The player must bet at least 1 chip.
        int maximumBet = playerCurrentNumberOfChipsToPlay; // There is no limit to maximum bet.
        int playerBetInChips = blackjackPresenter.askPlayerToBetChips(minimumBet, maximumBet);
        player.isBetting(playerBetInChips);
    }

    bool playerHasAvailableChipsToPlay() {
        return player.hasAvailableChipsToPlay();
    }

    int getPlayerCurrentNumberOfChipsToPlay() {
        return player.getCurrentNumberOfChipsToPlay();
    }

    void informPlayerAboutLackOfChips() {
        blackjackPresenter.displayRegretMessageNoChips();
    }

    void displayPlayerHandContents() {
        std::string playerHandInTextFormat = player.getHandInTextFormat();
        blackjackPresenter.displayPlayerHand(playerHandInTextFormat);
        int playerHandValue = player.getHandValue();
        blackjackPresenter.displayPlayerHandValue(playerHandValue);
    }

    int getPlayerHandValue() {
        return player.getHandValue();
    }

    void hideTheHoleCardFromPlayer() {
        blackjackPresenter.announceSecondCardOfDealerIsHidden(); // The hole card is kept hidden for now.
    }

    void dealCardToPlayer() {
        if (isDeckEmpty()) {
            placeShuffledDeckIntoDealingShoe();
        }
        Card* playerCard = deck.drawCardfromDeck();
        player.isHitting(playerCard);
    }

    void dealAdditionalCardsToPlayer() {
        while (!playerIsBusted() && !playerHasBlackjack()) {
            bool playerWantsOneMoreCard = checkPlayerWantsOneMoreCard();
            if (!playerWantsOneMoreCard) {
                return;
            } else {
                dealCardToPlayer();
                displayPlayerHandContents();
            }
        }
    }

    bool checkPlayerWantsOneMoreCard() {
        return blackjackPresenter.askPlayerForAdditionalCard();
    }

    bool playerIsBusted() {
        return player.isBusted();
    }

    bool playerHasBlackjack() {
        return player.hasBlackjack();
    }

    void playerWins() {
        player.wins();
        blackjackPresenter.announcePlayerWins();
        informPlayerAboutTheirCurrentNumberOfChips();
    }

    void playerPushes() {
        player.pushes();
        blackjackPresenter.announcePlayerPushes();
        informPlayerAboutTheirCurrentNumberOfChips();
    }

    void playerLoses() {
        player.loses();
        blackjackPresenter.announcePlayerLoses();
        informPlayerAboutTheirCurrentNumberOfChips();
    }

    void informPlayerAboutTheirCurrentNumberOfChips() {
        int playerCurrentNumberOfChipsToPlay = getPlayerCurrentNumberOfChipsToPlay();
        blackjackPresenter.displayPlayerCurrentNumberOfChips(playerCurrentNumberOfChipsToPlay);
    }

    bool askPlayerToPlayNewRound() {
        return blackjackPresenter.askPlayerToPlayNewRound();
    }

    void displayDealerHandContents() {
        std::string dealerHandInTextFormat = dealer.getHandInTextFormat();
        blackjackPresenter.displayDealerHand(dealerHandInTextFormat);
        int dealerHandValue = dealer.getHandValue();
        blackjackPresenter.displayDealerHandValue(dealerHandValue);
    }

    int getDealerHandValue() {
        return dealer.getHandValue();
    }

    void dealCardToDealer() {
        if (isDeckEmpty()) {
            placeShuffledDeckIntoDealingShoe();
        }
        Card* dealerCard = deck.drawCardfromDeck();
        dealer.isHitting(dealerCard);
    }

    void dealAdditionalCardsToDealer() {
        while (!dealerHandValueIsAtLeast17()) {
            dealCardToDealer();
            displayDealerHandContents();
        }
    }

    bool dealerHandValueIsAtLeast17() {
        return dealer.handValueIsAtLeast17();
    }

    bool dealerIsBusted() {
        return dealer.isBusted();
    }

    bool playerHandValueGreaterThanDealerHandValue() {
        int playerHandValue = getPlayerHandValue();
        int dealerHandValue = getDealerHandValue();
        if (playerHandValue > dealerHandValue) {
            return true;
        } else {
            return false;
        }
    }

    bool playerHandValueIsEqualToDealerHandValue() {
        int playerHandValue = getPlayerHandValue();
        int dealerHandValue = getDealerHandValue();
        if (playerHandValue == dealerHandValue) {
            return true;
        } else {
            return false;
        }
    }

    bool playerHandValueLessThanDealerHandValue() {
        int playerHandValue = getPlayerHandValue();
        int dealerHandValue = getDealerHandValue();
        if (playerHandValue < dealerHandValue) {
            return true;
        } else {
            return false;
        }
    }

    // Discard player's hand, dealer's hand, and remaining cards in deck.
    void discardAllCardsFromTable() {
        player.clearHand();
        dealer.clearHand();
        deck.clearDeck();
    }

public:
    void beginPlaying() {
        // A Blackjack game consists of 1 or more rounds.
        gameStarts();
        if (!playerHasAvailableChipsToPlay()) {
            informPlayerAboutLackOfChips();
            gameEnds();
            return;
        }
        do {
            roundStarts();
            roundEnds();
            if (!playerHasAvailableChipsToPlay()) {
                informPlayerAboutLackOfChips();
                gameEnds();
                return;
            }
        } while (askPlayerToPlayNewRound() == true);
        gameEnds();
        return;
    }
};

int main() {
    try {
        BlackjackGame game;
        game.beginPlaying();
    }
    catch (const CustomExceptionWithErrorMessage& e) {
        std::cout << std::endl;
        std::cout << e.what() << std::endl; // error message
        std::cout << "Quitting Blackjack... Goodbye!" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
