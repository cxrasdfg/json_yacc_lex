/**
 * Created by theppsh on 17-5-5.
 */
#pragma once

#include "ast.hpp"

auto ParseFile(const std::string &file_path)->ast::pNode ;
auto ParseString(const std::string &str) -> ast::pNode;