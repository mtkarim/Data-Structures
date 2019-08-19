/*
 * Name: Mubasshir Karim
 * WSU ID: G498M939
 * File: List.hpp
 * Assignment: 3
 * Description: Doubly linked-list.
 */

#ifndef DOUBLE_LINK_LIST_HPP
#define DOUBLE_LINK_LISH_HPP

// Necessary includes
#include <iostream>
#include <utility>
#include <cstdlib>
#include <stdexcept>
#include <memory>

// CLASS DECLARATIONS
template<typename T>
class List
{
public:
    List();                         // Default constructor
    List(T data);                   // Constructor that takes first item
    List(const List<T> &rhs);       // Copy constructor
    ~List();                        // Destructor

    T& front();         // function front; l-value
    T& front() const;   // function front; return by value
    T& back();          // function back; l-value
    T& back() const;    // function back; return by value

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    iterator begin();                           // function begin
    iterator end();                             // function end
    const_iterator begin() const;               // function begn; const_iterator overload
    const_iterator end() const;                 // function end; const_iterator overload
    const_iterator cbegin() const noexcept;     // function cbegin
    const_iterator cend() const noexcept;       // function cend
    reverse_iterator rbegin();                  // function rbegin
    reverse_iterator rend();                    // function rend
    const_reverse_iterator rbegin() const;      // function rbegin; const_reverse_iterator overload
    const_reverse_iterator rend() const;        // function rend; const_reverse_iterator overload
    const_reverse_iterator crbegin() const;     // function crbegin
    const_reverse_iterator crend() const;       // function crend

    iterator search(const T &item);                 // function search; returns iterator            // throws std::invalid_argument
    const_iterator search(const T &item) const;     // function search; returns const_iterator      // throws std::invalid_argument
    iterator erase(const T &item);                  // function erase; returns iterator to one after what was erased    // throws std::invalid_argument
    iterator erase(iterator pos);                   // function erase; overload that takes an iterator to what should be erased // throws std::invalid_argument
    iterator insert(iterator pos, const T &item);   // function insert; takes an iterator to position where insertion occurs as well as item to insert, returns iterator to inserted item
    void push_back(const T &data);                  // function push_back;
    void push_front(const T &data);                 // function push_front;

    template<typename ...Args>
    iterator emplace(iterator pos, Args&&...);      // function emplace; takes an iterator to position where insertion occurs as well as item constructor parameters, returns iterator to inserted item

    template<typename ...Args>
    void emplace_back(Args&&... args);              // function emplace_back; takes item constructor parameters

    template<typename ...Args>
    void emplace_front(Args&&... args);             // function emplace_front; takes item constructor parameters

    unsigned int size() const;                      // function size();
    bool empty() const;                             // function empty();

    List<T>& operator=(const List<T> &rhs);         // function copy assignment overload;
    List<T>& operator=(List<T> &&rhs);              // function move assignment overload;
private:
    class Node;
    Node *head;         // the pointer to the first node
    Node *tail;         // the pointer to the last node
    unsigned int count;
};

template<typename T>
class List<T>::Node
{
    public:
        Node(T dat);

        template<typename ...Args>
        Node(Args&&... args);

        T& getData() {return data;};
        void setData(T dat) {data = dat;};
        void setNext(Node* nPtr) {next = nPtr;};        // sets pointer to next node and declared here
        Node* getNext() const {return next;};           // way to get to next node and declared here
        void setPrev(Node* pPtr) {prev = pPtr;};        // sets pointer to previous node and declared here
        Node* getPrev() const {return prev;};           // way to get to previous node and declared here
    private:
        T data;
        Node *next;
        Node *prev;
};

// LIST CLASS IMPLEMENTATIONS BELOW //

// Default constructor
template <typename T>
List<T>::List()
: head(nullptr)
, tail(nullptr)
, count(0)
{};

// Constructor that takes first item
template <typename T>
List<T>::List(T first)
{
    head = tail = new Node(first);
    tail = head;
    count = 1;
};

