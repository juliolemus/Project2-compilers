#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_POWER,
    T_DIVIDE,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_OPENBRACKET,
    T_CLOSEBRACKET,
    T_EQUALS,
    T_SEMICOLON,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_EOF
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
private:
    int lineCount;
    int lastNum;

    
public:
    token nextToken(); 
    void eatToken(token);
    int lineNumber();
    int getNumberValue();
    
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME
    Scanner();
};

Scanner::Scanner()
{
   lineCount=1;
   lastNum=0;
}

token Scanner::nextToken() 
{
    char c=std::cin.peek();

    while(c=='\n')
    {
        lineCount++;
        std::cin.get();
        c=std::cin.peek();
    }

    while(c==' ' || c=='\t')
    {
        std::cin.get();
        c=std::cin.peek();
    }

    if (c>='0' && c<='9')
    {
       return T_NUMBER;
    }
    else if(c=='p' || c=='P')
    {
        std::string y;
        std::cin >> y;

        if(y=="print" || y=="Print")
        {
          std::cin.putback(' ');
          std::cin.putback('t');
          std::cin.putback('n');
          std::cin.putback('i');
          std::cin.putback('r');
          std::cin.putback('p');
 
          return T_PRINT;
        }
        else
        {
            if(y=="pirnt")
            {
                scanError(lineCount,'i');
            }
            else if(y=="pinrt")
            {
                scanError(lineCount,'i');
            }
            else if(y=="pintr")
            {
                scanError(lineCount,'i');
            }
            else if(y=="pritn")
            {
                scanError(lineCount,'i');
            }
            else if(y=="prnit")
            {
                scanError(lineCount,'n');
            }
            else if(y=="prnti")
            {
                scanError(lineCount,'n');
            }
            else if(y=="pnrit")
            {
                scanError(lineCount,'n');
            }
            else if(y=="prnit")
            {
                scanError(lineCount,'n');
            }
            else if(y=="ptrni")
            {
                scanError(lineCount,'t');
            }
            else if(y=="prtni")
            {
                scanError(lineCount,'t');
            }
            else if(y=="prnti")
            {
                scanError(lineCount,'t');
            }
            else if(y=="ptrin")
            {
                scanError(lineCount,'t');
            }
            else if(y=="p")
            {
                scanError(lineCount,' ');
            }
            else if(y=="pr")
            {
                scanError(lineCount,' ');
            }
            else if(y=="pri")
            {
                scanError(lineCount,' ');
            }
            else if(y=="prin")
            {
                scanError(lineCount,' ');
            }
        }
    }
    else if(c==';')
    {
        return T_SEMICOLON;
    }
    else if(c=='(')
    {
        return T_OPENPAREN;
    }
    else if(c==')')
    {
        return T_CLOSEPAREN;
    }
    else if(c=='+')
    {
        return T_PLUS;
    }
    else if(c=='-')
    {
        return T_MINUS;
    }
    else if(c=='=')
    {
        return T_EQUALS;
    }
    else if(c=='/')
    {
        return T_DIVIDE;
    }
    else if(c=='[')
    {
        return T_OPENBRACKET;
    }
    else if(c==']')
    {
        return T_CLOSEBRACKET;
    }
    else if(c=='m')
    {
        return T_M;
    }
    else if(c=='M')
    {
        return T_M;
    }
    else if(c=='*')
    {
        char c2;
        c2=std::cin.get();
        c=std::cin.peek();
        if(c=='*')
        {
            std::cin.putback(c2);
            return T_POWER;
        }
        else
        {
            std::cin.putback(c2);
            return T_MULTIPLY;
        }
    }
    else if(c==EOF)
    {
        return T_EOF;
    }
    else
    {
        scanError(lineCount,c);
    }
 
}

void Scanner::eatToken(token toConsume) 
{

    if(toConsume==T_NUMBER)
    {
        int x1;
        std::cin >> x1;
        lastNum=x1;
    }
    else if(toConsume==T_PRINT)
    {
        std::string x2;
        std::cin >> x2;
    }
    else if(toConsume==T_MULTIPLY)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_SEMICOLON)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_OPENPAREN)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_CLOSEPAREN)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_PLUS)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_MINUS)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_EQUALS)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_DIVIDE)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_OPENBRACKET)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_CLOSEBRACKET)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_MULTIPLY)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_M)
    {
        char x3;
        std::cin >> x3;
    }
    else if(toConsume==T_POWER)
    {
        char x3;
        std::cin >> x3;
        std::cin >> x3;
    }
    else if(toConsume==T_EOF)
    {
        char x3;
        std::cin >> x3;
    }
    
}

int Scanner::lineNumber() 
{
    return lineCount;
}

int Scanner::getNumberValue() 
{
    return lastNum;
}

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
private:
    Scanner scanner;
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    int *array;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    void Stmnts();
    void Stmnt();
    void Stmnts_p(); //p stands for prime
    int Exp();
    int Exp_p(int);
    int Term();
    int Term_p(int);
    int Factor();
    int Factor_p(int);
    int Factor2();

public:
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
        array = new int[100];
        for (int i = 0 ; i < 100; i++){
            array[i] = 0;
        }
    }
};

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    Start();
}

void Parser::Start() {
    Stmnts();
}

void Parser::Stmnts()
{
    Stmnt();
    Stmnts_p();
    
}

