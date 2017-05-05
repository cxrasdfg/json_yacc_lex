/**
 * Created by theppsh on 17-5-3.
 */

#include "json.hpp"
int main(){

    ParseString("{\n"
                        "  \"asd\" :  2123,\"asd\\\\23\\\"\":[123,1231,\"abcdefg\"],\"1232\":12.3}");
    return 0;
}