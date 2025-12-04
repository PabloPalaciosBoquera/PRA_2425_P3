#ifndef DICT_H
#define DICT_H

#include <string>

template <typename V>   // Clase genérica
class Dict {
public:
    virtual ~Dict() {}    // Destructor virtual

    virtual void insert(std::string key, V value) = 0;    // Inserta el par key->value en el diccionario

    virtual V search(std::string key) = 0;    // Busca el valor correspondiente a key

    virtual V remove(std::string key) = 0;    // Elimina el par key->value si se encuentra en el diccionario

    virtual int entries() = 0;    // Devuelve el número de elementos que tiene el Diccionario. 
};

#endif

