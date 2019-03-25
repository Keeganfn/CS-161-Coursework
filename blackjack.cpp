
/********************************************************************
** Program Filename: Game.cpp
** Date:2/3/2019
** Description:This program plays a game of 21 with up to 4 players
** Input:Number of players, User Betting, User Bank, User decisions
** Output:Bet Amounts, Instructions, Dealer Amounts, Total Score
*********************************************************************/ 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

int betting(int playerBet);
int turn();
int dealer();
int playerStart();
int wholeRound(int player);

int main(){
	
	int playAgain = 1;
	int playerNumber;
	int check;
	
	while(playAgain == 1){

		int player1 = 0;
		int player2 = 0;
		int player3 = 0;
		int player4 = 0;

		// This takes the number of players and checks to make sure the user inputs a valid value
		do{
			check = 0;

			cout << "Enter number of players (1-4): \n" << endl;
			cin >> playerNumber;
			
			if(playerNumber < 1 || playerNumber > 4){
				cout << "Invalid input \n" << endl;
				check = 1;
			}
		}while(check == 1);

		//This loops through the number of players and gets players initial values with a switch statment (depending on number of players)
		for(int i = 0; i < playerNumber; i++){
			check = 0;
			switch(i){
				case(0): cout << "Player 1 \n" << endl;
					 player1 = playerStart();
					 break;
					 				
				case(1): cout << "Player 2 \n" << endl;
					 player2 = playerStart();
					 break;
					 				
				case(2): cout << "Player 3 \n" << endl;
					player3 = playerStart();
					 break;
					 				
				case(3): cout << "Player 4 \n" << endl;
					 player4 = playerStart();
					 break;
			}
		}

		check = 1;
		
		
		while(check == 1){
		//Player1 turn		
		if(player1 > 0){
			cout << "Player 1" << endl;
			player1 = wholeRound(player1);
						
		}
		//Player2 turn	
		if(player2 > 0){
			cout << "Player 2" << endl;
			player2 = wholeRound(player2);
						
		}
		//Player 3 turn
		if(player3 > 0){
			cout << "Player 3" << endl;
			player3 = wholeRound(player3);
						
		}
		//Player 4 turn
		if(player4 > 0){
			cout << "Player 4" << endl;
			player4 = wholeRound(player4);
						
		}	int roundcheck = 2;
			//Checks that input is 1 or 0
			while(!(roundcheck == 0 || roundcheck == 1)){
				cout << "Do you want to go another round? (1 = yes)(0 = no) \n" << endl;
				cin >> roundcheck;
				check = roundcheck;
				
				if(player1 == 0 && player2 == 0 && player3 == 0 && player4 ==0){
					cout << "You cant play any more, you are out of money! Game over! \n" << endl;
					check = 0;
				}
			} 
		}

		//Sees if player wants to go again
		cout << "Do you want to play again? (1 = yes)(0 = no) \n" << endl;
		cin >> playAgain; 
	}


}
/*********************************************************************
 * ** Function: PlayerStart
 * ** Description: This gets the players total amount and makes sure it is valid
 * ** Parameters:None
 * ** Pre-Conditions:playerStart must be called and number of players specified
 * ** Post-Conditions:initializes the player amount
 * *********************************************************************/ 
int playerStart(){
	int player;
	int check = 0;
	while(check == 0){
							
		cout << "How much would you like to start with: \n" << endl;
		cin >> player;
						
		//Makes sure value is positive and not 0
		if(player >= 0){
			check = 1;	
		}
					
	}
	return(player);
}
/*********************************************************************
 * ** Function:wholeRound
 * ** Description: This executes all of the other functions necessary in 1 round of play for 1 player
 * ** Parameters:Player total amount
 * ** Pre-Conditions:Must be called and total amount must be given
 * ** Post-Conditions:The players new total is returned 
 * *********************************************************************/ 
int wholeRound(int player){

	int bet = betting(player);
	int playerTurn = turn();
	
	//checks if dealer busted
	if(playerTurn > 21){
		cout << "You busted! \n" << endl;
		player -= bet;
		cout << "your total money is now " << player << "\n" << endl;
		return(player);
	}

	//dealer turn	
	int dealerTurn = dealer();
	
	//PLayer win	
	if(playerTurn > dealerTurn){
		cout << "You win! \n" << endl;
		player += bet;
		cout << "Your total money is now " << player << "\n" <<  endl;
	}
	
	//Player Lose	
	else if(playerTurn < dealerTurn){
		cout << "You Lose! \n" << endl;
		player -= bet;
		cout << "Your total money is now " << player << "\n" <<  endl;
	}

	//Player Tie
	else if(playerTurn == dealerTurn){
		cout << "You both Tie! No one wins or loses \n" << endl;
		cout << "Your total money is now " << player << "\n" <<  endl;
	}
	return(player);

}

/*********************************************************************
 * ** Function:betting
 * ** Description:This gets the user bet and checks to make sure it is valid
 * ** Parameters:Takes in the players total amount
 * ** Pre-Conditions: Have to get players total amount
 * ** Post-Conditions:Returns the users bet amount to be stored
 * *********************************************************************/ 
int betting(int playerBet){
	int check = 0;
	int bet = 0;
	
	//checks if the bet is valid
	while(check == 0){
		cout << "How much do you want to bet?: \n" << endl;
		cin >> bet;
		
		//Makes sure the bet is above 0 and below or equal to the players bank
		if(bet > 0 && bet <= playerBet){
			check = 1;
		}
		else{
			cout << "That is not a valid bet" << endl;
		}
	}
	return(bet);
}
/*********************************************************************
 * ** Function:turn
 * ** Description:Gives the user their cards and allows them to hit or stand
 * ** Parameters:none
 * ** Pre-Conditions:Number of players needs to be initialized
 * ** Post-Conditions:Returns the players card total
 * *********************************************************************/ 
int turn(){
	int total = 0;
	int random;
	int hit = 1;
	int check = 0;

	//gives the player a random number between 1 and 11
	while(hit == 1){
		srand(time(NULL));
		random = rand() % (11 - 1 + 1) + 1;
		cout << "you got a " << random << "\n" << endl;
		total += random;
		
		cout << "Your total is " << total << "\n" << endl;
		
		//Checks if player has busted
		if(total > 21){
			return(total);
		}
		
		check = 0;
		
		//Asks if the user wants to hit or stand and makes sure they input either a 1 or 0
		while(check == 0){
			cout << "Would you like to hit again?( no = 0) (yes = 1): \n" << endl;
			cin >> hit;
			
			if(hit == 0 || hit == 1){
				check = 1;
			}
		}
	
	}
	return(total);
}
/*********************************************************************
 * ** Function:dealer
 * ** Description:Executes the dealers turn
 * ** Parameters:none
 * ** Pre-Conditions:Player has their turn
 * ** Post-Conditions:Returns the Dealers card total
 * *********************************************************************/ 
int dealer(){
	int total = 0;
	int random;
	
	//Adds a random number to the dealers total until they reach 17 or they bust
	while(total <= 17){
		random = rand() % (11 - 1 + 1) + 1;
		total += random;
		cout << "The dealer got a " << random << "\n" << endl;
		
		//Checks if dealer busted
		if(total > 21){
			cout << "The dealer busted! \n" << endl;
			return(0);
		}

	}
	cout << "The dealer ends with a total of " << total << "\n" << endl;
	return(total);
}
