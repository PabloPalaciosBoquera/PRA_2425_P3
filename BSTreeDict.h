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
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    int entries() const override {
        return tree->size();
    }

    void insert(std::string key, V value) override {
        tree->insert(TableEntry<V>(key, value));
    }

    V search(std::string key) const override {
        return tree->search(TableEntry<V>(key)).value;
    }

    V operator[](std::string key) const override {
        return search(key);
    }

    void remove(std::string key) override {
        tree->remove(TableEntry<V>(key));
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& d) {
        out << *(d.tree);
        return out;
    }
};

#endif

