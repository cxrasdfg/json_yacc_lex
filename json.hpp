/**
 * Created by theppsh on 17-5-5.
 */
#pragma once

#include "json_ast.hpp"
namespace json{
    auto ParseFile(const std::string &file_path)->json_ast::pNode ;
    auto ParseString(const std::string &str) -> json_ast::pNode;
}
