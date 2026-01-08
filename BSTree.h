#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) throw std::runtime_error("search: element not found");
        if (e < n->elem) return search(n->left, e);
        if (n->elem < e) return search(n->right, e);
        return n;
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e < n->elem) n->left = insert(n->left, e);
        else if (n->elem < e) n->right = insert(n->right, e);
        else throw std::runtime_error("insert: element already exists");
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (!n) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) throw std::runtime_error("max: empty subtree");
        if (n->right == nullptr) return n->elem;
        return max(n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) throw std::runtime_error("remove: element not found");

        if (e < n->elem) {
            n->left = remove(n->left, e);
            return n;
        }
        if (n->elem < e) {
            n->right = remove(n->right, e);
            return n;
        }

        // encontrado
        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            nelem--;
            return nullptr;
        }
        if (n->left == nullptr) {
            BSNode<T>* r = n->right;
            delete n;
            nelem--;
            return r;
        }
        if (n->right == nullptr) {
            BSNode<T>* l = n->left;
            delete n;
            nelem--;
            return l;
        }

        // dos hijos: reemplazo por máximo del subárbol izquierdo
        T pred = max(n->left);
        n->elem = pred;
        n->left = remove(n->left, pred);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
        root = nullptr;
        nelem = 0;
    }

    int size() const { return nelem; }

    T search(T e) const { return search(root, e)->elem; }

    T operator[](T e) const { return search(e); }

    void insert(T e) { root = insert(root, e); }

    void remove(T e) { root = remove(root, e); }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

