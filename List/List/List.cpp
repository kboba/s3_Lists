
#include "List.h"


List::List() : size(0), first(nullptr) {}

List::List(const List & list) : size(list.size), first(nullptr)
{
    Node * node = list.first;
    Node * last = first;
    if (node)
    {
        first = new Node(node->point);
        node = node->next;
        last = first;
    }
    while (node)
    {
        last->next = new Node(node->point);
        last = last->next;
        node = node->next;
    }
}

List::List(const std::vector<Point>& points) : size(0), first(nullptr)
{
    Point p;
    for (std::vector<Point>::const_iterator i = points.begin(); i != points.end(); ++i)
    {
        p = *i;
        push_back(p);
    }
}



List::~List()
{
    size_t size_before = get_size();
    for (size_t i = 0; i < size_before; i++)
    {
        pop_back();
    }
}


size_t List::get_size()
{
    return size;
}


List::Node * List::find(const size_t idx)
{
    Node * node = first;

    for (size_t i = 0; i < idx; i++)
    {
        node = node->next;
    }

    return node;
}


List::Error List::find(Point &p, size_t idx)
{
    if (size == 0)
        return Error::LIST_EMPTY;
    if (idx >= size || idx < 0)
        return Error::INDEX_OUT_OF_BOUNDS;

    Node * node = find(idx);
    p = node->point;

    return Error::SUCCESS;
}



void List::push(const Point & point, const size_t idx)
{
    if (idx == 0)
    {
        Node * tail = first;
        first = new Node(point);
        first->next = tail;
    }
    else
    {
        Node * prev = find(idx - 1);
        Node * tail = prev->next;
        prev->next = new Node(point);
        prev->next->next = tail;
    }
    size++;
}


void List::push(const List & list, const size_t idx)
{
    List copy(list);
    Node * node = copy.first;
    if (idx == 0)
    {
        Node * tail = first;
        Node * last = first;
        if (node)
        {
            first = new Node(node->point);
            node = node->next;
            last = first;
        }
        while (node)
        {
            last->next = new Node(node->point);
            last = last->next;
            node = node->next;
        }
        last->next = tail;
    }
    else
    {
        Node * prev = find(idx-1);
        Node * tail = prev->next;
        while (node)
        {
            prev->next = new Node(node->point);
            node = node->next;
            prev = prev->next;
        }
        prev->next = tail;
    }

    size += list.size;
}


void List::pop(const size_t idx)
{
    if (idx == 0)
    {
        Node * tail = first->next;
        delete first;
        first = tail;	
    }
    else
    {
        Node * prev = find(idx - 1);
        Node * tail = prev->next->next;
        delete prev->next;
        prev->next = tail;
    }
    size--;
}



List::Error List::pop_back()
{
    if (size == 0)
        return Error::LIST_EMPTY;

    Node* pre_last = find(size-2);
    delete pre_last->next;
    pre_last->next = nullptr;
    
    size--;
    return Error::SUCCESS;
}



List::Error List::push_back(const Point& p)
{
    if (size == 0)
    {
        first = new Node(p);
        first->next = nullptr;
    }
    else
    {
        Node* prev = find(size-1);
        prev->next = new Node(p);
        prev->next->next = nullptr;
    }

    size++;
    return Error::SUCCESS;
}



List::Error List::insert(Point p, size_t idx)
{
    if (idx > size || idx < 0)
        return Error::INDEX_OUT_OF_BOUNDS;
    
    if (idx == 0)
    {
        Node* tail = first;
        first = new Node(p);
        first->next = tail;
    }
    else
    {
        Node* node = find(idx - 1);
        Node* tail = node->next;
        node->next = new Node(p);
        node->next->next = tail;
    }

    return Error::SUCCESS;
}




void List::Multiply(const int x)
{
    Node* node = first;
    for (size_t i = 0; i < size; i++)
    {
        node->point = Point(node->point.x * x, node->point.y * x, node->point.z * x);
        node = node->next;
    }
}



void List::Concat(List& list)
{
    List copy(list);

    Node* last = copy.find(copy.size);
    Node* node = copy.first;

    while (node)
    {
        last->next = new Node(node->point);
        last = last->next;
        node = node->next;
        list.size++;
    }

    last->next = nullptr;
}



List & List::operator=(const List &list)
{
    List copy(list);
    this->~List();
    push(copy, size);
    return *this;
}



List List::operator--()
{
    List copy(*this);
    this->pop_back();
    return copy;
}



List & List::operator+=(const List & list)
{
    push(list, size);
    return *this;
}



List List::operator+(const List & list)
{
    List copy(*this);
    copy.push(list, copy.size);
    return copy;
}



List List::operator*(const int x)
{
    List copy(*this);
    for (int i = 0; i < x; i++)
        copy.push(*this, size);
    
    return copy;
}


Point & List::operator[](const size_t idx)
{
    Point p;
    find(p, idx);
    return p;
}


void List::operator++(int)
{
    /*this->~List();*/
    // destruktor listy, zwracam kopie;
    size_t size_before = /*this->*/get_size();
    for (size_t i = 1; i <= size_before; i++)
    {
        /*this->*/pop_back();
    }
}



std::ostream& operator<<(std::ostream& output, const List& list)
{
    List copy(list);
    Point p;
    for (size_t i = 1; i <= copy.size; i++)
    {
        copy.find(p, i);
        output << "Point " << i << ": " << p.x << "," << p.y << "," << p.z << std::endl;
    }

    return output;
}
