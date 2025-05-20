//#include <QtGui> //importing the QtGui module
#include "scene3D.h"
#include <math.h> //importing the math library

#define N 1000

const static float pi = 3.141593, k = pi / 180; //global variable



Scene3D::Scene3D(int n_x, int n_y, int k, int k1, int k2, double nu,
                double x_a, double x_b, double y_a, double y_b)
    : xRot(-90), yRot(0), zRot(90), zTra(0), nSca(0.8),
    x_a(x_a), x_b(x_b), y_a(y_a), y_b(y_b), n_x(n_x), n_y(n_y),k(k),k1(k1),k2(k2),nu(nu),
    ctx1(interpolation2_create(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b))
{
    x_a1 = x_a;
    x_b1 = x_b;
    y_a1 = y_a;
    y_b1 = y_b;



    draw_f();
    update();
}

void Scene3D::change_function()
{
    k = (k + 1) % 8;
    draw_f();
}
void Scene3D::change_function1()
{
    k1 = (k1 + 1) % 8;
    draw_f();
}
void Scene3D::change_function2()
{
    k2 = (k2 + 1) % 8;
    draw_f();
}


double Scene3D::method(double x, double y)
{
    double res;
    res = interpolation2_calculate(ctx1, x, y);
    if (fabs(res) < 1e-15)
    {
        res = 0;
    }
    return res;
}




void Scene3D::draw_f()
{
    scale = 1;
    new_interpolation2(n_x, n_y, k, k1, k2, nu , x_a, x_b, y_a, y_b);
    x_a1 = x_a;
    x_b1 = x_b;
    y_a1 = y_a;
    y_b1 = y_b;
    last_inf = 0;
    last_sup = 0;

    switch (k1)
    {
    case 0:
        function_name1 = "a(t) = 1";
        break;
    case 1:
        function_name1 = "a(t) = 0";
        break;
    case 2:
        function_name1 = "a(t) = cos t";
        break;
    case 3:
        function_name1 = "a(t) = t";
        break;
    case 4:
        function_name1 = "a(t) = sqrt(t)";
        break;
    case 5:
        function_name1 = "a(t) = t * t";
        break;
    case 6:
        function_name1 = "a(t) = exp(t)";
        break;
    case 7:
        function_name1 = "a(t) = 1/(25*t*t+1)";
        break;
    }

    switch (k2)
    {
    case 0:
        function_name2 = "b(t) = 1";
        break;
    case 1:
        function_name2 = "b(t) = 0";
        break;
    case 2:
        function_name2 = "b(t) = cos t";
        break;
    case 3:
        function_name2 = "b(t) = t";
        break;
    case 4:
        function_name2 = "b(t) = sqrt(t)";
        break;
    case 5:
        function_name2 = "b(t) = t * t";
        break;
    case 6:
        function_name2 = "b(t) = exp(t)";
        break;
    case 7:
        function_name2 = "b(t) = 1/(25*t*t+1)";
        break;
    }

    switch (k)
    {
    case 0:
        function_name = "u0(x) = 1";
        break;
    case 1:
        function_name = "u0(x) = 0";
        break;
    case 2:
        function_name = "u0(x) = cos x";
        break;
    case 3:
        function_name = "u0(x) = x";
        break;
    case 4:
        function_name = "u0(x) = sqrt(x)";
        break;
    case 5:
        function_name = "u0(x) = x * x";
        break;
    case 6:
        function_name = "u0(x) = exp(x)";
        break;
    case 7:
        function_name = "u0(x) = 1/(25*x*x+1)";
        break;
    }

    update();
}

void Scene3D::initializeGL() // initialization
{
    initializeOpenGLFunctions();

    // just the window backgroun
    glClearColor(255,255,255,1); // color for clearing the image buffer - here
    glEnable(GL_DEPTH_TEST); // sets the pixel depth checking mode
    glShadeModel(GL_FLAT); // disables color smoothing mode
    glEnable(GL_CULL_FACE); // sets the mode where only
    // external surfaces are drawn
}



/*virtual*/ void Scene3D::resizeGL(int nWidth, int nHeight) // widget window
{
    glMatrixMode(GL_PROJECTION); // sets the current projection matrix
    glLoadIdentity(); // assigns the identity matrix to the projection matrix
    GLfloat ratio =
        (GLfloat)nHeight /
        (GLfloat)nWidth; // ratio of widget window height to its width

    // world window
    if (nWidth >= nHeight)
        glOrtho(-1.0 / ratio, 1.0 / ratio, -1.0, 1.0, -10.0, 1.0); // visibility parameters for orthogonal projection
    else
        glOrtho(-1.0, 1.0, -1.0 * ratio, 1.0 * ratio, -10.0, 1.0); // visibility parameters for orthogonal projection
    // clipping planes (left, right, top, bottom, near, far)

    // viewport
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}



