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

	//-------------------------------------------------
	// initialise the expression() so that primary() can use it
double expression();
double primary();
double term();
/*
 Grammar:
 
 Expression:
 Term
 Expression '+' Term
 Expression '-' Term
 
 Term:
 Primary
 Term '*' Primary
 Term '/' Primary
 Term '%' Primary
 
 Primary:
 Number
 '{' Expression '}
 '(' Expression ')'
 
 Number:
 floating-point literal
 
 */

/*
 Grammar functions used by the calculator:
 1. expression() is used to handle addition & subtraction
 2. term() is used to handle multiplication, division & modulo
 3. primary() is used to handle numbers, parentheses and curly braces
 */

	//Primary() function definition

double primary(){
	Token t = ts.get();
	switch(t.type_token){
			/*case '{':
			 {
			 double d = expression();
			 t = ts.get();
			 if(t.type_token != '}')error("Expected '}'");
			 return d;
			 }*/
		case '(':
		{
		double d = expression();
		t = ts.get();
		if(t.type_token != ')')error("Expected ')'");
		return d;
		}
		case '8':
				//cout<<"number evaluated ok"<<endl;
				//return t.value_token;
			return t.value_token;
			/*
			 default:
			 //cout <<" back to the start!"<<endl;
			 error("primary expected"); */
	}
	return 0;
}

	//-------------------------------------------------

	//Term() function definition
double term() {
		//error("term called");
	double user_expression = primary();
	Token t = ts.get();
	while(true){
		switch (t.type_token)
		{
			case '*':
			user_expression *= primary();
			t = ts.get();
			break;
			
			case '/':
			{
			double divis_expression = primary();
			if(divis_expression == 0) error("Division By Zero");
			user_expression /= divis_expression;
			t = ts.get();
			break;
			}
			case '%':
			{
			double rounding = round(primary());
			int mod_num = (int)rounding;
			cout << mod_num;
			if(mod_num == 0)error("Cannot modulo by Zero");
			int user_Expr_Int = (int)user_expression;
			user_Expr_Int %= mod_num;
			user_expression = user_Expr_Int;
			t = ts.get();
			break;
			}
			default:
				//cout<<"putting back"<<endl;
			ts.putback(t);
			return user_expression;
		}
	}
}
//-------------------------------------------------


int main() {
	
    return 0;
}
