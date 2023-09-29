%{
    #define EXIT_OK 0
    #define EXIT_FAIL 1

    // global variables
    int identifiers = 0;
    int lines = 1;
%}
letter [a-zA-Z]
letter_ {letter}|_
digit [0-9]
lineFeedMac \r\n
line_feed_win \n

IF if
ELSE else
WHILE while
RET return
INT int
CHAR char
S_QUOTE \'

RESERVED {IF}|{ELSE}|{WHILE}|{RET}|{INT}|{CHAR}

%%
{S_QUOTE}({letter_}|{digit})*{S_QUOTE} {}
{RESERVED} {}
{digit}+{letter_} {}
{letter_}({letter_}|{digit})* { identifiers++; printf("line %d: %s\n", lines, yytext); } 
{lineFeedMac}|{line_feed_win} { lines++; }
[\t\r ]+ { /* does nothing when seeing white spaces except new line */ }
. { /* a final rule that matches when seeing any character but new line */ }
<<EOF>> { printf("There are %d occurrences of valid identifiers\n", identifiers); yyterminate(); }

%%
int main(int argc, char **argv)
{
    char *file_path;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAIL;
    } else if (argc == 2)
    {
        file_path = argv[1];
        if (!(yyin = fopen(file_path, "r")))
        {
            perror(argv[1]);
            return EXIT_FAIL;
        }
        yylex();
        return EXIT_OK;
    }
    else
    {
        fputs("Too many arguments! Expected: 2.\n", stderr);
        return EXIT_FAIL;
    }
}