// Copy constructor
template <typename T>
List<T>::List(const List<T> &rhs)
: head(nullptr)
, tail(nullptr)
, count(0)
{
    if (rhs.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    head = new Node(rhs.head->getData());
    Node *newPtr = head;
    iterator iterate(rhs.head);
    iterate++;

    while(iterate.getPtr() != nullptr)
    {
        newPtr->setNext(new Node(iterate.getPtr()->getData()));
        newPtr = newPtr->getNext();
        newPtr->setPrev(iterate.getPtr()->getPrev());
        ++iterate;
    }

    tail = newPtr;

    count = rhs.size();
};

// Destructor
template<typename T>
List<T>::~List()
{
    while (head != tail)                // if list not empty, then run functions to remove all
    {
        List<T>::Node *newPtr = head;
        head = head->getNext();
        delete newPtr;
    }
    delete head;
    head = nullptr;
    tail = nullptr;
    count = 0;
};

// function front; l-value
template<typename T>
T& List<T>::front()
{
    return head->getData();
}

// function front; return by value
template<typename T>
T& List<T>::front() const
{
  return head->getData();
}

// function back; l-value
template<typename T>
T& List<T>::back()
{
  return tail->getData();
}

// function back; return by value
template<typename T>
T& List<T>::back() const
{
  return tail->getData();
}

// function search; returns iterator -- throws std::invalid_argument
template<typename T>
typename List<T>::iterator List<T>::search(const T &item)
{
    Node *newPtr = new Node(item);
    iterator iterate(newPtr);

    return iterate;
}

// function search; returns const_iterator -- throws std::invalid_argument
template<typename T>
typename List<T>::const_iterator List<T>::search(const T &item) const
{
    Node *newPtr = new Node(item);
    const_iterator iterate(newPtr);

    return iterate;
}

// function erase; returns iterator to one after what was erased -- throws std::invalid_argument
template<typename T>
typename List<T>::iterator List<T>::erase(const T &item)
{
    Node *node = new Node(item);

    return iterator(node);
}

// function erase; overload that takes an iterator to what should be erased -- throws std::invalid_argument
template<typename T>
typename List<T>::iterator List<T>::erase(iterator pos)
{
    Node* newPtr = nullptr;

    if (pos.getPtr() == head)
    {
        if(size() == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return nullptr;
        }

            newPtr = head;
            head = head->getNext();
            head->setPrev(nullptr);
            delete newPtr;
            newPtr = head;

    }
    else if (pos.getPtr() == tail)
    {
        newPtr = tail;
        tail = tail->getPrev();
        tail->setNext(nullptr);
        delete newPtr;
        newPtr = tail->getNext();
    }
    else
    {
        newPtr = pos.getPtr();
        newPtr = newPtr->getPrev();
        newPtr->setNext(newPtr->getNext()->getNext());
        newPtr = newPtr->getNext();
        newPtr->setPrev(newPtr->getPrev()->getPrev());
        newPtr = pos.getPtr();
        pos++;
        delete newPtr;
        newPtr = pos.getPtr();
    }
    count--;
    return iterator(newPtr);
}

// function insert; takes an iterator to position where insertion occurs as well as item to insert, returns iterator to inserted item
template<typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const T &item)
{
    Node *temp = new Node(item);
    Node *tempPrev = pos.getPtr()->getPrev();
    Node *tempNext = pos.getPtr();

    tempPrev->setNext(temp);
    temp->setPrev(tempPrev);
    tempNext->setPrev(temp);
    temp->setNext(tempNext);

    iterator itr(temp);

    count++;

    return itr;
}

// function push_back;
template<typename T>
void List<T>::push_back(const T &data)
{
    Node *newPtr;

    if (head == nullptr)
    {
        head = new Node(data);
        tail = head;
        count++;
        return;
    }

    tail->setNext(new Node(data));
    newPtr = tail;
    tail = tail->getNext();
    tail->setPrev(newPtr);

    count++;
}

