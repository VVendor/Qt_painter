#include "ellipse.h"
#include <QtMath>

Ellipse::Ellipse(): Figure()
{
    fig_type = FigureType::Ellipse;
}

void Ellipse::draw(QPainter& painter) const
{
    painter.drawPolygon(figure_polygon);
}

void Ellipse::updateStartFigPoint(const QPointF& pnt)
{
    start_pnt = pnt;
}
void Ellipse::updateEndFigPoint(const QPointF& pnt)
{
    end_pnt = pnt;
}

void Ellipse::updateFigCoords()
{
    figure_polygon.clear();
    QRectF rect(start_pnt, end_pnt);
    rect = rect.normalized();

    for (int idx = 0; idx < points_num; idx++)
    {
        qreal angle = 2 * M_PI * idx / points_num;
        qreal x = rect.center().x() + rect.width() / 2 * qCos(angle);
        qreal y = rect.center().y() + rect.height() / 2 * qSin(angle);
        figure_polygon << QPointF(x, y);
    }
}

bool Ellipse::isContainsPoint(const QPointF& pnt) const
{
    return figure_polygon.containsPoint(pnt, Qt::OddEvenFill);
}

QPointF Ellipse::calculateOffset(const QPointF& pnt) const
{
    return pnt - figure_polygon.boundingRect().topLeft();
}

void Ellipse::translate(const QPointF& curr_pnt, const QPointF& offset)
{
    figure_polygon.translate(curr_pnt - offset - figure_polygon.boundingRect().topLeft());
}

void Ellipse::serialize(QDataStream& out) const
{
    out<<fig_type<<start_pnt<<end_pnt<<figure_polygon;
}

void Ellipse::deserialize(QDataStream& in)
{
    in>>start_pnt>>end_pnt>>figure_polygon;
}

QPointF Ellipse::getCentralPoint() const
{
    return figure_polygon.boundingRect().center();
}

Ellipse::~Ellipse()
{
    figure_polygon.clear();
}
