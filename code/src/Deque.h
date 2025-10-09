#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>

// Node structure for deque
template <typename T>
struct Node
{
    T mData;
    Node *mPrevious;
    Node *mNext;

    Node(const T &valueParm) : mData(valueParm), mPrevious(nullptr), mNext(nullptr)
    {
    }
};

// Deque class definition
template <typename T>
class Deque
{
private:
    size_t mSize;
    Node<T>* mHead;
    Node<T>* mTail;

    // Private helper to get a node at a specific index
    Node<T>* pGetNodeAt(size_t indexParm) const;

public:
    Deque();
    Deque(size_t sizeParm, const T &valueParm);
    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;
    Deque(Deque&&) = delete;
    Deque& operator=(Deque&&) = delete;
    ~Deque();

    void push_back(const T &dataParm);
    void pop_back();
    void push_front(const T &dataParm);
    void pop_front();
    
    /*Function name: addAt
      Input Parameters: indexParm (position to add), dataParm (data to add)
      Output: None
      Purpose: Adds an element at a specific index in the middle of the DLL (EDLL).
    */
    void addAt(size_t indexParm, const T &dataParm); 
    
    /*Function name: removeFrom
      Input Parameters: indexParm (position to remove)
      Output: None
      Purpose: Removes an element from a specific index in the middle of the DLL (EDLL).
    */
    void removeFrom(size_t indexParm);

    const T &front() const;
    const T &back() const;
    bool empty() const;
    size_t size() const;
    
    enum ResizeDirection {
        Forward,
        Reverse
    };
    void resize(size_t newSizeParm, const T &defaultValueParm, ResizeDirection directionParm);
    
    void clear();
    
    /*Function name: operator[]
      Input Parameters: indexParm (position of the element to access)
      Output: Const reference to the element at the specified index
      Purpose: Provides read-only access to the element at 'index' in the deque.
    */
    const T& operator[](size_t indexParm) const;

    /*Function name: operator[]
      Input Parameters: indexParm (position of the element to access)
      Output: Non-const reference to the element at the specified index
      Purpose: Provides read/write access to the element at 'index' in the deque (REQUIRED for EDLL modification).
    */
    T& operator[](size_t indexParm); 

};

// --- Deque Implementation ---

template <typename T>
Deque<T>::Deque() : mSize(0), mHead(nullptr), mTail(nullptr)
{
}

template <typename T>
Deque<T>::Deque(size_t sizeParm, const T &valueParm) : mSize(0), mHead(nullptr), mTail(nullptr)
{
    for (size_t sI = 0; sI < sizeParm; ++sI)
    {
        push_back(valueParm);
    }
}

template <typename T>
Deque<T>::~Deque()
{
    clear();
}

template <typename T>
Node<T>* Deque<T>::pGetNodeAt(size_t indexParm) const
{
    if (indexParm >= mSize)
    {
        return nullptr;
    }
    
    Node<T>* sCurrent;
    // Optimization: start from head or tail based on index
    if (indexParm < mSize / 2)
    {
        sCurrent = mHead;
        for (size_t sI = 0; sI < indexParm; ++sI)
        {
            sCurrent = sCurrent->mNext;
        }
    }
    else
    {
        sCurrent = mTail;
        for (size_t sI = mSize - 1; sI > indexParm; --sI)
        {
            sCurrent = sCurrent->mPrevious;
        }
    }
    return sCurrent;
}

template <typename T>
void Deque<T>::push_back(const T &dataParm)
{
    Node<T>* sNewNode = new Node<T>(dataParm);
    if (empty())
    {
        mHead = mTail = sNewNode;
    }
    else
    {
        sNewNode->mPrevious = mTail;
        mTail->mNext = sNewNode;
        mTail = sNewNode;
    }
    mSize++;
}

template <typename T>
void Deque<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("Cannot pop_back from an empty deque.");
    }
    Node<T>* sTemp = mTail;
    if (mHead == mTail) // Single element
    {
        mHead = mTail = nullptr;
    }
    else
    {
        mTail = mTail->mPrevious;
        mTail->mNext = nullptr;
    }
    delete sTemp;
    mSize--;
}

template <typename T>
void Deque<T>::push_front(const T &dataParm)
{
    Node<T>* sNewNode = new Node<T>(dataParm);
    if (empty())
    {
        mHead = mTail = sNewNode;
    }
    else
    {
        sNewNode->mNext = mHead;
        mHead->mPrevious = sNewNode;
        mHead = sNewNode;
    }
    mSize++;
}

