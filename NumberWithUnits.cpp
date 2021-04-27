/**
 * Author: Mayan Bashan
 */
#include "NumberWithUnits.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <map>
#include <math.h>
using namespace std;

namespace ariel{

        std::map<std::string, std::map<std::string, double>> NumberWithUnits::units_map{};
        std::map<std::string, bool> NumberWithUnits::units_map_visited{};
        const double EPS = 0.0001;

        double converted(const string &original_unit, const string &unit_to_convert){ 
            if (original_unit == unit_to_convert){
                return 1;
            }
            // Go over the units_map
            for(map<string, map<string, double>>::iterator it = NumberWithUnits::units_map.begin(); it!= NumberWithUnits::units_map.end(); it++){
                if (it->first == original_unit){
                    // Go over the inner map in units_map
                    for (map<string,double>::iterator inner_map = (it->second).begin(); inner_map!=(it->second).end(); inner_map++){
                        if (inner_map->first == unit_to_convert){
                            return inner_map->second;
                        }
                        if (NumberWithUnits::units_map_visited.find(inner_map->first) == NumberWithUnits::units_map_visited.end()){
                            NumberWithUnits::units_map_visited.insert({inner_map->first, true}); //mark curr unit as visited
                            double ans = converted(inner_map->first, unit_to_convert);
                            if (ans != -1){
                                return ans * (inner_map->second);
                            }
                        }
                    }
                }
            }
            return -1;        
        }

        double converted_wrap(const string &original_unit, const string &unit_to_convert){
            double ans = -1;
            NumberWithUnits::units_map_visited.insert({original_unit, true}); //mark original_unit as visited
            ans = converted(original_unit,unit_to_convert);
            NumberWithUnits::units_map_visited.clear(); // reset visited map
            if (ans == -1){
                throw("Units do not match - ["+unit_to_convert+"] "+"cannot be converted to ["+original_unit+"]");
            }
            return ans;
        }

         void ariel::NumberWithUnits::read_units(std::ifstream &ufile){
            double left_amount = 0;
            double right_amount = 0;
            string left_unit;
            string right_unit;
            char eq_sign = 0;
            if (ufile.is_open()){
                while(ufile >> left_amount >> left_unit >> eq_sign >> right_amount >> right_unit){
                    NumberWithUnits::units_map[left_unit][right_unit] = 1/right_amount;
                    NumberWithUnits::units_map[right_unit][left_unit] = right_amount;
                }
                ufile.close();
            }
            else{
                std::cout << "File is not open" << '\n';
            }
         }

