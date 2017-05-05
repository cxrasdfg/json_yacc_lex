/**
 * Created by theppsh on 17-5-5.
 */

#include "ast.hpp"
ast::pNode ast::AllocNode(const ASTType type) {
return std::make_shared<ASTNode>(type);
}

ast::pNode ast::CreateString(const char *str, const int leng) {

    auto result = AllocNode(ASTType::AT_STRING);
    result->string_val.resize(leng);
    std::memcpy(const_cast<char*>(result->string_val.data()),str,leng);
    return result;

}

int ast::ASTNode::deep =0;