/*virtual*/ void Scene3D::paintGL() // drawing
{


    // glClear(GL_COLOR_BUFFER_BIT); // widget window is cleared with the current color
    // of clearing
    glClear(GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT); // clearing the image and depth buffers

    glMatrixMode(GL_MODELVIEW); // sets the position and orientation of the model matrix
    glLoadIdentity(); // loads the identity model matrix

    // sequential transformations
    glScalef(nSca, nSca, nSca); // scaling
    glTranslatef(0.0f, zTra, 0.0f); // translation
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // rotation around X axis
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // rotation around Y axis
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // rotation around Z axis

    //drawAxis(); // drawing coordinate axes
    drawFigure(); // draw figure


}



void Scene3D::drawFigure() // build the figure
{

    double x1 = x_a1, y1 = y_a1, z1;
    double s_x = (x_b1 - x_a1) / N;
    double s_y = (y_b1 - y_a1) / N;
    double abs_max = 1;
    double s;
    sup = 0;
    inf = 0;
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = 0; j < N + 1; j++)
        {

            z1 = (this->method)(x1, y1);

            if (z1 >= sup)
            {
                sup = z1;
            }
            if (z1 <= inf)
            {
                inf = z1;
            }
            y1 = y1 + s_y;
            
        }
        x1 = x1 + s_x;
        y1 = y_a1;
       

    }
    abs_max = fmax(fabs(sup), fabs(inf));
    if (abs_max < 1e-15)
    {
        abs_max = 10;
    }


    s=fmin((x_b1 - x_a1),(y_b1 - y_a1));
    glScalef(nSca / s, nSca / s, nSca / abs_max);
    glTranslatef(-(x_a1 + x_b1) / 2, -(y_a1 + y_b1) / 2, -abs_max / 2);



    glLineWidth(2.0f); // set line width approximately in pixels.
    // before calling the command the width is equal to one pixel by default.

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // sets the color of subsequent primitives.
    // axis X.
    glBegin(GL_LINES); 
    if (x_a1 * x_b1 > 0)
    {
        if (x_a1 > 0)
        {
            glVertex3f(0, 0.0f, 0.0f); //  first point.
            glVertex3f(2 * x_b1, 0.0f, 0.0f); // second point.
        }
        else
        {
            glVertex3f(2 * x_a1, 0.0f, 0.0f); // first point.
            glVertex3f(0, 0.0f, 0.0f); // second point.
        }
    }
    else
    {
        glVertex3f(2 * x_a1, 0.0f, 0.0f); // first point.
        glVertex3f(2 * x_b1, 0.0f, 0.0f); // second point.
    }
    // axis Y.
    if (y_a1 * y_b1 > 0)
    {
        if (y_a1 > 0)
        {
            glVertex3f(0, 0.0f, 0.0f); // first point.
            glVertex3f(0, 2 * y_b1, 0.0f); // second point.
        }
        else
        {
            glVertex3f(0, 2 * y_a1, 0.0f); // first point.
            glVertex3f(0, 0.0f, 0.0f); // second point.
        }
    }
    else
    {
        glVertex3f(0, 2 * y_a1, 0.0f); // first point.
        glVertex3f(0, 2 * y_b1, 0.0f); // second point.
    }
    //axis Z.
    glVertex3f(0.0f, 0.0f, abs_max);
    glVertex3f(0.0f, 0.0f, -abs_max);
    glEnd();


    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.2f, 3.0f, 0.3f, 0.7);
    glBegin(GL_TRIANGLES);
    x1 = x_a1 + s_x;
    y1 = y_a1 + s_y;
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {

            glColor4f((x_a1 + x1) / (x_b1 - x_a1) / 2 + 0.5, (y_a1 + y1) / (y_b1 - y_a1) / 2 + 0.5, 0.5f, 0.7);
            glVertex3f(x1 - s_x, y1, (this->method)(x1 - s_x, y1));
            glVertex3f(x1 - s_x, y1 - s_y, (this->method)(x1 - s_x, y1 - s_y));
            glVertex3f(x1, y1, (this->method)(x1, y1));
            glVertex3f(x1, y1 - s_y, (this->method)(x1, y1 - s_y));
            glVertex3f(x1, y1, (this->method)(x1, y1));
            glVertex3f(x1 - s_x, y1 - s_y, (this->method)(x1 - s_x, y1 - s_y));
            y1 = y1 + s_y;

        }
        x1 = x1 + s_x;
        y1 = y_a1 + s_y;
    }

    glEnd();
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(0, 20, "nu-: Tab");
    painter.drawText(50, 20, "nu+: 1");
    painter.drawText(90, 20, "Increase scale: 2");
    painter.drawText(200, 20, "Decrease scale: 3");
    painter.drawText(310, 20, "Double points: 4");
    painter.drawText(415, 20, "Half points: 5");
    painter.drawText(500, 20, "Next a(t): 8");
    painter.drawText(600, 20, "Next b(t): 9");
    painter.drawText(700, 20, "Next u0: 0");
    painter.drawText(800, 20, "Exit: Esc");

    painter.setPen(Qt::blue);
    painter.drawText(0, 40, function_name);
    painter.drawText(100, 40, function_name1);
    painter.drawText(200, 40, function_name2);
    painter.drawText(330, 40, "u_t=nu*u_xx+u*u_x");
    painter.drawText(0, 60, "n_x = " + QString::number(n_x));
    painter.drawText(100, 60, "n_t = " + QString::number(n_y));
    painter.drawText(0, 80, "nu = " + QString::number(nu));
    painter.drawText(0, 100, "scale = " + QString::number(scale));
    painter.drawText(0, 120, "angle = " + QString::number(zRot - 360 * floor(zRot / 360)) + " degree");
    painter.setPen(Qt::red);
    painter.drawText(0, 140, "max = " + QString::number(sup));
    painter.drawText(0, 160, "min = " + QString::number(inf));
    painter.drawText(0, 180, "x: (" + QString::number(x_a1) + ", " + QString::number(x_b1) + ")");
    painter.drawText(0, 200, "t: (" + QString::number(y_a1) + ", " + QString::number(y_b1) + ")");
    painter.end();
}

