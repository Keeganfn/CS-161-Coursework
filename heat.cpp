#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

double doubleCheck(string message);
int intCheck(string message);
bool isStable1d(double, double, double, double, double);
double calculation1d(double *, double , double , double, double, double, int, int);
void wireCalc();
void plateCalc();
bool isStable2d(double deltaX, double p, double c, double k, double deltaT);
double **create2dArray(int sections, double btTemp, double rlTemp, double iTemp);

void calculation2d(double **array2d, double deltaX, double deltaT, double c,
	double p, double k, int sections, int timeInterval);

void get1d(double &k, double &p, double &c, double &len, int &s, int &ti,
	 double &ts, double &r, double &l, double &i, double&, double&);

void get2d(double &k,double &p,double &c,double &hw,int &s,int &ti,double &ts,
	double &rTlT,double &bTtT,double &iT,double &dX,double &dT);

/*********************************************************************
 * ** Program Filename:heat.cpp
 * ** Author:Keegan Nave
 * ** Date:3/19/2019
 * ** Description:This calculates heat transfer over a plate or wire
 * ** Input: p,c,k,temps,sections,time,intervals
 * ** Output:each section and the heat in an array
 * *********************************************************************/
int main(){
	int playAgain = 1;
	
	while(playAgain == 1){
		int choice;
		//Gets choice of plate or wire and will also prompt user to play again
		do{
		choice = intCheck("Choose to calculate a wire or plate (wire = 0)(plate = 1)");
		}while(choice != 0 && choice != 1);
		
		if(choice == 0){
			wireCalc();
		}		
		else if(choice == 1){
			plateCalc();
		}

		do{
			playAgain = intCheck("Do you wish to play again? (1=yes)(0=no)");
		}while(playAgain != 0 && playAgain != 1);
	}
}
/*********************************************************************
 * ** Function:plateCalc
 * ** Description:This calculates heat transfer over a plate 
 * ** Parameters: none
 * ** Pre-Conditions:function must be called from user choice
 * ** Post-Conditions:Array of heat transfers will be outputted
 * *********************************************************************/ 	
void plateCalc(){

	double k, p, c, heightWidth, timeSim, rlTemp, btTemp, iTemp, deltaX, deltaT;
	int sections, timeInterval;


	//Gets initial values for the 1d object and repeats until stable values are given
	do{
	get2d(k, p, c, heightWidth, sections, timeInterval, timeSim,
		 rlTemp, btTemp, iTemp, deltaX, deltaT);
	}while(!(isStable2d(deltaX, p, c, k, deltaT)));

	double **array2d = create2dArray(sections, btTemp, rlTemp, iTemp);
	
	calculation2d(array2d, deltaX, deltaT, c, p, k, sections, timeInterval);

	for(int i = 0; i < sections; i++){
		delete [] array2d[i];
	}
	delete [] array2d;
}
/*********************************************************************
 * ** Function:create2dArray
 * ** Description:creates a 2d array and initializes the values based on the user input
 * ** Parameters: sections and temperatures
 * ** Pre-Conditions:Must be called by function and values must be set by user
 * ** Post-Conditions:Returns an initialized 2d array
 * *********************************************************************/ 
double **create2dArray(int sections, double btTemp, double rlTemp, double iTemp){

	double **array2d = new double *[sections];
	//Initializes and sets everything to 0
	for(int i = 0; i < sections; i++){
		array2d[i] = new double[sections];
		for(int j = 0; j < sections; j++){
			array2d[i][j] = iTemp;
		}
	}
	//puts all of the initial values from user in the array
	for(int i = 0; i < sections; i++){
		array2d[0][i] = btTemp;
		array2d[sections-1][i] = btTemp;
		array2d[i][0] = rlTemp;
		array2d[i][sections-1] = rlTemp;
	}
	return array2d;
}
/*********************************************************************
 * ** Function:calculation2d
 * ** Description:Calculates each array piece and prints them out
 * ** Parameters: array2d, deltax, deltat, c, p, k, sections, timeInterval
 * ** Pre-Conditions:must be called by function and arrays and values must be created
 * ** Post-Conditions:2d arrays created and outputted showing the transfer of heat
 * *********************************************************************/ 
