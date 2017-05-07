/**
 * Created by theppsh on 17-5-7.
 */
#include "json.hpp"

json_ast::pNode json_ast::AllocNode(const ASTType type) {
    return std::make_shared<json::JsonObject>(type);
}

json_ast::pNode json_ast::CreateString(const char *str, const int leng) {

    auto result = AllocNode(ASTType::AT_STRING);
    result->string_val.resize(leng);
    std::memcpy(const_cast<char*>(result->string_val.data()),str,leng);
    return result;

}

json_ast::pNode json_ast::CreateInt(const char *str, const int leng) {

    auto result = AllocNode(ASTType::AT_INT);
    std::sscanf(str,"%d",&result->int_val);
    return result;
}

json_ast::pNode json_ast::CreateDouble(const char *str, const int leng) {
    auto result = AllocNode(ASTType::AT_DOUBLE);
    std::sscanf(str,"%lf",&result->double_val);
    return result;
}

/**
 * convert '\b' '\f' '\n' '\r' '\t' '\\' '\"'
 * @param raw_string
 * @return
 */
std::string json_ast::RawToString(const std::string &raw_string) {

    auto clip_str= raw_string.substr(1,raw_string.size()-2);
    std::string result;
    for(unsigned long i=0;i<clip_str.size();i++){
        auto ch = clip_str[i];
        if(ch=='\\'){
            if(i==clip_str.size()-1){
                throw json::JsonException("json parser error: '\\'' should be followed as the '\\r' '\\f' '\\n' '\\r' '\\t' '\\\\' '\\\"' ");
            }else{
                i++;
                auto next_ch = clip_str[i];
                switch (next_ch){
                    case 'b':
                    {
                        result.push_back('\b');
                    }
                        break;
                    case 'f':
                    {
                        result.push_back('\f');
                    }
                        break;
                    case 'n':
                    {
                        result.push_back('\n');
                    }
                        break;
                    case 'r':
                    {
                        result.push_back('\r');
                    }
                        break;
                    case 't':
                    {
                        result.push_back('\t');
                    }
                        break;
                    case '\\':
                    {
                        result.push_back('\\');
                    }
                        break;
                    case '\"':
                    {
                        result.push_back('\"');
                    }
                        break;
                    default:
                        throw json::JsonException("json parser error: '\\'' should be followed as the '\\r' '\\f' '\\n' '\\r' '\\t' '\\\\' '\\\"' ");
                        break;
                }

            }
        }else{
            result.push_back(ch);
        }
    }

    return result;
}

std::string json_ast::StringToRaw(const std::string &string) {
    std::string result;

    result.push_back('\"');

    for(auto ch:string){
        switch (ch){
            case '\b':
            {
                result.push_back('\\');
                result.push_back('b');
            }
                break;
            case '\f':
            {
                result.push_back('\\');
                result.push_back('f');
            }
                break;
            case '\n':
            {
                result.push_back('\\');
                result.push_back('n');
            }
                break;
            case '\r':
            {
                result.push_back('\\');
                result.push_back('r');
            }
                break;
            case '\t':
            {
                result.push_back('\\');
                result.push_back('t');
            }
                break;
            case '\\':
            {
                result.push_back('\\');
                result.push_back('\\');
            }
                break;
            case '\"':
            {
                result.push_back('\\');
                result.push_back('\"');
            }
                break;
            default:
                result.push_back(ch);
                break;
        }
    }

    result.push_back('\"');

    return result;
}

json_ast::ASTNode::~ASTNode() {}
json_ast::ASTNode::ASTNode(ASTType type):type(type) {}
void json_ast::ASTNode::ShowTree() {
    ShowTreeHelp(this);
}

void json_ast::ASTNode::ShowTreeHelp(ASTNode *ptr) {
    std::cout<<json::JsonToString(ptr);
}

json::JsonException::JsonException(const std::string &__arg) : runtime_error(__arg) {

}

void json ::JsonToStringHelp(json_ast::ASTNode *ptr, std::string &result) {
    if(ptr!= nullptr){
        using namespace json_ast;
        auto &dict_children = ptr->dict_children;
        auto &array_children = ptr->array_children;

        switch(ptr->type){
            case json_ast::ASTType ::AT_INT:
            {
                //std::cout<<ptr->int_val;
                result.append(std::to_string(ptr->int_val));
            }
                break;

            case ASTType ::AT_DOUBLE:
            {
                //std::cout<<ptr->double_val;
                result.append(std::to_string(ptr->double_val));
            }
                break;
            case ASTType ::AT_STRING:
            {
                //std::cout<<StringToRaw(ptr->string_val);
                result.append(StringToRaw(ptr->string_val));
            }
                break;
            case ASTType ::AT_DICT:
            {
                //std::cout<<"{"/**<<std::endl*/;
                result.push_back('{');
                int i=0;
                for(auto elem : dict_children){
                    //std::cout<<StringToRaw(elem.first)<<":";
                    result.append(StringToRaw((elem.first)));
                    result.push_back(':');
                    JsonToStringHelp(elem.second.get(),result);
                    if((++i)!=dict_children.size())
                        //std::cout<<","/**<<std::endl*/;
                        result.push_back(',');
                }

                //std::cout<<"}"/**<<std::endl*/;
                result.push_back('}');

            }
                break;
            case ASTType ::AT_ARRAY:
            {
                //std::cout<<"["/**<<std::endl*/;
                result.push_back('[');
                int i=0;
                for(auto elem:array_children){
                    JsonToStringHelp(elem.get(),result);
                    if((++i)!=array_children.size())
                        //std::cout<<","/**<<std::endl*/;
                        result.push_back(',');
                }

                //std::cout<<"]"/**<<std::endl*/;
                result.push_back(']');
            }
                break;
        }
    }
}


