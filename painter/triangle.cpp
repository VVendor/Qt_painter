#include "triangle.h"
#include <algorithm>

Triangle::Triangle(): Figure()
{
    fig_type = FigureType::Triangle;
}

void Triangle::draw(QPainter& painter) const
{
    painter.drawPolygon(figure_polygon);
}

void Triangle::updateStartFigPoint(const QPointF& pnt)
{
    start_pnt = pnt;
}
void Triangle::updateEndFigPoint(const QPointF& pnt)
{
    end_pnt = pnt;
}

void Triangle::updateFigCoords()
{
    figure_polygon.clear();
    QRectF rect(start_pnt, end_pnt);
    rect = rect.normalized();
    figure_polygon<<rect.bottomLeft()<<(rect.topLeft()+rect.topRight())/2<<rect.bottomRight();
}

bool Triangle::isContainsPoint(const QPointF& pnt) const
{
    return figure_polygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Triangle::calculateOffset(const QPointF& pnt) const
{
    return pnt - figure_polygon.boundingRect().topLeft();
}

void Triangle::translate(const QPointF& curr_pnt, const QPointF& offset)
{
    figure_polygon.translate(curr_pnt - offset - figure_polygon.boundingRect().topLeft());
}

void Triangle::serialize(QDataStream& out) const
{
    out<<fig_type<<start_pnt<<end_pnt<<figure_polygon;
}

void Triangle::deserialize(QDataStream& in)
{
    in>>start_pnt>>end_pnt>>figure_polygon;
}

QPointF Triangle::getCentralPoint() const
{
    return figure_polygon.boundingRect().center();
}

Triangle::~Triangle()
{
    figure_polygon.clear();
}
