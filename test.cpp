/**
 * Created by theppsh on 17-5-3.
 */

#include "json.hpp"

int main(){

    json_ast::pNode x= json:: ParseFile("../target.json");
    json_ast::pNode y = json::ParseString("{\n"
                                       "  \"asd\" :  2123,\"asd\\\\23\\\"\":[123,1231,\"abcdefg\"],\"1232\":12.3}");

    x->ShowTree(x);
    y->ShowTree(y);
    return 0;
}