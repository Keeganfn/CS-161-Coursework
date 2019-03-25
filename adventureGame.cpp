/*********************************************************************
 * ** Program Filename: adventure.cpp
 * ** Date:1/20/19
 * ** Description:Text based adventure game
 * ** Input:The user will input 1 or 0
 * ** Output:The output will be a line of text and present the user their  options
 * *********************************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
     
	int coinflip;
	int userInput;
	int keepPlaying = 1;

	while (keepPlaying == 1){

		cout << "You are a travelling merchant attempting to deliver their goods one town over (You will enter either 1 or 0)\n" << endl;
		cout << "To begin your journey you must decide whether to [0] Take the path along the mountain or [1] Follow the river:\n " << endl;
		cin >> userInput;
		
		//Path 1
		if (userInput == 0){
			cout << "As you walk up the mountain you see a crazy old man, do you [0] Talk with him or [1] Try and fight him:\n " << endl;
			cin >> userInput;
			
			//Depth 1	
			if (userInput == 0){
				cout << "The old man tells you not to take the right path up the road, do you [0] Listen to  his advice or [1] ignore his rambling:\n " << endl;
				cin >> userInput;		
			
				//Depth 2	
				if (userInput == 0){
					cout << "You take the right path and run into a bear! do you [0] throw your food at the bear or [1] Throw your gold at the bear:  \n " << endl;
					cin >> userInput;		
				
					//Depth 3	
					if (userInput == 0){
						cout << "The bear is distracted by your food which allows you to escape! You make it to your destination hungry but intact.\n " << endl;
						cout << "YOU WIN" << endl;
				
					}

					//Depth 3
					else if (userInput == 1){
						cout << "Bears dont care about gold, you are eaten. \n" << endl;
						cout << "GAME OVER\n" << endl;	
					}	

					//Handles the instance that an incorrect input is given
					else{
						cout << "That was not a correct input, you will have to start the game over\n" << endl;
					}	
				}
				
				//Depth 2
				else if (userInput == 1){
					cout << "You take the left path and reach your destination succesfully!\n" << endl;
					cout << "YOU WIN" << endl;
				}
				
				//Handles the instance that an incorrect input is given
				else{
					cout << "That was not a correct input, you will have to start the game over\n" << endl;
				}

			}

			//Depth 1
			else if (userInput == 1){
				cout << "Turns out merchants aren't very good fighters, you are slain in battle: \n" << endl;
				cout << "GAME OVER\n" << endl;	
			}	

			//Handles the instance that an incorrect input is given
			else{
				cout << "That was not a correct input, you will have to start the game over\n" << endl;
			}
		}

		//Path 2
		else if (userInput == 1){
			cout << "Walking  up the river you come across a ferry, do you [0] Talk with them or [1] Attempt to steal the ship:\n " << endl;
			cin >> userInput;
			//Depth 1	
			if (userInput == 0){
				cout << "They offer to let you ride across the river for a small sum, do you [0] take them up on the offer or [1] atttempt to ford the river on your own (50/50 chance): \n " << endl;
				cin >> userInput;		
			
				//Depth 2	
				if (userInput == 0){
					cout << "You start across on the ferry but it begins to sink! Do you [0] Try to swim across and abandon the goods [1] Try to paddle back to shore with your goods:  \n " << endl;
					cin >> userInput;		
				
					//Depth 3	
					if (userInput == 0){
						cout << "You make it across safely and make it to your destination, without any goods.\n " << endl;
						cout << "YOU WIN" << endl;
				
					}

					//Depth 3
					else if (userInput == 1){
						cout << "The river overtakes you as you attempt to paddle back. \n" << endl;
						cout << "GAME OVER\n" << endl;	
					}	

					//Handles the instance that an incorrect input is given
					else{
						cout << "That was not a correct input, you will have to start the game over\n" << endl;
					}	
				}
				
				//Depth 2 (COINFLIP)
				else if (userInput == 1){
					srand(time(NULL));
					coinflip = rand() % 2;
				
					//This is the coinflip and decides the outcome based on a 50/50 chance
					if (coinflip == 0){
						cout << "The river was tougher than it looked, you are overtaken by the river. \n" << endl;
						cout << "GAME OVER\n" << endl;	
					}	
					
					else if (coinflip == 1){
						cout << "You succesfully ford the river and reach your destination!\n" << endl;
						cout << "YOU WIN" << endl;
					}

				}
				
				//Handles the instance that an incorrect input is given
				else{
					cout << "That was not a correct input, you will have to start the game over\n" << endl;
				}

			}

			//Depth 1 
			else if (userInput == 1){			
				cout << "You arent a very good pirate and are slain. \n" << endl;
				cout << "GAME OVER\n" << endl;	
					

			}	

			//Handles the instance that an incorrect input is given
			else{
				cout << "That was not a correct input, you will have to start the game over\n" << endl;
			}			

		}

		//Handles the instance that an incorrect input is given
		else{
			cout << "That was not a correct input, you will have to start the game over\n" << endl;
		}	
		
		
		//This allows the user to play the game again or exit in the event of a bad input or if they finish the game
		cout << "Would you like to play again? [0] to quit [1] to play again:\n " << endl;
		cin >> keepPlaying;
	
		if (keepPlaying == 0){
			exit(0);
		}
	}

	return(0);
}
