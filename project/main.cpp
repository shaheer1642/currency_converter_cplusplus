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

class Currency {
	private:
    	json currencyData;
    	json currencyNames;

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
            int i = 1;
            int j = 1;
            for (const auto& item : currencyNames.items()) {
                cout << setw(12) << i << " - " << strUpper(item.key());
                if (j % 6 == 0)
                    cout<<endl;
                i++;
                j++;
            }
        }

        string getCurrencyName(int num) {
            int i = 1;
            for (const auto& item : currencyNames.items()) {
                if (i == num) {
                    return item.key();
                }
                i++;
            }
            return "undefined";
        }
};
Currency currencyObj;

string printMenu1() {
    system("cls");
    int input;
    currencyObj.printCurrencyNames();
    cout<<endl<<"Select base currency: ";
    cin>>input;
    if (input < 1 || input > 150)
        return printMenu1();
    return currencyObj.getCurrencyName(input);
}
string printMenu2() {
    system("cls");
    int input;
    currencyObj.printCurrencyNames();
    cout<<endl<<"Select converted currency: ";
    cin>>input;
    if (input < 1 || input > 150)
        return printMenu2();
    return currencyObj.getCurrencyName(input);
}
float printMenu3() {
    system("cls");
    float input;
    cout<<"Enter amount: ";
    cin>>input;
    return input;
}
void printMenu4(string baseCurr, string convCurr, float baseCurrVal) {
    system("cls");
    cout<<baseCurrVal<<" "<<strUpper(baseCurr)<<" = "<<currencyObj.getCurrencyRate(baseCurr,convCurr,baseCurrVal)<<" "<<strUpper(convCurr)<<endl;
    cout<<"Press any key to continue...";
    getch();
}
void getInput(int lo, int hi, char* textArr[], int &input) {
    system("cls");
    for (int i=0; i<sizeof(textArr)/sizeof(textArr[0]); i++) {
        if (i + 1 == input)
            cout<<"-> ";
        cout<<textArr[i]<<endl;
    }
    cout<<"\n\n(Use arrow keys to navigate)";
    int ch = getch();
    if (ch == 72) {
        input--;
        if (input < lo)
            input = lo;
        getInput(lo, hi, textArr, input);
    }
    else if (ch == 80) {
        input++;
        if (input > hi)
            input = hi;
        getInput(lo, hi, textArr, input);
    }
    else if (char(ch) != '\r') {
        getInput(lo, hi, textArr, input);
    }
}
int printMainMenu() {
    string baseCurr,convCurr;
    float baseCurrVal;
    int input = 1;

    getInput(1, 3, {"Perform conversion","View previous conversions","Exit"}, input);

    if (input == 1) {
        baseCurr = printMenu1();
        convCurr = printMenu2();
        baseCurrVal = printMenu3();
        printMenu4(baseCurr,convCurr,baseCurrVal);
        printMainMenu();
    }
    if (input == 2) {   // end program
        cout<<"This functionality is not implemented yet";
        return 0;
    }
    if (input == 3) {   // end program
        return 0;
    }
}

int main() {
    printMainMenu();
    return 0;
}
