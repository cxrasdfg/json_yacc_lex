/**
 * Created by theppsh on 17-5-1.
 */
#pragma once
namespace token{
    enum class TokenType{
        TT_LEFT_BRACE,
        TT_RIGHT_BRACE,
        TT_LEFT_BRACKET,
        TT_RIGHT_BRACKET,
        TT_COMMA,
        TT_COLON,
        TT_INT,
        TT_DOUBLE,
        TT_STRING
    };
}