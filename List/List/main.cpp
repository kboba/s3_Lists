#include "List.h"

int main()
{
    std::vector<Point>points;
    int i;
    List lista;
    for (i = 1; i <= 100000; i++)
    {
        points.push_back(Point(i, 2 * i, 3 * i));
    }

    while (true)
    {
        for (i = 0; i < 100000; i++)
        {
            lista.push_back(points[i]);
        }
        for (i = 0; i < 100000; i++)
        {
            lista.pop_back();
        }
    }

    system("pause");
    return 0;
}
