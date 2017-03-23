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
#include <math.h>

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

//------------------------------------------------
//1st member function of Token_stream - putback()
/*
 1. Takes argument, token t and puts it back into the stream
 2. Flag(full) is switched to true if a token is in the buffer
 */

void Token_stream::putback(Token t){
	if(full)error("putback() into a full buffer!");
	buffer = t;
	full = true;
}
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
						//case '%':
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
			//if(t.type_token != ')')error("Expected ')'");
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
		case '-':
			return - primary();
		
		case '+':
			return primary();
			
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
			/*{
			double rounding = round(primary());
			int mod_num = (int)rounding;
			cout << mod_num;
			if(mod_num == 0)error("Cannot modulo by Zero");
			int user_Expr_Int = (int)user_expression;
			user_Expr_Int %= mod_num;
			user_expression = user_Expr_Int;
			t = ts.get();
			break;
			}*/
			{
				double d = primary();
				if(d == 0)error("%: divide by zero");
				user_expression = std::fmod(user_expression,d);
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

	//Expression() function definition
double expression() {
	/*
	 1. Call term()
	 2. Retrieve token and evaluate it
	 3. Return the result
	 */
	
	double user_expression = term();
	Token t = ts.get();
	while(true){
		switch(t.type_token){
				
			case '+': //Checks for a token with type '+'
					  //cout<<"found a +"<<endl;
				user_expression += term(); //Evaulates addition
				t = ts.get(); //Get the next token from the stream
				break;
				
			case '-':
				user_expression -= term();//Same as above but for subtraction
				t = ts.get();
				break;
				
			default:
					//cout<<" in default path "<<endl;
				ts.putback(t); //Once there are no more tokens matching the case above, the token t is putback into the stream
				return user_expression; //Return the result(Hopefully the correct one)
		}
	}
	
}


	//------------------------------------------------

int main() {
	try{
		cout << "Hello, and welcome to my simple calculator program!\n"
		<< "Here are the instructions for using the calculator:\n"
		<< "Enter an expression that you want to evaluate followed by a semi-colon, ';' to finish the expression\n"
		<< "To terminate the program, use 'q' for 'QUIT'\n";
		double result = 0;
		while(cin){
			cout << ">";
			Token t  = ts.get();
			if(t.type_token == 'q')break;
			if(t.type_token ==';'){
				cout <<"="<< result << endl;
			}
			else{
				ts.putback(t);
				
			}
		result = expression();
		}
		
	}
	catch(runtime_error& e){
		cerr<<e.what()<<'\n';
			//keep_window_open();
		cout << "Please enter the character ~ to close the window\n";
		for(char ch; cin >> ch;){
			if(ch =='~') return 1;
		}
		return 1;
	}
	catch(...){
		cerr<<"exception has occurred"<<endl;
		keep_window_open();
		return 2;
	}
	
	return 0;
}
