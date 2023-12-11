#include "sll.h"
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <stack>

template <typename T>
void SinglyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
T& SinglyLinkedList<T>::operator[](std::size_t index) {
    Node<T>* current = head;
    for (std::size_t i = 0; i < index && current; ++i) {
        current = current->next;
    }
    if (!current) {
        throw std::out_of_range("Index out of bounds");
    }
    return current->data;
}

template <typename T>
void SinglyLinkedList<T>::copyList(const SinglyLinkedList& oth) {
    if (oth.head == nullptr) {
        return;
    }
    head = new Node<T>(oth.head->data);
    Node<T>* curr = head;
    Node<T>* othCurr = oth.head->next;
    while (othCurr != nullptr) {
        curr->next = new Node<T>(othCurr->data);
        curr = curr->next;
        othCurr = othCurr->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::swap(SinglyLinkedList& first, SinglyLinkedList& second) {
    std::swap(first.head, second.head);
}

template <typename T>
Node<T>::Node() : data{T()}, next{nullptr} {}

template <typename T>
Node<T>::Node(const T& val) : data{val}, next{nullptr} {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head{nullptr} {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& oth) {
    copyList(oth);
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& oth) {
    if (this != &oth) {
        clear();
        copyList(oth);
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& oth) {
    swap(*this, oth);
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& oth) {
    if (this != &oth) {
        clear();
        swap(*this, oth);
    }
    return *this;
}

template <typename T>
void SinglyLinkedList<T>::push_back(T val) {
    Node<T>* newNode = new Node<T>(val);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

template <typename T>
void SinglyLinkedList<T>::push_front(T val) {
    Node<T>* newNode = new Node<T>(val);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void SinglyLinkedList<T>::insert(std::size_t pos, T val) {
    Node<T>* newNode = new Node<T>(val);
    if (pos == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<T>* curr = head;
        for (std::size_t i = 0; i < pos - 1 && curr != nullptr; ++i) {
            curr = curr->next;
        }
        if(curr == nullptr) {
            throw std::out_of_range("Invalid position");
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}
template <typename T>
void SinglyLinkedList<T>::pop_back() {
    if (head == nullptr) {
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node<T>* curr = head;
    while (curr->next != nullptr && curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::pop_front() {
    if (head == nullptr) {
        return;
    }
    Node<T>* tmp = head;
    head = head->next;
    delete tmp;
}

template <typename T>
void SinglyLinkedList<T>::deleteItem(std::size_t pos) {
    Node<T>* current = head;
    Node<T>* previous = nullptr;
    for (std::size_t i = 0; i < pos && current; ++i) {
        previous = current;
        current = current->next;
    }
    if (!current) {
        throw std::out_of_range("Invalid position for deletion");
    }
    if (!previous) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;
}

template <typename T>
std::size_t SinglyLinkedList<T>::search(T val) const {
    std::size_t i = 0;
    Node<T>* curr = head;
    while (curr != nullptr) {
        if (curr->data == val) {
            return i;
        }
        curr = curr->next;
        ++i;
    }
    throw std::out_of_range("Value is not found");
}


template <typename T>
void SinglyLinkedList<T>::insert(std::size_t pos, const SinglyLinkedList<T>& otherList) {
    Node<T>* current = head;
    Node<T>* previous = nullptr;

    for (std::size_t i = 0; i < pos && current; ++i) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::out_of_range("Invalid position for insertion");
    }

    Node<T>* otherCurrent = otherList.head;

    while (otherCurrent) {
        Node<T>* newNode = new Node<T>(otherCurrent->data);

        if (!previous) {
            newNode->next = head;
            head = newNode;
        } else {
            newNode->next = current;
            previous->next = newNode;
        }

        previous = newNode;
        otherCurrent = otherCurrent->next;
    }
}

template <typename T>
std::size_t SinglyLinkedList<T>::Size() const {
    std::size_t count = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

template <typename T>
void SinglyLinkedList<T>::printList() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SinglyLinkedList<T>::printListReversed() const {
    std::stack<T> stack;

    for (Node<T>* current = head; current != nullptr; current = current->next) {
        stack.push(current->data);
    }
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
}

// template <typename T>
// void SinglyLinkedList<T>::reverse() {
//     Node<T>* next = nullptr;
//     Node<T>* prev = nullptr;
//     Node<T>* curr = head;

//     while (curr != nullptr) {
//         next = curr->next;
//         curr->next = prev;
//         prev = curr;
//         curr = next;
//     }
//     head = prev;
// }
template <typename T>
Node<T>* SinglyLinkedList<T>::reverse(Node<T>* curr) {
    if (curr == nullptr || curr->next == nullptr) {
        return curr;
    }
    Node<T>* tmp = reverse(curr->next);
    curr->next->next = curr;
    curr->next = nullptr;

    return tmp;
}

template <typename T>
void SinglyLinkedList<T>::reverse() {
    head = reverse(head);
}

template <typename T>
bool SinglyLinkedList<T>::hasCycle() const {
    Node <T>* slow = head;
    Node <T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }  
    return false;
}

template <typename T>
T SinglyLinkedList<T>::getStartPoint() const {
    Node <T>* slow = head;
    Node <T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow->data;
        } 
    }  
    return T();
}

template <typename T>
T SinglyLinkedList<T>::getMiddleNode() const {
    if (head == nullptr) {
        return T();
    }
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->data;
}

template <typename T>
void SinglyLinkedList<T>::mergeTwoSortedLinkedLists(const SinglyLinkedList& l1, const SinglyLinkedList& l2) {
    clear();

    Node<T>* curr1 = l1.head;
    Node<T>* curr2 = l2.head;

    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->data < curr2->data) {
            push_back(curr1->data);
            curr1 = curr1->next;
        } else {
            push_back(curr2->data);
            curr2 = curr2->next;
        }
    }
    while (curr1 != nullptr) {
        push_back(curr1->data);
        curr1 = curr1->next;
    }

    while (curr2 != nullptr) {
        push_back(curr2->data);
        curr2 = curr2->next;
    }
}

