#pragma once

#include <stdexcept>

template <typename T>
class LinkedList {
protected:
    class Node;

public:
    LinkedList() = default;

    LinkedList(const LinkedList&) = delete;

    LinkedList& operator=(const LinkedList&) = delete;

    virtual ~LinkedList() noexcept;

    T& Head() const;

    T& Tail() const;

    void Push(T element) noexcept;

    void Pop();

    bool TryPop() noexcept;

    void Pop(unsigned int number);

    unsigned int TryPop(unsigned int number) noexcept;

    void PopTail();

    bool TryPopTail() noexcept;

    void Remove(unsigned int index, unsigned int number);

    unsigned int TryRemove(unsigned int index, unsigned int number) noexcept;

    T& operator[](unsigned int index) const;

    class Iterator {
    public:
        explicit Iterator(Node* node_ptr) noexcept;

        bool operator!=(const Iterator& other) const noexcept;

        const T& operator*() const noexcept;

        Iterator& operator++() noexcept;

    private:
        Node* _node;
    };

    Iterator begin() const noexcept;

    Iterator end() const noexcept;

protected:
    class Node {
    public:
        explicit Node(const T& value) noexcept;

        T value;
        Node* next = nullptr;
    };

    Node* _head = nullptr;
    Node* _tail = nullptr;

    void CutNode(Node*& node) noexcept;

    virtual void FreeNode(Node* node) const noexcept;
};

#include "linked_list_imp.h"