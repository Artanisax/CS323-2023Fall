#include <iostream>
#include <cstring>

using std::cout, std::endl, std::min;

#define MAX_LEN 100

const size_t SIGN_NUM = 14, SIGN_LEN = 2;
const char *KEY_SIGN[] =
{
    ";",
    "=",
    "<",
    "<=",
    ">",
    ">=",
    "!=",
    "==",
    "+",
    "-",
    "(",
    ")",
    "{",
    "}",
};
const char *SIGN_NAME[] =
{
    "SEMI",
    "ASSIGN",
    "LT",
    "LE",
    "GT",
    "GE",
    "NE",
    "EQ",
    "PLUS",
    "MINUS",
    "LP",
    "RP",
    "LC",
    "RC",
};

const size_t WORD_NUM = 5, WORD_LEN = 6;
const char *KEY_WORD[] =
{
    "int",
    "if",
    "else",
    "while",
    "return",
};
const char *WORD_NAME[] =
{
    "TYPE",
    "IF",
    "ELSE",
    "WHILE",
    "RET"
};

enum STATE
{
    EMPTY,
    SIGN,
    DIGIT,
    LETTER,
    POS_NEG,
};

bool is_empty(char x)
{ return x == ' '; }

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

bool pos_or_neg(char x)
{ return x == '+' or x == '-'; }

bool valid(char x)
{
    return is_empty(x) || end_of_line(x) ||
        is_sign(x) || is_digit(x) || is_letter(x);
}

void print_sign(char *s, size_t len)
{
    for (size_t start = 0, length = min(SIGN_LEN, len); start < len; length--)
        for (int i = 0; i < SIGN_NUM; i++)
        {
            if (strncmp(s + start, KEY_SIGN[i], length) == 0)
            {
                cout << SIGN_NAME[i] << ' ';
                start += length;
                length = min(SIGN_LEN, len - start);
                break;
            }
        }
}

void print_word(char *s, size_t len)
{
    if (len <= WORD_LEN)
        for (size_t i = 0; i < WORD_NUM; i++)
            if (strncmp(s, KEY_WORD[i], len) == 0)
            {
                cout << WORD_NAME[i] << ' ';
                return;
            }
    cout << "ID ";
}

void analyze(FILE *f)
{
    char *line = new char[MAX_LEN];
    while (fgets(line, MAX_LEN, f))
    {
        size_t p = 0, state = STATE::EMPTY, start = 0;
        while (true)
        {
            char ch = line[p];
            if (!valid(ch))
                goto ERROR;
            switch (state)
            {
                case STATE::EMPTY:
                    start = p;
                    if (is_sign(ch))
                        if (pos_or_neg(ch))
                            state = STATE::POS_NEG;
                        else
                            state = STATE::SIGN;
                    if (is_digit(ch))
                        state = STATE::DIGIT;
                    if (is_letter(ch))
                        state = STATE::LETTER;
                    break;
                case STATE::POS_NEG:
                    if (is_digit(ch))
                        state = STATE::DIGIT;
                    else
                        state = STATE::DIGIT;
                    break;
                case STATE::SIGN:
                    if (!is_sign(ch))
                    {
                        print_sign(line + start, p - start);
                        p -= !end_of_line(ch);
                        state = STATE::EMPTY;
                    }
                    break;
                case STATE::DIGIT:
                    if (!is_digit(ch))
                    {
                        if (is_letter(ch))
                            goto ERROR;
                        cout << "INT ";
                        p -= !end_of_line(ch);
                        state = STATE::EMPTY;
                    }
                    break;
                case STATE::LETTER:
                    if (!is_letter(ch) && !is_digit(ch))
                    {
                        print_word(line + start, p - start);
                        p -= !end_of_line(ch);
                        state = STATE::EMPTY;
                    }
                    break;
                default:
                    goto ERROR;
            }
            if (end_of_line(ch))
                break;
            p++;
        }
        cout << endl;
    }
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
    f = fopen("test1.spl", "r");
    analyze(f);
    fclose(f);
    cout << endl;

    cout << "testcase 2:\n";
    f = fopen("test2.spl", "r");
    analyze(f);
    fclose(f);
    cout << endl;

    return 0;
}