void calculation2d(double **array2d, double deltaX, double deltaT, double c,
	 double p, double k, int sections, int timeInterval){
	//This function is 18 lines not counting whitespace or variable dec, 
	//but I didnt want to have to create a seperate function for just a small amount

	double first = 0, second = 0;
	//Creates a copy of the original array to store the initial values and values after change
	double **arrayCopy = new double *[sections];
	for(int i = 0; i < sections; i++){
		arrayCopy[i] = new double[sections];
		for(int j = 0; j < sections; j++){
			arrayCopy[i][j] = array2d[i][j];
		}
	}
	//Applies the equation for each time interval
	for(int i = 1; i < timeInterval; i++){
		for(int b = 1; b < sections -1; b++){
			for(int j = 1; j < sections - 1; j++){

			first = ((array2d[b+1][j]) - (2*array2d[b][j]) + (array2d[b-1][j])) / pow(deltaX, 2);

			second = ((array2d[b][j+1]) - (2*array2d[b][j]) + (array2d[b][j-1])) / pow(deltaX, 2);

			arrayCopy[b][j] = (((k * deltaT) / (c * p)) * (first + second)) + array2d[b][j];
			}			
		}
		//Prints out the array and assigns the old values to the copy array
		for(int i = 0; i < sections; i++){
			for(int j = 0; j < sections; j++){
				array2d[i][j] = arrayCopy[i][j];
				cout << array2d[i][j] << "  ";
			}
			cout << endl;
		}
	}
	//Frees memory
	for(int i = 0; i < sections; i++){
		delete [] arrayCopy[i];
	}
	delete [] arrayCopy;

}
/*********************************************************************
 * ** Function:isStable2d
 * ** Description:Checks if the inputs are stable 
 * ** Parameters:deltax, p, c, k, deltat
 * ** Pre-Conditions:Must be called by functions and values must be created from user
 * ** Post-Conditions:returns true or false depending on if it is stable
 * *********************************************************************/ 
bool isStable2d(double deltaX, double p, double c, double k, double deltaT){
	
	//Gets stability and outputs error or success method
	double total;	
	total = (deltaX * deltaX * p * c) / (4 * k);

	if(deltaT <= total){
		cout << "Your equation is stable" << endl;
		return true;
	}
	else if(deltaT > total){
		cout << "Your equation is not stable, you will need to enter new values" << endl;
		return false;
	}
}
/*********************************************************************
 * ** Function:get2d
 * ** Description:This gets all of the values from the user for the equation (passes them through input check function)
 * ** Parameters:k,p,c,hw,s,ti,ts,rTlT,bTtT,iT,dX,dT
 * ** Pre-Conditions:Must be called by function and variables declared
 * ** Post-Conditions:Changes the variable values in the function that called it
 * *********************************************************************/ 
void get2d(double &k, double &p, double &c, double &hw, int &s, int &ti,
	double &ts, double &rTlT, double &bTtT, double &iT, double &dX, double &dT){

	// Variable names shortened to save space 
	// This gets all of the needed inputs and checks their inputs until a valid input is given

	k = doubleCheck("What is the Thermal conductivity");
	p = doubleCheck("What is the material density");
	c = doubleCheck("What is the heat capacity");
	hw = doubleCheck("What is the height and width");
	s = intCheck("How many sections (integer)");
	ti = intCheck("How many time intervals (integer)");
	ts = doubleCheck("What is the total time of simulation");
	rTlT = doubleCheck("What is the right and left temp");
	bTtT = doubleCheck("What is the bottom and top temp");
	iT = doubleCheck("What is the initial Temp");
	dX = hw / double(s);
	dT = ts / double(ti);
}
/*********************************************************************
 * ** Function:WireCalc
 * ** Description:Calculates the heat transfer over a wire based on user inputs
 * ** Parameters:none
 * ** Pre-Conditions:Must be called
 * ** Post-Conditions:Wire transfer arrays will be created and outputted based on the equation
 * *********************************************************************/ 
void wireCalc(){

	double k, p, c, length, timeSim, rTemp, lTemp, iTemp, deltaX, deltaT;
	int sections, timeInterval;

	do{
	//Gets initial values for the 1d object until a stable value is found
	get1d(k, p, c, length, sections, timeInterval, timeSim, rTemp, lTemp, iTemp, deltaX, deltaT);
	
	}while(!(isStable1d(k, deltaT, deltaX, c, p)));
	
	//Creates array and initializes the left, right and initial temps
	double *array1d = new double[sections];

	for(int i = 0; i < (sections); i++){
		array1d[i] = iTemp;

	}
	array1d[0] = lTemp;
	array1d[sections-1] = rTemp;	
	//Calculates everything and outputs each interval
	calculation1d(array1d, deltaT, deltaX, k, c, p, sections, timeInterval);
	
	delete [] array1d;
}
/*********************************************************************
 * ** Function:calculation1d
 * ** Description:Calculates each section and puts them in an array that is outputted
 * ** Parameters: array1d, deltat, deltax, k
 * ** Pre-Conditions:Must be called by function and all variables must be initialized
 * ** Post-Conditions:outputs 1d arrays that show the heat transfer on a wire based on user inputs
 * *********************************************************************/ 
