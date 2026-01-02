#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;   // Lo que devuelve size(), contador de elementos
    BSNode<T>* root;   // Puntero a la raíz del árbol

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) throw std::runtime_error("search: element not found");   // Si llegas a nullptr, no está
        if (e < n->elem) return search(n->left, e);   // Si e < elem, vas a la izquierda
        if (n->elem < e) return search(n->right, e);   // Si e > elem, vas a la derecha
        return n;   // Si es igual, devuelve el nodo
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {   // Si cae en nullptr, sitio libre
            nelem++;   // Incrementa nelem
            return new BSNode<T>(e);   // Crea nodo
        }
        if (e < n->elem) n->left = insert(n->left, e);   // Si e es menor, inserta en subárbol izquierdo
        else if (n->elem < e) n->right = insert(n->right, e);   // Si e es mayor, inserta en subárbol derecho
        else throw std::runtime_error("insert: element already exists");   // Si es igual, excepción (ya existe)
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {   // Inorden (izq, nodo, der)
        if (!n) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) throw std::runtime_error("max: empty subtree");   // Si el subárbol está vacío, error
ed_value = search(key);
        tree->remove(TableEntry<V>(key));
        return removed_value;
    }
        if (n->right == nullptr) return n->elem;   // El máximo en BST está en el más a la derecha
        return max(n->right);
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n == nullptr) throw std::runtime_error("remove_max: empty subtree");
        if (n->right == nullptr) {   // Si no tiene nodo derecho, este nodo es el máximo
            BSNode<T>* left = n->left;
            delete n;   // Borra el nodo máximo
            nelem--;   // Actualiza nelem
            return left;
        }
        n->right = remove_max(n->right);   // El hijo izquierdo del máximo sube y así queda el BST bien enlazado
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        // Si no está, excepción
        if (n == nullptr) throw std::runtime_error("remove: element not found");
        
        // Baja por el árbol hasta encontrarlo
        if (e < n->elem) {
            n->left = remove(n->left, e);
            return n;
        }
        if (n->elem < e) {
            n->right = remove(n->right, e);
            return n;
        }

        // Caso: hoja
        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            nelem--;
            return nullptr;
        }

        // Caso: solo hijo derecho
        if (n->left == nullptr) {
            BSNode<T>* r = n->right;
            delete n;
            nelem--;
            return r;
        }

        // Caso: solo hijo izquierdo
        if (n->right == nullptr) {
            BSNode<T>* l = n->left;
            delete n;
            nelem--;
            return l;
        }

        // Caso: Dos hijos: reemplazo por máximo del subárbol izquierdo
        T pred = max(n->left);   // Elige el predecesor (máximo del subárbol izquierdo)
        n->elem = pred;   // Copia su valor al nodo actual
        n->left = remove(n->left, pred);   // Borra el predecesor en el subárbol izquierdo
        return n;
    }

    // Destructor - Borra todo el árbol (Postorder: borra hijos antes que el padre)
    void delete_cascade(BSNode<T>* n) {
        if (!n) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:

    // Árbol vacío
    BSTree() : nelem(0), root(nullptr) {}

    // Destructor
    ~BSTree() {
        delete_cascade(root);
        root = nullptr;
        nelem = 0;
    }

    // Devuelve el nº de elementos
    int size() const { return nelem; }

    T search(T e) const {
        return search(root, e)->elem;
    }

    T operator[](T e) const { return search(e); }

    void insert(T e) { root = insert(root, e); }

    void remove(T e) { root = remove(root, e); }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

