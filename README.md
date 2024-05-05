# Truco++
**Truco++** é um compilador inspirado no famoso jogo brasileiro truco, oferecendo uma abordagem simplificada e intuitiva para aprender a programar em outras linguagens. Nosso objetivo é proporcionar um ambiente divertido e estimulante para aqueles que desejam se aventurar na programação usando este projeto.

## Estrutura Básica
Este compilador apresenta uma série de comandos e funções para facilitar o aprendizado. Abaixo estão alguns exemplos:

### Variáveis
> **tento** var1 = 0;                     **(Inteiro)**

> **casal** var2 = 1.4;                   **(Flutuante)**

> **pe** var3 = “truco”;                  **(String)**

> **mao** var4 = ‘x’;                     **(Caractere)**

> **blefe** var5 = 1;                     **(Booleano)**

### Funções
> **truco** (var1 == 0) {                 **(Se)**

>     var3 = “Correto”;

> };

> **meio-pau** (var1 == 1){               **(Senão se)**

>     var3 = “Errado”;

> };

> **cai** { (Senão)

>     var3 = “Errado”;

> };

### Blocos de Repetição
> **rodada** (var1; var1 <= 3; var1++){   **(Loop)**

>      @@ Código @@                       **(Comentário)**

>     **reembaralha** var1;               **(Retorno)**
    
> };

### Operadores Matemáticos
> var1 = var1 **+** var2;                 **(Soma)**

> var1 = var1 **-** var2;                 **(Subtração)**

> var1 = var1 __*__ var2;                 **(Multiplicação)**

> var1 = var1 **/** var2;                 **(Divisão)**

> var1 = var1 **^** var2;                 **(Elevar)**

### Operadores Lógicos
> var1 **||** var2                        **(Ou)**

> var1 **&&** var2                        **(E)**

> var1 **!=** var2                        **(Diferente)**

> var1 **>** var2                         **(Maior)**

> var1 **>=** var2                        **(Maior ou igual)**

> var1 **<** var2                         **(Menor)**

> var1 **<=** var2                        **(Menor ou igual)**

> var1 **==** var2                        **(Igualdade)**

> **!**var1                               **(Negação)**

## Análise Léxica
Durante esta fase, o código é lido e traduzido para facilitar seu manuseio. Cada token é analisado e separado em: tipo, valor, linha e coluna.
Exemplificando o código:

> tento temporario = 10;

![graficoLexica](https://github.com/DavilaGustavo/compiladorTruco/assets/106328212/fca99262-fc97-42a9-844a-028d21e8f2fe)

## Análise Sintática
O analisador sintático percorre a lista de tokens para verificar se estão no formato correto, seguindo as regras do compilador definidas na EBNF.

![graficoSintatica](https://github.com/DavilaGustavo/compiladorTruco/assets/106328212/e21839ee-9ccf-477b-b49e-91500c473589)

## Análise Semântica
Esta etapa verifica se as construções do código-fonte têm um significado válido de acordo com as regras semânticas do compilador, como a verificação de identificadores.

O exemplo abaixo resultaria em erro semântico, porém código válido pela análise sintática.

> tento main(){​

>     tento x = 30;​

>     tento x = 10;​

> } 

## Conclusão
A criação do **Truco++** foi uma jornada desafiadora, porém essencial para compreender cada parte de um compilador. Embora ainda haja espaço para melhorias, estamos comprometidos em aprimorar este projeto continuamente.