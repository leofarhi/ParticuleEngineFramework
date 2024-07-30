#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <initializer_list>

template <typename T>
struct ListNode
{
    T data;
    ListNode* next;
};

template <typename T>
class List
{
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t size;
public:
    List();
    //Operator cast  = {...,...}
    List(std::initializer_list<T> list) : List() {
        for (const T& item : list) {
            Append(item);
        }
    }
    ~List();

    void Append(const T& data);
    void Remove(const T& data);
    T Get(size_t index) const;
    size_t Size() const;
    void Clear();
    size_t IndexOf(const T& data) const;
    T Pop();
    T Pop(size_t index);
    void Insert(size_t index, const T& data);
    void RemoveAt(size_t index);
    void Sort(int (*compare)(const T&, const T&));
    bool Contains(const T& data) const;
    bool ForEach(ListNode<T> **next);
    // Operator[] for non-const access
    T& operator[](size_t index);
    // Operator[] for const access
    const T& operator[](size_t index) const;
    T& First();
    const T& First() const;
    T& Last();
    const T& Last() const;

    // Iterator class
    class Iterator {
    private:
        ListNode<T>* current;

    public:
        Iterator(ListNode<T>* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }   
};

#include "List.tpp"

/*
Example:
List<int> list = {1, 2, 3, 4, 5};

for (auto& item : list) {
    printf("%d\n", item);
}
*/

#endif // LIST_HPP