template <typename T>
void Deque<T>::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("Cannot pop_front from an empty deque.");
    }
    Node<T>* sTemp = mHead;
    if (mHead == mTail) // Single element
    {
        mHead = mTail = nullptr;
    }
    else
    {
        mHead = mHead->mNext;
        mHead->mPrevious = nullptr;
    }
    delete sTemp;
    mSize--;
}

template <typename T>
void Deque<T>::addAt(size_t indexParm, const T &dataParm)
{
    if (indexParm > mSize)
    {
        throw std::out_of_range("Index out of bounds for addAt");
    }

    if (indexParm == 0)
    {
        push_front(dataParm);
    }
    else if (indexParm == mSize)
    {
        push_back(dataParm);
    }
    else
    {
        Node<T>* sCurrent = pGetNodeAt(indexParm);
        Node<T>* sNewNode = new Node<T>(dataParm);

        sNewNode->mPrevious = sCurrent->mPrevious;
        sNewNode->mNext = sCurrent;
        sCurrent->mPrevious->mNext = sNewNode;
        sCurrent->mPrevious = sNewNode;
        mSize++;
    }
}

template <typename T>
void Deque<T>::removeFrom(size_t indexParm)
{
    if (indexParm >= mSize)
    {
        throw std::out_of_range("Index out of bounds for removeFrom");
    }

    if (indexParm == 0)
    {
        pop_front();
    }
    else if (indexParm == mSize - 1)
    {
        pop_back();
    }
    else
    {
        Node<T>* sCurrent = pGetNodeAt(indexParm);
        
        sCurrent->mPrevious->mNext = sCurrent->mNext;
        sCurrent->mNext->mPrevious = sCurrent->mPrevious;

        delete sCurrent;
        mSize--;
    }
}

template <typename T>
const T &Deque<T>::front() const
{
    if (empty())
    {
        throw std::out_of_range("Front from empty deque.");
    }
    return mHead->mData;
}

template <typename T>
const T &Deque<T>::back() const
{
    if (empty())
    {
        throw std::out_of_range("Back from empty deque.");
    }
    return mTail->mData;
}

template <typename T>
bool Deque<T>::empty() const
{
    return mSize == 0;
}

template <typename T>
size_t Deque<T>::size() const
{
    return mSize;
}

template <typename T>
void Deque<T>::resize(size_t newSizeParm, const T &defaultValueParm, ResizeDirection directionParm)
{
    if (newSizeParm > mSize)
    {
        size_t sAddCount = newSizeParm - mSize;
        for (size_t sI = 0; sI < sAddCount; ++sI)
        {
            if (directionParm == Forward)
            {
                push_back(defaultValueParm);
            }
            else if (directionParm == Reverse)
            {
                push_front(defaultValueParm);
            }
        }
    }
    else if (newSizeParm < mSize)
    {
        size_t sRemoveCount = mSize - newSizeParm;
        for (size_t sI = 0; sI < sRemoveCount; ++sI)
        {
            if (directionParm == Forward)
            {
                pop_back();
            }
            else if (directionParm == Reverse)
            {
                pop_front();
            }
        }
    }
}

/*Function name: clear
  Input Parameters: None
  Output: None
  Purpose: Clears all elements (nodes) from the deque. NOTE: Does not delete T* if T is a pointer type.
*/
template <typename T>
void Deque<T>::clear()
{
    while (!empty())
    {
        pop_front();
    }
}

/*Function name: operator[]
  Input Parameters: indexParm (position of the element to access)
  Output: Const reference to the element at the specified index
  Purpose: Provides read-only access to the element at 'index' in the deque.
*/
template <typename T>
const T& Deque<T>::operator[](size_t indexParm) const
{
    Node<T>* sNode = pGetNodeAt(indexParm);
    if (!sNode)
    {
        throw std::out_of_range("Index out of bounds for const access");
    }
    return sNode->mData;
}

/*Function name: operator[]
  Input Parameters: indexParm (position of the element to access)
  Output: Non-const reference to the element at the specified index
  Purpose: Provides read/write access to the element at 'index' in the deque.
*/
template <typename T>
T& Deque<T>::operator[](size_t indexParm) 
{
    Node<T>* sNode = pGetNodeAt(indexParm);
    if (!sNode)
    {
        throw std::out_of_range("Index out of bounds for non-const access");
    }
    return sNode->mData;
}

#endif