void Parser::Stmnt(){
    int x,y;
    token symbol;
    switch (scanner.nextToken()) 
    {
        case T_PRINT:
            scanner.eatToken(T_PRINT);
            if(evaluate==false)
            {
                Exp();
            }
            else
            {
                std::cout<<Exp()<<std::endl;
            }
            break;
        case T_M:
            scanner.eatToken(T_M);
            symbol=scanner.nextToken();
            if(symbol!=T_OPENBRACKET)
            {
                mismatchError(scanner.lineNumber(),T_OPENBRACKET,symbol);
            }
            else
            {
                scanner.eatToken(T_OPENBRACKET);
            }
            x=Exp();
            symbol=scanner.nextToken();
            if(symbol!=T_CLOSEBRACKET)
            {
                mismatchError(scanner.lineNumber(),T_CLOSEBRACKET,symbol);
            }
            else
            {
                scanner.eatToken(T_CLOSEBRACKET);
            }
            scanner.eatToken(T_EQUALS);
            y=Exp();
            if (x >= 0 && x <= 99)
            {
                if(evaluate)
                {
                    array[x]=y;
                    
                }
            }
            else
            {
                if(evaluate){
                    indexError(scanner.lineNumber(),x);
                    
                }
            }
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break; 
    }
}

void Parser::Stmnts_p()
{
    switch (scanner.nextToken()) 
    {
        case T_SEMICOLON:
            scanner.eatToken(T_SEMICOLON);
            Stmnt();
            Stmnts_p();
            break;
        case T_EOF:
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break; 
    }
}

int Parser::Exp()
{   
    return Exp_p(Term());
}


int Parser::Exp_p(int num)
{
    switch (scanner.nextToken()) 
    {
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            return Exp_p(num+Term());
            break;
        case T_MINUS:
            scanner.eatToken(T_MINUS);
            return Exp_p(num-Term()); 
            break;
        case T_CLOSEBRACKET:
            return num;
            break;
        case T_SEMICOLON:
            return num;
            break;
        case T_CLOSEPAREN:
            return num;
            break;
        case T_EOF:
            return num;
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }

}

int Parser::Term(){
    return Term_p(Factor());
}

int Parser::Term_p(int factor)
{
    switch(scanner.nextToken())
    {
        int x;
        case T_MULTIPLY:
            scanner.eatToken(T_MULTIPLY);
            return Term_p(factor*Factor());
            break;
        case T_DIVIDE:
            scanner.eatToken(T_DIVIDE);
            x=Factor();    
            if(evaluate==false)
            {
              return Term_p(factor);
            }
            else
            {
              if(x==0)
              {
                divideError(scanner.lineNumber());
              }
              else
              {
                return Term_p(factor/x);
              }
            } 
            break;
        case T_PLUS:
            return factor;
            break;
        case T_MINUS:
            return factor;
            break;
        case T_CLOSEBRACKET:
            return factor;
            break;
        case T_SEMICOLON:
            return factor;
            break;
        case T_CLOSEPAREN:
            return factor;
            break;
        case T_EOF:
            return factor;
            break;
        default:
            parseError(scanner.lineNumber(),scanner.nextToken());
            break;
     }
}

int Parser::Factor()
{
    return Factor_p(Factor2());
}

int Parser::Factor_p(int factor2)
{
    switch(scanner.nextToken())
    {
        case T_POWER:
            scanner.eatToken(T_POWER);
            return Factor_p(pow(factor2,Factor_p(Factor2()))); //second arguement evaluates itself with Factor_p  //evalutes 2**(1**2) but does (1**2) first then does 2**(1**2) to return the answer
            break;
        case T_MULTIPLY:
            return factor2;
            break;
        case T_DIVIDE:
            return factor2;
            break;
        case T_PLUS:
            return factor2;
            break;
        case T_MINUS:
            return factor2;
            break;
        case T_SEMICOLON:
            return factor2;
            break;
        case T_CLOSEPAREN:
            return factor2;
            break;
        case T_CLOSEBRACKET:
            return factor2;
            break;
        case T_EOF:
            return factor2; 
            break;
        default:
            parseError(scanner.lineNumber(),scanner.nextToken());
            break;
     }
}

int Parser::Factor2()
{  
    int x;
    token symbol;
    switch (scanner.nextToken()) 
    {
        case T_NUMBER:
            scanner.eatToken(T_NUMBER);
            if(evaluate==false)
            {
                return 1;
            }
            return scanner.getNumberValue();
            break;
        case T_EOF:
            return x; 
            break;
        case T_OPENPAREN:
            scanner.eatToken(T_OPENPAREN);
            x=Exp();
            symbol=scanner.nextToken();
            if(symbol!=T_CLOSEPAREN)
            {
                mismatchError(scanner.lineNumber(),T_CLOSEPAREN,symbol);
            }
            else
            {
                scanner.eatToken(T_CLOSEPAREN);
            }
            return x;
            break;
        case T_M:
            scanner.eatToken(T_M);
            scanner.eatToken(T_OPENBRACKET);
            x=Exp();
            symbol=scanner.nextToken();
            if(symbol!=T_CLOSEBRACKET)
            {
                mismatchError(scanner.lineNumber(),T_CLOSEBRACKET,symbol);
            }
            else
            {
                scanner.eatToken(T_CLOSEBRACKET);
            }
            if(evaluate==false)
            {
                return 1;
            }
            else
            {
                if (x >= 0 && x <= 99 )
                {
                    if (evaluate){
                        return array[x];
                    }
                }
                else
                {
                    if (evaluate){
                        indexError(scanner.lineNumber(),x);
                    }
                }
            }
            break;
        default:
            parseError(scanner.lineNumber(),scanner.nextToken());
            break; 
    }

}



int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }

    return 0;
}
