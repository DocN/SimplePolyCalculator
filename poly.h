//Functions imported
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string>

struct term{ 
	int coeff;
	int deg_x;
	int deg_y;
};

struct node {
	term * value;
	node * next;
};

class poly {
	public:
		poly();
		~poly();
		poly(int,int,int);
		void addPoly(int,int,int);
		void removePoly(int,int,int);
		void printPoly();
		void mergeSort();
		node * getHead();
		node * mergeSort(node*);
		node * split(node *);
		node * merge(node *, node *);
		poly & operator+(poly &poly2);
		
	private:
		node * current;
		node * head;
};