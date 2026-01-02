#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <stdexcept>
#include <ostream>

#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h"

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
// Constructor
template <typename V>
HashTable<V>::HashTable(int size)
    : n(0), max(size)   // Inicializa n = 0 y max = size
{
    if (size <= 0)   // Si size inválido, excepción
        throw std::runtime_error("Tamaño de tabla no válido");

    table = new ListLinked<TableEntry<V>>[max];   // Crea un array de max listas enlazadas vacías
}   // Cada cubeta comienza vacía

// Destructor
template <typename V>
HashTable<V>::~HashTable() {
    delete[] table;
}

// nº de cubetas
template <typename V>
int HashTable<V>::capacity() {
    return max;
}

// nº de elementos guardados
template <typename V>
int HashTable<V>::entries() {
    return n;
}

template <typename V>
int HashTable<V>::h(std::string key) {
    int suma = 0;
    for (char c : key)
        suma += static_cast<int>(c);   // Suma ASCII de los caracteres

    return suma % max;   // Max para caer en rango
}

template <typename V>
void HashTable<V>::insert(std::string key, V value) {
    int idx = h(key);   // Calcula cubeta idx
    TableEntry<V> nuevo(key, value);   // Crea entrada (key, value)

    int pos = table[idx].search(nuevo); // Busca si ya existe en esa cubeta

    if (pos != -1)   
        throw std::runtime_error("insert: clave ya existente");   // Si existe, excepción

    table[idx].prepend(nuevo); // Inserta al principio de la lista
    n++;   // Incrementa contador global
}

template <typename V>
V HashTable<V>::search(std::string key) {
    int idx = h(key);   // Calcula cubeta
    TableEntry<V> buscado(key);   // Crea TableEntry(key) "solo con clave"

    int pos = table[idx].search(buscado);   // Busca en la lista

    if (pos == -1)
        throw std::runtime_error("search: clave no encontrada");   // Si no está, excepción

    return table[idx].get(pos).value;   // Si está, devuelve el .value de esa entrada
}

template <typename V>
V HashTable<V>::remove(std::string key) {
    int idx = h(key);   // Calcula cubeta
    TableEntry<V> buscado(key);

    int pos = table[idx].search(buscado);   // Busca posición
    if (pos == -1)
        throw std::runtime_error("remove: clave no encontrada");   // Si no existe, excepción

    TableEntry<V> eliminado = table[idx].remove(pos);   // Borra la posición y recupera el TableEntry eliminado
    n--;   // Decrementa n
    return eliminado.value;   // Devuelve el valor eliminado
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

