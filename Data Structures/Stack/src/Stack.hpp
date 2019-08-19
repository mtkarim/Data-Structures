/*
 * Name: Mubasshir Karim
 * WSU ID: G498M939
 * File: Stack.hpp
 * Assignment: 4
 * Description: Create a stack program.
 * This stack program is done by using doubly linked approach.
 */

#ifndef STACK_CLASS_HPP
#define STACK_CLASS_HPP

// Necessary includes
#include <iostream>
#include <utility>
#include <stdexcept>

// Stack Template Class
template<typename T>
class Stack
{
public:
    Stack();                                    // default constructor
    Stack(T first);                             // parameterized constructor that takes first item
    Stack(const Stack<T>& rhs);                 // copy constructor
    Stack(Stack<T>&& rhs);                      // move constructor
    ~Stack();                                   // destructor
    bool empty() const;                         // function empty; does not throw exceptions
    size_t size() const;                        // function size; does not throw exceptions
    T& top();                                   // function top; l-value; throws underflow if stack is empty    -- acts as front
    const T& top() const;                       // function top; read-only; throws underflow if stack is empty  -- acts as front const
    void push(const T &first) noexcept;         // function push; does not throw exceptions                     -- acts as push_front

    template<typename ...Args>
    void emplace(Args&&... args);               // function emplace; does not throw exceptions

    void pop();                                 // function pop; throws underflow if stack is empty
    Stack<T>& operator=(const Stack<T> &rhs);   // copy assignment operator overload
    Stack<T>& operator=(Stack<T> &&rhs);        // move assignment operator overload
private:
    class Node;             // forward declaring a Node class, which has implementations below
    Node *_top;             // acts as top of stack
    Node *_bottom;          // acts as bottom of stack
    unsigned int count;     // size of stack
};

// Node Template class from hw03
template<typename T>
class Stack<T>::Node
{
    public:
        Node(T dat)
        : data(dat)
        , next(nullptr)
        , prev(nullptr)
        {};

        template<typename ...Args>
        Node(Args&&... args)
        : data(std::forward<Args>(args)...)
        , next(nullptr)
        , prev(nullptr)
        {};

        T& getData() {return data;}
        void setData(T dat) {data = dat;}
        void setNext(Node* nPtr) {next = nPtr;}         // sets pointer to next node and declared here
        Node* getNext() const {return next;}            // way to get to next node and declared here
        void setPrev(Node* pPtr) {prev = pPtr;}         // sets pointer to previous node and declared here
        Node* getPrev() const {return prev;}            // way to get to previous node and declared here
    private:
        T data;
        Node *next;
        Node *prev;
};

// STACK FUNCTIONS

// default constructor
template<typename T>
Stack<T>::Stack()
: _top(nullptr)
, _bottom(nullptr)
, count(0)              // empties the stack
{};

// parameterized constructor that takes first item
template<typename T>
Stack<T>::Stack(T first)
: _top(nullptr)
, _bottom(nullptr)
, count(0)
// initialization done above
{
    push(first);        // using push function and passing through 'first' which is being passed in this case
};

// copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& rhs)
: _top(nullptr)
, _bottom(nullptr)
, count(0)
// initialization done above -- needs to be done otherwise segfault occurrs
{
    Node *newPtr = rhs._bottom;

    while (newPtr != nullptr)
    {
        push(newPtr->getData());
        newPtr = newPtr->getPrev();
    }
};

// move constructor
template<typename T>
Stack<T>::Stack(Stack<T>&& rhs)
: _top(rhs._top)
, _bottom(rhs._bottom)
, count(rhs.size())
// copying data from the passing rhs into _top, _bottom, count
// then deleting them which is done below
{
    rhs._top = nullptr;
    rhs._bottom = nullptr;
    rhs.count = 0;
};

// destructor
template<typename T>
Stack<T>::~Stack()
{
    while (_top)
    {
        Stack<T>::Node *newPtr = _top;
        _top = _top->getNext();
        delete newPtr;
    }
    delete _top;
    _top = nullptr;
    _bottom = nullptr;
    count = 0;
};

// function empty; does not throw exceptions
template<typename T>
bool Stack<T>::empty() const
{
    return (_top == nullptr);
};

// function size; does not throw exceptions
template<typename T>
size_t Stack<T>::size() const
{
    return count;
};

// function top; l-value; throws underflow if stack is empty
// like 'front' but throws exception if empty
template<typename T>
T& Stack<T>::top()
{
    if (!empty())   // stack not empty
    {
        return _top->getData();
    }
    else    // stack empty
    {
        throw std::underflow_error("Stack Underflow");
    }
};

// function top; read-only; throws underflow if stack is empty
// like 'front const' but throws exception if empty
template<typename T>
const T& Stack<T>::top() const
{
    if (!empty())   // stack not empty
    {
        return _top->getData();
    }
    else    // stack empty
    {
        throw std::underflow_error("Stack Underflow");
    }
};

// function push; does not throw exceptions
// like 'push_front' from DLlist
template<typename T>
void Stack<T>::push(const T& data) noexcept
{
    Node *newPtr;

    if (empty())
    {
        _top = new Node(data);
        _bottom = _top;
        count++;
        return;
    }

    _top->setPrev(new Node(data));
    newPtr = _top;
    _top = _top->getPrev();
    _top->setNext(newPtr);
    _top->getNext()->setPrev(_top);

    count++;
};

// function emplace; does not throw exceptions
// like 'emplace_front' from DLlist
template<typename T>
template<typename ...Args>
void Stack<T>::emplace(Args&& ...args)
{
    Node *newPtr;

    if (empty())
    {
        _top = new Node(args...);
        _bottom = _top;
        count++;
        return;
    }

    _top->setPrev(new Node(args...));
    newPtr = _top;
    _top = _top->getPrev();
    _top->setNext(newPtr);
    _top->getNext()->setPrev(_top);

    count++;
};

// function pop; throws underflow if stack is empty
template<typename T>
void Stack<T>::pop()
{
    if (!empty())   // stack not empty
    {
        Node *newPtr = _top;
        _top = _top->getNext();
        if (!empty())
        {
            _top->setPrev(nullptr);
        }
        delete newPtr;
        count--;
    }
    else    // stack empty
    {
        throw std::underflow_error("Stack Underflow");
    }
};

// copy assignment overload
// like copy constructor but checks
// the stack and returns itself
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
    if (this != &rhs)
    {
        while (!empty())    // stack not empty
        {
            _top = _top->getNext();
        }

        Node *newPtr = rhs._bottom;

        while (newPtr != nullptr)
        {
            push(newPtr->getData());
            newPtr = newPtr->getPrev();
        }
        count = rhs.size();
    }
    return *this;
};

// move assignment overload
// like move constructor but checks
// the stack and returns itself
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> &&rhs)
{
    if(this != &rhs)
    {
        _top = rhs._top;
        _bottom = rhs._bottom;
        count = rhs.count;

        rhs._top = nullptr;
        rhs._bottom = nullptr;
        rhs.count = 0;
    }
    return *this;
};

#endif
