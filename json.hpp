/**
 * Created by theppsh on 17-5-5.
 */
#pragma once

#include <memory>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <cassert>

namespace json{
    enum class JsonObjectType{
        AT_INT=1, //整数
        AT_DOUBLE=2, //双精度浮点数
        AT_STRING=3, //字符串
        AT_DICT=4,  //字典
        AT_ARRAY=5, // 数组
    };
}

namespace json_ast{

    /**将raw string 转义*/
    std::string RawToString(const std::string &raw_string);

    /**将string转为raw string*/
    std::string StringToRaw(const std::string &string);

    using ASTType= json::JsonObjectType ;

    class ASTNode{
    private:
        void ShowTreeHelp( ASTNode* ptr);
    public:
        virtual ~ASTNode();

        ASTType  type;
        ASTNode(ASTType type);
        int int_val;
        double double_val;
        std::string string_val;
        std::vector<std::shared_ptr<ASTNode>> array_children;
        std::unordered_map<std::string,std::shared_ptr<ASTNode>> dict_children;

        void ShowTree();

    };

    using pNode =std::shared_ptr<ASTNode>;

    pNode CreateString(const char *str,const int leng) ;
    pNode CreateInt(const char * str,const int leng);
    pNode CreateDouble(const char *str,const int leng);

    pNode AllocNode(const ASTType type);

}

namespace json{
    class JsonException:public std::runtime_error{
    public:
        JsonException(const std::string &__arg);
    };



    class JsonObject;
    using PJsonObject= std::shared_ptr<JsonObject> ;
    class JsonObject: public json_ast::ASTNode{
    protected:
    public:
        JsonObject(json_ast::ASTType type);


        virtual ~JsonObject();

        JsonObject& DictInsert(const std::string & name,PJsonObject pJson);


        std::vector<std::string > DictKeys();

        std::vector<PJsonObject> DictValues();

        PJsonObject DictGet(const std::string &key);

        JsonObject& ArrayInsert(PJsonObject,int _pos=-1);

        PJsonObject ArrayGet(int _pos);


        int Int();
        double Double();
        std::string String();

        std::string JsonToString();
    };

    PJsonObject PJson(const int);
    PJsonObject PJson(const double);
    PJsonObject PJson(const std::string &);
    PJsonObject PJson(const char*);

    std::string JsonToString(json_ast::ASTNode * ptr);
    std::string JsonToString(std::shared_ptr<json_ast::ASTNode> ptr);
    static void JsonToStringHelp(json_ast:: ASTNode*ptr,std::string & result);

    PJsonObject CreateJsonObject(const JsonObjectType type);
}

namespace json{
    auto ParseFile(const std::string &file_path)->PJsonObject;
    auto ParseString(const std::string &str) -> PJsonObject ;
}