// function push_front;
template<typename T>
void List<T>::push_front(const T &data)
{
    Node *newPtr;

    if (head == nullptr)
    {
        head = new Node(data);
        tail = head;
        count++;
        return;
    }

    head->setPrev(new Node(data));
    newPtr = head;
    head = head->getPrev();
    head->setNext(newPtr);
    head->getNext()->setPrev(head);

    count++;
};

// function emplace; takes an iterator to position where insertion occurs as well as item constructor parameters, returns iterator to inserted item
template<typename T>
template <typename ...Args>
typename List<T>::iterator List<T>::emplace(iterator pos, Args&&... args)
{
    Node *temp = new Node(args...);
    Node *tempPrev = pos.getPtr()->getPrev();
    Node *tempNext = pos.getPtr();

    tempPrev->setNext(temp);
    temp->setPrev(tempPrev);
    tempNext->setPrev(temp);
    temp->setNext(tempNext);

    count++;

    return iterator(temp);
}

// function emplace_back; takes item constructor parameters
template<typename T>
template <typename ...Args>
void List<T>::emplace_back(Args&&... args)
{
    Node *newPtr;

    if (head == nullptr)
    {
        head = new Node(args...);
        tail = head;
        count++;
        return;
    }

    tail->setNext(new Node(args...));
    newPtr = tail;
    tail = tail->getNext();
    tail->setPrev(newPtr);

    count++;
}

// function emplace_front; takes item constructor parameters
template<typename T>
template <typename ...Args>
void List<T>::emplace_front(Args&&... args)
{
    Node *newPtr;

    if (head == nullptr)
    {
        head = new Node(args...);
        tail = head;
        count++;
        return;
    }

    head->setPrev(new Node(args...));
    newPtr = head;
    head = head->getPrev();
    head->setNext(newPtr);
    head->getNext()->setPrev(head);

    count++;
}

// function size();
template<typename T>
unsigned int List<T>::size() const
{
    return count;
}

// function empty();
template<typename T>
bool List<T>::empty() const
{
    return (head == nullptr && tail == nullptr);
}

// function copy assignment overload;
template<typename T>
List<T>& List<T>::operator=(const List<T> &rhs)
{
    if(head != rhs.head && tail != rhs.tail)
    {
        iterator starhead(head);

        while (starhead.getPtr() != nullptr)
        {
            delete starhead.getPtr()->getNext();
            ++starhead;
        }

        head = new Node(rhs.head->getData());                                     
        Node *newPtr = head;
        iterator iterate(rhs.head);
        ++iterate;

        for (; iterate.getPtr() != nullptr; ++iterate)
        {
            newPtr->setNext(new Node(iterate.getPtr()->getData()));       
            newPtr = newPtr->getNext();                                       
        }
        tail = newPtr;

        count = rhs.count;
    }

    return *this;
}

// function move assignment overload;
template<typename T>
List<T>& List<T>::operator=(List<T> &&rhs)
{
    if(head != rhs.head && tail != rhs.tail)
    {
        if (rhs.head == nullptr)
        {
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

        head = rhs.head;
        tail = rhs.tail;
        count = rhs.count;

        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.count = 0;
    }
    return *this;
}

// ITERATOR CLASS //
template <typename T>
class List<T>::iterator
{
public:
    iterator(Node *nodeItr);        // Only need one constructor
    iterator &operator++();         // prefix increment operator overload
    iterator operator++(int);       // postfix increment operator overload
    iterator &operator--();         // prefix decrement operator overload
    const T operator*() const;      // de-reference operator overload; l-value
    Node* getPtr();                 // getter function

    friend bool operator==(const List<T>::iterator &lhs, const List<T>::iterator &rhs)  // equivalency operator overload
    {
        return lhs.source == rhs.source;
    }

    friend bool operator!=(const List<T>::iterator &lhs, const List<T>::iterator &rhs)  // inequivalency operator overload
    {
        return lhs.source != rhs.source;
    }
private:
    Node *source;
};

// ITERATOR CLASS FUNCTIONS //

// default function for source
template<typename T>
List<T>::iterator::iterator(Node *nodeItr):source(nodeItr)
{}

// iterator function begin()
template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(head);
}

