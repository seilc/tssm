#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "xDebug.h"
#include "xMemMgr.h"

struct tier_queue_allocator
{
    struct block_data
    {
        U8 prev;
        U8 next;
        U16 flags;
        void* data;
    };

    block_data* blocks;
    U32 _unit_size;
    U32 _block_size;
    U32 _block_size_shift;
    U32 _max_blocks;
    U32 _max_blocks_shift;
    U8 head;
};

template <class T> struct tier_queue
{
    U32 first;
    U32 _size;
    U32 wrap_mask;
    tier_queue_allocator* alloc;
    U8 blocks[256];
};

template <class T>
class static_queue
{
public:
    class iterator
    {
    public:
        bool operator==(const iterator& c) const { return _it == c._it; }
        bool operator!=(const iterator& c) const { return _it != c._it; }
        iterator& operator++() { *this += 1; return *this; }

        iterator& operator+=(int i)
        {
            xASSERT(_owner != 0);
            xASSERT(i >= -(int)_owner->_max_size);
            _it = _owner->mod_max_size(_it + i);
            return *this;
        }

        T& operator*() const { return _owner->_buffer[_it]; }

        size_t _it;
        static_queue* _owner;
    };

    void init(size_t size)
    {
        xASSERT(size > 0);
        size_t power = 0;
        size++;
        while (size > 1) { size >>= 1; power++; }
        _max_size = (1 << power);
        _max_size_mask = _max_size - 1;
        _buffer = (T*)xMEMALLOC(_max_size * sizeof(T), 0);
        xASSERT(_buffer != 0);
        clear();
    }

    size_t size() const { return _size; }
    size_t max_size() const { return _max_size - 1; }
    bool empty() const { return size() == 0; }
    bool full() const { return size() == max_size(); }
    void clear() { _first = _size = 0; }
    T& push_front() { xASSERT(!full()); _size++; _first = mod_max_size(_first-1); return front(); }
    void pop_back() { xASSERT(!empty()); _size--; }
    iterator begin() const { return create_iterator(_first); }
    iterator end() const { return create_iterator(mod_max_size(_first + _size)); }
    T& front() { xASSERT(!empty()); return *begin(); }

    void erase(const iterator& first, const iterator& last)
    {
        xASSERT((first == begin()) || (last == end()));

        if (first._it == _first) {
            size_t tail = _first + _size;
            _first = last._it;
            _size = mod_max_size(tail - _first);
            return;
        }

        size_t diff = mod_max_size(last._it - first._it);
        xASSERT(diff <= _size);
        _size -= diff;
    }

private:
    iterator create_iterator(size_t i) const { iterator r; r._it = i; r._owner = (static_queue*)this; return r; }
    size_t mod_max_size(size_t v) const { return v & _max_size_mask; }

public:
    size_t _first;
    size_t _size;
    size_t _max_size;
    size_t _max_size_mask;
    T* _buffer;

    friend class iterator;
};

class pool_list_base
{
protected:
    struct node_base
    {
        node_base* prev;
        node_base* next;
    };

public:
    S32 size() const { return _size; }
    S32 max_size() const { return _max_size; }
    bool empty() const { return _size == 0; }
    bool full() const { return size() == max_size(); }

protected:
    void push_back();
    void create(S32 node_size, S32 max_size, void* buffer);
    void reset(S32 node_size);
    node_base* erase(node_base* it);

protected:
    S32 _size;
    S32 _max_size;
    node_base head;
    node_base tail;
    node_base* stack;
    void* buffer;
};

template <class T>
class pool_list : public pool_list_base
{
public:
    struct node_type
    {
        node_type* prev;
        node_type* next;
        T value;
    };

    enum { NODE_SIZE = sizeof(node_type) };

    void create(S32 max_size, void* buffer)
    {
        pool_list_base::create(NODE_SIZE, max_size, buffer);
    }

    void reset()
    {
        pool_list_base::reset(NODE_SIZE);
    }

    node_type* begin() const { return (node_type*)head.next; }
    node_type* end() const { return (node_type*)&tail; }
    T& back() { xASSERT(!empty()); return ((node_type*)tail.prev)->value; }

    node_type* erase(node_type* it)
    {
        return (node_type*)pool_list_base::erase((node_base*)it);
    }

    node_type* get_iterator(const T* value)
    {
        xASSERT((void*)value >= (void*)buffer);
        xASSERT((void*)value < (void*)((U8*)buffer + _max_size*NODE_SIZE));
        U8* p = ((U8*)value - sizeof(node_base));
        xASSERT(((p - (U8*)buffer) % NODE_SIZE) == 0);
        return (node_type*)p;
    }

    void push_back() { pool_list_base::push_back(); }
};

template <class T, U32 N> struct fixed_queue
{
    U32 _first;
    U32 _last;
    T _buffer[N + 1];

    void reset();
    void push_front(const T& element);
    bool full() const;
    void pop_back();
    bool empty() const;
};

#endif
