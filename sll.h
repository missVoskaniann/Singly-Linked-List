#ifndef SLL_H
#define SLL_H

#include <cstddef>

template <typename T>
class Node {
public: 
    T data;
    Node* next;

    Node();
    Node(const T& val);
};

template <typename T> 
class SinglyLinkedList {
private:
    Node<T>* head;
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList& oth);
    SinglyLinkedList& operator=(const SinglyLinkedList& oth);
    SinglyLinkedList(SinglyLinkedList&& oth);
    SinglyLinkedList& operator=(SinglyLinkedList&& oth);
    T& operator[](std::size_t index);
    void push_back(T val);
    void push_front(T val);
    void insert(std::size_t pos, T val);
    
    void pop_back();
    void pop_front();
    void deleteItem(std::size_t pos);

    std::size_t search(T val) const;
    void insert(std::size_t pos, const SinglyLinkedList<T>& oth);

    std::size_t Size() const;
    void printList() const;
    void printListReversed() const;
    void clear();

    //new functionality from the second lesson
    void reverse();
    bool hasCycle() const;
    T getStartPoint() const;
    T getMiddleNode() const;
    void mergeTwoSortedLinkedLists(const SinglyLinkedList& l1, const SinglyLinkedList& l2);
private:
    Node<T>* reverse(Node<T>* curr);
    void copyList(const SinglyLinkedList& oth);
    void swap(SinglyLinkedList& first, SinglyLinkedList& second);
};

#include "sll.tpp"
#endif // SLL_H