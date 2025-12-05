#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <stdexcept>
#include <ostream>

#include "Dict.h"
#include "TableEntry.h"

#include "../../PRA_2425_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;    // Número de elementos almacenados
    int max;  // Número de cubetas
    ListLinked<TableEntry<V>>* table; // Array dinámico de listas

    // Función hash: suma ASCII de los caracteres y módulo
    int h(std::string key);

public:
    // Constructor
    HashTable(int size);

    // Destructor
    ~HashTable();

    // Número de cubetas
    int capacity();

    // Implementación del TAD Dict<V>
    void insert(std::string key, V value) override;
    V search(std::string key) override;
    V remove(std::string key) override;
    int entries() override;

    // Acceso tipo dict["clave"]
    V operator[](std::string key);

    // Mostrar tabla completa por pantalla
    template <typename U>
    friend std::ostream& operator<<(std::ostream &out, const HashTable<U> &t);
};


// Métodos

template <typename V>
HashTable<V>::HashTable(int size)
    : n(0), max(size)
{
    if (size <= 0)
        throw std::runtime_error("Tamaño de tabla no válido");

    table = new ListLinked<TableEntry<V>>[max];
}

template <typename V>
HashTable<V>::~HashTable() {
    delete[] table;
}

template <typename V>
int HashTable<V>::capacity() {
    return max;
}

template <typename V>
int HashTable<V>::entries() {
    return n;
}

template <typename V>
int HashTable<V>::h(std::string key) {
    int suma = 0;
    for (char c : key)
        suma += static_cast<int>(c);

    return suma % max;
}

template <typename V>
void HashTable<V>::insert(std::string key, V value) {
    int idx = h(key);
    TableEntry<V> nuevo(key, value);

    int pos = table[idx].search(nuevo); // -1 si no existe

    if (pos != -1)
        throw std::runtime_error("insert: clave ya existente");

    table[idx].prepend(nuevo); // Inserta al principio
    n++;
}

template <typename V>
V HashTable<V>::search(std::string key) {
    int idx = h(key);
    TableEntry<V> buscado(key);

    int pos = table[idx].search(buscado);

    if (pos == -1)
        throw std::runtime_error("search: clave no encontrada");

    return table[idx].get(pos).value;
}

template <typename V>
V HashTable<V>::remove(std::string key) {
    int idx = h(key);
    TableEntry<V> buscado(key);

    int pos = table[idx].search(buscado);
    if (pos == -1)
        throw std::runtime_error("remove: clave no encontrada");

    TableEntry<V> eliminado = table[idx].remove(pos);
    n--;
    return eliminado.value;
}

template <typename V>
V HashTable<V>::operator[](std::string key) {
    return search(key);
}

template <typename U>
std::ostream& operator<<(std::ostream &out, const HashTable<U> &t) {
    out << "HashTable [entries: " << t.n
        << ", capacity: " << t.max << "]\n\n";

    for (int i = 0; i < t.max; ++i) {
        out << "Cubeta " << i << ": ";
        out << t.table[i]; // requiere operator<< en ListLinked
        out << "\n";
    }

    return out;
}

#endif

