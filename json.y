%{
#include "ast.hpp"
using namespace ast;

#define YYSTYPE pNode
#include <iostream>
#include <memory>
#include "lex.yy.cpp"


pNode current_node= nullptr;

 %}
 %token TT_LEFT_BRACE TT_RIGHT_BRACE TT_LEFT_BRACKET TT_RIGHT_BRACKET
        TT_COMMA TT_COLON TT_INT TT_DOUBLE TT_STRING TT_ERROR

 %%

 json_object: json_array{
   printf("json_object1\n");
   $$=$1;
 }| json_dict{
   printf("json_object2\n");
   $$=$1;
 };

 json_array: TT_LEFT_BRACKET json_array_elem TT_RIGHT_BRACKET{
     $$ = $2;
     printf("json_array1\n");
 }| TT_LEFT_BRACKET TT_RIGHT_BRACKET{
     printf("json_array2\n");
     $$ = AllocNode(ASTType::AT_ARRAY);
 };

 json_array_elem:  json_array_object{
    printf("json_array_elem1\n");
    $$=AllocNode(ASTType::AT_ARRAY);
    $$->array_children.insert($$->array_children.begin(),$1);
 } | json_array_object TT_COMMA json_array_elem{
    printf("json_array_elem2\n");
    $$=$3;
    $$->array_children.insert($$->array_children.begin(),$1);
 };
 json_array_object:TT_STRING {
     printf("TT_STRING1:%s\n",$1->string_val.data());
     $$=$1;
  }| TT_DOUBLE{
     printf("TT_DOUBLE2:%s\n",$1->string_val.data());
     $$=$1;
  } | TT_INT{
     printf("TT_INT3:%s\n",$1->string_val.data());
     $$=$1;
  } | json_object{
     printf("json_array_object4\n");
     $$=$1;
  };


json_dict: TT_LEFT_BRACE json_dict_elem TT_RIGHT_BRACE
  {
    printf("json_dict1\n");
    $$=$2;
  }
  |TT_LEFT_BRACE TT_RIGHT_BRACE{
    printf("json_dict2\n");
    $$=AllocNode(ASTType::AT_DICT);
  };

json_dict_elem: json_dict_object{
  printf("json_dict_elem1\n");
  $$=AllocNode(ASTType::AT_DICT);
  $$->dict_children.insert(std::make_pair($1->string_val,$1->array_children[0]));
} | json_dict_object TT_COMMA json_dict_elem {
  printf("json_dict_elem2\n");
  $$=$3;
  $$->dict_children.insert(std::make_pair($1->string_val,$1->array_children[0]));

};
json_dict_object:TT_STRING TT_COLON json_array_object{
   printf("json_dict_object:%s\n",$1->string_val.data());
   $$=AllocNode(ASTType::AT_INT);
   $$->string_val = $1->string_val;
   $$->array_children.push_back($3);
};

%%

int main(){
 extern char * yytext;
 extern int yyparse(void);
 extern FILE * yyin;
 yyin= fopen("../target.json","r+");
 yyparse();

 return 0;
}

int yyerror(char *msg){
   extern int lineNumber;
   extern int colNumber;
   fprintf(stderr,"Error: %s 行号:%d 列号:%d\n",msg,lineNumber,colNumber);
}