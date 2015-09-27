//————————————DESCRIPTION———————————— 
Equivalent of a Java class that implements a tokenizer. Accepts a string as command line argument which contains one or more tokens. Tokens may be adjacent or separated by whitespace. Tokenizer shall print out token and token type. Escape characters shall produce an error. Valid tokens include:

A word token is an alphabetic character followed by any number of alphanumeric characters.
A decimal integer constant token is a digit (0-9) followed by any number of digits.
An octal integer constant token is a 0 followed by any number of octal digits (i.e. 0-7).
A hexadecimal integer constant token is 0x (or 0X) followed by any number of hexadecimal digits (i.e. 0-9, a-f, A-F).
A floating-point constant token is follows the rules for floating-point constants in Java or C.
C operator tokens are any of the C operators shown below:

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
The tokenizer takes a string as input from the command line. This string is stored in a Tokenizer structure. This structure stores the string, the pointer that is used to traverse the string, variables to store the current character and a valid token extracted from the string.
The FSM is implemented using a switch case ladder, where each type of token is assigned a case (e.g. o for octal). The program flow starts from printToken function which parses the whole string and calls the getNextToken function to fetch a valid token.
In getNextToken function, the variables currentState and prevState store the type of current and previous token respectively. When a case change is observed, the token is obtained by the returnToken function.
The validity of the token is checked by the mcheck variable, and if the token is malformed then the appropriate error message is given.For operators and escape sequences, functions isSymbol, iscombinedSymbol and isEscape are used to see if the symbol or the escape sequence is a valid token. Look-ahead logic is used to fetch the complete symbol or escape sequence.
Finally the tokenizer object is de-allocated using the free function.

Sample test cases:

./tokenizer "What a beautiful day"word "What"word "a"word "beautiful"word "day"

./tokenizer " \t indent a little \t \f"[0x09] "\t"word "indent"word "a"word "little"[0x09] "\t"[0x0C] "\f"

./tokenizer "0x1234 007 3.14 1010"hex constant "0x1234"octal constant "007"float "3.14"integer "1010"

./tokenizer "a+b=c; j ++"word "a"plus "+"word "b"equal to "="word "c"semi-colon ";"word "j"increment "++"