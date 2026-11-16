
#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
using namespace std;

struct Point
{
    int x, y;
};

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawLine(Point start, Point end)
{
    int x = start.x;
    int y = start.y;

    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);

    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        gotoxy(x, y);
        cout << "*";

        if (x == end.x && y == end.y)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

class Shape
{
protected:
    string type;

public:
    Shape(string type)
    {
        this->type = type;
    }

    virtual void Print() = 0;

    virtual ~Shape()
    {
    }
};

class Line : public Shape
{
private:
    Point start;
    Point end;

public:
    Line(Point start, Point end) : Shape("Line")
    {
        this->start = start;
        this->end = end;
    }

    void Print() override
    {
        cout << type << endl;
        DrawLine(start, end);
    }
};

class MyRectangle : public Shape
{
private:
    Point topLeft;
    int width;
    int length;

public:
    MyRectangle(Point topLeft, int width, int length)
        : Shape("Rectangle")
    {
        this->topLeft = topLeft;
        this->width = width;
        this->length = length;
    }

    void Print() override
    {
        cout << type << endl;

        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || i == length - 1 ||
                    j == 0 || j == width - 1)
                {
                    gotoxy(topLeft.x + j, topLeft.y + i);
                    cout << "*";
                }
            }
        }
    }
};

class MyPolyline : public Shape
{
private:
    Point* points;
    int count;

public:
    MyPolyline(Point points[], int count) : Shape("Polyline")
    {
        this->count = count;
        this->points = new Point[count];

        for (int i = 0; i < count; i++)
        {
            this->points[i] = points[i];
        }
    }

    void Print() override
    {
        cout << type << endl;

        for (int i = 0; i < count - 1; i++)
        {
            DrawLine(points[i], points[i + 1]);
        }

        if (count == 1)
        {
            gotoxy(points[0].x, points[0].y);
            cout << "*";
        }
    }

    ~MyPolyline()
    {
        delete[] points;
    }
};

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Shape* shapes[3];

    Point p1 = { 5, 5 };
    Point p2 = { 30, 15 };

    Point p3 = { 40, 5 };

    Point polyPoints[] =
    {
        { 5, 20 },
        { 10, 17 },
        { 15, 20 },
        { 20, 17 },
        { 25, 20 }
    };

    shapes[0] = new Line(p1, p2);
    shapes[1] = new MyRectangle(p3, 15, 8);
    shapes[2] = new MyPolyline(polyPoints, 5);

    for (int i = 0; i < 3; i++)
    {
        shapes[i]->Print();
        cout << endl;
    }

    for (int i = 0; i < 3; i++)
    {
        delete shapes[i];
    }

    gotoxy(0, 30 );
}
