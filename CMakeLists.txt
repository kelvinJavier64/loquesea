cmake_minimum_required(VERSION 4.1)
project(Interprete)

set(CMAKE_CXX_STANDARD 17)

add_executable(Interprete Lexer.cpp
        Parser.cpp
        Lexer.h
        Parser.h
        main.cpp
        ASTNode.cpp
        ASTNode.h
        Interpreter.cpp
        Interpreter.h
        Environment.cpp
        Environment.h
        loadInitState.cpp
        loadInitState.h
        GetSC.cpp
        GetSC.h)
