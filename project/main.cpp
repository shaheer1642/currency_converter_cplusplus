#include <iostream>
#include <fstream>
#include "lib\json.hpp"

using namespace std;
using json = nlohmann::json;


class Currency {
	private:
    	json currencyData;

    public: 
	    Currency() {
	        string fileContent;
	        string line;
	
	        ifstream MyReadFile("data/currencies.json");
	
	        while (getline (MyReadFile, line)) {
	            fileContent += line;
	        }
	
	        currencyData = json::parse(fileContent);
	    }

        float getCurrencyRate(string baseCurr, string convCurr, float baseCurrVal) {
            try {
                return baseCurrVal * float(this->currencyData[baseCurr][convCurr]);
            } catch (json::type_error e) {
                cout<<e.what()<<endl;
                return -1;
            }
        }
};

int main() {
    Currency currencyObj;
    
    string baseCurr,convCurr;
    float baseCurrVal;
    cout<<"Enter base currency: ";
    cin>>baseCurr;
    cout<<"Enter convertion currency: ";
    cin>>convCurr;
    cout<<"Enter base currency value: ";
    cin>>baseCurrVal;
    
    cout<<"Result = "<<currencyObj.getCurrencyRate(baseCurr,convCurr,baseCurrVal);

    return 0;
}
