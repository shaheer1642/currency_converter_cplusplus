/* 
IMPORTANT NOTE: 

	Add the following line to Tools > Compiler Options > General:
		-std=c++11 
		
	or else the program will not compile
*/

#include <iostream>         // includring for cout/cin
#include <fstream>          // including for file handling
#include <iomanip>          // including for setw() function
#include <conio.h>          // including for getch() function
#include "lib/json.hpp"     // including for JSON data structure support

using namespace std;
using json = nlohmann::json;        // defining json as data type

string strUpper(string str) {       // this function converts a given string to upper case
    string upper;
    // loop through each character and convert to upper case using toupper() built-in function
    for (int x=0; x<str.length(); x++) {   
        upper += toupper(str[x]);
    }
    
    return upper;
}
string strLower(string str) {       // this function converts a given string to lower case
    string upper;
    // loop through each character and convert to lower case using tolower() built-in function
    for (int x=0; x<str.length(); x++) {
        upper += tolower(str[x]);
    }
    
    return upper;
}

// the Currency class that contains data about each currency and some methods
class Currency {
	private:
    	json currencyData;      // contains data for upto 150 currency rates
    public:
        string currencyNamesArr[150];       // contains all currency names

    public: 
	    Currency() {        // the constructor method to iniatialize class variables
	        string fileContent;
	        string line;
	
	        ifstream file1("data/currencies.json");     // this file contains json formatted data about currency rates
            // read each line and append to fileContent variable
	        while (getline (file1, line)) {     // read the file line by line and append to fileContent var
	            fileContent += line;
	        }
            // parsing/converting the read string into json data structure
	        currencyData = json::parse(fileContent);

            fileContent = "";   // empty the variable
	        ifstream file2("data/currencyNames.json");      // this file contains json formatted data about all currency names and codes
            // read each line and append to fileContent variable
	        while (getline (file2, line)) {      // read the file line by line and append to fileContent var
	            fileContent += line;
	        }
            // parsing/converting the read string into json data structure
	        json currencyNames = json::parse(fileContent);
            int i = 0;
            for (const auto& item : currencyNames.items()) {    // convert the json data into an array structure and store into currencyNamesArr
                currencyNamesArr[i] = item.key();
                i++;
            }
	    }

        // this function calculates the currency rate between 2 currencies
        float getCurrencyRate(string baseCurr, string convCurr, float baseCurrVal) {    
            if (baseCurr == convCurr)   // if both currency are the same, return the base value
                return baseCurrVal;
            try {
                return baseCurrVal * float(this->currencyData[baseCurr][convCurr]);   // get currency rate from currencyData and multiply with base value
            } catch (json::type_error e) {
                cout<<e.what()<<endl;   // if error occurs, return -1
                return -1;
            }
        }

        // this function prints currency names on the console
        void printCurrencyNames() {
            for (int i = 0; i<150; i++) {
                cout << setw(12) << strUpper(currencyNamesArr[i]);

                if ((i+1) % 6 == 0)
                    cout<<endl;
            }
        }

        // this function verifies if a currnecy name is valid
        bool checkCurrencyName(string name) {
            if (currencyData.contains(name))
                return true;
            return false;
        }
};
Currency currencyObj;   // create new object of the Currency class

