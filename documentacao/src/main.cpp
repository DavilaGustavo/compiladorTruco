#include "bibliotecas.h"
#include "lexica.h"
#include "sintatica.h"
#include "semantica.h"

// Modifique o arquivo programa.txt (ou programa2.txt caso modifique abaixo) para diferentes testes

int main(){
    Lexer lexer("programa.txt"); // ou programa2.txt
    vector<Lexica::Token> tokensLex = lexer.tokenize();
    for (Lexica::Token token1 : tokensLex) {
    cout << token1.toString() << endl;
    }


vector<Sintatica::Token> tokensSint;
    for (const Lexica::Token& tokenLex : tokensLex) {
        Sintatica::Token tokenSint;
        tokenSint.setValue(tokenLex.getValue());
        tokenSint.setType(tokenLex.getType());
        tokenSint.setLine(tokenLex.getLine());
        tokenSint.setColumn(tokenLex.getColumn());
        tokensSint.push_back(tokenSint);
    }

    Sintatica::Token token;
    token.setTokens(tokensSint);

    //printTokens(tokensSint);

    if (token.parseProgram()) {
        cout << "(Sintatica) Codigo valido!" << endl;
    } else {
        cout << "(Sintatica) Codigo invalido!" << endl;
    }


    vector<Semantica::Token> tokensSem;
    for (const Lexica::Token& tokenLex : tokensLex) {
        Semantica::Token tokenSem;
        tokenSem.value = tokenLex.getValue();
        tokenSem.type = tokenLex.getType();
        tokenSem.line = tokenLex.getLine();
        tokenSem.column = tokenLex.getColumn();
        tokensSem.push_back(tokenSem);
    }

    bool check = checkEverything(tokensSem);
    if (check){
        cout << "(Semantica) Codigo valido!" << endl;
    } else {
        cout << "(Semantica) Codigo invalido!" << endl;
    }

    return 0;
}
