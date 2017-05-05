/**
 * Created by theppsh on 17-5-3.
 */
#pragma once

#include<memory>
#include <vector>
#include <unordered_map>

namespace ast{

    enum class ASTType{
        AT_INT, //整数
        AT_DOUBLE, //双精度浮点数
        AT_STRING, //字符串
        AT_DICT,  //字典
        AT_ARRAY, // 数组
    };

    struct ASTNode{
        ASTType  type;
        ASTNode(ASTType type):type(type){}
        int int_val;
        double double_val;
        std::string string_val;
        std::vector<std::shared_ptr<ASTNode>> array_children;
        std::unordered_map<std::string,std::shared_ptr<ASTNode>> dict_children;

    };

    auto AllocNode(const ASTType type){
        return std::make_shared<ASTNode>(type);
    }

    using pNode =std::shared_ptr<ASTNode>;
}