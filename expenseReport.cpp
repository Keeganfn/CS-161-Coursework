/*********************************************************************
 * ** Program Filename:cost.cpp
 * ** Date:2/17/19
 * ** Description:This program calculates an expense report
 * ** Input:Travel times, meals, fees, days, hotel, car expenses, etc
 * ** Output: Total cost and total reimbursed
 * *********************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void secondMeal(double &total, double &totalReimbursed, double departureReimbursment);
void firstMeal(double &total, double &totalReimbursed, double arrivalReimbursment);
void meals(double &total, double &totalReimbursed, double arrivalReimbursment, double departureReimbursment, int days);
void travelTimes(double &arrivalTime, double &departureTime, double &arrivalReimbursment, double &departureReimbursment);
void daysTraveled(int &days);
void airfare(double &total, double &totalReimbursed);
void fees(double &total, double &totalReimbursed);
void carCost(double &total, double &totalReimbursed, int days);
void carTaxi(double &total, double &totalReimbursed, int days);
void taxiCost(double &total, double &totalReimbursed, int days);
void parking(double &total, double &totalReimbursed, int days);
void hotel(double &total, double &totalReimbursed, int days);
int intCheck(string);
int intCheck(string);
double doubleCheck(string);
double timeCheck(string);

int main(){

	int playAgain = 0;
	//keeps going until user stops
	while(playAgain == 0){

		int days = 0;
		double arrivalTime = 0;
		double departureTime = 0;
		double total = 0;
		double arrivalReimbursment = 0;
		double departureReimbursment = 0;	
		double totalReimbursed = 0;
		//calls all relevant functions
		daysTraveled(days);	
		travelTimes(arrivalTime, departureTime, arrivalReimbursment, departureReimbursment);
		airfare(total, totalReimbursed); 
		fees(total, totalReimbursed);	
		meals(total, totalReimbursed, arrivalReimbursment, departureReimbursment, days);
		carTaxi(total, totalReimbursed, days);
		hotel(total, totalReimbursed, days);
		cout << "Your total is " << total << " And your total reimbursed is "<< totalReimbursed << endl;






	cout << "Do you want to play again? 0 = yes 1 = no " << endl;
	cin >> playAgain;
	cin.ignore();
	}
}


/*********************************************************************
 * ** Function:days traveled
 * ** Description:gets number of days gone
 * ** Parameters:refrence to days variable
 * ** Pre-Conditions:function called
 * ** Post-Conditions:days is assigned a value
 * *********************************************************************/ 
void daysTraveled(int &days){
	//Makes sure it is not less than 0 and error checks
	do{
	string dayMessage = "How many days will you be gone?";
	days = intCheck(dayMessage);
	}while(days <= 0);

}
/*********************************************************************
 * ** Function: TravelTimes
 * ** Description:Gets the time for travel and calculates meals comped
 * ** Parameters: reference to arrivalTime departureTime arrivalReimbusment and departure Reimbursment
 * ** Pre-Conditions:function called and days called
 * ** Post-Conditions:reimbursment info and travel times
 * *********************************************************************/ 
void travelTimes(double &arrivalTime, double &departureTime, double &arrivalReimbursment, double &departureReimbursment){

	string departureMessage = "When is your departure time on the first day?";
	string arrivalMessage = "When is your arrival time on the last day";

	//Gets times and makes sure they are in range
	do{		
		departureTime = timeCheck(departureMessage);

	}while(departureTime > 24.59 || departureTime < 1);
		
	do{		
		arrivalTime = timeCheck(arrivalMessage);

	}while(arrivalTime > 24.59 || arrivalTime < 1);		
	
	//calculates the number of meals comped based on time
	if(arrivalTime >= 8 && arrivalTime < 13){
		arrivalReimbursment = 1;
	}else if(arrivalTime >= 13 && arrivalTime < 19){
		arrivalReimbursment = 2;
	}else if(arrivalTime >= 19){
		arrivalReimbursment = 3;
	}	
	if(departureTime <= 7){
		departureReimbursment = 3;
	}else if(departureTime <= 12){
		departureReimbursment = 2;
	}else if(departureTime <= 18){
		departureReimbursment = 1;
	}
	

}

