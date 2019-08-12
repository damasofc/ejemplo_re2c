#include <iostream>
#include <sstream>
#include "expr_lexer.h"
#include
/*!max:re2c*/  

Token ExprLexer::getNextToken()
{
    #define YYFILL(n)\
        do\
        {\
            fillstatus x = ctx.fill(n);\
            switch (x)\
            {\
            case fillstatus::Error:\
                return Token::Error;\
            case fillstatus::Eof:\
                return Token::Eof;\
            default:\
                break;\
            }\
        } while (0);
        
    while (true)
    {
        ctx.tok = ctx.curr;
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYLIMIT = ctx.lim;
            re2c:define:YYCURSOR = ctx.curr;
            re2c:define:YYFILL:naked = 0;

            * { return makeToken(Token::Error); }
            [ \t] {continue;}
            "\n" {lineno++; continue;}
            [0-9]+ { return makeToken(Token::Num); }
            "+" { return makeToken(Token::opAdd);}
            "-" { return makeToken(Token::opSub);}
            "*" { return makeToken(Token::opMul);}
            "/" { return makeToken(Token::opDiv);}
            "\x00" {return ctx.eof? Token::Eof: Token::Error;}
         */
    }
    
}

ExprLexer::Context::Context(std::istream& in):in(in)
{
    buf = new char[SIZE + YYMAXFILL];
    lim = buf + size;
    curr = lim;
    tok = lim;
    eof = false;
}

ExprLexer::fillstatus Context::fill(size_t need)
{
    if (Eof)
    {
        return fillstatus::Eof;
    }
    const size_t free = tok - buf;
    if (free < need)
    {
        return fillstatus::Error;
    }
    
    memmove(buf,tok,lim-tok);
    lim -= free;
    curr -= free;
    tok -= free;
    in.read(lim,free);
    lim += in.gcount();

    if (lim < buf + SIZE)
    {
        eof = true;
        memset(lim,0, YYMAXFILL);
        lim += YYMAXFILL;
    }
    return fillstatus::Ok;
    
    
    
    
}
