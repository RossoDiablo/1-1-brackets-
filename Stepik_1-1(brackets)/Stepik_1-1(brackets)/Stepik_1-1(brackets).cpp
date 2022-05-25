// Stepik_1-1(brackets).cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class MyStack {
	struct Node {
		char item;
		int position;
		Node *next;
	};
	Node *top;
public:
	MyStack() {top = nullptr;};
	~MyStack();
	void Push(char item_new, int position_new);
	pair<char,int> Pop();
	bool isEmpty();
};

void MyStack::Push(char item_new, int position_new){
	Node *temp_node = new Node;
	temp_node->item = item_new;
	temp_node->position = position_new;
	temp_node->next = top;
	top = temp_node;
};

bool MyStack::isEmpty() {
	return top ? false : true;
}

pair<char,int> MyStack::Pop() {
	pair<char,int> p1;
	if (isEmpty()) {
		p1.first = '-';
		p1.second = -2;
		return p1;
	}
	char temp_item = top->item;
	int temp_position = top->position;
	Node *temp = top;
	top = top->next;
	delete temp;
	p1.first = temp_item;
	p1.second = temp_position;
	return p1;
}

MyStack::~MyStack() {
	while (top) {
		Node *temp_node = top;
		top = top->next;
		delete temp_node;
	}
}

int CheckBrackets (string temp) {
	MyStack stack;
	int bracket_number = 0;
	for (int i = 0; i < temp.length(); i++) {
		if ( (temp[i] == '{') || (temp[i] == '(') || (temp[i] == '[')) {
			stack.Push(temp[i], i+1);
			bracket_number += 1;
		}
		else {
			if ((temp[i] == '}') || (temp[i] == ')') || (temp[i] == ']')) {
				if (stack.isEmpty()) return i + 1;
				pair<char,int> top = stack.Pop();
				if ( 
					(top.first == '[' && temp[i] != ']') || 
					(top.first == '{' && temp[i] != '}') ||
					(top.first == '(' && temp[i] != ')') 
				) return i+1;
				bracket_number -= 1;
			}
		}
	}
	if (stack.isEmpty()) return -1;
	else {
		pair<char,int> top = stack.Pop();
		while (bracket_number > 1) {
			top = stack.Pop();
			bracket_number -= 1;
		}
		return top.second;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str;
	cout << "Type the string: ";
	getline(cin, str);
	int pos = CheckBrackets(str);
	if (pos == -1) cout << endl << "Success" << endl;
	else cout << endl << pos << endl;
	_getch();
	return 0;
}

