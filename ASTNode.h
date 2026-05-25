#pragma once
#include <iostream>
#include <vector>

    //----------------------------------ahora el arbol AST que se basa en el parser---------------
    class ASTNode { // se crea la clase AST que se maneja como nodos asi evito cambiar mucho la estructura del parser porque me da rabia
    public:  //publico para que se pueda utilizar en las demas clases
        std::string type; //variable de tipo string donde se guardara el tipo de nodo osea lo que ya tenemos en parser rule, cond and
        std::string value; // copia que guarda el contenido del nodo
        std::vector<ASTNode*> children; // esto es importantisisimo guarda los hijos del nodo para hacer el arbol y la jerarquia

        ASTNode( //un puntero contructor
            const std::string& type,
            const std::string& value = "" //esto es por defecto
        );

        void addChild(ASTNode* child);//simplemente agrega hijos a un nodo

        void print(int posicion = 0) const;//print imprime el arbol
    };