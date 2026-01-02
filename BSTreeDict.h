#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <string>
#include <ostream>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;   // tree es un puntero a un árbol

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();   // Crea el árbol vacío en memoria dinámica y apunta tree a un BST válido
    }
    
    // Destructor
    ~BSTreeDict() {
        delete tree;
    }

    int entries() override {
        return tree->size();   // Devuelve el número de elementos del diccionario
    }

    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));   // Construye un TableEntry(key, value) y lo inserta en el BST
    }

    V search(std::string key) override {
        return tree->search(TableEntry<V>(key)).value;   // Buscar y devuelve el .value
    }

    V operator[](std::string key) {
        return search(key);
    }

    V remove(std::string key) override {
        V removed_value = search(key);   // Busca y guarda el valor
        tree->remove(TableEntry<V>(key));   // Borra la entrada del BST
        return removed_value;   // Devuelve el valor eliminado
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& d) {
        out << *(d.tree);
        return out;
    }
};

#endif


