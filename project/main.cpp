#include <iostream>
#include <fstream>
#include <iomanip>
#include "lib\json.hpp"

using namespace std;
using json = nlohmann::json;


string strUpper(string str) {
    string upper;
    for (int x=0; x<str.length(); x++)
        upper += toupper(str[x]);
    
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
    return currencyObj.getCurrencyName(input);
}
string printMenu2() {
    system("cls");
    int input;
    currencyObj.printCurrencyNames();
    cout<<endl<<"Select converted currency: ";
    cin>>input;
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
    cout<<"Result = "<<currencyObj.getCurrencyRate(baseCurr,convCurr,baseCurrVal);
}

int main() {

    string baseCurr,convCurr;
    float baseCurrVal;

    baseCurr = printMenu1();
    convCurr = printMenu2();
    baseCurrVal = printMenu3();
    printMenu4(baseCurr,convCurr,baseCurrVal);

    return 0;
}
