#include "Dict.hpp"

template <typename T>
Dict<T>::Dict()
{
    data = new List<DictNode<T>>();
}

template <typename T>
Dict<T>::~Dict()
{
    Clear();
    delete data;
}

template <typename T>
void Dict<T>::Remove(char* key)
{
    for (size_t i = 0; i < data->Size(); i++) {
        if (strcmp(data->Get(i).key, key) == 0) {
            data->RemoveAt(i);
            return;
        }
    }
}

template <typename T>
void Dict<T>::Clear()
{
    data->Clear();
}

template <typename T>
T& Dict<T>::operator[](char* key)
{
    for (size_t i = 0; i < data->Size(); i++) {
        if (strcmp(data->Get(i).key, key) == 0) {
            return data->Get(i).data;
        }
    }
    DictNode<T> node;
    node.key = key;
    data->Append(node);
    return data->Get(data->Size() - 1).data;
}

template <typename T>
const T& Dict<T>::operator[](char* key) const
{
    for (size_t i = 0; i < data->Size(); i++) {
        if (strcmp(data->Get(i).key, key) == 0) {
            return data->Get(i).data;
        }
    }
    DictNode<T> node;
    node.key = key;
    data->Append(node);
    return data->Get(data->Size() - 1).data;
}