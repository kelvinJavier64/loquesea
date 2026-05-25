#include "ASTNode.h"

ASTNode::ASTNode(const std::string &type, const std::string &value) {
        this->type = type; //this->type es igual al tipo lo guarda en el objeto
        this->value = value;
};

void ASTNode::addChild(ASTNode *child) {
        children.push_back(child);
}

void ASTNode::print(int posicion) const {
        for (int i = 0; i < posicion; i++) { //repite espacios
                std::cout << " ";
        }

        std::cout << type; //el tipo
        if (!value.empty()) { //si value no esta vacio pues
                std::cout // pone : y agrega el value
                << " : "
                << value;
        }
        std::cout << std::endl;

        for (ASTNode* child : children) { //se termina y recorro todos los hijos
                child->print(posicion + 4); //se llama a si misma y se desplaza a la derecha por nivel
        }
}