// iterator function end()
template<typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator(nullptr);
}

// function postfix increment operator overload
template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    if (source != nullptr)
    {
        source = source -> getNext();
    }
    return *this;
}

// function postfix decrement operator overload
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator temp(source);
    ++(*this);
    return temp;
}

// function prefix decrement operator overload
template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    if (source != nullptr)
    {
        source = source -> getPrev();
    }
    return *this;
}

// function de-reference operator overlaod; l-value
template<typename T>
const T List<T>::iterator::operator*() const
{
    return source -> getData();
}

// CONST ITERATOR CLASS //
template <typename T>
class List<T>::const_iterator
{
public:
    const_iterator(Node *nodeItr);      // Only need one constructor
    const_iterator &operator++();       // prefix increment operator overload
    const_iterator operator++(int);     // postfix increment operator overload
    const_iterator &operator--();       // prefix decrement operator overload
    const T operator*() const;          // de-reference operator overload; l-value
    Node* getPtr();                     // getter function

    friend bool operator==(const List<T>::const_iterator &lhs, const List<T>::const_iterator &rhs)  // equivalency operator overload
    {
        return lhs.source == rhs.source;
    }

    friend bool operator!=(const List<T>::const_iterator &lhs, const List<T>::const_iterator &rhs)  // inequivalency operator overload
    {
        return lhs.source != rhs.source;
    }
private:
    Node *source;
};

// CONST ITERATOR FUNCTIONS //

// default function for source
template<typename T>
List<T>::const_iterator::const_iterator(Node *nodeItr):source(nodeItr)
{}

// function postfix increment operator overload
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    if (source != nullptr)
    {
        source = source -> getNext();
    }
    return *this;
}

// function postfix decrement operator overload
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator temp(source);
    ++(*this);
    return temp;
}

// function prefix decrement operator overload
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    if (source != nullptr)
    {
        source = source -> getPrev();
    }
    return *this;
}

// function de-reference operator overlaod; l-value
template<typename T>
const T List<T>::const_iterator::operator*() const
{
    return source -> getData();
}

// REVERSE ITERATOR CLASS //
template <typename T>
class List<T>::reverse_iterator
{
public:
    reverse_iterator(Node *nodeItr);    // Only need one constructor
    reverse_iterator &operator++();     // prefix increment operator overload
    reverse_iterator operator++(int);   // postfix increment operator overload
    reverse_iterator &operator--();     // prefix decrement operator overload
    const T operator*() const;          // de-reference operator overload; l-value
    Node* getPtr();                     // getter function

    // equivalency operator overload
    friend bool operator==(const List<T>::reverse_iterator &lhs, const List<T>::reverse_iterator &rhs)
    {
        return lhs.source == rhs.source;
    }

    // inequivalency operator overload
    friend bool operator!=(const List<T>::reverse_iterator &lhs, const List<T>::reverse_iterator &rhs)
    {
        return lhs.source != rhs.source;
    }
private:
    Node *source;       // Resource that iterator manages (Node pointer)
};

// REVERSE ITERATOR FUNCTIONS //

// default function for source
template<typename T>
List<T>::reverse_iterator::reverse_iterator(Node *nodeItr):source(nodeItr)
{}

// function postfix increment operator overload
template<typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator++()
{
    if (source != nullptr)
    {
        source = source -> getPrev();
    }
    return *this;
}

// function postfix decrement operator overload
template<typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator++(int)
{
    reverse_iterator temp(source);
    ++(*this);
    return temp;
}

// function prefix decrement operator overload
template<typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator--()
{
    if (source != nullptr)
    {
        source = source -> getNext();
    }
    return *this;
}

// function de-reference operator overlaod; l-value
template<typename T>
const T List<T>::reverse_iterator::operator*() const
{
    return source -> getData();
}

