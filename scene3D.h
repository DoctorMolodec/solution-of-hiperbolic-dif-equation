#ifndef SCENE3D_H
#define SCENE3D_H

#include <QWidget>
#include <QMouseEvent>
#include <QAction>
#include <QString>
#include <QtOpenGL>
#include <QKeyEvent>
#include <QPainter>

extern "C"
{
#include "interpolation2.h"
}

class Scene3D
    : public QOpenGLWindow, protected QOpenGLFunctions // класс Scene3D наследует встроенный класс QGLWidget
{
    GLfloat xRot; // переменная хранит угол поворота вокруг оси X
    GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
    GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
    GLfloat zTra; // переменная хранит величину трансляции оси Z
    GLfloat nSca; // переменная отвечает за масштабирование обьекта



protected:
    void initializeGL(); // метод для проведения инициализаций, связанных с OpenGL
    void resizeGL(int nWidth=1000, int nHeight=800); // метод вызывается при изменении размеров окна виджета
    void paintGL(); // метод, чтобы заново перерисовать содержимое виджета
    void drawFigure(); // построить фигуру
    void draw_f();


    double x_a, x_b, y_a, y_b, x_a1, x_b1, y_a1, y_b1, nu;
    int  n_x, n_y, n_x1, n_y1;
    const char* function_name;
    const char* function_name1;
    const char* function_name2;
    double last_sup, last_inf;
    double sup, inf;
    double scale;
    int k;
    int k1;
    int k2;
    //double nu;
    interpolation2_ctx ctx1;


    //QColor colors[5];



    double method(double x, double y);




    void keyPressEvent(QKeyEvent* pe); // методы обработки события при нажатии определенной клавиши

public slots:

    void rotate_up(); // повернуть сцену вверх
    void rotate_down(); // повернуть сцену вниз
    void rotate_left(); // повернуть сцену влево
    void rotate_right(); // повернуть сцену вправо

    void new_interpolation2(int n_x, int n_y, int k,
    int k1, int k2, double nu, double x_a, double x_b, double y_a, double y_b);
    void change_function();
    void change_function2();
    void change_function1();
    void plus_change_nu();
    void minus_change_nu();

    void zoom_in();
    void zoom_out();
    void double_n();
    void half_n();
    void rotate_z(int factor);
public:
    Scene3D(int n_x, int n_y, int k,
            int k1, int k2, double nu,
            double x_a, double x_b, double y_a, double y_b); // конструктор класса
    ~Scene3D();

};
#endif
