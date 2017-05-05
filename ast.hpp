/**
 * Created by theppsh on 17-5-3.
 */
#pragma once

#include <memory>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <cassert>

namespace ast{

    enum class ASTType{
        AT_INT, //整数
        AT_DOUBLE, //双精度浮点数
        AT_STRING, //字符串
        AT_DICT,  //字典
        AT_ARRAY, // 数组
    };

    class ASTNode{
    private:
        static int deep;

        static void ShowTreeHelp( std::shared_ptr<ASTNode> ptr){
            if(ptr!= nullptr){
                deep++;
                auto &dict_children = ptr->dict_children;
                auto &array_children = ptr->array_children;

                switch(ptr->type){
                    case ASTType ::AT_INT:
                    {
                        PrintDeep();
                        std::cout<<ptr->int_val;
                    }
                        break;

                    case ASTType ::AT_DOUBLE:
                    {
                        PrintDeep();
                        std::cout<<ptr->double_val;
                    }
                        break;
                    case ASTType ::AT_STRING:
                    {
                        PrintDeep();
                        std::cout<<ptr->string_val;
                    }
                        break;
                    case ASTType ::AT_DICT:
                    {
                        PrintDeep();
                        std::cout<<"{"<<std::endl;

                        for(auto elem : dict_children){
                            PrintDeep();
                            std::cout<<elem.first<<":";
                            ShowTreeHelp(elem.second);
                            std::cout<<","<<std::endl;
                        }

                        PrintDeep();
                        std::cout<<"}"<<std::endl;

                    }
                        break;
                    case ASTType ::AT_ARRAY:
                    {
                        PrintDeep();
                        std::cout<<"["<<std::endl;

                        for(auto elem:array_children){
                            PrintDeep();
                            ShowTreeHelp(elem);
                            std::cout<<","<<std::endl;
                        }

                        PrintDeep();
                        std::cout<<"]"<<std::endl;
                    }
                        break;
                }

                deep--;
            }
        }

        static void PrintDeep(){
            for(int i=1;i<deep;i++)
                std::cout<<" ";

        }
    public:
        ASTNode(){

        }
        virtual ~ASTNode(){

        }

        ASTType  type;
        ASTNode(ASTType type):type(type){}
        int int_val;
        double double_val;
        std::string string_val;
        std::vector<std::shared_ptr<ASTNode>> array_children;
        std::unordered_map<std::string,std::shared_ptr<ASTNode>> dict_children;

        static void ShowTree(std::shared_ptr<ASTNode> ptr){

            ShowTreeHelp(ptr);
            deep=0;
        }

    };

    using pNode =std::shared_ptr<ASTNode>;


    pNode AllocNode(const ASTType type);

    pNode CreateString(const char *str,const int leng) ;


}