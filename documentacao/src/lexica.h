#ifndef ANALISE_LEXICA_H
#define ANALISE_LEXICA_H
#include "bibliotecas.h"


// Implementacao do construtor
Lexica::Token::Token(TokenType type, string value, int line, int column) {
    this->type = type;
        this->value = value;
        this->line = line;
        this->column = column;
}

// Implementacao da funcao toString()
string Lexica::Token::toString() {
        return "<" + this->value + ", " + getTokenTypeString(this->type) + ">";
}

    // Implementacao da funcao getValue()
string Lexica::Token::getValue() const {
    return this->value;
}

   // Implementacao da funcao getType()
TokenType Lexica::Token::getType() const {
    return this->type;
}

int Lexica::Token::getLine() const {
    return this-> line;
}

int Lexica::Token::getColumn() const {
    return this-> column;
}

    // Implementacao da funcao getTokenTypeString()
string Lexica::Token::getTokenTypeString(TokenType type) {
    switch (type) {
            case IDENTIFIER:
                return "IDENTIFIER";
            case COMMA:
                return "COMMA";
            case INTEGER:
                return "INTEGER";
            case OPERATOR:
                return "OPERATOR";
            case ASSIGNMENT:
                return "ASSIGNMENT";
            case COMPARISON:
                return "COMPARISON";
            case LEFT_PARENTHESIS:
                return "LEFT_PARENTHESIS";
            case RIGHT_PARENTHESIS:
                return "RIGHT_PARENTHESIS";
            case LEFT_BRACKET:
                return "LEFT_BRACKET";
            case RIGHT_BRACKET:
                return "RIGHT_BRACKET";
            case SEMICOLON:
                return "SEMICOLON";
            case IF:
                return "IF";
            case ELSE:
                return "ELSE";
            case WHILE:
                return "WHILE";
            case FOR:
                return "FOR";
            case INT:
                return "INT";
            case FLOAT:
                return "FLOAT";
            case FLOATNUMBER:
                return "FLOATNUMBER";
            case CHAR:
                return "CHAR";
            case CHARLETTER:
                return "CHARLETTER";
            case STRING:
                return "STRING";
            case STRINGWORD:
                return "STRINGWORD";
            case BOOL:
                return "BOOL";
            case RETURN:
                return "RETURN";
            case INCDEC:
                return "INCDEC";
            case VOID:
                return "VOID";
            default:
                return "UNKNOWN";
        }
}

    // Implementacao do construtor
Lexer::Lexer(string filename) {
    this->input.open(filename);
        this->current_char = ' ';
        this->line = 1;
        this->column = 1;
}

    // Implementacao da funcao tokenize()
vector<Lexica::Token> Lexer::tokenize() {
    vector<Lexica::Token> tokens;
        while (this->current_char != EOF) {
            this->readChar();
            if (this->current_char == '@' && this->peekChar() == '@') {
                this->skipComment();
            } else if (isalpha(this->current_char)) {
                tokens.push_back(this->readIdentifier());
            } else if (isdigit(this->current_char)) {
                Lexica::Token numberToken = this->readNumber();
                this->unreadChar();
                tokens.push_back(numberToken);
            } else if (this->current_char == '=') {
                this->readChar();
                if (this->current_char == '=') {
                    tokens.push_back(Lexica::Token(COMPARISON, "==", this->line, this->column));
                } else {
                    tokens.push_back(Lexica::Token(ASSIGNMENT, "=", this->line, this->column));
                    this->unreadChar();
                }
            } else if (this->current_char == '+') {
    this->readChar();
    if (this->current_char == '+') {
        // Adiciona o token INCDEC com o IDENTIFIER anterior como parte
        Lexica::Token identifier = tokens.back();
        tokens.pop_back();
        tokens.push_back(Lexica::Token(INCDEC, identifier.getValue() + "++", this->line, this->column));
    } else {
        tokens.push_back(Lexica::Token(OPERATOR, "+", this->line, this->column));
        this->unreadChar();
    }
} else if (this->current_char == '-') {
    this->readChar();
    if (this->current_char == '-') {
        // Adiciona o token INCDEC com o IDENTIFIER anterior como parte
        Lexica::Token identifier = tokens.back();
        tokens.pop_back();
        tokens.push_back(Lexica::Token(INCDEC, identifier.getValue() + "--", this->line, this->column));
    } else {
        tokens.push_back(Lexica::Token(OPERATOR, "-", this->line, this->column));
        this->unreadChar();
    }
} else if (this->current_char == '*') {
                tokens.push_back(Lexica::Token(OPERATOR, "*", this->line, this->column));
            } else if (this->current_char == '/') {
                tokens.push_back(Lexica::Token(OPERATOR, "/", this->line, this->column));
            } else if (this->current_char == '(') {
                tokens.push_back(Lexica::Token(LEFT_PARENTHESIS, "(", this->line, this->column));
            } else if (this->current_char == ')') {
                tokens.push_back(Lexica::Token(RIGHT_PARENTHESIS, ")", this->line, this->column));
            } else if (this->current_char == '{') {
                tokens.push_back(Lexica::Token(LEFT_BRACKET, "{", this->line, this->column));
            } else if (this->current_char == '}') {
                tokens.push_back(Lexica::Token(RIGHT_BRACKET, "}", this->line, this->column));
            } else if (this->current_char == ';') {
                tokens.push_back(Lexica::Token(SEMICOLON, ";", this->line, this->column));
            } else if (this->current_char == ',') {
                tokens.push_back(Lexica::Token(COMMA, ",", this->line, this->column));
            } else if (this->current_char == '!') {
                tokens.push_back(Lexica::Token(OPERATOR, "!", this->line, this->column));
            } else if (this->current_char == '^') {
                tokens.push_back(Lexica::Token(OPERATOR, "^", this->line, this->column));
            } else if (this->current_char == '&'  && this->peekChar() == '&') {
                this->readChar();
                tokens.push_back(Lexica::Token(OPERATOR, "&&", this->line, this->column));
            } else if (this->current_char == '|' && this->peekChar() == '|') {
                this->readChar();
                tokens.push_back(Lexica::Token(OPERATOR, "||", this->line, this->column));
            } else if (this->current_char == '<') {
                this->readChar();
                if (this->current_char == '=') {
                    tokens.push_back(Lexica::Token(COMPARISON, "<=", this->line, this->column));
                } else {
                    tokens.push_back(Lexica::Token(COMPARISON, "<", this->line, this->column));
                    this->unreadChar();
                }
            } else if (this->current_char == '>') {
                this->readChar();
                if (this->current_char == '=') {
                    tokens.push_back(Lexica::Token(COMPARISON, ">=", this->line, this->column));
                } else {
                    tokens.push_back(Lexica::Token(COMPARISON, ">", this->line, this->column));
                    this->unreadChar();
                }
            } else if (this->current_char == '!') {
                this->readChar();
                if (this->current_char == '=') {
                    tokens.push_back(Lexica::Token(COMPARISON, "!=", this->line, this->column));
                } else {
                    cout << "Erro lexico na linha " << this->line << ", posicao " << this->column << ": caractere nao reconhecido '" << this->current_char << "'" << endl;
                }
            } else if (this->current_char == '"') {
                tokens.push_back(this->readString());
            } else if (this->current_char == '\'') {
                tokens.push_back(this->readCharLiteral());
            } else if (this->current_char == ' ' || this->current_char == '\t') {
                // Espaços em branco e tabulações são ignorados
            } else if (this->current_char == '\n') {
                this->line++;
                this->column = 0;
            } else {
                if(this->current_char != EOF)
                    cout << "Erro lexico na linha " << this->line << ", posicao " << this->column << ": caractere nao reconhecido '" << this->current_char << "'" << endl;
            }
        }
    return tokens;
    }

