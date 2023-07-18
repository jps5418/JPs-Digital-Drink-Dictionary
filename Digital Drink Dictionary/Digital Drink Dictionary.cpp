// Digital Drink Dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


using namespace::std;

//may not actually use this class but it has the same stuff as the json file of drinks
class drinkEntry {
public:
    string drinkName;
    list <string> ingredients;
    string drinkDescription;
    string drinkInstructions;

};

void printDrinks() {
    ifstream dJson("drinks.json");
    stringstream buffer;
    buffer << dJson.rdbuf();

    auto json = nlohmann::json::parse(buffer.str());

    for (auto drink : json["drinks"]) {
        cout << drink["drinkName"] << "\n\n";
        cout << "\t" << drink["drinkDescription"] << "\n";
        for (auto ingredient : drink["ingredients"]) {
            cout << "\t\t" << ingredient << "\n";
        }
        cout << "\t" << drink["instructions"] << "\n\n\n";
    }
}

void searchByName() {
    ifstream dJson("drinks.json");
    stringstream buffer;
    buffer << dJson.rdbuf();

    auto json = nlohmann::json::parse(buffer.str());

    cout << "Please enter the name or part of the name of a drink: ";

    string userInput;

    cin >> userInput;

    int drinkCount = 0;

    for (auto drink : json["drinks"]) {
        string temp(drink["drinkName"]);
        if (temp.find(userInput) != string::npos) {
            drinkCount++;
            cout << drink["drinkName"] << "\n\n";
            cout << "\t" << drink["drinkDescription"] << "\n";
            for (auto ingredient : drink["ingredients"]) {
                cout << "\t\t" << ingredient << "\n";
            }
            cout << "\t" << drink["instructions"] << "\n\n\n";
        }
    }
    if (drinkCount == 0) {
        cout << "No drinks found :(\n\n" << endl;
    }
    else {
        cout << drinkCount << " drinks found! :)\n\n" << endl;
    }
}

void searchByIngredients() {
    ifstream dJson("drinks.json");
    stringstream buffer;
    buffer << dJson.rdbuf();

    auto json = nlohmann::json::parse(buffer.str());

    cout << "Name an ingredient then press ENTER.  \nRepeat until all desired ingredients are listed.\nEnter 0 to begin search" << endl;

    string userInput = "start";

    vector <string> ingredientList;

    while (!userInput.empty()) {
        userInput.clear();
        cin >> userInput;
        if (userInput != "0") {
            ingredientList.push_back(userInput);
        }

        if (userInput == "0") {
            break;
        }
    }

    if (ingredientList.size() == 0) {
        cout << "No ingredients input.\nReturning to Main Menu\n\n" << endl;
        return;
    }

    int drinkCount = 0;
    int numIngredients = ingredientList.size();

    for (auto drink : json["drinks"]) {
        int foundIngredient = 0;

        for (auto ingredient : drink["ingredients"]) {
            for (auto userIngredient : ingredientList) {
                string temp1(ingredient);
                //string temp2(
                if (temp1.find(userIngredient) != string::npos) {
                    foundIngredient++;
                }
            }
        }

        if (foundIngredient == numIngredients) {
            drinkCount++;
            cout << drink["drinkName"] << "\n\n";
            cout << "\t" << drink["drinkDescription"] << "\n";
            for (auto ingredient : drink["ingredients"]) {
                cout << "\t\t" << ingredient << "\n";
            }
            cout << "\t" << drink["instructions"] << "\n\n\n";
        }

        /*
        string temp(drink["drinkName"]);
        if (temp.find(userInput) != string::npos) {
            drinkCount++;
            cout << drink["drinkName"] << "\n\n";
            cout << "\t" << drink["drinkDescription"] << "\n";
            for (auto ingredient : drink["ingredients"]) {
                cout << "\t\t" << ingredient << "\n";
            }
            cout << "\t" << drink["instructions"] << "\n\n\n";
        }
        */
    }
    if (drinkCount == 0) {
        cout << "No drinks found :(\n\n" << endl;
    }
    else {
        cout << drinkCount << " drinks found! :)\n\n" << endl;
    }
}

int main()
{
    std::cout << "JP's Digital Drink Dictionary!\n";
    /*
    ifstream dJson("drinks.json");
    stringstream buffer;
    buffer << dJson.rdbuf();

    auto json = nlohmann::json::parse(buffer.str());
    */
    

    char userInput = -1;

    while (userInput != '4') {
        cout << "\nMain Menu:" << endl;
        cout << "\t1. Show all drinks" << endl;
        cout << "\t2. Search by drink name" << endl;
        cout << "\t3. Search by ingredients" << endl;
        cout << "\t4. End Program" << endl;
        cout << "\n\n";

        cin >> userInput;

        switch(userInput) {
            case '1':
                cout << "Printing all drinks!" << endl;
                printDrinks();
                break;
            case '2':
                cout << "Entering search by name!" << endl;
                searchByName();
                break;
            case '3':
                cout << "Entering search by ingredients" << endl;
                searchByIngredients();
                break;
            case '4':
                cout << "Exiting program" << endl;
                break;
            default:
                cout << "INVALID INPUT" << endl;
        }
    }
    

    
    /*
    for (auto drink : json["drinks"]) {
        cout << drink["drinkName"] << "\n\n";
        cout << "\t" << drink["drinkDescription"] << "\n";
        for (auto ingredient : drink["ingredients"]) {
            cout << "\t\t" << ingredient << "\n";
        }
        cout << "\t" << drink["instructions"] << "\n\n\n";
    }
    */
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
