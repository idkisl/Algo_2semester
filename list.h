#pragma once
#include <iostream>

template <class T>
class List
{
    size_t lenght = 0;
    struct Node
    {
        T value;
        Node* next = nullptr;
        Node* previous = nullptr;
        Node() : value(T()) { next = previous = nullptr; }
        Node(T&& value) : value(std::move(value)) { next = previous = nullptr; }
        Node(const Node& p) : value(p.value) { next = previous = nullptr; }
        Node(const Node* p) : value(p->value) { next = previous = nullptr; }
        template<class... Args>
        Node(Args&&... args) : value(std::forward<Args>(args)...) {}
    };
    Node* start = nullptr;
    Node* finish = nullptr;
    void _createList(Node* new_node)
    {
        assert(lenght == 0);
        assert(start == nullptr);
        assert(finish == nullptr);
        lenght = 1;
        start = finish = new_node;
    }
    template<class type_iterator>
    type_iterator insert_by_node(type_iterator it, Node* new_node)
    {
        if (lenght == 0)
        {
            _createList(new_node);
            return type_iterator(this, start);
        }

        if (it.node == nullptr)
        {
            push_back_by_node(new_node);
            return type_iterator(this, new_node);
        }

        ++lenght;
        if (it.node == start)
        {
            new_node->next = start;
            start->previous = new_node;
            start = new_node;
            return type_iterator(this, new_node);
        }
        Node* previous = it.node->previous;
        previous->next = new_node;
        new_node->previous = previous;
        new_node->next = it.node;
        it.node->previous = new_node;
        return type_iterator(this, new_node);
    }
    void push_back_by_node(Node* new_node)
    {
        if (lenght == 0)
        {
            _createList(new_node);
            return;
        }
        ++lenght;
        finish->next = new_node;
        new_node->previous = finish;
        finish = new_node;
    }
    void push_front_by_node(Node* new_node)
    {
        if (lenght == 0)
        {
            _createList(new_node);
            return;
        }
        start->previous = new_node;
        new_node->next = start;
        start = new_node;
        ++lenght;
    }
public:
    using value_type = T;

    template <class Ref, bool isReverse>
    class BaseIterator
    {
        List* list;
        Node* node;
        BaseIterator(List* list, Node* node) : list(list), node(node) {}
    public:
        using cv_type = typename std::remove_reference<Ref>::type;
        using self_type = BaseIterator;
        using value_type = T;
        using reference = Ref;
        using pointer = cv_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = int;

        template <class second_iterator_type>
        bool operator!=(const second_iterator_type& other) const
        {
            return node != other.node;
        }
        template <class second_iterator_type>
        bool operator==(const second_iterator_type& other) const
        {
            return node == other.node;
        }
        Ref operator*() const
        {
            if (node == nullptr)
                std::cout << "Node in Iterator is nullptr. operator*";
            //throw std::runtime_error("node in Iterator is nullptr. operator*");
            return node->value;
        }
        BaseIterator operator++()
        {
            if (node == nullptr)
                std::cout << "Node in Iterator is nullptr. operator++";
            //throw std::runtime_error("node in Iterator is nullptr. operator++");
            if (isReverse)
                node = node->previous;
            else
                node = node->next;
            return BaseIterator(list, node);
        }
        BaseIterator operator++(int)
        {
            return operator++();
        }
        BaseIterator operator--()
        {
            if (node == nullptr)
            {
                if (isReverse)
                    node = list->start;
                else
                    node = list->finish;
                return BaseIterator(list, node);
            }
            if (isReverse)
                node = node->next;
            else
                node = node->previous;
            return BaseIterator(list, node);
        }
        BaseIterator operator--(int)
        {
            return operator--();
        }
        friend List;
    };
    using iterator = BaseIterator<T&, false>;
    using const_iterator = BaseIterator<const T&, false>;
    using reverse_iterator = BaseIterator<T&, true>;
    using reverse_const_iterator = BaseIterator<const T&, true>;

    friend iterator;
    friend const_iterator;
    friend reverse_iterator;
    friend reverse_const_iterator;