/*********************************************************************
 * ** Function:Airfare
 * ** Description:Gets total airfare fee
 * ** Parameters: reference to total and total reimbursed
 * ** Pre-Conditions:function called
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void airfare(double &total, double &totalReimbursed){
	double cost;
	//adds airfare to the totals
	string airfareMessage = "What is your total airfare fee?";
	cost = doubleCheck(airfareMessage);
	totalReimbursed += cost;
	total += cost;
}

/*********************************************************************
 * ** Function:fees
 * ** Description:Gets total fees
 * ** Parameters:total and totalReimbursed
 * ** Pre-Conditions:function called
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void fees(double &total, double &totalReimbursed){
	double cost;
	//adds fees to totals
	string feeMessage = "What is your total conference fee?";
	cost = doubleCheck(feeMessage);
	totalReimbursed += cost;
	total += cost;
}

/*********************************************************************
 * ** Function:carTaxi
 * ** Description:sees if the user used a taxi or car and calls functions
 * ** Parameters:total totalReimbursed days
 * ** Pre-Conditions:function called and days called
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void carTaxi(double &total, double &totalReimbursed, int days){
	int choice;
	//gets user choice
	do{
	string carTaxiMessage = "Did you rent a car or taxi? (0 = car)(1 = taxi)";
	choice = intCheck(carTaxiMessage);
	}while(!(choice == 0 || choice == 1));
	//calls correct function based on user choice
	if(choice == 0){
		carCost(total, totalReimbursed, days);
		parking(total, totalReimbursed, days);
	}else{
		taxiCost(total, totalReimbursed, days);
	}

}

/*********************************************************************
 * ** Function:carCost
 * ** Description:gets total cost for using a car over trip
 * ** Parameters:total totalReimbursed and days
 * ** Pre-Conditions:function must be called by carTaxi
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void carCost(double &total, double &totalReimbursed, int days){
	int choice, car;
	double gasCost, rentalCost, milesDriven, gasReim, carReim;
	string carType = "What kind of car did you use?(1=Sedan)(2=SUV)(3=Van)(4=Convertible)";
	string rental = "How much was the rental fee per day?";
	string gas = "How much did you spend on gas?";
	string miles = "How many miles did you drive(round to nearest mile)";

	
	//gets values from users	
	gasCost = doubleCheck(gas);
	rentalCost = doubleCheck(rental);
	milesDriven = intCheck(miles);
	do{
		car = intCheck(carType);
	}while(car <= 0 || car >= 4);
		switch(car){
			//gets car type and reimbursments
			case(1): gasReim = .24; carReim = 20;break;
			case(2): gasReim = .27; carReim = 25;break;
			case(3): gasReim = .32; carReim = 30;break;
			case(4): gasReim = .45; carReim = 50;break;
		}

		//Calculates totals 
		total += (rentalCost * double(days)) + gasCost;
		if(carReim >= rentalCost){
			totalReimbursed += (double(milesDriven) * gasReim) + (rentalCost * double(days));	
		}else{
			totalReimbursed += (double(milesDriven) * gasReim) + (carReim * double(days));
		}


}

/*********************************************************************
 * ** Function:parking
 * ** Description:gets parking fees every day
 * ** Parameters:total totalReimbursed and days
 * ** Pre-Conditions:carTaxi executed and function called
 * ** Post-Conditions:updated totals
 * *********************************************************************/ 
void parking(double &total, double &totalReimbursed, int days){
	string parkingMessage;
	double parkingCost;
	//Gets parking every day based on number of days
	for(int i = 1; i <= days; i++){
		parkingCost = 0;
		cout << "Day " << i << endl;
		parkingMessage = "How much did you spend on parking";
		parkingCost = doubleCheck(parkingMessage);
		total += parkingCost;
	//Calculates totals 
		if(parkingCost > (6)){
			totalReimbursed += 6.0;
		}else{
			totalReimbursed += parkingCost;
		}	
	}
}

