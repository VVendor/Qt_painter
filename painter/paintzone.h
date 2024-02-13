#ifndef PAINTZONE_H
#define PAINTZONE_H

#include <QWidget>
#include <QMouseEvent>

#include <memory>
#include "figureconnector.h"

enum class Action{None, Move, Draw, Remove, Connect};

class PaintZone : public QWidget
{
    Q_OBJECT
public:
    explicit PaintZone(QWidget *parent = nullptr);
    void setAction(const Action& action);
    void setCurrFigure(const std::shared_ptr<Figure>& fig);
    void serialize(QDataStream& out) const;
    void deserialize(QDataStream& in);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    ~PaintZone();

private:
    void deserializeFigures(QDataStream& in);
    void deserializeConnectors(QDataStream& in);
    int getFigureIdxByPoint(const QPointF& pnt) const;
    void removeFigure(const int& figure_idx);
    void removeFigureConnectors(const int& figure_idx, const std::shared_ptr<Figure>& figure);

signals:

private:
    Action curr_action;
    QPointF moving_offset;
    QList<std::shared_ptr<Figure>> figures;
    std::shared_ptr<Figure> curr_figure;
    FigureConnector curr_connector;
    std::vector<FigureConnector> figures_connectors;
};

#endif // PAINTZONE_H
