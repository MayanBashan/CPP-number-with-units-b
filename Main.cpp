/**
 * Author: Mayan Bashan
 */

#include "NumberWithUnits.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <exception>
#include <map>
using namespace std;

int main(){
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 km = 1000 m" << endl;
    myfile << "1 m = 100 cm" << endl;
    myfile << "1 kg = 1000 g" << endl;
    myfile << "1 ton = 1000 kg" << endl;
    myfile << "1 hour = 60 min" << endl;
    myfile << "1 min = 60 sec" << endl;
    myfile << "1 day = 24 hour" << endl;
    myfile << "1 month = 30 day" << endl;
    myfile << "1 year = 12 month" << endl;   
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    ariel::NumberWithUnits::read_units(units_file);
   
    string all_units[] = {"km", "m", "kg", "ton", "hour", "min", "day", "month", "year"};
    double num1=0;
    double num2=0;
    int option=0;
    int unit_option1 = 0;
    int unit_option2 = 0;
    string unit;
    int continue_exit = 0;
    
    while (option != -1) // put whatever your loop exit condition is here
    {
        // creates first object
        cout << "\nHere you can compare between units: \n";
        cout << "\nFirst, enter a number: ";
        cin >> num1;
        cout << "Now, choose a unit from the following: \n";
        cout << "   0.km\n   1.m\n   2.kg\n   3.ton\n   4.hour\n   5.min\n   6.day\n   7.month\n   8.year\n   " <<"\n";
        cin >> unit_option1;
        while (unit_option1 < 0 || unit_option1 > 8){
            cout << "Invalid input, please try again, choose a unit from the following: \n";
            cout << "   0.km\n   1.m\n   2.kg\n   3.ton\n   4.hour\n   5.min\n   6.day\n   7.month\n   8.year\n   " <<"\n";
            cin >> unit_option1;
        }
        ariel::NumberWithUnits A = ariel::NumberWithUnits(num1, all_units[unit_option1]);
        
        // creates second object
        cout << "\nSecond, enter a number: ";
        cin >> num2;
        cout << "Now, choose a unit from the following: \n";
        cout << "   0. km\n   1. m\n   2. kg\n   3. ton\n   4. hour\n   5. min\n   6. day\n   7. month\n   8. year\n";
        cin >> unit_option2;
        while (unit_option1 < 0 || unit_option2 > 8){
            cout << "Invalid input, please try again, choose a unit from the following: \n";
            cout << "   0. km\n   1. m\n   2. kg\n   3. ton\n   4. hour\n   5. min\n   6. day\n   7. month\n   8. year\n";
            cin >> unit_option1;
        }
        ariel::NumberWithUnits B = ariel::NumberWithUnits(num2, all_units[unit_option2]);

        cout << "\nChoose the operation you want to operate between A" << " = " << num1 << "[" << all_units[unit_option1] << "] , to B:" << " = " << num2 << "[" << all_units[unit_option2] << "] :\n";
        cout << "   0. -\n   1. +\n   2. >\n   3. <\n   4. >=\n   5. <=\n   6. ==\n";
        cin >> option;
        bool ans;
        bool flag = false;
        while (option!=-1){
            flag = true;        
            if (option == 0){
                try{
                    cout << (A-B) << "\n";
                }
                catch(exception &e){
                    flag = false;
                    cout << ("Units cannot be converted, try again\n");
                }
            }
            else if (option == 1){
                try{
                    cout << (A+B) << "\n";
                }
                catch(exception &e){
                    flag = false;
                    cout << ("Units cannot be converted, try again\n");
                }
            }
            else if (option == 2){
                try{
                    ans = (A>B);
                    if(ans ==true){
                        cout << "YES, " << num1 << "[" << all_units[unit_option1] << "] > " << num2 << "[" << all_units[unit_option2] << "]\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                catch(exception &e){
                    cout << ("Units cannot be converted, try again\n");
                    flag = false;
                }
            }
            else if (option == 3){
                try{
                    ans = (A<B);
                    if(ans ==true){
                        cout << "YES, " << num1 << "[" << all_units[unit_option1] << "] < " << num2 << "[" << all_units[unit_option2] << "]\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                catch(exception &e){
                    flag = false;
                    cout <<("Units cannot be converted, try again\n");
                }
            }
            else if (option == 4){
                try{
                    ans = (A>=B);
                    if(ans ==true){
                        cout << "YES, " << num1 << "[" << all_units[unit_option1] << "] >= " << num2 << "[" << all_units[unit_option2] << "]\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                catch(exception &e){
                    flag = false;
                    cout << ("Units cannot be converted, try again\n");
                }
            }
            else if (option == 5){
                 try{
                    ans = (A<=B);
                    if(ans ==true){
                        cout << "YES, " << num1 << "[" << all_units[unit_option1] << "] <= " << num2 << "[" << all_units[unit_option2] << "]\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                catch(exception &e){
                    flag = false;
                    cout << ("Units cannot be converted, try again\n");
                }
            }
            else if (option == 6){
                 try{
                    ans = (A==B);
                    if(ans == true){
                        cout << "YES, " << num1 << "[" << all_units[unit_option1] << "] == " << num2 << "[" << all_units[unit_option2] << "]\n";
                    }
                    else{
                        cout << "NO\n";
                    }
                }
                catch (exception &e){
                    flag = false;
                    cout << ("Units cannot be converted, try again\n");
                }
            }
            else{
                cout << "Invalid input, try again!";
                flag = false;
            }
            if (flag == true){
                cout << "\nTo continue press 0, For exit press -1:\n";
                cin >> option;
                while ((option!=0) && (option!=-1)){
                    cout << "Try again, to continue press 0 For exit press -1:\n";
                    cin >> option;
                }
            }
            if (option == -1){
                    cout << "Bye Bye\n";
                }
            else{
                cout << "\nChoose the operation you want to operate between A" << " = " << num1 << "[" << all_units[unit_option1] << "] , to B:" << " = " << num2 << "[" << all_units[unit_option2] << "] :\n";
                cout << "   0. -\n   1. +\n   2. >\n   3. <\n   4. >=\n   5. <=\n   6. ==\n";
                cin >> option;
            }
        }
    }
    return 0;
}
     