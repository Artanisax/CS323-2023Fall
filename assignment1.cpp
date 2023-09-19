#include <iostream>
#include <cstring>

using std::cout, std::endl;

// enum TOKEN
// {   // lexemes
//     TYPE,   // int
//     INT,    // integer
//     ID,     // {L, _, $}{L, D, _, $}*
//     IF,     // if
//     ELSE,   // else
//     WHILE,  // while
//     RET,    // return
//     SEMI,   // ;
//     ASSIGN, // =
//     LT,     // <
//     LE,     // <=
//     GT,     // >
//     GE,     // >=
//     NE,     // !=
//     EQ,     // ==
//     PLUS,   // +
//     MINUS,  // -
//     LP,     // (
//     RP,     // )
//     LC,     // {
//     RC,     // }
// };

// const char *TOKEN_NAME[] =
// {
//     "TYPE",
//     "INT",
//     "ID",
//     "IF",
//     "ELSE",
//     "WHILE",
//     "RET",
//     "SEMI",
//     "ASSIGN",
//     "LT",
//     "LE",
//     "GT",
//     "GE",
//     "NE",
//     "EQ",
//     "PLUS",
//     "MINUS",
//     "LP",
//     "RP",
//     "LC",
//     "RC",
// };

#define MAX_LEN 100

enum STATE
{
    EMPTY,
    SIGN,
    DIGIT,
    LETTER,
};


bool is_sign(char x)
{
    return x == ';' || x == '=' || x == '<' || x == '>' || x == '!' || x == '+' || x == '-' ||
            x == '(' || x == ')' || x == '{' || x == '}';
}

bool is_digit(char x)
{ return isdigit(x); }

bool is_letter(char x)
{ return islower(x) || isupper(x) || x == '_' || x =='$'; }

bool end_of_line(char x)
{ return x == '\n' || x == '\r' || x == '\0'; }

void analyze(FILE *f)
{
    char *line = new char[MAX_LEN];
    while (fgets(line, MAX_LEN, f))
    {
        size_t st = 0;
        for (size_t p = 0, state = STATE::EMPTY; !end_of_line(line[p]); p++)
        {
            char ch = line[p];
            switch (state)
            {
                case STATE::EMPTY:
                    if (is_sign(ch))
                    {
                        st = p;
                        state = STATE::SIGN;
                    }
                    if (is_digit(ch))
                    {
                        state = STATE::DIGIT;
                    }
                    break;
                case STATE::SIGN:
                    
                    break;
                case STATE::DIGIT:
                    
                    break;
                case STATE::LETTER:
                    
                    break;
                default:
                    goto ERROR;
            }
        }
        cout << endl;
    }
    cout << endl;
    delete[] line;
    return;

ERROR:
    cout << "ERROR" << endl;
    delete[] line;
}


int main()
{
    FILE *f;
    
    cout << "testcase 1:\n";
    f = fopen("testcase_1.txt", "r");
    analyze(f);
    fclose(f);
    cout << endl;

    cout << "testcase 2:\n";
    f = fopen("testcase_2.txt", "r");
    analyze(f);
    fclose(f);
    cout << endl;

    return 0;
}
