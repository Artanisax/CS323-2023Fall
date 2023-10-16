%{
    #define YYSTYPE char *
    #include "lex.yy.c"
    #include <string.h>
    int yyerror(char* s);
%}

%token X
%token DOT
%token COLON

%%
// please design a grammar for the valid ip addresses and provide necessary semantic actions for production rules
IP: IPv4 | IPv6
IPv4: Dec DOT Dec DOT Dec DOT Dec
    {
        if ((int)$1 + (int)$3 + (int)$5 + (int)$7 != 0)
            puts("Invalid");
        else
            puts("IPv4");
    }
    ;
IPv6: Hex COLON Hex COLON Hex COLON Hex COLON Hex COLON Hex COLON Hex COLON Hex
    {
        if ((int)$1 + (int)$3 + (int)$5 + (int)$7 + (int)$9 + (int)$11 + (int)$13 + (int)$15 != 0)
            puts("Invalid");
        else
            puts("IPv6");
    }
    ;
Dec: X
    {
        int len = strlen($1), val = atoi($1);
        if (len <= 3 && val <= 255 && !(len > 1 && val == 0) && !($1[0] == '0' && val != 0))
            $$ = 0;
        else
            $$ = 1;
    }
    ;
Hex: X
    {
        int len = strlen($1);
        if (len <= 4 || (len == 1 && $1[0] == '0'))
            $$ = 0;
        else
            $$ = 1;
    }
    ;
%%

int yyerror(char* s) {
    fprintf(stderr, "%s\n", "Invalid");
    return 1;
}
int main() {
    yyparse();
}
