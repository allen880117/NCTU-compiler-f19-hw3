%{
#include <stdint.h>

#include "include/core/error.h"
#include "parser.h"

#define YY_USER_ACTION                                                         \
  yylloc.first_line = LineNum;                                                \
  yylloc.first_column = ColNum;                                               \
  ColNum += yyleng;

#define LIST                strCat(yytext)
#define TOKEN(t)            {LIST; if (OptTok) printf("<%s>\n", #t);}
#define TOKEN_CHAR(t)       {LIST; if (OptTok) printf("<%c>\n", (t));}
#define TOKEN_STRING(t, s)  {LIST; if (OptTok) printf("<%s: %s>\n", #t, (s));}
#define MAX_LINE_LENG       512

uint32_t LineNum = 1;
uint32_t ColNum = 1;
char Buffer[MAX_LINE_LENG];

static int32_t OptSrc = 1;
static int32_t OptTok = 1;
static char StringLiteral[MAX_LINE_LENG];
static char *BufferPtr = Buffer;

static void strCat(const char *Text);

%}

integer 0|[1-9][0-9]*
float {integer}\.(0|[0-9]*[1-9])

%x CCOMMENT

%%
    /* Delimiter */
"," { TOKEN_CHAR(','); return COMMA; }
";" { TOKEN_CHAR(';'); return SEMICOLON; }
":" { TOKEN_CHAR(':'); return COLON; }
"(" { TOKEN_CHAR('('); return L_PARENTHESIS; }
")" { TOKEN_CHAR(')'); return R_PARENTHESIS; }
"[" { TOKEN_CHAR('['); return L_BRACKET; }
"]" { TOKEN_CHAR(']'); return R_BRACKET; }

    /* Operator */
"+"   { TOKEN_CHAR('+'); return PLUS; }
"-"   { TOKEN_CHAR('-'); return MINUS; }
"*"   { TOKEN_CHAR('*'); return MULTIPLY; }
"/"   { TOKEN_CHAR('/'); return DIVIDE; }
"mod" { TOKEN(mod);      return MOD; }
":="  { TOKEN(:=);       return ASSIGN; }
"<"   { TOKEN_CHAR('<'); return LESS; }
"<="  { TOKEN(<=);       return LESS_OR_EQUAL; }
"<>"  { TOKEN(<>);       return NOT_EQUAL; }
">="  { TOKEN(>=);       return GREATER_OR_EQUAL; }
">"   { TOKEN_CHAR('>'); return GREATER; }
"="   { TOKEN_CHAR('='); return EQUAL; }
"and" { TOKEN(and);      return AND; }
"or"  { TOKEN(or);       return OR; }
"not" { TOKEN(not);      return NOT; }

    /* Keyword */
"array"   { TOKEN(KWarray);   return ARRAY; }
"begin"   { TOKEN(KWbegin);   return BEGIN_; }
"boolean" { TOKEN(KWboolean); return BOOLEAN; }
"def"     { TOKEN(KWdef);     return DEF; }
"do"      { TOKEN(KWdo);      return DO; }
"else"    { TOKEN(KWelse);    return ELSE; }
"end"     { TOKEN(KWend);     return END; }
"false"   { TOKEN(KWfalse);   return FALSE; }
"for"     { TOKEN(KWfor);     return FOR; }
"integer" { TOKEN(KWinteger); return INTEGER; }
"if"      { TOKEN(KWif);      return IF; }
"of"      { TOKEN(KWof);      return OF; }
"print"   { TOKEN(KWprint);   return PRINT; }
"read"    { TOKEN(KWread);    return READ; }
"real"    { TOKEN(KWreal);    return REAL; }
"string"  { TOKEN(KWstring);  return STRING; }
"then"    { TOKEN(KWthen);    return THEN; }
"to"      { TOKEN(KWto);      return TO; }
"true"    { TOKEN(KWtrue);    return TRUE; }
"return"  { TOKEN(KWreturn);  return RETURN; }
"var"     { TOKEN(KWvar);     return VAR; }
"while"   { TOKEN(KWwhile);   return WHILE; }

    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { TOKEN_STRING(id, yytext); return ID; }

    /* Integer (decimal/octal) */
{integer} { TOKEN_STRING(integer, yytext);     return INT_LITERAL; }
0[0-7]+   { TOKEN_STRING(oct_integer, yytext); return INT_LITERAL; }

    /* Floating-Point */
{float} { TOKEN_STRING(float, yytext); return REAL_LITERAL; }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({integer}|{float})[Ee][+-]?({integer}) {
    TOKEN_STRING(scientific, yytext);
    return REAL_LITERAL;
}

    /* String */
\"([^"\n]|\"\")*\" {
    char *YytextPtr = yytext;
    char *StrPtr = StringLiteral;

    /* Condition guard of the end of string literal
       Check only when *YytextPtr == '"' */
    while (*(YytextPtr + 1) != '\0') {
        ++YytextPtr;

        /* Handle the situation of double quotes */
        if (*YytextPtr == '"' && *(YytextPtr + 1) != '\0')
            *StrPtr++ = *YytextPtr++;

        while (*YytextPtr != '"')
            *StrPtr++ = *YytextPtr++;
    }
    *StrPtr = '\0';
    TOKEN_STRING(string, StringLiteral);
    return STRING_LITERAL;
}
    /* Whitespace */
[ \t]+ { LIST; }

    /* Pseudocomment */
"//&"[ST][+-].* {
    LIST;
    char option = yytext[3];
    switch (option) {
    case 'S':
        OptSrc = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        OptTok = (yytext[4] == '+') ? 1 : 0;
        break;
    }
}

    /* C++ Style Comment */
"//".* { LIST; }

    /* C Style Comment */
"/*"           { LIST; BEGIN(CCOMMENT); }
<CCOMMENT>"*/" { LIST; BEGIN(INITIAL); }
<CCOMMENT>.    { LIST; }

    /* Newline */
<INITIAL,CCOMMENT>\n {
    if (OptSrc)
        printf("%d: %s\n", LineNum, Buffer);
    ++LineNum;
    ColNum = 1;
    Buffer[0] = '\0';
    BufferPtr = Buffer;
}

    /* Catch the character which is not accepted by rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", LineNum, yytext);
    exit(-1);
}

%%

static void strCat(const char *Text) {
    while (*Text) {
        *BufferPtr++ = *Text++;
    }
    *BufferPtr = '\0';
}
