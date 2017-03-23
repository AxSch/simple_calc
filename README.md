# simple_calc
Simple calculator written in C++

The program is written using a set of grammar rules:
Expression --> Term --> Primary

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
        
The implemented grammar is use to 'teach' the computer to evaluate BIDMAS(Brackets, Indices, Division, Multiplication, Addition & Subtraction)