// CONST REVERSE ITERATOR CLASS //
template <typename T>
class List<T>::const_reverse_iterator
{
public:
    const_reverse_iterator(Node *nodeItr);      // Only need one constructor
    const_reverse_iterator &operator++();       // prefix increment operator overload
    const_reverse_iterator operator++(int);     // postfix increment operator overload
    const_reverse_iterator &operator--();       // prefix decrement operator overload
    const T operator*() const;                  // de-reference operator overload; l-value
    Node* getPtr();                             // getter function

    // equivalency operator overload
    friend bool operator==(const List<T>::const_reverse_iterator &lhs, const List<T>::const_reverse_iterator &rhs)
    {
        return lhs.source == rhs.source;
    }

    // inequivalency operator overload
    friend bool operator!=(const List<T>::const_reverse_iterator &lhs, const List<T>::const_reverse_iterator &rhs)
    {
        return lhs.source != rhs.source;
    }
private:
    Node *source;       // Resource that iterator manages (Node pointer)
};

// CONST REVERSE ITERATOR FUNCTIONS

// default function for source
template<typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(Node *nodeItr):source(nodeItr)
{}

// function postfix increment operator overload
template<typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator++()
{
    if (source != nullptr)
    {
        source = source -> getPrev();
    }
    return *this;
}

// function postfix decrement operator overload
template<typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp(source);
    ++(*this);
    return temp;
}

// function prefix decrement operator overload
template<typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator--()
{
    if(source != nullptr)
    {
        source = source->getNext();
    }

    return *this;
}

// function de-reference operator overlaod; l-value
template<typename T>
const T List<T>::const_reverse_iterator::operator*() const
{
    return source -> getData();
}

// OTHER ITERATOR FUNCTIONS IMPLEMENTED BELOW //

// function begn; const_iterator overload
template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(head);
}

// function end; const_iterator overload
template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(nullptr);
}

// function rbegin
template<typename T>
typename List<T>::reverse_iterator List<T>::rbegin()
{
    return reverse_iterator(tail);
}

// function begin; const_reverse_iterator overload
template<typename T>
typename List<T>::const_reverse_iterator List<T>::rbegin() const
{
    return const_reverse_iterator(tail);
}

// function rend
template<typename T>
typename List<T>::reverse_iterator List<T>::rend()
{
    return reverse_iterator(nullptr);
}

// function rend; const_reverse_iterator overload
template<typename T>
typename List<T>::const_reverse_iterator List<T>::rend() const
{
    return const_reverse_iterator(nullptr);
}

// function cbegin
template<typename T>
typename List<T>::const_iterator List<T>::cbegin() const noexcept
{
    return const_iterator(head);
}

// function cend
template<typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept
{
    return const_iterator(nullptr);
}

// function crbegin
template<typename T>
typename List<T>::const_reverse_iterator List<T>::crbegin() const
{
    return const_reverse_iterator(tail);
}

// function crend
template<typename T>
typename List<T>::const_reverse_iterator List<T>::crend() const
{
    return const_reverse_iterator(nullptr);
}

// OTHER NODE CLASS FUNCTIONS //

//
template<typename T>
List<T>::Node::Node(T item)
: data(item)
, next(nullptr)
, prev(nullptr)
{}

// Node args
template<typename T>
template<typename ...Args>
List<T>::Node::Node(Args&&... args)
: data(std::forward<Args>(args)...)
, next(nullptr)
, prev(nullptr)
{}

// getter for iterator pointers
template<typename T>
typename List<T>::Node* List<T>::iterator::getPtr()
{
    return source;
}

// getter for reverse_iterator pointers
template<typename T>
typename List<T>::Node* List<T>::reverse_iterator::getPtr()
{
    return source;
}

// getter for const_reverse_iterator pointers
template<typename T>
typename List<T>::Node* List<T>::const_reverse_iterator::getPtr()
{
    return source;
}

#endif