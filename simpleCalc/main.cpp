//
//  main.cpp
//  simpleCalc
//
//  Created by Korrol Schuneman on 22/03/2017.
//  Copyright © 2017 Korrol Alexander Schuneman. All rights reserved.
//  main.cpp
//  Chapter6Exercise2
//
//  Created by Korrol Schuneman on 20/03/2017.
//  Copyright © 2017 Korrol Alexander Schuneman. All rights reserved.
//  Simple calculator to implement a set of grammar rules


#include "std_lib_facilities.h"

/*
 Classes used Token & Token_Stream
 */
	//Token declaration - read sequence of characters

class Token{
	
public:
	char type_token;
	double value_token;
};
	//-------------------------------------------------

	//Token Stream declaration
/*
 1. Uses Token to get the token data
 2. Uses a buffer to store token using putback()
 3. bool is used as a flag to indicate whether there is a token in the buffer or not
 */

class Token_stream {
	
public:
	Token get();
	void putback(Token t);
	
private:
	bool full{false};
	Token buffer;
	
};
	//-------------------------------------------------
	//2nd member function of Token_stream - get()
	/*
	 1. checks if buffer is full
	 2. read token and
	 */
Token Token_stream::get(){
	if(full){
		full = false;
		return buffer;
	}
	
	char ch;
	cin >> ch;
			
			switch(ch){
				case 'q':
					exit(0);
				case ';':
				case '(':
				case ')':
				case '+':
				case '-':
				case '/':
				case '*':
				case '%':
					return Token{ch};
					
				case '.':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					cin.putback(ch);
					double val;
					cin >> val;
					return Token{'8', val};
				}
				default:
					error("Bad token");
			}
			return Token();
}
//----------------------------------------------
	//-------------------------------------------------
//Initialising a token stream
Token_stream ts;

int main() {
	
    return 0;
}
