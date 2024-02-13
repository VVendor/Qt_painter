#ifndef FIGURECONNECTOR_H
#define FIGURECONNECTOR_H

#include "figure.h"
#include <memory>


class FigureConnector
{
public:
    FigureConnector();
    void setFirstFigure(const int& fig_id, const std::shared_ptr<Figure>& figure);
    void setSecondFigure(const int& fig_id, const std::shared_ptr<Figure>& figure);
    void setInterimPoint(const QPointF& pnt);
    void paintInterimConnector(QPainter& painter) const;
    void paintFullConnector(QPainter& painter) const;
    bool isFigureConnector(const std::shared_ptr<Figure>& figure);
    void updateConnectorsOnRemove(const int& figure_id);
    void serialize(QDataStream& out) const;
    bool isConnectingSameFigure() const;
    void reset();
    ~FigureConnector();
private:
    int fig1_id, fig2_id;
    QPointF interim_point;
    std::shared_ptr<Figure> figure1, figure2;
};

#endif // FIGURECONNECTOR_H
