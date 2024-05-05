#ifndef ANALISE_SEMANTICA_H
#define ANALISE_SEMANTICA_H
#include "bibliotecas.h"


Semantica::Token getPreviousToken(const vector<Semantica::Token>& tokens, int index) {
    if (index > 0 && index < tokens.size()) {
        return tokens[index - 1];
    }
    return Semantica::Token();
}

Semantica::Token getNextToken(const vector<Semantica::Token>& tokens, int index) {
    if (index > 0 && index < tokens.size()) {
        return tokens[index + 1];
    }
    return Semantica::Token();
}


// Função de análise semântica para verificar a atribuição de um literal para um tipo incompatível
bool checkAssignment(const vector<Semantica::Token>& tokens) {

    bool errorFound = false;
    int temp = 0;
    vector<string> backupLexeme;
    vector<TokenType> backupType;
    vector<int> backupPosition;
    Semantica::Token previousToken;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == TokenType::IDENTIFIER) {
            const Semantica::Token& currentToken = tokens[i];
            if (i > 0) {
                previousToken = tokens[i - 1];  // Atualizar o valor de previousToken
            } else {
                previousToken = Semantica::Token();  // Definir um valor padrão caso seja o primeiro token
            }
            const Semantica::Token& nextToken1 = (i + 1 < tokens.size()) ? tokens[i + 1] : Semantica::Token();
            const Semantica::Token& nextToken2 = (i + 2 < tokens.size()) ? tokens[i + 2] : Semantica::Token();

            if (previousToken.type == INT || previousToken.type == FLOAT || previousToken.type == STRING || previousToken.type == CHAR || previousToken.type == BOOL) {
                backupLexeme.push_back(currentToken.value);
                backupType.push_back(previousToken.type);
                backupPosition.push_back(i-1);
                temp++;

            }
            if (previousToken.type != INT && previousToken.type != FLOAT && previousToken.type != STRING && previousToken.type != CHAR && previousToken.type != BOOL && previousToken.type != VOID) {
                    int found = 0;
                for (int j = 0; j < temp; j++) {
                    if (currentToken.value == backupLexeme[j]){
                        previousToken = tokens[backupPosition[j]];
                        found++;
                    }
                }
                if (found == 0){
                    //cout << "Erro semântico: Identificador '" << currentToken.value << "' deve ser precedido por um tipo válido." << endl;
                    errorFound = true;
                }

            }
            if ((previousToken.type == INT || previousToken.type == FLOAT) && (nextToken1.type == STRINGWORD || nextToken1.type == CHARLETTER || nextToken2.type == STRINGWORD || nextToken2.type == CHARLETTER)) {
                //cout << "Erro semântico: INT/FLOAT armazenando STRING/CHAR." << endl;
                errorFound = true;
            }
            else if ((previousToken.type == STRING || previousToken.type == CHAR) && (nextToken1.type == INTEGER || nextToken1.type == FLOATNUMBER || nextToken2.type == INTEGER || nextToken2.type == FLOATNUMBER)) {
                //cout << "Erro semântico: STRING/CHAR armazenando INT/FLOAT." << endl;
                errorFound = true;
            }
            else if (previousToken.type == BOOL && (nextToken1.type == CHARLETTER || nextToken1.type == FLOATNUMBER || nextToken2.type == CHARLETTER || nextToken2.type == FLOATNUMBER)) {
                //cout << "Erro semântico: BOOL armazenando CHAR/FLOAT." << endl;
                errorFound = true;
            }
        }
    }

    if (errorFound){
        errorFound = false;
        return false;
    }
    else
        return true;
}

bool checkIdentifier(const vector<Semantica::Token>& tokens) {
    bool errorFound = false;
    vector<string> declaredIdentifiers;

    for (int i = 0; i < tokens.size(); i++) {
        const Semantica::Token& currentToken = tokens[i];

        if (currentToken.type == TokenType::IDENTIFIER) {
            string identifierLexeme = currentToken.value;
            bool typeFound = false;
            int typeCount = 0;

            if (i >= 1) {
                const Semantica::Token& previousToken = tokens[i - 1];

                if (previousToken.type == TokenType::INT || previousToken.type == TokenType::CHAR || previousToken.type == TokenType::FLOAT || previousToken.type == TokenType::STRING || previousToken.type == TokenType::BOOL || previousToken.type == TokenType::VOID) {
                    typeFound = true;
                }
            }

            if (find(declaredIdentifiers.begin(), declaredIdentifiers.end(), identifierLexeme) != declaredIdentifiers.end()) {
                if (typeFound) {
                    // Verifica se o identificador possui mais de uma ocorrência de um tipo válido
                    for (int j = 0; j < i; j++) {
                        const Semantica::Token& previousToken = tokens[j];

                        if (previousToken.type == TokenType::IDENTIFIER && previousToken.value == identifierLexeme) {
                            const Semantica::Token& typeToken = tokens[j - 1];

                            if (typeToken.type == TokenType::INT || typeToken.type == TokenType::CHAR || typeToken.type == TokenType::FLOAT || typeToken.type == TokenType::STRING || typeToken.type == TokenType::BOOL) {
                                typeCount++;
                                if (typeCount >= 1) {
                                    errorFound = true;
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    // Ignora o erro se o identificador já foi declarado anteriormente e não possui um tipo válido
                    continue;
                }
            }

            if (typeFound) {
                declaredIdentifiers.push_back(identifierLexeme);
            } else if (!typeFound) {
                errorFound = true;
            }
        }
    }


    if(errorFound){
        errorFound = false;
        return false;
    }
    return true;
}

bool checkMath (const vector<Semantica::Token>& tokens) {
    bool errorFound = false;
    for (int i = 0; i < tokens.size(); i++) {
        const Semantica::Token& currentToken = tokens[i];

        if ((currentToken.type == TokenType::OPERATOR) && (currentToken.value == "+" || currentToken.value == "-" || currentToken.value == "*" || currentToken.value == "/" || currentToken.value == "^")){
            Semantica::Token previousToken = getPreviousToken(tokens, i);
            Semantica::Token nextToken = getNextToken(tokens, i);
            if(previousToken.type != IDENTIFIER){
                if(!((previousToken.type == INTEGER || previousToken.type == FLOATNUMBER) && (previousToken.type == nextToken.type))){
                    errorFound = true;
                }
            }
        } else if ((currentToken.type == TokenType::OPERATOR) && !(currentToken.value == "+" || currentToken.value == "-" || currentToken.value == "*" || currentToken.value == "/" || currentToken.value == "^" || currentToken.value == "!" || currentToken.value == "||" || currentToken.value == "&&")){
            errorFound = true;
        }
    }

    if(errorFound){
        errorFound = false;
        return false;
    }
    return true;
}

bool checkEverything (const vector<Semantica::Token>& tokens){
    if(checkAssignment(tokens) && checkIdentifier(tokens) && checkMath(tokens)){
        return true;
    }
    return false;
}


#endif