void Lexer::skipComment() {
        while (this->current_char != EOF) {
            this->readChar();
            if (this->current_char == '@' && this->peekChar() == '@') {
                this->readChar();
                return;
            }
        }
}

char Lexer::peekChar() {
        char next_char = this->input.peek();
        if(next_char == EOF)
            return '\0';
        else
            return next_char;
}

void Lexer::readChar() {
        this->current_char = this->input.get();
        this->column++;
}

void Lexer::unreadChar() {
        this->input.unget();
        this->column--;
}

Lexica::Token Lexer::readIdentifier() {
    string value;
    while (isalnum(this->current_char) || this->current_char == '_') {
        value += this->current_char;
        this->readChar();
    }
    this->unreadChar();
    if (value == "truco") {
        return Lexica::Token(IF, value, this->line, this->column);
    } else if (value == "cai") {
        return Lexica::Token(ELSE, value, this->line, this->column);
    } else if (value == "partida") {
        return Lexica::Token(FOR, value, this->line, this->column);
    } else if (value == "tento") {
        return Lexica::Token(INT, value, this->line, this->column);
    } else if (value == "casal") {
        return Lexica::Token(FLOAT, value, this->line, this->column);
    } else if (value == "mao") {
        return Lexica::Token(CHAR, value, this->line, this->column);
    } else if (value == "pe") {
        return Lexica::Token(STRING, value, this->line, this->column);
    } else if (value == "blefe") {
        return Lexica::Token(BOOL, value, this->line, this->column);
    } else if (value == "pato") {
        return Lexica::Token(VOID, value, this->line, this->column);
    } else if (value == "reembaralha") {
        return Lexica::Token(RETURN, value, this->line, this->column);
    } else {
        return Lexica::Token(IDENTIFIER, value, this->line, this->column);
    }
}

Lexica::Token Lexer::readNumber() {
        string value;
        int dot_count = 0;
        do {
            value += this->current_char;
            if(this->current_char == '.')
                dot_count++;
            this->readChar();
        } while (isdigit(this->current_char) || this->current_char == '.');

        if (dot_count > 1) {
            cout << "Erro lexico na linha " << this->line << ", posicao " << this->column << ": formato invalido de numero float '" << value << "'" << endl;
        }

        if (dot_count == 0) {
            return Lexica::Token(INTEGER, value, this->line, this->column - value.size());
        } else {
            return Lexica::Token(FLOATNUMBER, value, this->line, this->column - value.size());
        }
}

Lexica::Token Lexer::readString() {
    string value;
    this->readChar();
    while (this->current_char != '"') {
        value += this->current_char;
        this->readChar();
    }
    return Lexica::Token(STRINGWORD, value, this->line, this->column);
}

Lexica::Token Lexer::readCharLiteral() {
    this->readChar();
    Lexica::Token token(CHARLETTER, string(1, this->current_char), this->line, this->column);
    this->readChar();
    return token;
}

#endif
