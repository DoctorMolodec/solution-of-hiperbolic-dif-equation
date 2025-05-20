#include "scene3D.h"
#include <QApplication>
//#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QAction>
#include <iostream>


//initially, a request is entered from the console in the form 1 100 100 4 -1 1 -10 10 where
//1 is the method, 100 and 100 are the number of interpolation points in x and y respectively
//4 is the interpolated function from the list, -1 1 is the interval for x, -10 10 is the interval for y
int main(int argc, char** argv)
{ 
    //below, checks are performed for data correctness
    //both by type and by value
    double x_a, x_b, y_a, y_b, nu;
    int n_x, n_y, k, k1, k2;

    if (argc < 11)
    {
        std::cout << "Not enough arguments" << std::endl;
        return -1;
    }
    else
        if (argc > 11)
        {
            std::cout << "Exceeding the number of arguments" << std::endl;
            return -1;
        }



    if (sscanf(argv[1], "%d", &n_x) != 1)
    {
        std::cout << "Error in the data type in the amount of points" << std::endl;
        return -1;
    }
    else
        if (n_x < 5)
        {
            std::cout << "Not enough amount of points" << std::endl;
            return -1;
        }
    if (sscanf(argv[2], "%d", &n_y) != 1)
    {
        std::cout << "Error in the data type in the amount of points" << std::endl;
        return -1;
    }
    else
        if (n_y < 5)
        {
            std::cout << "Not enough amount of points" << std::endl;
            return -1;
        }

    if (sscanf(argv[3], "%d", &k) != 1)
    {
        std::cout << "Error in the data type in the function" << std::endl;
        return -1;
    }
    else
        if ((k < 0) || (k > 7))
        {
            std::cout << "Invalid function" << std::endl;
            return -1;
        }

    if (sscanf(argv[4], "%d", &k1) != 1)
    {
        std::cout << "Error in the data type in the function" << std::endl;
        return -1;
    }
    else
        if ((k1 < 0) || (k1 > 7))
        {
            std::cout << "Invalid function" << std::endl;
            return -1;
        }

    if (sscanf(argv[5], "%d", &k2) != 1)
    {
        std::cout << "Error in the data type in the function" << std::endl;
        return -1;
    }
    else
        if ((k2 < 0) || (k2 > 7))
        {
            std::cout << "Invalid function" << std::endl;
            return -1;
        }

    if (sscanf(argv[6], "%lf", &nu) != 1)
    {
        std::cout << "Error in the data type in the function" << std::endl;
        return -1;
    }


    if (sscanf(argv[7], "%lf", &x_a) != 1 || sscanf(argv[8], "%lf", &x_b) != 1)
    {
        std::cout << "Error in the data type in the segment" << std::endl;
        return -1;
    }
    else
        if (x_a > x_b || x_b - x_a > 1e9 || x_b - x_a < 1e-6)
        {
            std::cout << "Incorrect segment" << std::endl;
            return -1;
        }
    if (sscanf(argv[9], "%lf", &y_a) != 1 || sscanf(argv[10], "%lf", &y_b) != 1)
    {
        std::cout << "Error in the data type in the segment" << std::endl;
        return -1;
    }
    else
        if (y_a > y_b || y_b - y_a > 1e9 || y_b - y_a < 1e-6)
        {
            std::cout << "Incorrect segment" << std::endl;
            return -1;
        }

    QApplication app(argc, argv);
    Scene3D scene1(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);

    scene1.show(); 


    return app.exec();
}