    explicit List() {}
    explicit List(const T& value)
    {
        _createList(new Node(value));
    }
    explicit List(size_t count, const T& value = T())
    {
        if (count == 0)
            return;
        for (size_t i = 0; i < count; ++i)
            push_back(value);
        assert(lenght == count);
    }
    List(const List& other)
    {
        *this = other;
    }
    List(List&& other) noexcept
    {
        *this = std::move(other);
    }
    ~List()
    {
        clear();
    }
    const List& operator=(const List& other)
    {
        clear();
        if (other.lenght == 0)
            return *this;
        Node* current_other = other.start;
        while (current_other != nullptr)
        {
            push_back(current_other->value);
            current_other = current_other->next;
        }
        assert(lenght == other.lenght);
        return *this;
    }
    List& operator=(List&& other) noexcept
    {
        clear();
        lenght = other.lenght;
        start = other.start;
        finish = other.finish;
        other.lenght = 0;
        other.start = nullptr;
        other.finish = nullptr;
        return *this;
    }
    size_t size() const { return lenght; }
    const T& front() const { return start->value; }
    const T& back() const { return finish->value; }
    bool empty() const { return lenght == 0; }
    void clear()
    {
        if (lenght == 0)
            return;
        Node* it = start;
        Node* current;
        while (it != nullptr)
        {
            current = it;
            it = it->next;
            delete current;
        }
        start = finish = nullptr;
        lenght = 0;
    }
    iterator begin() { return iterator(this, start); }
    iterator end() { return iterator(this, nullptr); }
    const_iterator cbegin() { return const_iterator(this, start); }
    const_iterator cend() { return const_iterator(this, nullptr); }
    reverse_iterator rbegin() { return reverse_iterator(this, finish); }
    reverse_iterator rend() { return reverse_iterator(this, nullptr); }
    reverse_const_iterator rcbegin() { return reverse_const_iterator(this, finish); }
    reverse_const_iterator rcend() { return reverse_const_iterator(this, nullptr); }

    template <class type_iterator>
    void erase(type_iterator it)
    {
        if (lenght == 0)
            return;
        if (lenght == 1)
        {
            clear();
            return;
        }
        --lenght;
        if (it.node == start)
        {
            start = it.node->next;
            delete it.node;
            start->previous = nullptr;
            return;
        }
        if (it.node == finish)
        {
            finish = it.node->previous;
            delete it.node;
            finish->next = nullptr;
            return;
        }
        it.node->previous->next = it.node->next;
        it.node->next->previous = it.node->previous;
        delete it.node;
    }
    template <class type_iterator>
    void erase(type_iterator it, type_iterator last)
    {
        while (it != last)
        {
            auto iter = it;
            ++iter;
            erase(it);
            it = iter;
        }
    }
    template <class type_iterator_second>
    const_iterator insert(const_iterator it, type_iterator_second first, type_iterator_second last)
    {
        const_iterator temp;
        bool is_first_iteration = true;
        while (first != last)
        {
            ++lenght;
            if (is_first_iteration)
            {
                temp = insert(it, first.pointer->value);
                is_first_iteration = false;
            }
            else
                insert(it, first.pointer->value);
            ++first;
        }
        //if first == last
        ++lenght;
        if (is_first_iteration)
            temp = insert(it, first.pointer->value);
        else
            insert(it, first.pointer->value);
        return temp;
    }
    template <class type_iterator>
    type_iterator insert(type_iterator it, const T& value) { return insert_by_node(it, new Node(value)); }
    template <class type_iterator>
    type_iterator insert(type_iterator it, T&& value) { return insert_by_node(it, new Node(std::move(value))); }
    void push_back(const T& value) { push_back_by_node(new Node(value)); }
    void push_back(T&& value) { push_back_by_node(new Node(std::move(value))); }
    void push_front(const T& value) { push_front_by_node(new Node(value)); }
    void push_front(T&& value) { push_front_by_node(new Node(std::move(value))); }
    void pop_back() { erase(const_iterator(this, finish)); }
    void pop_front() { erase(const_iterator(this, start)); }
    template<class type_iterator, class... Args >
    type_iterator emplace(type_iterator it, Args&&... args) { return insert_by_node(it, new Node(std::forward<Args>(args)...)); }
    template<class... Args >
    void emplace_front(Args&&... args) { push_front_by_node(new Node(std::forward<Args>(args)...)); }
    template<class... Args >
    void emplace_back(Args&&... args) { push_back_by_node(new Node(std::forward<Args>(args)...)); }
    void unique()
    {
        if (lenght == 0)
            return;
        Node* iter = start->next;
        Node* previous = start;
        while (iter != nullptr)
        {
            if (previous->value == iter->value)
                erase(const_iterator(this, previous));
            previous = iter;
            iter = iter->next;
        }
    }
    void reverse()
    {
        if (lenght == 0)
            return;
        auto my_swap = [](Node*& a, Node*& b)
        {
            Node* old_a = a;
            a = b;
            b = old_a;
        };
        Node* node = start;
        while (node != nullptr)
        {
            my_swap(node->previous, node->next);
            node = node->previous;
        }
        my_swap(start, finish);
    }
    void PrintList() const
    {
        Node* current = start;
        while (current != nullptr)
        {
            std::cout << current->value << " <-> ";
            current = current->next;
        }
        std::cout << "END" << std::endl;
    }
};