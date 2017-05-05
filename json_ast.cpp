/**
 * Created by theppsh on 17-5-5.
 */

#include "json_ast.hpp"
json_ast::pNode json_ast::AllocNode(const ASTType type) {
return std::make_shared<ASTNode>(type);
}

json_ast::pNode json_ast::CreateString(const char *str, const int leng) {

    auto result = AllocNode(ASTType::AT_STRING);
    result->string_val.resize(leng);
    std::memcpy(const_cast<char*>(result->string_val.data()),str,leng);
    return result;

}

int json_ast::ASTNode::deep =0;