/*********************************************************************
 * ** Function:taxiCost
 * ** Description:gets cost of taxi usage
 * ** Parameters:total totalReimbursed and days
 * ** Pre-Conditions:has to be called by cartaxi
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void taxiCost(double &total, double &totalReimbursed, int days){
	double dailyCost;
	string taxiMessage = "How much did you spend per day on taxis?";
	//gets taxi costs per day
	dailyCost = doubleCheck(taxiMessage);
	total += dailyCost * double(days);
	//calculates totals
	if(dailyCost > 10){
		totalReimbursed += 10 * double(days);
	}else{
		totalReimbursed += (dailyCost * double(days));
	}

}

/*********************************************************************
 * ** Function:hotel
 * ** Description:gets total hotel expenses
 * ** Parameters:total totalReimbursed and days
 * ** Pre-Conditions:Function called
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void hotel(double &total, double &totalReimbursed, int days){
	string hotelMessage;
	double hotelCost;
	//Gets hotel price every night based on number of days
	for(int i = 1; i < days; i++){
		hotelCost = 0;
		cout << "Day " << i << endl;
		hotelMessage = "How much did you spend on your hotel";
		hotelCost += doubleCheck(hotelMessage);
	
		total += hotelCost;
		if(hotelCost > (90)){
			totalReimbursed += 90.0;
		}else{
			totalReimbursed += hotelCost;
		}
	}


}

/*********************************************************************
 * ** Function:firstMeal
 * ** Description:Gets reimbursment from meals on the first day based on time
 * ** Parameters:total totalReimbursed and departureReimbursment
 * ** Pre-Conditions:called by meals function
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void firstMeal(double &total, double &totalReimbursed, double departureReimbursment){
	string mealMessage = "How much was your meal";
	double mealCost;
	// prevents seg fault
	if(departureReimbursment != 0){
		cout << "You were comped for some meals based on your arrival time on the first day \n";
		//goes through and calculates reimbursment based on how many meals are valid due to time
		for(departureReimbursment; departureReimbursment >= 1; departureReimbursment--){
			mealCost = doubleCheck(mealMessage);
			total += mealCost;
			if(departureReimbursment == 1){
				if(mealCost > 16){
					totalReimbursed += 16;
				}else{
					totalReimbursed += mealCost;
				}

			}else if(departureReimbursment == 2){
				if(mealCost > 12){
					totalReimbursed += 12;
				}else{
					totalReimbursed += mealCost;
				}

			}else{
				if(mealCost > 9){
					totalReimbursed += 9;
				}else{
					totalReimbursed += mealCost;
				}
			}		
		}
	}
}

/*********************************************************************
 * ** Function:secondMeal
 * ** Description:Gets meal reimbursement on last day based on time
 * ** Parameters:total totalReimbursed arrivalReimbursment
 * ** Pre-Conditions:called by meals function
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void secondMeal(double &total, double &totalReimbursed, double arrivalReimbursment){
	string mealMessage = "How much was your meal";
	double mealCost;

	if(arrivalReimbursment != 0){
		cout << "You were comped for some meals based on your arrival time on the last day \n";
		//Gets meal prices and comps based on arrival time on the last day done earlier
		for(arrivalReimbursment; arrivalReimbursment >= 1; arrivalReimbursment--){
			mealCost = doubleCheck(mealMessage);
			total += mealCost;
			if(arrivalReimbursment == 1){
				if(mealCost > 16){
					totalReimbursed += 16;
				}else{
					totalReimbursed += mealCost;
				}

			}else if(arrivalReimbursment == 2){
				if(mealCost > 12){
					totalReimbursed += 12;
				}else{
					totalReimbursed += mealCost;
				}

			}else{
				if(mealCost > 9){
					totalReimbursed += 9;
				}else{
					totalReimbursed += mealCost;
				}
			}		
		}
	}
}

/*********************************************************************
 * ** Function:meals
 * ** Description:gets meals totals and comps
 * ** Parameters:total totalReimbursed arrivalReimbursement departure reimbursment and days
 * ** Pre-Conditions:function called and times made
 * ** Post-Conditions:totals updated
 * *********************************************************************/ 