void Scene3D::zoom_in()
{
    scale *= 2;
    double x2_a, x2_b, y2_a, y2_b;
    x2_a = (x_a1 + x_b1) / 2 - (x_b1 - x_a1) / 4;
    x2_b = (x_a1 + x_b1) / 2 + (x_b1 - x_a1) / 4;
    x_a1 = x2_a;
    x_b1 = x2_b;

    y2_a = (y_a1 + y_b1) / 2 - (y_b1 - y_a1) / 4;
    y2_b = (y_a1 + y_b1) / 2 + (y_b1 - y_a1) / 4;
    y_a1 = y2_a;
    y_b1 = y2_b;

    last_inf = 0;
    last_sup = 0;

    update();
}

void Scene3D::zoom_out()
{
    scale /= 2;
    double x2_a, x2_b, y2_a, y2_b;
    x2_a = (x_a1 + x_b1) / 2 - (x_b1 - x_a1);
    x2_b = (x_a1 + x_b1) / 2 + (x_b1 - x_a1);
    x_a1 = x2_a;
    x_b1 = x2_b;

    y2_a = (y_a1 + y_b1) / 2 - (y_b1 - y_a1);
    y2_b = (y_a1 + y_b1) / 2 + (y_b1 - y_a1);
    y_a1 = y2_a;
    y_b1 = y2_b;

    last_inf = 0;
    last_sup = 0;

    update();
}

void Scene3D::double_n()
{
    n_x *= 2;
    n_y *= 2;
    new_interpolation2(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);
    last_inf = inf;
    last_sup = sup;
    update();
}

void Scene3D::half_n()
{
    n_x /= 2;
    n_x = fmax(n_x, 5);

    n_y /= 2;
    n_y = fmax(n_y, 5);
    new_interpolation2(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);
    last_inf = inf;
    last_sup = sup;
    update();
}

void Scene3D::rotate_z(int factor) {
    zRot += factor * 15;
}


void Scene3D::rotate_up() 
{
    xRot += 15.0;
}

void Scene3D::rotate_down()
{
    xRot -= 15.0;
}

void Scene3D::rotate_left() 
{
    zRot += 1.0;
}

void Scene3D::rotate_right() 
{
    zRot -= 1.0;
}

void Scene3D::plus_change_nu()
{
    nu=nu+0.01;
    if(fabs(nu)<1e-15)
    {
        nu=0;
    }
    new_interpolation2(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);
    update();
}
void Scene3D::minus_change_nu()
{
    nu=nu-0.01;
    if(nu<1e-15)
    {
        nu=0;
    }
    new_interpolation2(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);
    update();
}

void Scene3D::keyPressEvent(QKeyEvent* pe) // key press event
{
    switch (pe->key())
    {
    case Qt::Key_Up:
        rotate_up(); // rotate the scene up
        break;

    case Qt::Key_Down:
        rotate_down(); // rotate the scene down
        break;

    case Qt::Key_Left:
        rotate_left(); // rotate the scene left
        break;

    case Qt::Key_Right:
        rotate_right(); // rotate the scene right
        break;

    case Qt::Key_Escape: // escape key
        this->close(); // close the application
        break;

    case Qt::Key_0:
        this->change_function();
        break;

    case Qt::Key_1:
        this->plus_change_nu();
        break;
    case Qt::Key_Tab:
        this->minus_change_nu();
        break;

    case Qt::Key_2:
        this->zoom_in();
        break;

    case Qt::Key_3:
        this->zoom_out();
        break;

    case Qt::Key_4:
        this->double_n();
        break;

    case Qt::Key_5:
        this->half_n();
        break;

    case Qt::Key_8:
        this->change_function1();
        break;

    case Qt::Key_9:
        this->change_function2();
        break;
    }

    update();
}



void Scene3D::new_interpolation2(int n_x, int n_y, int k, int k1, int k2, double nu, double x_a, double x_b, double y_a, double y_b)
{
    interpolation2_ctx t = interpolation2_create(n_x, n_y, k, k1, k2, nu, x_a, x_b, y_a, y_b);
    interpolation2_destroy(ctx1);
    ctx1 = t;
}

Scene3D::~Scene3D()
{
    interpolation2_destroy(ctx1);
}
