#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>

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
    bool ForEach(List<T> *list, ListNode<T> **next, T *data);
    // Operator[] for non-const access
    T& operator[](size_t index);
    // Operator[] for const access
    const T& operator[](size_t index) const;
};

// define FOREACH_LIST to iterate over a list like this:T data; for (ListNode<T>* next = nullptr; ForEach(list, &next, &data);)
#define FOREACH_LIST(list, next, data) for (ListNode<decltype(list)::T>* next = nullptr; list.ForEach(&next, &data);)
//exemple of use:
// List<int> list;
// list.Append(1);
// list.Append(2);
// list.Append(3);
// int data;
// FOREACH_LIST(list, next, data) {
//     std::cout << data << std::endl;
// }
#endif // LIST_HPP