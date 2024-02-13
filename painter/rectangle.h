#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure
{
public:
    Rectangle();
    void draw(QPainter& painter) const override;
    void updateStartFigPoint(const QPointF& pnt) override;
    void updateEndFigPoint(const QPointF& pnt) override;
    void updateFigCoords() override;
    bool isContainsPoint(const QPointF& pnt) const override;
    QPointF calculateOffset(const QPointF& pnt) const override;
    void translate(const QPointF& curr_pnt, const QPointF& offset) override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;
    QPointF getCentralPoint() const override;
    ~Rectangle();
};

#endif // RECTANGLE_H