std::string json::JsonToString(json_ast::ASTNode *ptr) {
    std::string result;

    JsonToStringHelp(ptr,result);

    return result;
}


std::string json::JsonToString(std::shared_ptr<json_ast::ASTNode> ptr) {
    std::string result;
    JsonToStringHelp(ptr.get(),result);

    return result;
}



json::JsonObject& json::JsonObject::DictInsert(const std::string &name, PJsonObject pJson) {
    if(type != json::JsonObjectType::AT_DICT){
        throw json::JsonException("JsonObject invokes error: only dictionary can invoke DictInsert...");
    }

    dict_children.insert(std::make_pair(name, std::dynamic_pointer_cast<json_ast::ASTNode>(pJson)));

    return *this;
}

json::PJsonObject json::JsonObject::DictGet(const std::string &key)  {
    if(type != json::JsonObjectType::AT_DICT){
        throw json::JsonException("JsonObject invokes error: only dictionary can invoke DictGet...");
    }
    auto result= dict_children.find(key);
    if(result!= dict_children.end()){
        return std::dynamic_pointer_cast<JsonObject>(result->second);
    }
    return nullptr;
}

std::vector<std::string > json::JsonObject::DictKeys() {
    if(type != json::JsonObjectType::AT_DICT){
        throw json::JsonException("JsonObject invokes error: only dictionary can invoke DictKeys...");
    }
    std::vector<std::string > result;

    for(auto elem :dict_children){
        result.push_back(elem.first);
    }

    return result;
}

std::vector<json:: PJsonObject> json::JsonObject::DictValues() {
    if(type != json::JsonObjectType::AT_DICT){
        throw json::JsonException("JsonObject invokes error: only dictionary can invoke DictValues...");
    }
    std::vector<json:: PJsonObject> result;
    for(auto elem :dict_children){
        result.push_back(std::dynamic_pointer_cast<json::JsonObject>(elem.second));
    }
    return result;
}

json::JsonObject& json::JsonObject::ArrayInsert(PJsonObject pJson, int _pos) {
    if(type != json::JsonObjectType::AT_ARRAY){
        throw json::JsonException("JsonObject invokes error: only array can invoke ArrayInsert...");
    }

    if(_pos==-1){
        array_children.push_back(std::dynamic_pointer_cast<json_ast::ASTNode>(pJson));
    }
    else if(_pos>=0){
        array_children.insert(array_children.begin()+_pos,std::dynamic_pointer_cast<json_ast::ASTNode>(pJson));
    }
    return *this;
}

json::PJsonObject json::JsonObject::ArrayGet(int _pos) {
    if(type != json::JsonObjectType::AT_ARRAY){
        throw json::JsonException("JsonObject invokes error: only array can invoke ArrayGet...");
    }

    if(_pos>=0 && _pos< array_children.size()){
        return std::dynamic_pointer_cast<json::JsonObject>(array_children[_pos]);
    }

    return nullptr;
}

int json::JsonObject::Int(){
    if(type != json::JsonObjectType::AT_INT){
        throw json::JsonException("JsonObject type converts error: int...");
    }

    return int_val;
}

double json::JsonObject:: Double(){
    if(type != json::JsonObjectType::AT_DOUBLE){
        throw json::JsonException("JsonObject type converts error: double...");
    }

    return double_val;
}


std::string json::JsonObject::String() {
    if(type != json::JsonObjectType::AT_STRING){
        throw json::JsonException("JsonObject type converts error: string...");
    }

    return string_val;
}


std::string json::JsonObject::JsonToString() {
    return json::JsonToString(this);
}

json::JsonObject::JsonObject(json_ast::ASTType type) : ASTNode(type) {}

json::JsonObject::~JsonObject() {}
json:: PJsonObject json::PJson(const int x) {
    auto result = json_ast::AllocNode(json_ast::ASTType::AT_INT);
    result->int_val=x;
    return std::dynamic_pointer_cast<json::JsonObject>(result);
}

json:: PJsonObject json::PJson(const char *x) {
    auto result = json_ast::AllocNode(json_ast::ASTType::AT_STRING);
    result->string_val=x;
    return std::dynamic_pointer_cast<json::JsonObject>(result);
}

json:: PJsonObject json::PJson(const double x) {
    auto result = json_ast::AllocNode(json_ast::ASTType::AT_DOUBLE);
    result->double_val=x;
    return std::dynamic_pointer_cast<json::JsonObject>(result);
}

json:: PJsonObject json::PJson(const std::string &x) {
    auto result = json_ast::AllocNode(json_ast::ASTType::AT_STRING);
    result->string_val=x;
    return std::dynamic_pointer_cast<json::JsonObject>(result);
}


json::PJsonObject json::CreateJsonObject(const JsonObjectType type) {
    return std::make_shared<JsonObject>(type);
}
