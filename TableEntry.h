#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>   // V es el tipo de valor
class TableEntry {
public:
    // Atributos públicos
    std::string key;  // Clave
    V value;          // Valor

    // Constructores
    TableEntry(std::string key, V value)    // Método constructor
        : key(key), value(value) {}

    TableEntry(std::string key)   // Crea una entrada solo con clave
        : key(key), value() {}

    TableEntry()    // Entrada con la clave ""
        : key(""), value() {}

    friend bool operator==(const TableEntry<V> &a, const TableEntry<V> &b) {    // Sobrecarga global del operador ==
        return a.key == b.key;
    }

    friend bool operator!=(const TableEntry<V> &a, const TableEntry<V> &b) {    // Sobrecarga global !=
        return !(a == b);
    }

    friend std::ostream& operator<<(std::ostream &out,    // Sobrecarga global del operador << 
                                    const TableEntry<V> &e) {
        out << "('" << e.key << "' => " << e.value << ")";
        return out;
    }
};

#endif

