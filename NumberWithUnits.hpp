/**
 * Author: Mayan Bashan
 */

#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <map>
using namespace std;

namespace ariel{
    class NumberWithUnits{

        private:
            double number;
            string unit; 
            static std::map<std::string, std::map<std::string, double>> units_map;
            static std::map<std::string, bool> units_map_visited;
        
        public:
            NumberWithUnits(){
                number = 0;
                unit = "";
            }
            ~NumberWithUnits(){}; // destructor

            NumberWithUnits(double _number, string _unit){
                // checks if unit appears in map
                if(NumberWithUnits::units_map.find(_unit) == NumberWithUnits::units_map.end()){
                    throw("Unit is Unknown");
                }
                else{
                    number = _number;
                    unit = _unit;
                }
            }
            NumberWithUnits(const NumberWithUnits& other){
                number = other.number;
                unit = other.unit;
            }

            friend double converted_wrap(const string &original_unit, const string &unit_to_convert);
            friend double converted(const string &original_unit, const string &unit_to_convert);

            static void read_units(std::ifstream &ufile);

            NumberWithUnits operator +(const NumberWithUnits& nwu) const;
            friend NumberWithUnits operator +(const NumberWithUnits& nwu); // + Unary (+x)
            NumberWithUnits operator -(const NumberWithUnits& nwu) const;
            friend NumberWithUnits operator -(const NumberWithUnits& nwu); // - Unary (-x)
            NumberWithUnits& operator +=(const NumberWithUnits& nwu); 
            NumberWithUnits& operator -=(const NumberWithUnits& nwu);
            NumberWithUnits operator *(double d) const;
            friend NumberWithUnits operator *(double d, const NumberWithUnits& nwu);

            bool operator >(const NumberWithUnits& nwu) const;
            bool operator <(const NumberWithUnits& nwu) const;
            bool operator >=(const NumberWithUnits& nwu) const;
            bool operator <=(const NumberWithUnits& nwu) const;
            bool operator ==(const NumberWithUnits& nwu) const;
            bool operator !=(const NumberWithUnits& nwu) const;

            NumberWithUnits operator ++(int); // x++ 
            friend NumberWithUnits& operator ++(NumberWithUnits& nwu); // ++x
            NumberWithUnits operator --(int); // x--
            friend NumberWithUnits& operator --(NumberWithUnits& nwu); // --x

            friend ostream& operator <<(ostream& output, const NumberWithUnits& nwu);
            friend istream& operator >>(istream& input, NumberWithUnits& nwu);
    };
}