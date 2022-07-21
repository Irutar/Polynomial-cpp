
#ifndef POLYNOMIAL_POLY_H
#define POLYNOMIAL_POLY_H
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class poly {
private:

    vector<double> coefficient;
    unsigned int current;

public:

    poly() {
		current = 0;
	}

    poly(double value) {
		current = 0;
		coefficient.push_back(value);
	}

    poly& operator[] (unsigned int pos){
		this->current = pos;
		return *this;
	}

    poly& operator= (double value){
		if (coefficient.size() <= current +1) {
			coefficient.resize(current + 1);
		}
		coefficient.at(current) = value;
		return *this;
	}

    poly& operator= (const poly &newPoly){
		coefficient = newPoly.coefficient;
		current = newPoly.current;
		return *this;
	}

    poly operator+ (const poly &newPoly){

		poly temp = newPoly;

		if (temp.coefficient.size() > coefficient.size() ) {
			coefficient.resize(temp.coefficient.size());
		} else {
			temp.coefficient.resize(coefficient.size());
		}

		transform( temp.coefficient.begin(), temp.coefficient.end(), coefficient.begin(), temp.coefficient.begin(), plus<double>() );

		return temp;
	}

    friend ostream &operator<<(ostream &out, const poly &toPrint){

		const char *sign;
		sign = "";
		if( toPrint.coefficient.size() == 0) {
			out << "0" <<endl;
		}

		for (int i = toPrint.coefficient.size() - 1; i >= 0; i--) {
			if (toPrint.coefficient[i] != 0) {

				if (toPrint.coefficient[i] < 0) {
					sign = "-";
				} else if (i == toPrint.coefficient.size() - 1){
					sign = "";
				} else {
					sign = "+";
				}


				if(i == 0){
					out <<sign << " " << toPrint.coefficient[i] << " ";
				} else if (i == 1){
					if (toPrint.coefficient[i] == 1) {
						out <<sign << " x ";
					} else {
						out <<sign << " " << toPrint.coefficient[i] <<"x ";
					}
				} else {
					if (toPrint.coefficient[i] == 1) {
						out <<sign << " x^" <<i <<" ";
					} else {
						out <<sign << " " << toPrint.coefficient[i] <<"x^" <<i <<" ";
					}

				}
			}
		}

		return out<< endl;
	}

    friend poly operator*(double number, const poly &polynomial) {
		poly temp;
		temp.coefficient.resize(polynomial.coefficient.size());

		for(unsigned int i=0; i < polynomial.coefficient.size(); i++) {
			temp.coefficient.at(i) = number * polynomial.coefficient.at(i);
		}
		return temp;
	}


    double operator() (double point) {
		double value = 0;

		if (coefficient.size() == 0) {
			return value;
		}

		value += coefficient.at(0);
		if(coefficient.size() == 1) {
			return value;
		}

		for(unsigned int i = 1; i < coefficient.size(); i++) {
			if(coefficient.at(i)) {
				value += coefficient.at(i) * pow(point, i);
			}
		}
		return value;
	}

    poly operator* (const poly &polynomial) {
		poly result;
		result.coefficient.resize(coefficient.size() + polynomial.coefficient.size() - 1);

		for (unsigned int i = 0; i < coefficient.size(); i++) {
			for (unsigned int j = 0; j < polynomial.coefficient.size(); j++) {
				result.coefficient.at(i + j) += (coefficient.at(i) * polynomial.coefficient.at(j));
			}
		}
		return result;
	}

};

#endif //POLYNOMIAL_POLY_H
