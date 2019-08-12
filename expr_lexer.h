#include <iostream>
enum class Token{
    Num,
    Error,
    opAdd,
    opSub,
    opDiv,
    opMul,
    Eof
}


class ExprLexer
{
private:
    enum class fillstatus{
        Error,
        Eof,
        Ok
    }
    struct Context
    {
        char* lim;
        char* curr;
        char* tok;
        char* buf;
        Bool Eof;
        std::istream& in;
        Token makeToken(Token tk){
            text = ctx.tokenText();
            return tk;
        }
        std::string tokenText()
        {
            return std::string(tok,curr - tok);
        }
        fillstatus fill(size_t need);
        Context(std::istream& in);
        ~Context(){
            delete [] buf;
        }
    };
    
public:
    ExprLexer(std::istream& in):in(in),lineno(1){}
    Token getNextToken();
    std::string getText(){return text;}
    int getLineNo(){return lineno;}
    ~ExprLexer();
    std::string text;
    int lineno;
    Context ctx;
};