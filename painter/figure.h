#ifndef FIGURE_H
#define FIGURE_H

#include <QPointF>
#include <QPolygonF>
#include <QPainter>
#include <QDataStream>

enum class FigureType{None, Triangle, Rectangle, Ellipse};

class Figure{
public:
    Figure() = default;
    virtual void draw(QPainter& painter) const = 0;
    virtual void updateStartFigPoint(const QPointF& pnt) = 0;
    virtual void updateEndFigPoint(const QPointF& pnt) = 0;
    virtual void updateFigCoords() = 0;
    virtual bool isContainsPoint(const QPointF& pnt) const = 0;
    virtual QPointF calculateOffset(const QPointF& pnt) const = 0;
    virtual void translate(const QPointF& curr_pnt, const QPointF& offset) = 0;
    virtual void serialize(QDataStream& out) const = 0;
    virtual void deserialize(QDataStream& in) = 0;
    virtual QPointF getCentralPoint() const = 0;
    virtual ~Figure() = default;

protected:
    QPointF start_pnt, end_pnt; // start and end pnts for figure box
    QPolygonF figure_polygon;
    FigureType fig_type;
};

#endif // FIGURE_H
