#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
public:
    T elem;   // Dato del Nodo
    BSNode<T>* left;   // Puntero al hijo izquierdo
    BSNode<T>* right;   // Puntero al hijo derecho
    
    // Constructor
    BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr)
        : elem(elem), left(left), right(right) {}   // Recibe el dato del nodo e hijos

    friend std::ostream& operator<<(std::ostream& out, const BSNode<T>& bsn) {
        out << bsn.elem;
        return out;
    }
};

#endif

