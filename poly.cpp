#include "poly.h"

//Functions imported
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string>
int const DEFAULT = 0;

using namespace std;
poly::poly() {
	current = new node;
	current->value = new term;
	current->value->coeff = DEFAULT;
	current->value->deg_x = DEFAULT;
	current->value->deg_y = DEFAULT;
	current-> next = NULL;
	head = current;
}

poly::poly(int co,int x,int y) {
	current = new node;
	current->value = new term;
	current->value->coeff = co;
	current->value->deg_x = x;
	current->value->deg_y = y;
	current-> next = NULL;
	head = current;
}
poly::~poly() {
	node * previous;
	while(head != NULL) {
		delete &head->value->coeff;
		delete &head->value->deg_x;
		delete &head->value->deg_y;
		previous = head;
		head = head->next;
		delete previous->next;
	}

}
void poly::printPoly() {
	node * list = head;
	while(list != NULL) {
		if(list == head) {
			//if this is the first term we do not need to output + adding operator
		}
		else {
			cout << " + ";
		}
		cout << list->value-> coeff << "(x^"<<list->value-> deg_x << ")" << "(y^" << list->value->deg_y << ")";
		list = list -> next;
	}
	cout << endl;
}
void poly::addPoly(int co,int x,int y) {
	node * checkExist = head;
	bool exists = false;
	while(checkExist != NULL) {
		if((checkExist->value->deg_x == x )&& (checkExist->value->deg_y == y)) {
			checkExist->value->coeff = co + checkExist->value->coeff;
			if(checkExist->value->coeff == 0){ 
				if(checkExist == head && head->next == NULL) {
					checkExist->value->coeff = 0;
					checkExist->value->deg_x = 0;
					checkExist->value->deg_y = 0;
				}
				else {
					removePoly(checkExist->value->coeff, checkExist->value->deg_x, checkExist->value->deg_y);
				}
				exists = true;
				break;
			}
			exists = true;
		}
		checkExist = checkExist -> next;
	}
	if(exists == false) {
		if((current-> value-> coeff == DEFAULT) && (current-> value-> deg_x == DEFAULT) && (current-> value-> deg_y == DEFAULT)) {
			//no need to setup new node because the current one is empty
		}
		else {
			//setup new node
			node * newNode = new node;
			current-> next = newNode;
			current = newNode;
			current->next = NULL;
			current->value = new term;
		}
		current->value-> coeff = co;
		current->value-> deg_x = x;
		current->value-> deg_y = y;
	}
}

void poly::removePoly(int co, int x, int y) {
	if(head == NULL) {
		return;
	}
	node * search = head;
	node * previous = head;
	//check whole linklist for the term
	while(search != NULL) {
		if((search-> value-> coeff == co) && (search-> value-> deg_x == x) && (search-> value-> deg_y == y)) {
			if(search == head) {
				//set head to next node since head needs to be removed
				head = head-> next;
				//deallocate node 
				free(previous->value);
				free(previous);
				previous = head;
				search = head;
			}
			else {
				previous -> next = search-> next;
				free(search->value);
				free(search);
				search = previous -> next;
			}
			break;
		}
		previous = search;
		search = search-> next;
	}
}
void poly::mergeSort() {
	 head =  mergeSort(head);
}
node * poly::mergeSort(node * cHead) {
	if(cHead == NULL || cHead->next == NULL) {
		return cHead;
	}
	node * cHead2 = split(cHead);
	cHead = mergeSort(cHead);
	cHead2 = mergeSort(cHead2);
	return merge(cHead,cHead2);
}

node * poly::split(node * cHead) {
	if(cHead == NULL || cHead->next == NULL) {
		return NULL;
	}
	node * cHead2 = cHead -> next;
	cHead -> next = cHead2-> next;
	cHead2-> next = split(cHead2->next);
	return cHead2;
}

node * poly::merge(node * cHead, node * cHead2) {
	if(cHead == NULL) {
		return cHead2;
	}
	if(cHead2 == NULL) {
		return cHead;
	}
	if(cHead->value->deg_x <= cHead2->value->deg_x) {
		if(cHead->value->deg_x == cHead2->value->deg_x) {
				if(cHead->value->deg_y> cHead2->value->deg_y) {
					cHead2->next = merge(cHead,cHead2->next);
					return cHead2;
				}
		}
		cHead->next = merge(cHead->next, cHead2);
		return cHead;		
	}
	else {
		cHead2->next = merge(cHead, cHead2->next);
		return cHead2;
	}
}
node * poly::getHead() {
	return head;
}
poly& poly::operator+(poly &poly2) {
	node * list1 = head;
	node * list2 = poly2.getHead();
	poly total = poly();
	
	while(list1 != NULL) {
		total.addPoly(list1->value->coeff, list1->value->deg_x,list1->value->deg_y);
		list1 = list1->next;
	}
	while(list2 != NULL) {
		total.addPoly(list2->value->coeff, list2->value->deg_x,list2->value->deg_y);
		list2 = list2->next;
	}

	total.mergeSort();
	return total;
}



