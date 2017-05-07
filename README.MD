利用lex&yacc的一个json解析器
====================

测试系统环境:ubuntu 17.04 64位
这个东西主要是用来熟悉lex&yacc的使用

用法:
---
1. cmake-build-release下面有个libjson.a 是生成的静态链接库
2. json解析器实现的头文件为json.hpp,用的时候只需要包含json.hpp即可,

   编译的时候需要连接下库，库可以重新编译生成
3. test.cpp为具体的测试内容