void meals(double &total, double &totalReimbursed, double arrivalReimbursment, double departureReimbursment, int days){
	string mealMessage = "What was the cost of your meal?";
	double mealCost;

	firstMeal(total, totalReimbursed, departureReimbursment);
	//gets meal cost and comp for the remaning days
	for(int j = 1; j <= ((days - 2)); j++){
		cout << "Day " << j + 1 << endl;
		for(int i = 1; i <= 3; i++){
			mealCost = doubleCheck(mealMessage);
			total += mealCost;
			if(i == 1){
				if(mealCost > 16){
					totalReimbursed += 16;
				}else{
					totalReimbursed += mealCost;
				}

			}else if(i == 2){
				if(mealCost > 12){
					totalReimbursed += 12;
				}else{
					totalReimbursed += mealCost;
				}

			}else{
				if(mealCost > 9){
					totalReimbursed += 9;
				}else{
					totalReimbursed += mealCost;
				}
			}		
	}
	}
	secondMeal(total, totalReimbursed, arrivalReimbursment);

}

/*********************************************************************
 * ** Function:intcheck
 * ** Description:Checks to make sure an integer is valid
 * ** Parameters:a string 
 * ** Pre-Conditions:function called
 * ** Post-Conditions:output returned as int
 * *********************************************************************/ 
int intCheck(string message){
	string store;
	int total;
	bool error;
	// Checks to see if int does not contain any letters or symbols 
	do{
		error = false;
		cout << message << "\n" << endl;
		getline(cin, store);
		for(int i = 0; i < store.size(); i++){
			if(!(store.at(i) >= '0' && store.at(i) <= '9')){
				error = true;
			}	
		}
	}while(error);
	total = atoi(store.c_str());
	return total;
}

/*********************************************************************
 * ** Function:doubleCheck
 * ** Description:Checks a double to make sure it is valid
 * ** Parameters:string message
 * ** Pre-Conditions:function called
 * ** Post-Conditions:double returned
 * *********************************************************************/ 
double doubleCheck(string message){
	string store;
	double total;
	bool error;
	//makes sure double does not go past 2 decimal places and has all valid characters
	do{
		int dot = 0;
		error = false;
		cout << message << "\n" << endl;
		getline(cin, store);
		for(int i = 0; i < store.size(); i++){
			if(store.at(i) == '.' ){
				dot+=1;
				if(store.size() - i > 3){
					error = true;
				}	
			}
			else if(dot > 1 || !(store.at(i) >= '0' && store.at(i) <= '9')) {
				error = true;	
			}	
		}
	}while(error);
	total = atof(store.c_str());
	return total;
	// returns a double


}

/*********************************************************************
 * ** Function:timeChekc
 * ** Description:checks a double value to see if it is within the time constraints
 * ** Parameters:string message
 * ** Pre-Conditions:function called
 * ** Post-Conditions:double returned
 * *********************************************************************/ 
double timeCheck(string message){
	string store;
	double total;
	bool error;
	//Makes sure thatt it is within length requirements and isnt past 2 decimal places
	do{
		int dot = 0;
		error = false;
		cout << message << "\n" << endl;
		getline(cin, store);
		if(store.size() == 4 && store.at(2) > '5'){
			error = true;
		}else if(store.size() == 5 && store.at(3) > '5'){
			error = true;
		}else if(store.size() == 3 && store.at(2) > '5'){
			error = true;
		}		
		for(int i = 0; i < store.size(); i++){
			if(store.at(i) == '.' ){
				dot+=1;
				if(store.size() - i > 3){
					error = true;
				}	
			}
			else if(dot > 1 || store.size() > 5 || !(store.at(i) >= '0' && store.at(i) <= '9')) {
				error = true;	
			}	
		}
	}while(error);
	total = atof(store.c_str());
	return total;
	//returns double 
}
