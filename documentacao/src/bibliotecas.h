#ifndef BIBLIOTECAS_H
#define BIBLIOTECAS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;


enum TokenType {
    IDENTIFIER,
    COMMA,
    INTEGER,
    OPERATOR,
    ASSIGNMENT,
    COMPARISON,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    SEMICOLON,
    IF,
    ELSE,
    WHILE,
    FOR,
    INT,
    FLOAT,
    FLOATNUMBER,
    CHAR,
    CHARLETTER,
    STRING,
    STRINGWORD,
    BOOL,
    RETURN,
    INCDEC,
    VOID
};


//LEXICA.H

namespace Lexica{
    class Token {
    public:
        Token(TokenType type, string value, int line, int column);
        string toString();
        string getValue() const;
        TokenType getType() const;
        int getLine() const;
        int getColumn() const;
    private:
        TokenType type;
        string value;
        int line = 1;
        int column;
        string getTokenTypeString(TokenType type);
    };
}
// Classe para o analisador lexico
class Lexer {
public:
    Lexer(string filename);
    vector<Lexica::Token> tokenize();
private:
    ifstream input;
    char current_char;
    int line;
    int column;
    void skipComment();
    char peekChar();
    void readChar();
    void unreadChar();
    Lexica::Token readIdentifier();
    Lexica::Token readNumber();
    Lexica::Token readString();
    Lexica::Token readCharLiteral();
};



//SINTATICA.H

namespace Sintatica{
class Token {
public:
    TokenType type;
    string value;
    int line = 1;
    int column;
    Token();
    Token(TokenType type, string value, int line, int column);
    string getValue() const;
    TokenType getType() const;
    int getLine() const;
    int getColumn() const;
    void setValue(string value);
    void setType(TokenType type);
    void setLine(int line);
    void setColumn(int column);

    int temp = 0;
    size_t currentTokenIndex = 0;
    bool loop = false;
    bool returnFound = false;
    bool returnRequired = false;


    bool parseProgram();
    void setTokens(const vector<Token>& tokenList);
    void printTokens(const std::vector<Sintatica::Token>& tokens);
    bool parseDeclaration();

private:
    vector<Token> tokens;
    bool parseType();
    bool match(TokenType expectedType);
    Token currentToken();
    Token nextToken();
    Token olderToken();
    bool parseMath();
    bool parseDeclarationComparison();
    bool parseValue();
    bool parseCommand();
    bool parseConditionalCommand();
    bool parseLoopCommand();
    bool parseReturnCommand();
    bool parseFunction();
    bool parseParameterList();
    bool parseBlock();
};
}

namespace Semantica{
struct Token {
    TokenType type;
    string value;
    int line;
    int column;
};
}
Semantica::Token getPreviousToken(const vector<Semantica::Token>& tokens, int index);
Semantica::Token getNextToken(const vector<Semantica::Token>& tokens, int index);
bool checkAssignment(const vector<Semantica::Token>& tokens);
bool checkIdentifier(const vector<Semantica::Token>& tokens);
bool checkMath(const vector<Semantica::Token>& tokens);
bool checkEverything(const vector<Semantica::Token>& tokens);

#endif
