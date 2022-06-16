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
	
	        ifstream MyReadFile("currencies.json");
	
	        while (getline (MyReadFile, line)) {
	            fileContent += line;
	        }
	
	        currencyData = json::parse(fileContent);
	    }

        int getCurrencyRate(string baseCurr, string convCurr) {
            try {
                return this -> currencyData[baseCurr][convCurr];
            } catch (json::type_error e) {
                cout<<e.what()<<endl;
                return -1;
            }
        }
};

int main() {
    Currency currencyObj;
    
    cout<<currencyObj.getCurrencyRate("usde","pkr");

    return 0;
}
