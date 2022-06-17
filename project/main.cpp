#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "lib\json.hpp"

using namespace std;
using json = nlohmann::json;


string strUpper(string str) {
    string upper;
    for (int x=0; x<str.length(); x++) {
        upper += toupper(str[x]);
    }
    
    return upper;
}
string strLower(string str) {
    string upper;
    for (int x=0; x<str.length(); x++) {
        upper += tolower(str[x]);
    }
    
    return upper;
}

class Currency {
	private:
    	json currencyData;
    	json currencyNames;
    public:
        string currencyNamesArr[150]; 

    public: 
	    Currency() {
	        string fileContent;
	        string line;
	
	        ifstream file1("data/currencies.json");
	        while (getline (file1, line)) {
	            fileContent += line;
	        }
	        currencyData = json::parse(fileContent);

            fileContent = "";
	        ifstream file2("data/currencyNames.json");
	        while (getline (file2, line)) {
	            fileContent += line;
	        }
	        currencyNames = json::parse(fileContent);
            int i = 0;
            for (const auto& item : currencyNames.items()) {
                currencyNamesArr[i] = item.key();
                i++;
            }
	    }

        float getCurrencyRate(string baseCurr, string convCurr, float baseCurrVal) {
            if (baseCurr == convCurr)
                return baseCurrVal;
            try {
                return baseCurrVal * float(this->currencyData[baseCurr][convCurr]);
            } catch (json::type_error e) {
                cout<<e.what()<<endl;
                return -1;
            }
        }

        void printCurrencyNames() {
            for (int i = 0; i<150; i++) {
                cout << setw(12) << strUpper(currencyNamesArr[i]);

                if ((i+1) % 6 == 0)
                    cout<<endl;
            }
        }

        bool checkCurrencyName(string name) {
            if (currencyData.contains(name))
                return true;
            return false;
        }
};
Currency currencyObj;

string printMenu1() {
    system("cls");
    currencyObj.printCurrencyNames();
    string input;
    cout<<endl<<"Type base currency: ";
    cin>>input;
    input = strLower(input);
    if (currencyObj.checkCurrencyName(input))
        return input;
    else 
        return printMenu1();
}
string printMenu2() {
    system("cls");
    currencyObj.printCurrencyNames();
    string input;
    cout<<endl<<"Type converted currency: ";
    cin>>input;
    input = strLower(input);
    if (currencyObj.checkCurrencyName(input))
        return input;
    else 
        return printMenu2();
}
float printMenu3(string baseCurr, string convCurr) {
    system("cls");
    float input;
    cout<<"Converting "<<strUpper(baseCurr)<<" to "<<strUpper(convCurr)<<endl;
    cout<<"---------------------\n\n";
    cout<<"1 "<<strUpper(baseCurr)<<" = "<<currencyObj.getCurrencyRate(baseCurr,convCurr,1)<<" "<<strUpper(convCurr);
    cout<<"\n\nEnter amount in "<<strUpper(baseCurr)<<": ";
    cin>>input;
    return input;
}
void saveConversion(string output) {
    ofstream fout;
    fout.open("data/userConversions.txt",ios::app);
    fout<<output<<endl;
    fout.close();
}
void printMenu4(string baseCurr, string convCurr, float baseCurrVal) {
    system("cls");
    string output = to_string(baseCurrVal) + " " + strUpper(baseCurr) + " = " + to_string(currencyObj.getCurrencyRate(baseCurr,convCurr,baseCurrVal)) + " " + strUpper(convCurr);
    cout<<output;
    saveConversion(output);
    cout<<endl<<endl<<"Press any key to continue...";
    getch();
}
void printMenu5() {
    system("cls");
	string line;
    ifstream fin("data/userConversions.txt");
    while (getline (fin, line)) {
        cout<<line<<endl;
    }
    cout<<endl<<endl<<"Press any key to continue...";
    getch();
}
void getInput(int &input) {
    system("cls");
    cout<<"Welcome to Currency Converter"<<endl;
    cout<<"-----------------------------\n\n";
    if (input == 1)
        cout<<"-> ";
    cout<<"Perform conversion"<<endl;
    if (input == 2)
        cout<<"-> ";
    cout<<"View previous conversions"<<endl;
    if (input == 3)
        cout<<"-> ";
    cout<<"Exit\n\n";
    cout<<"-----------------------------";

    cout<<"\n\n(Use arrow keys to navigate. Press enter to select)";
    int ch = getch();
    if (ch == 72) {
        input--;
        if (input < 1)
            input = 1;
        getInput(input);
    }
    else if (ch == 80) {
        input++;
        if (input > 3)
            input = 3;
        getInput(input);
    }
    else if (char(ch) != '\r') {
        getInput(input);
    }
}
int printMainMenu() {
    string baseCurr,convCurr;
    float baseCurrVal;
    int input = 1;

    getInput(input);

    if (input == 1) {
        baseCurr = printMenu1();
        convCurr = printMenu2();
        baseCurrVal = printMenu3(baseCurr, convCurr);
        printMenu4(baseCurr,convCurr,baseCurrVal);
        printMainMenu();
    }
    if (input == 2) {  
        printMenu5();
        printMainMenu();
    }
    if (input == 3) {  // end program
        system("cls");
        cout<<"Exiting program. Goodbye!";
        return 0;
    }
}

int main() {
    printMainMenu();
    return 0;
}
