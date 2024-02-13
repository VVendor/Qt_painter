#include "figureconnector.h"

FigureConnector::FigureConnector(): fig1_id(-1), fig2_id(-1), figure1(nullptr), figure2(nullptr){}

void FigureConnector::setFirstFigure(const int &fig_id, const std::shared_ptr<Figure>& figure)
{
    fig1_id = fig_id;
    figure1 = figure;
    interim_point = figure->getCentralPoint();
}

void FigureConnector::setSecondFigure(const int &fig_id, const std::shared_ptr<Figure>& figure)
{
    fig2_id = fig_id;
    figure2 = figure;
}

void FigureConnector::setInterimPoint(const QPointF &pnt)
{
    interim_point = pnt;
}

void FigureConnector::paintInterimConnector(QPainter &painter) const
{
    painter.drawLine(QLineF(figure1->getCentralPoint(), interim_point));
}

void FigureConnector::paintFullConnector(QPainter &painter) const
{
    painter.drawLine(QLineF(figure1->getCentralPoint(), figure2->getCentralPoint()));
}

bool FigureConnector::isFigureConnector(const std::shared_ptr<Figure> &figure)
{
    return figure1 == figure || figure2 == figure;
}

void FigureConnector::updateConnectorsOnRemove(const int& figure_id){
    if(fig1_id > figure_id) fig1_id--;
    if(fig2_id > figure_id) fig2_id--;
}

void FigureConnector::serialize(QDataStream &out) const
{
    out<<fig1_id<<fig2_id;
}

bool FigureConnector::isConnectingSameFigure() const
{
    return fig1_id == fig2_id;
}

void FigureConnector::reset()
{
   figure1 = nullptr;
   figure2 = nullptr;
   fig1_id = -1;
   fig2_id = -1;
}

FigureConnector::~FigureConnector(){}
