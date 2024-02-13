#include "rectangle.h"
#include <algorithm>

Rectangle::Rectangle():Figure()
{
    fig_type = FigureType::Rectangle;
}
void Rectangle::draw(QPainter& painter) const
{
    painter.drawPolygon(figure_polygon);
}

void Rectangle::updateStartFigPoint(const QPointF& pnt)
{
    start_pnt = pnt;
}
void Rectangle::updateEndFigPoint(const QPointF& pnt)
{
    end_pnt = pnt;
}

void Rectangle::updateFigCoords()
{
    figure_polygon.clear();
    QRectF rect(start_pnt, end_pnt);
    rect = rect.normalized();
    figure_polygon<<rect.bottomLeft()<<rect.bottomRight()<<rect.topRight()<<rect.topLeft();
}

bool Rectangle::isContainsPoint(const QPointF& pnt) const
{
    return figure_polygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Rectangle::calculateOffset(const QPointF& pnt) const
{
    return pnt - figure_polygon.boundingRect().topLeft();
}

void Rectangle::translate(const QPointF& curr_pnt, const QPointF& offset)
{
    figure_polygon.translate(curr_pnt - offset - figure_polygon.boundingRect().topLeft());
}

void Rectangle::serialize(QDataStream& out) const
{
    out<<fig_type<<start_pnt<<end_pnt<<figure_polygon;
}

void Rectangle::deserialize(QDataStream& in)
{
    in>>start_pnt>>end_pnt>>figure_polygon;
}

QPointF Rectangle::getCentralPoint() const
{
    return figure_polygon.boundingRect().center();
}

Rectangle::~Rectangle()
{
    figure_polygon.clear();
}