// this function takes input from the user for base currency
string printMenu1() {
    system("cls");  // clear screen
    currencyObj.printCurrencyNames();   // print the currency names on console
    string input;
    cout<<endl<<"Type base currency: ";
    cin>>input;
    input = strLower(input);
    if (currencyObj.checkCurrencyName(input))   // check if user input is a valid currency name
        return input;
    else 
        return printMenu1();    // else recall the function to take a valid input
}
// this function takes input from the user for converted currency
string printMenu2() {
    system("cls");  // clear screen
    currencyObj.printCurrencyNames();   // print the currency names on console
    string input;
    cout<<endl<<"Type converted currency: ";
    cin>>input;
    input = strLower(input);
    if (currencyObj.checkCurrencyName(input))   // check if user input is a valid currency name
        return input;
    else 
        return printMenu2();    // else recall the function to take a valid input
}
// this function takes input from the user for amount
float printMenu3(string baseCurr, string convCurr) {
    system("cls");  // clear screen
    float input;
    cout<<"Converting "<<strUpper(baseCurr)<<" to "<<strUpper(convCurr)<<endl;
    cout<<"---------------------\n\n";
    cout<<"1 "<<strUpper(baseCurr)<<" = "<<currencyObj.getCurrencyRate(baseCurr,convCurr,1)<<" "<<strUpper(convCurr);  // print the currency rate
    cout<<"\n\nEnter amount in "<<strUpper(baseCurr)<<": ";     // take input for amount
    cin>>input;
    return input;
}
// this function saves the conversion to userConversions.txt file
void saveConversion(string output) {
    ofstream fout;  // create new output file stream
    fout.open("data/userConversions.txt",ios::app);     // open userConversions.txt file
    fout<<output<<endl;     // append the conversion to the file
    fout.close();       // close and clear file from memory
}
// this function output the conversion result on the screen
void printMenu4(string baseCurr, string convCurr, float baseCurrVal) {
    system("cls");  // clear screen
    // format the output in readable form
    string output = to_string(baseCurrVal) + " " + strUpper(baseCurr) + " = " + to_string(currencyObj.getCurrencyRate(baseCurr,convCurr,baseCurrVal)) + " " + strUpper(convCurr);
    cout<<output;
    // save the conversion
    saveConversion(output);
    cout<<endl<<endl<<"Press any key to continue...";
    getch();    // wait for user input and terminate the function
}
// this function prints all previous conversion on the screen
void printMenu5() {
    system("cls");  // clear screen
	string line;
    ifstream fin("data/userConversions.txt");  // open the userConversions.txt file
    while (getline (fin, line)) {   // read and print the file contents line by line
        cout<<line<<endl;
    }
    cout<<endl<<endl<<"Press any key to continue...";
    getch();    // wait for user input and terminate the function
}
// this function prints a navigation menu and return input of the user
void getInput(int &input) {
    system("cls");  // clear screen
    cout<<"Welcome to Currency Converter"<<endl;
    cout<<"-----------------------------\n\n";
    if (input == 1)     // print arrow if select is at current position
        cout<<"-> ";
    cout<<"Perform conversion"<<endl;
    if (input == 2)     // print arrow if select is at current position
        cout<<"-> ";
    cout<<"View previous conversions"<<endl;
    if (input == 3)     // print arrow if select is at current position
        cout<<"-> ";
    cout<<"Exit\n\n";
    cout<<"-----------------------------";

    cout<<"\n\n(Use arrow keys to navigate. Press enter to select)";
    int ch = getch();   // wait for user input and store in ch variable
    if (ch == 72) {     // if user input is UP arrow key, decrement input 
        input--;
        if (input < 1)      // input cannot be less than 1
            input = 1;
        getInput(input);    // recall function wait for another key press
    }
    else if (ch == 80) {     // if user input is DOWN arrow key, increment input 
        input++;
        if (input > 3)      // input cannot be greater than 3
            input = 3;
        getInput(input);    // recall function wait for another key press
    }
    else if (char(ch) != '\r') {
        getInput(input);    // if input is not enter key, recall function wait for another key press
    }
    // else terminate the function
}
// this function prints the main menu with 3 options
int printMainMenu() {
    string baseCurr,convCurr;
    float baseCurrVal;
    int input = 1;

    getInput(input);

    if (input == 1) {   // the first option performs conversion 
        baseCurr = printMenu1();    // get the base currency
        convCurr = printMenu2();    // get the converted currency
        baseCurrVal = printMenu3(baseCurr, convCurr);    // get the amount
        printMenu4(baseCurr,convCurr,baseCurrVal);  // print the conversion result
        printMainMenu();    // go back to main menu
    }
    if (input == 2) {   // the second option shows previous conversions
        printMenu5();       // print previous conversions
        printMainMenu();    // go back to main menu
    }
    if (input == 3) {  // the third option ends the program
        system("cls");  // clear screen
        cout<<"Exiting program. Goodbye!";      // print goodbye message
        return 0;
    }
}

int main() {
    printMainMenu();    // call main menu until it returns 0
    return 0;
}
