#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <string>
#include <stdlib.h>
#include "List.hpp"

template <typename T>
struct DictNode
{
    char* key;
    T data;
};

template <typename T>
class Dict
{
private:
    List<DictNode<T>> *data;
public:
    Dict();
    ~Dict();
    void Remove(char* key);
    void Clear();
    T& operator[](char* key);
    const T& operator[](char* key) const;
};

#endif // DICTIONARY_HPP