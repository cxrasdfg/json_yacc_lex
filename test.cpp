/**
 * Created by theppsh on 17-5-3.
 */

#include "json.hpp"

int main(){

    try {

        auto x = json::ParseFile("../target.json");
        auto y = json::ParseString("[123,321]");


        x->ShowTree();
        std::cout<<std::endl;
        y->ShowTree();
        std::cout<<std::endl;
        {
            json::JsonObject test(json::JsonObjectType ::AT_DICT);

            std::string s1;

            test.DictInsert("123",json::PJson(23132));

            std::cout<<test.JsonToString()<<std::endl;

            auto result =(test.DictGet("123"));
            std::cout<<result->Int()<<std::endl;
        }

        {
            auto array_test=json::CreateJsonObject(json::JsonObjectType::AT_ARRAY);
            auto dict_test=json::CreateJsonObject(json::JsonObjectType::AT_DICT);

            array_test->ArrayInsert(json::PJson(123)).ArrayInsert(json::PJson("abdc"));

            dict_test->DictInsert("123",json::PJson("321231")).DictInsert("sdads",json::PJson(123.2));

            array_test->ArrayInsert(dict_test);

            std::cout<<array_test->JsonToString()<<std::endl;
        }

        {
            auto array_test=json::CreateJsonObject(json::JsonObjectType::AT_ARRAY);
            auto dict_test=json::CreateJsonObject(json::JsonObjectType::AT_DICT);

            array_test->ArrayInsert(json::PJson(123)).ArrayInsert(json::PJson("abdc"));

            dict_test->DictInsert("123",json::PJson("321231")).DictInsert("sdads",json::PJson(123.2));

            dict_test->DictInsert("array_test\n",array_test);

            auto str1=dict_test->JsonToString();
            std::cout<<str1<<std::endl;

            auto test2= json::ParseString(str1);

            auto keys= test2->DictKeys();

            std::cout<<keys[0]<<std::endl;
            std::cout<<123<<std::endl;
        }
    }catch (json::JsonException &exception){
        std::cerr<<exception.what()<<std::endl;
    }
    return 0;
}