#include "List.hpp"

template <typename T>
List<T>::List()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
List<T>::~List()
{
    Clear();
}

template <typename T>
void List<T>::Append(const T& data) {
    ListNode<T>* newListNode = new ListNode<T>{data, nullptr};
    if (!head) {
        head = tail = newListNode;
    } else {
        tail->next = newListNode;
        tail = newListNode;
    }
    size++;
}

template <typename T>
void List<T>::Remove(const T& data) {
    ListNode<T>* current = head;
    ListNode<T>* previous = nullptr;
    while (current) {
        if (current->data == data) {
            if (current == head) {
                head = current->next;
            } else if (current == tail) {
                tail = previous;
                tail->next = nullptr;
            } else {
                previous->next = current->next;
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

template <typename T>
T List<T>::Get(size_t index) const {
    ListNode<T>* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
size_t List<T>::Size() const {
    return size;
}

template <typename T>
void List<T>::Clear() {
    ListNode<T>* current = head;
    while (current) {
        ListNode<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
size_t List<T>::IndexOf(const T& data) const {
    ListNode<T>* current = head;
    size_t index = 0;
    while (current) {
        if (current->data == data)
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
T List<T>::Pop() {
    if (!head) {
        return T{};
    }
    T data = head->data;
    ListNode<T>* next = head->next;
    delete head;
    head = next;
    size--;
    return data;
}

template <typename T>
T List<T>::Pop(size_t index) {
    if (index == 0) {
        return Pop();
    }
    ListNode<T>* current = head;
    ListNode<T>* previous = nullptr;
    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }
    T data = current->data;
    previous->next = current->next;
    delete current;
    size--;
    return data;
}

template <typename T>
void List<T>::Insert(size_t index, const T& data) {
    if (index == 0) {
        ListNode<T>* newListNode = new ListNode<T>{data, head};
        head = newListNode;
        size++;
        return;
    }
    ListNode<T>* current = head;
    ListNode<T>* previous = nullptr;
    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }
    ListNode<T>* newListNode = new ListNode<T>{data, current};
    previous->next = newListNode;
    size++;
}

template <typename T>
void List<T>::RemoveAt(size_t index) {
    if (index == 0) {
        ListNode<T>* next = head->next;
        delete head;
        head = next;
        size--;
        return;
    }
    ListNode<T>* current = head;
    ListNode<T>* previous = nullptr;
    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    delete current;
    size--;
}

template <typename T>
void List<T>::Sort(int (*compare)(const T&, const T&)) {
    if (size < 2) {
        return;
    }
    ListNode<T>* current = head;
    ListNode<T>* next = head->next;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (compare(current->data, next->data) > 0) {
                T temp = current->data;
                current->data = next->data;
                next->data = temp;
            }
            next = next->next;
        }
        current = current->next;
        next = current->next;
    }
}

template <typename T>
bool List<T>::Contains(const T& data) const {
    ListNode<T>* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool List<T>::ForEach(ListNode<T> **next) {
    if (*next == nullptr) 
        *next = this->head;
    else
        *next = (*next)->next;
    if (*next == nullptr)
        return false;
    return true;
}


template <typename T>
T& List<T>::operator[](size_t index) {
    ListNode<T>* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& List<T>::operator[](size_t index) const {
    ListNode<T>* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
T& List<T>::First() {
    return head->data;
}

template <typename T>
const T& List<T>::First() const {
    return head->data;
}

template <typename T>
T& List<T>::Last() {
    return tail->data;
}

template <typename T>
const T& List<T>::Last() const {
    return tail->data;
}