double calculation1d(double *array1d, double deltaT, double deltaX, double k,
	double c,double p, int sections, int timeInterval){

	double heatEquationTop = 0;
	double *arrayCopy = new double[sections];
	//copys array so that it has left, right, and initial values
	for(int i = 0; i < sections; i++){
		arrayCopy[i] = array1d[i];
	}
	//Equation that repeats for the set number of time intervals
	for(int i = 1; i < timeInterval; i++){
		for(int j = 1; j < (sections - 1); j++){

			heatEquationTop = 0;
			heatEquationTop = (array1d[j+1]) - (2.0 * (array1d[j])) + (array1d[j-1]);
			arrayCopy[j] = ((heatEquationTop / (pow(deltaX, 2))) * ((k * deltaT) / (c * p))) + (array1d[j]);
		}
	//Prints out the array and copys the old array to the new one
	for(int k = 0; k < (sections); k++){
		array1d[k] = arrayCopy[k];
		cout << array1d[k] << "  ";

	}
	cout << endl;
	}
	//Frees memory
	delete [] arrayCopy;
}
/*********************************************************************
 * ** Function:isStable1d
 * ** Description:Checks if 1d equation is stable
 * ** Parameters: k, deltat, deltax, c, p
 * ** Pre-Conditions:must be called and variables must be initialized
 * ** Post-Conditions:returns true or false based on if equation is stable or not
 * *********************************************************************/ 
bool isStable1d(double k, double deltaT, double deltaX, double c, double p){
	double total;
	//Sees if equation is stable and returns true or false
	total = (k * deltaT) / (pow(deltaX, 2) * c * p);

	if(total < .5){
		cout << "Your inputs had a stability of " << total << " and is stable" << endl;
		return true;
	}
	else if(total >= .5){
		cout << "Your inputs had a stability of " << total << " and is not stable" << endl;
		cout << "The simulation will not run with these inputs, please enter new ones" << endl;
		return false;
	}
}


/*********************************************************************
 * ** Function:get1d
 * ** Description:Gets all of the values for the equation from the user (passes them through input check function)
 * ** Parameters: k, p, c, len, s, ti, ts, r, l, i, dx, dt
 * ** Pre-Conditions:Must be called 
 * ** Post-Conditions:All inputs will be valid and will be changed in original function
 * *********************************************************************/ 
void get1d(double &k, double &p, double &c, double &len, int &s, int &ti, double &ts,
	double &r, double &l, double &i, double &dX, double &dT){

	// Variable names shortened to save space 
	// Gets all of the values needed and makes sure the user enters a valid value
	k = doubleCheck("What is the Thermal conductivity");
	p = doubleCheck("What is the material density");
	c = doubleCheck("What is the heat capacity");
	len = doubleCheck("What is the length");
	s = intCheck("How many sections (integer)");
	ti = intCheck("How many time intervals (integer)");
	ts = doubleCheck("What is the total time of simulation");
	r = doubleCheck("What is the right temp");
	l = doubleCheck("What is the left temp");
	i = doubleCheck("What is the initial Temp");
	dX = len / double(s);
	dT = ts / double(ti);

}
/*********************************************************************
 * ** Function:doubleCheck
 * ** Description:Checks to see if value is valid and does not contain any bad characters
 * ** Parameters:string message
 * ** Pre-Conditions:must be called with a string
 * ** Post-Conditions:returns a valid double
 * *********************************************************************/ 
double doubleCheck(string message){
	string store;
	double total;
	bool error;
	//Takes in a string and checks for bad characters and other bad input also checks for more than 1 decimal
	do{
		int dot = 0;
		error = false;
		cout << message << "\n" << endl;
		getline(cin, store);
		for(int i = 0; i < store.size(); i++){
			if(store.at(i) == '.'){
				dot+=1;
			}
			else if(!(store.at(i) >= '0' && store.at(i) <= '9')){
				error = true;	
			}
		}
		if(store.size() == 0 || dot > 1){
			error = true;
		}	
		
	}while(error);
	total = strtod(store.c_str(), NULL);
	return total;


}

/*********************************************************************
 * ** Function:intCheck
 * ** Description:Checks user input to see if it is a valid integer and checks for all bad values
 * ** Parameters:string message
 * ** Pre-Conditions:Must be called with a string
 * ** Post-Conditions:Returns a valid integer
 * *********************************************************************/ 
int intCheck(string message){
	string store;
	int total;
	bool error;
	//Takes in a string and checks for bad characters and other bad input
	do{
		error = false;
		cout << message << "\n" << endl;
		getline(cin, store);
		if(store.size() == 0){
			error = true;
		}
		for(int i = 0; i < store.size(); i++){
			if(!(store.at(i) >= '0' && store.at(i) <= '9')){
				error = true;
			}	
		}
	}while(error);
	total = atoi(store.c_str());
	return total;
}