        // x + y
        NumberWithUnits ariel::NumberWithUnits::operator +(const NumberWithUnits& nwu) const{
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = this->number + (mult * nwu.number);
                return (NumberWithUnits(updated_number, original_unit));
            }
            catch (const std::exception& ex) {
                throw ("Units do not match, cannot use operator +");
            }
        }

        // + Unary (+x)
        NumberWithUnits operator +(const NumberWithUnits& nwu){ // friend func
            return (NumberWithUnits(nwu.number,nwu.unit));
        }

        // x - y
        NumberWithUnits ariel::NumberWithUnits::operator -(const NumberWithUnits& nwu) const{
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = this->number - (mult * nwu.number);
                return (NumberWithUnits(updated_number, original_unit));
            }
            catch (const std::exception& ex) {
                throw ("Units do not match, cannot use operator -");
            }
        }

         // - Unary (-x)
        NumberWithUnits operator -(const NumberWithUnits& nwu){ // friend function
            return (NumberWithUnits((-1)*nwu.number,nwu.unit));
        }

        // x += y
        NumberWithUnits& ariel::NumberWithUnits::operator +=(const NumberWithUnits& nwu){
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = this->number + (mult * nwu.number);
                this->number = updated_number;
                return *this;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
                throw ("Units do not match, cannot use operator +=");
            }
        }
        
        // x -= y
        NumberWithUnits& ariel::NumberWithUnits::operator -=(const NumberWithUnits& nwu){
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = this->number - (mult * nwu.number);
                this->number = updated_number;
                return *this;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
                throw ("Units do not match, cannot use operator -=");
            }
        }

        // x * number
        NumberWithUnits ariel::NumberWithUnits::operator *(double d) const{
            return (NumberWithUnits(d*(this->number),this->unit));
        }

        // number * x
        NumberWithUnits operator *(double d, const NumberWithUnits& nwu){ //friend function
            return nwu*d;
        }

        // x > y
        bool ariel::NumberWithUnits::operator >(const NumberWithUnits& nwu) const{
            if (this->unit == nwu.unit){
                return (this->number > nwu.number);
            }
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = mult * nwu.number;
                return ((this->number) - updated_number > EPS);
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
                throw ("Units do not match, cannot use operator >");
            }    
        }

        // x < y
        bool ariel::NumberWithUnits::operator <(const NumberWithUnits& nwu) const{
            if (this->unit == nwu.unit){
                return (this->number < nwu.number);
            }
            string unit_to_convert = nwu.unit;
            string original_unit = this->unit;
            try{
                double mult = converted_wrap(original_unit, unit_to_convert);
                double updated_number = mult * nwu.number;
                return (this->number < updated_number);
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
                throw ("Units do not match, cannot use operator <");
            }
        }
        
        // x >= y
        bool ariel::NumberWithUnits::operator >=(const NumberWithUnits& nwu) const{
            return ((*this == nwu) || (*this > nwu));        
        }

        // x <= y
        bool ariel::NumberWithUnits::operator <=(const NumberWithUnits& nwu) const{
            return ((*this == nwu) || (*this < nwu));         
        }

        // x == y
        bool ariel::NumberWithUnits::operator ==(const NumberWithUnits& nwu) const{
            if (this->unit == nwu.unit){
                return (abs(this->number-nwu.number) < EPS);
            }
                string unit_to_convert = nwu.unit;
                string original_unit = this->unit;
                try{
                    double mult = converted_wrap(original_unit, unit_to_convert);
                    double updated_number = mult * nwu.number;
                    return (abs(this->number-updated_number) < EPS);
                }
                catch (const std::exception& ex) {
                    throw ("Units do not match, cannot use operator ==");
                }
        }

        // x != y
        bool ariel::NumberWithUnits::operator !=(const NumberWithUnits& nwu) const{
            return !(*this == nwu);
        }

        // x++
        NumberWithUnits ariel::NumberWithUnits::operator ++(int){ 
            return NumberWithUnits(this->number++, this->unit);
        }

        // ++x
        NumberWithUnits& operator ++(NumberWithUnits& nwu){ // friend func
            nwu.number = nwu.number + 1;
            return nwu;
        }
        
        // x--
        NumberWithUnits ariel::NumberWithUnits::operator --(int){ 
           return NumberWithUnits(this->number--, this->unit);
        }

        // --x
        NumberWithUnits& operator --(NumberWithUnits& nwu){ // friend func
            nwu.number = nwu.number - 1;
            return nwu;        
        }


        // Overload output/input operators

        ostream& operator <<(ostream& output, const NumberWithUnits& nwu){ // friend func
            output << nwu.number << "[" << nwu.unit << "]";
            return output;
        }

        istream& operator >>(istream& input, NumberWithUnits& nwu){ // friend func
            double new_number = 0;
            string new_number_string;
            string new_unit;
            char ch = 0;
            // read the number from the input
            input.get(ch);
            while (ch != '['){
                new_number_string += ch;
                input.get(ch);
            }
            new_number = stod(new_number_string);

            // read the unit from the input
            input.get(ch);
            while (ch != ']') {
                // ignore spaces
                if (ch != ' '){
                    new_unit += ch;
                }
                input.get(ch);
            }

            if (NumberWithUnits::units_map.find(new_unit) == NumberWithUnits::units_map.end()){ //unit doesn't appear in map
                throw("Invalid Input - No such Unit");
            }
            //unit appear in map
            nwu.number = new_number;
            nwu.unit = new_unit;
            return input;
        }    
}
