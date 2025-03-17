#include "List.h"
using namespace cop4530;



//*****************//
// CONST ITERATORS //
//*****************//



// default zero parameter constructor
template <typename T>
List<T>::const_iterator::const_iterator() : current(nullptr) {}

// operator*() to return element
template <typename T>
const T& List<T>::const_iterator::operator*() const {
    return retrieve();
}

// operator->() to return pointer to element
template <typename T>
const T* List<T>::const_iterator::operator->() const {
    return &(retrieve());
}

// increment operator (++)
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}

// increment operator (++)
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

// decrement operator (--)
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}

// decrement operator (--)
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    const_iterator temp = *this;
    --(*this);
    return temp;
}

// comparison operator (==)
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator& rhs) const {
    return current == rhs.current;
}

// comparison operator (!=)
template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& rhs) const {
    return !(*this == rhs);
}

// retrieve the element refers to
template <typename T>
T& List<T>::const_iterator::retrieve() const {
    return current->data;
}

// protected constructor
template <typename T>
List<T>::const_iterator::const_iterator(Node* p) : current(p) {}



//********************//
// NON-CONST ITERATORS //
//********************//



// default zero parameter constructor
template <typename T>
List<T>::iterator::iterator() : const_iterator() {}

// operator*() to return element
template <typename T>
T& List<T>::iterator::operator*() {
    return const_iterator::retrieve();
}

// operator*() to return element
template <typename T>
const T& List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}

// return pointer to element
template <typename T>
T* List<T>::iterator::operator->() {
    return &(**this);
}

// return pointer to content element
template <typename T>
const T* List<T>::iterator::operator->() const {
    return &(**this);
}

// increment operator (++)
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    const_iterator::operator++();
    return *this;
}

// increment operator (++)
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

// decrement operator (--)
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    const_iterator::operator--();
    return *this;
}

// decrement operator (--)
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
}

// protected constructor
template <typename T>
List<T>::iterator::iterator(Node* p) : const_iterator(p) {}



//***********//
// LIST CLASS//
//***********//



// default zero parameter constructor
template<typename T>
List<T>::List() {
    init();
}

// copy constructor
template<typename T>
List<T>::List(const List& rhs) {
    init();
    for (auto& x : rhs) {
        push_back(x);
    }
}

// move constructor 
template<typename T>
List<T>::List(List&& rhs)
    : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail } {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// num elements with value of val
template <typename T>
List<T>::List(int num, const T& val) {
    if (num <= 0) return;

    init();

    for (int i = 0; i < num; ++i) {
        Node* newNode = new Node(val);

        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++theSize;
    }
}

// constructs with elements [start, end)
template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
    init();
    while (start != end) {
        push_back(*start++);
    }
}

// destructor 
template <typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}


// copy assignment operator
template <typename T>
const List<T>& List<T>::operator=(const List& rhs) {
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}

// move assignment operator
template <typename T>
List<T>& List<T>::operator=(List&& rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}



//**********************//
// LIST MEMBER FUNCTIONS//
//**********************//



 // number of elements
template <typename T>
int List<T>::size() const {
    return theSize;
}

// check if list is empty
template <typename T>
bool List<T>::empty() const {
    return size() == 0;
}

// delete all elements
template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// reverse the order of the elements
template <typename T>
void List<T>::reverse() {
    if (empty()) return;
    Node* current = head;
    Node* temp = nullptr;
    tail = head;

    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    head = temp->prev;
}

// reference to the first element
template <typename T>
T& List<T>::front() {
    return *begin();
}

// constant reference to the first element
template <typename T>
const T& List<T>::front() const {
    return *begin();
}

// reference to the last element
template <typename T>
T& List<T>::back() {
    return *--end();
}

// constant reference to the last element
template <typename T>
const T& List<T>::back() const {
    return *--end();
}

// insert to the beginning
template <typename T>
void List<T>::push_front(const T& val) {
    insert(begin(), val);
}

// move version of insert
template <typename T>
void List<T>::push_front(T&& val) {
    insert(begin(), std::move(val));
}

// insert to the end
template <typename T>
void List<T>::push_back(const T& val) {
    insert(end(), val);
}

// move version of insert
template <typename T>
void List<T>::push_back(T&& val) {
    insert(end(), std::move(val));
}

// delete first element
template <typename T>
void List<T>::pop_front() {
    erase(begin());
}

// delete last element
template <typename T>
void List<T>::pop_back() {
    erase(--end());
}

// remove all elements with value = val
template <typename T>
void List<T>::remove(const T& val) {
    for (auto itr = begin(); itr != end(); ) {
        if (*itr == val) {
            itr = erase(itr);
        }
        else {
            ++itr;
        }
    }
}

// print out all elements. ofc is deliminator
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
    for (auto itr = begin(); itr != end(); ++itr) {
        os << *itr << ofc;
    }
}


//***********************//
// LIST MEMBER ITERATORS//
//**********************//



 // iterator to first element
template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head->next);
}

// iterator to first element (const)
template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head->next);
}

//end marker iterator
template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(tail);
}

//end marker iterator (const)
template <typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(tail);
}

// insert val ahead of itr
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
    Node* p = itr.current;
    theSize++;
    return { p->prev = p->prev->next = new Node { val, p->prev, p} };
}

// move version of insert
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val) {
    Node* p = itr.current;
    theSize++;
    return { p->prev = p->prev->next
    = new Node { std::move(val), p->prev, p} };
}

// erase one element
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
    Node* p = itr.current;
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
}

// erase [start, end)
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
    for (iterator itr = start; itr != end;) {
        itr = erase(itr);
    }

    return end;
}

// initialization
template <typename T>
void List<T>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}



//*************************//
// LIST MEMBER COMPARATORS//
//************************//



 // Equality operator
template <typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    auto leftIt = lhs.begin();
    auto rightIt = rhs.begin();
    auto leftEnd = lhs.end();
    auto rightEnd = rhs.end();

    while (leftIt != leftEnd && rightIt != rightEnd) {
        if (*leftIt != *rightIt) {
            return false;
        }
        ++leftIt;
        ++rightIt;
    }

    return (leftIt == leftEnd && rightIt == rightEnd);
}


// Inequality operator
template <typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);  // Use the equality operator
}

// Output stream operator
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
        os << *it << " ";
    }
    return os;
}