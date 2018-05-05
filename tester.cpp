#include "poly.h"

//Functions imported
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;
struct listPoly {
	poly value;
	listPoly * next;
};

int stringToInteger(string value) {
	int numb;
	istringstream (value) >> numb;
	return numb;
}

int main () {
	listPoly * myList = NULL;
	listPoly * head;
	int counter = 0;
	int terms, coeff, deg_x, deg_y;
	int currentInteger;
	ifstream infile("poly.txt");
	
	if(!infile) {
		cout << "file can not be read" << endl;
	}
	else {
		while(infile >> currentInteger) {
			if(counter == 0) {
				listPoly * newPoly = new listPoly;
				if(myList == NULL) {
					head = newPoly;
				}
				else {
					myList-> next = newPoly;
				}
				newPoly->next = NULL;
				myList = newPoly;
				terms = currentInteger;
				counter = counter +1;
			}
			else if(counter == 1) {
				coeff = currentInteger;
				counter = counter +1;
			}
			else if(counter == 2) {
				deg_x = currentInteger;
				counter = counter +1;
			}
			else if(counter == 3) {
				deg_y = currentInteger;
				myList->value.addPoly(coeff,deg_x,deg_y);
				terms = terms -1;
				if(terms == 0) {
					counter = 0;
				}
				else {
					counter = 1;
				}
			}
			
		}
	}
	
	while(head != NULL) {
		head->value.mergeSort();
		head->value.printPoly();
		head = head->next;
	}
	return 0;
}