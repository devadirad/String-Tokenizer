//————————————DESCRIPTION———————————— 
Equivalent of a Java class that implements a tokenizer. Accepts a string as command line argument which contains one or more tokens. Tokens may be adjacent or separated by whitespace. Tokenizer shall print out token and token type. Escape characters shall produce an error. Valid tokens include:

A word token is an alphabetic character followed by any number of alphanumeric characters.






    {"(","round left brace"},
    {")","round right brace"},
    {"[","square left brace"},
    {"]","square right brace"},
    {"{","left curly brace"},
    {"}","right curly brace"},
    {"~","tilde"},
    {"!","not"},
    {"@","at"},
    {"#","hash"},
    {"$","dollar"},
    {"%","mod"},
    {"^","raised to"},
    {"&","and"},
    {"*","star"},
    {"-","dash"},
    {"+","plus"},
    {"++","increment"},
    {"_","underscore"},
    {"=","equal to"},
    {"==","is equal to"},
    {"--","decrement"},
    {"`","backtick "},
    {":","colon"},
    {";","semi-colon"},
    {"\"","quotes"},
    {"'","single quote"},
    {"<","less than"},
    {"<=","less than equal to"},
    {">","greater than"},
    {">=","greater than equal to"},
    {"<<","left shift"},
    {">>","right shift"},
    {".","dot"},
    {"/","forward slash"},
    {"|","or"},
    {"||","logical or"},
    {"&&","logical and"},
    {"!=","not equal to"},
    {"+=","plus equal"},
    {"-=","minus equal"},
    {"*=","star equal"},
    {"/=","divide equal"},
    {"%=","mod equal"},
    {"&=","and equal"},
    {"|=","or equal"},
    {"->","pointer"},
    {"?","question mark"},
    {",","comma"}

Escape characters that produce errors include:

    {"\\a","[0x07]"},
    {"\\b","[0x08]"},
    {"\\f","[0x0C]"},
    {"\\n","[0x0A]"},
    {"\\r","[0x0D]"},
    {"\\t","[0x09]"},
    {"\v","[0x0B]"},
    {"\\","[0x5C]"},
    {"\\'","[0x27]"},
    {"\\\"","[0x22]"},
    {"\\\?","[0x3F]"}

All whitespace is ignored.

//————————————IMPLEMENTATION———————————— 






Sample test cases:

./tokenizer "What a beautiful day"

./tokenizer " \t indent a little \t \f"

./tokenizer "0x1234 007 3.14 1010"

./tokenizer "a+b=c; j ++"