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

int main() {
	
    return 0;
}
