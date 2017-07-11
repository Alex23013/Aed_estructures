#ifndef CITYGRAPH_H
#define CITYGRAPH_H
#include "Cgraph.h"

#include <QPoint>

class CCityGraph :public cGraph<QPoint, int>
{
public:

    void GeneradorNodos(int numero)
    {
        int i = 0;
        int x_init = 0; int y_init = 0;
        QPoint n;
        n.setX(x_init); n.setY(y_init);
        insert_nodo(n);
        //int array_x[9] = { 1,3,-2,2,0,3,4,-1,-4 };
        //int array_y[9] = { -2,0,-3,-1,1,2,3,4,-4 };
        int semilla = numero / 5;

        while (i < numero)
        {
            //n.setX(n.x() + array_x[i % 9]);
            //n.setY(n.y() + array_y[i % 9]);


            n.setX(rand() % semilla);
            n.setY(rand() % semilla);

            if (insert_nodo(n))
            {
                ++i;
            }
        }
    }
};

#endif // CITYGRAPH_H
