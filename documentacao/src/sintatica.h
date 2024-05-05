#ifndef ANALISE_SINTATICA_H
#define ANALISE_SINTATICA_H
#include "bibliotecas.h"


    Sintatica::Token::Token() {
        this->type = type;
        this->value = value;
        this->line = line;
        this->column = column;
    }

    //construtor
    Sintatica::Token::Token(TokenType type, string value, int line, int column) {
        this->type = type;
        this->value = value;
        this->line = line;
        this->column = column;
    }

    string Sintatica::Token::getValue() const {
        return this-> value;
    }

    TokenType Sintatica::Token::getType() const {
        return this-> type;
    }

    int Sintatica::Token::getLine() const {
        return this-> line;
    }

    int Sintatica::Token::getColumn() const {
        return this-> column;
    }

    void Sintatica::Token::setValue(string value) {
        this->value = value;
    }

    void Sintatica::Token::setType(TokenType type) {
        this->type = type;
    }

    void Sintatica::Token::setLine(int line) {
        this->line = line;
    }

    void Sintatica::Token::setColumn(int column) {
        this->column = column;
    }

    bool Sintatica::Token::parseProgram() {
        while (currentTokenIndex < tokens.size()) {
            if (!parseDeclaration() && !parseDeclarationComparison() && !parseCommand()) {
                return false;
            }
        }
        return true;
    }

    // método para definir os tokens
    void Sintatica::Token::setTokens(const vector<Token>& tokenList) {
        tokens = tokenList;
    }

    void printTokens(const std::vector<Sintatica::Token>& tokens) {
        for (const Sintatica::Token& token : tokens) {
            std::cout << "Type: " << token.getType() << ", Value: " << token.getValue() << ", Line: " << token.getLine() << ", Column: " << token.getColumn() << std::endl;
        }
    }

    bool Sintatica::Token::parseDeclaration() {
        size_t initialTokenIndex = currentTokenIndex;
        if (parseType() && match(IDENTIFIER) && match(ASSIGNMENT)) {
            while (!(currentToken().value == "!" || currentToken().value == "||" || currentToken().value == "&&") && match(OPERATOR)) {
                if (!(parseMath())) {
                    currentTokenIndex = initialTokenIndex;
                    return false;
                }
            }
            if (parseValue() && match(SEMICOLON)) {
                return true;
            }
        }
        currentTokenIndex = initialTokenIndex;
        return false;
    }

    // Resto do código...

    vector<Sintatica::Token> tokens;

    bool Sintatica::Token::parseType() {
        return (match(INT) || match(CHAR) || match(FLOAT) || match(STRING) || match(BOOL) || match(VOID));
    }

    bool Sintatica::Token::match(TokenType expectedType) {
        if (currentTokenIndex < tokens.size() && tokens[currentTokenIndex].type == expectedType) {
            currentTokenIndex++;
            return true;
        }
        return false;
    }

    Sintatica::Token Sintatica::Token::currentToken() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex];
        }
        return tokens[currentTokenIndex];
    }

    Sintatica::Token Sintatica::Token::nextToken() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex + 1];
        }
        return tokens[currentTokenIndex + 1];
    }

    Sintatica::Token Sintatica::Token::olderToken() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex - 1];
        }
        return tokens[currentTokenIndex - 1];
    }

    bool Sintatica::Token::parseMath() {
        if (match(INTEGER) || match(FLOATNUMBER) || match(IDENTIFIER)){
            return true;
        }
        return false;
    }

    bool Sintatica::Token::parseDeclarationComparison() {
        size_t initialTokenIndex = currentTokenIndex;
        if(currentToken().value == "!")
            match(OPERATOR);
        while (match(LEFT_PARENTHESIS)) {
            if(currentToken().value == "!")
                match(OPERATOR);
            temp++;
        }
        if (loop == true){
            if (match(IDENTIFIER) && match(COMPARISON) && parseValue()) {
                    while (temp > 0 && match(RIGHT_PARENTHESIS)){
                            temp--;
                    }
                if(currentToken().type == TokenType::OPERATOR){
                    if(match(OPERATOR) && (olderToken().value == "&&" || olderToken().value == "||")){
                        parseDeclarationComparison();
                    }
                    else{
                        parseMath();
                    }
                }
                loop = false;
                if (temp == 0)
                    return true;
                else{
                    temp = 0;
                    currentTokenIndex = initialTokenIndex;
                    return false;
                }
            }
        } else {
                if (match(IDENTIFIER)){
                    if (match(SEMICOLON)){
                        if (temp == 0)
                            return true;
                    }
                    if (match(ASSIGNMENT) && parseValue()){
                        while (!(currentToken().value == "!" || currentToken().value == "||" || currentToken().value == "&&") && match(OPERATOR)){
                            if(!parseMath()){
                                currentTokenIndex = initialTokenIndex;
                                return false;
                            }
                        }
                        if(match(SEMICOLON)) {
                            if (temp == 0)
                                return true;
                        }
                    }
                }
        }
        currentTokenIndex = initialTokenIndex;
        return false;
    }

    bool Sintatica::Token::parseValue() {
        return (match(INTEGER) || match(FLOATNUMBER) || match(CHARLETTER) || match(STRINGWORD) || match(IDENTIFIER));
    }

    bool Sintatica::Token::parseCommand() {
        if (parseLoopCommand() || parseConditionalCommand() || parseReturnCommand() || parseFunction()) {
            if (match(SEMICOLON)) {
                return true;
            }
        }

        return false;
    }

    bool Sintatica::Token::parseConditionalCommand() {
        size_t initialTokenIndex = currentTokenIndex;
        if (match(IF) && match(LEFT_PARENTHESIS)) {
            loop = true;
            if (parseDeclarationComparison() && match(RIGHT_PARENTHESIS) && parseBlock()) {
            while (match(SEMICOLON) && match(ELSE)){
            if (parseBlock()) {
                return true;
            }
            while (match(IF) && match(LEFT_PARENTHESIS) && parseDeclarationComparison() && match(RIGHT_PARENTHESIS) && parseBlock()) {
            }
            }
            return true;
            }
        }
        currentTokenIndex = initialTokenIndex;
        return false;
    }

    bool Sintatica::Token::parseLoopCommand() {
        size_t initialTokenIndex = currentTokenIndex;
        if (match(FOR) && match(LEFT_PARENTHESIS) && (parseDeclaration() || parseDeclarationComparison())){
            loop = true;
            if (parseDeclarationComparison() && match(SEMICOLON) && match(INCDEC) && match(RIGHT_PARENTHESIS) && parseBlock()) {
            return true;
            }
        }
        currentTokenIndex = initialTokenIndex;
        return false;
    }

    bool Sintatica::Token::parseReturnCommand() {
        size_t initialTokenIndex = currentTokenIndex;
        if (match(RETURN) && parseValue()) {
            while (!(currentToken().value == "!" || currentToken().value == "||" || currentToken().value == "&&") && match(OPERATOR)){
                if(!parseMath()){
                    currentTokenIndex = initialTokenIndex;
                    temp = 0;
                    return false;
                }
            }
            returnFound = true;
            return true;
        }
        currentTokenIndex = initialTokenIndex;
        temp = 0;
        return false;
    }

    bool Sintatica::Token::parseFunction(){
        size_t initialTokenIndex = currentTokenIndex;
        if (!parseType()) {
            currentTokenIndex = initialTokenIndex;
            return false;
        }
        if (olderToken().type != VOID) {
            returnRequired = true;
        }
        if (match(IDENTIFIER) && match(LEFT_PARENTHESIS)) {
            parseParameterList();
            if (match(RIGHT_PARENTHESIS) && parseBlock()) {
                return true;
            }
        }
        currentTokenIndex = initialTokenIndex;
        returnRequired = false;
        return false;
    }

    bool Sintatica::Token::parseParameterList() {
        size_t initialTokenIndex = currentTokenIndex;
        if(parseType());
        if(match(IDENTIFIER)) {
            while (match(COMMA)) {
                if (!parseType());
                if (!match(IDENTIFIER)) {
                    currentTokenIndex = initialTokenIndex;
                    returnRequired = false;
                    return false;
                }
            }
        }
        return true;
    }

    bool Sintatica::Token::parseBlock() {
        size_t initialTokenIndex = currentTokenIndex;
        if (match(LEFT_BRACKET)) {
            while (!match(RIGHT_BRACKET)) {
                if (!parseDeclaration() && !parseCommand() && !parseDeclarationComparison() && !parseFunction()) {
                    currentTokenIndex = initialTokenIndex;
                    returnRequired = false;
                    return false;
                }
            }
            if(returnRequired && !returnFound){
                currentTokenIndex = initialTokenIndex;
                returnRequired = false;
                return false;
            }
                return true;
        }
        currentTokenIndex = initialTokenIndex;
        returnRequired = false;
        return false;
    }


#endif
