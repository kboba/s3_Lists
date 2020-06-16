#pragma once
#include <vector>
#include <iostream>
#include "Point.h"

class List
{
    struct Node
    {
        Point point;
        Node * next;
        Node(const Point &p) : point(p.x, p.y, p.z), next(nullptr){}
    };
    Node * first;
    size_t size;

    Node * find(const size_t);
    void push(const Point &, const size_t);
    void push(const List &, const size_t);
    void pop(const size_t);
    void Multiply(const int x);

public:
    enum class Error
    {
        SUCCESS,
        INDEX_OUT_OF_BOUNDS,
        LIST_EMPTY
    };

    List();
    List(const List& list);
    List(const std::vector<Point>& points);
    ~List();

    size_t get_size();
    Error pop_back();
    Error push_back(const Point& p);
    Error insert(Point p,size_t idx);
    Error find(Point &p,size_t idx);
    void Concat(List&);


    List& operator= (const List& list);
    List operator-- ();
    List& operator+= (const List& list);
    List operator+ (const List& list);
    List operator*(const int x);
    Point& operator[] (const size_t idx);
    void operator++(int);
    friend std::ostream& operator<<(std::ostream& output, const List& list);
};
