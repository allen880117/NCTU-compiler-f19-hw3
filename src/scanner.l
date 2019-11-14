%{
#include <stdint.h>

#include "error.h"

#define LIST                strCat(yytext)
#define TOKEN(t)            {LIST; if (OptTok) printf("<%s>\n", #t);}
#define TOKEN_CHAR(t)       {LIST; if (OptTok) printf("<%c>\n", (t));}
#define TOKEN_STRING(t, s)  {LIST; if (OptTok) printf("<%s: %s>\n", #t, (s));}
#define MAX_LINE_LENG       512

int32_t LineNum = 1;
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
"," { TOKEN_CHAR(','); }
";" { TOKEN_CHAR(';'); }
":" { TOKEN_CHAR(':'); }
"(" { TOKEN_CHAR('('); }
")" { TOKEN_CHAR(')'); }
"[" { TOKEN_CHAR('['); }
"]" { TOKEN_CHAR(']'); }

    /* Operator */
"+"   { TOKEN_CHAR('+'); }
"-"   { TOKEN_CHAR('-'); }
"*"   { TOKEN_CHAR('*'); }
"/"   { TOKEN_CHAR('/'); }
"mod" { TOKEN(mod); }
":="  { TOKEN(:=); }
"<"   { TOKEN_CHAR('<'); }
"<="  { TOKEN(<=); }
"<>"  { TOKEN(<>); }
">="  { TOKEN(>=); }
">"   { TOKEN_CHAR('>'); }
"="   { TOKEN_CHAR('='); }
"and" { TOKEN(and); }
"or"  { TOKEN(or); }
"not" { TOKEN(not); }

    /* Keyword */
"array"   { TOKEN(KWarray); }
"begin"   { TOKEN(KWbegin); }
"boolean" { TOKEN(KWboolean); }
"def"     { TOKEN(KWdef); }
"do"      { TOKEN(KWdo); }
"else"    { TOKEN(KWelse); }
"end"     { TOKEN(KWend); }
"false"   { TOKEN(KWfalse); }
"for"     { TOKEN(KWfor); }
"integer" { TOKEN(KWinteger); }
"if"      { TOKEN(KWif); }
"of"      { TOKEN(KWof); }
"print"   { TOKEN(KWprint); }
"read"    { TOKEN(KWread); }
"real"    { TOKEN(KWreal); }
"string"  { TOKEN(KWstring); }
"then"    { TOKEN(KWthen); }
"to"      { TOKEN(KWto); }
"true"    { TOKEN(KWtrue); }
"return"  { TOKEN(KWreturn); }
"var"     { TOKEN(KWvar); }
"while"   { TOKEN(KWwhile); }

    /* Identifier */
[a-zA-Z][a-zA-Z0-9]* { TOKEN_STRING(id, yytext); }

    /* Integer (decimal/octal) */
{integer} { TOKEN_STRING(integer, yytext); }
0[0-7]+   { TOKEN_STRING(oct_integer, yytext); }

    /* Floating-Point */
{float} { TOKEN_STRING(float, yytext); }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
({integer}|{float})[Ee][+-]?({integer}) { TOKEN_STRING(scientific, yytext); }

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
