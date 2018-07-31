#include "cell.h"

cell::cell(QPoint& _location, QPointF& _position, int _color)
{
    location = _location;
    position = _position;
    color = _color;
}

cell& cell::copy(const cell& c)
{
    color = c.color;
    position = c.position;
    location = c.location;

    return *this;
}

QColor cell::draw_cell_color() const
{
    QColor qcolor;
    switch(color)
    {
    case RED:
        qcolor = QColor("red");
        break;
    case YELLOW:
        qcolor = QColor("yellow");
        break;
    case BLUE:
        qcolor = QColor("blue");
        break;
    case GREEN:
        qcolor = QColor("green");
        break;
    case BLACK:
        qcolor = QColor("black");
        break;
    case PURPLE:
        qcolor = QColor("purple");
        break;
    case ORANGE:
        qcolor = QColor("orange");
        break;
    case GREY:
        qcolor = QColor("grey");
        break;
    default:
        qcolor = QColor("transparent");
        break;
    }

    return qcolor;
}

cell::~cell()
{

}
