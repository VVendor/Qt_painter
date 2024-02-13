#include "paintzone.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"

PaintZone::PaintZone(QWidget *parent)
    : QWidget{parent}, curr_figure(nullptr), curr_action(Action::None){
}

void PaintZone::setAction(const Action &action)
{
    curr_action = action;
}

void PaintZone::setCurrFigure(const std::shared_ptr<Figure> &fig)
{
    curr_figure = fig;
}

void PaintZone::serialize(QDataStream &out) const
{
    out<<figures.size();
    for(const auto& figure : figures){
        figure->serialize(out);
    }

    out<<((int)figures_connectors.size());
    for(const auto& connector : figures_connectors){
        connector.serialize(out);
    }
}

void PaintZone::deserialize(QDataStream &in)
{
    curr_figure = nullptr;
    deserializeFigures(in);
    deserializeConnectors(in);
}

void PaintZone::deserializeFigures(QDataStream& in)
{
    figures.clear();

    int figures_count;
    FigureType fig_type;

    in>>figures_count;

    for(int idx = 0; idx < figures_count; idx++){
        in>>fig_type;
        if(fig_type == FigureType::Ellipse){
            curr_figure = std::make_shared<Ellipse>();
        }
        else if(fig_type == FigureType::Rectangle){
            curr_figure = std::make_shared<Rectangle>();
        }
        else if(fig_type == FigureType::Triangle){
            curr_figure = std::make_shared<Triangle>();
        }
        curr_figure->deserialize(in);
        figures.append(curr_figure);
    }
}
void PaintZone::deserializeConnectors(QDataStream& in)
{
    figures_connectors.clear();

    int fig1_id, fig2_id, connectors_count;
    FigureConnector connector;

    in>>connectors_count;

    for(int idx = 0; idx < connectors_count; idx++){
        in>>fig1_id>>fig2_id;
        connector.setFirstFigure(fig1_id, figures[fig1_id]);
        connector.setSecondFigure(fig2_id, figures[fig2_id]);
        figures_connectors.emplace_back(connector);
    }
}

int PaintZone::getFigureIdxByPoint(const QPointF &pnt) const
{
    for(int idx = 0; idx < figures.size(); idx++){
        if(figures[idx]->isContainsPoint(pnt)){
            return idx;
        }
    }
    return -1;
}

void PaintZone::removeFigure(const int& figure_idx)
{
    removeFigureConnectors(figure_idx, figures[figure_idx]);
    figures.removeAt(figure_idx);
}

void PaintZone::removeFigureConnectors(const int& figure_idx, const std::shared_ptr<Figure>& figure)
{
    for(auto it = figures_connectors.begin(); it != figures_connectors.end();){
        if(it->isFigureConnector(figure)){
            it = figures_connectors.erase(it);
        }
        else{
            it->updateConnectorsOnRemove(figure_idx);
            ++it;
        }
    }
}

void PaintZone::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        setFocus();
        if(curr_action == Action::Draw){
            QPointF curr_pos = event->pos();
            curr_figure->updateStartFigPoint(curr_pos);
            curr_figure->updateEndFigPoint(curr_pos);
        }
        else if(curr_action != Action::None){
            curr_figure = nullptr;
            QPointF curr_pos = event->pos();
            int figure_idx = getFigureIdxByPoint(curr_pos);
            if(figure_idx > -1){
                if(curr_action == Action::Connect){
                    curr_connector.setFirstFigure(figure_idx, figures[figure_idx]);
                }
                else if(curr_action == Action::Remove){
                    removeFigure(figure_idx);
                    curr_action = Action::None;
                    update();
                }
                else if(curr_action == Action::Move){
                    curr_figure = figures[figure_idx];
                    moving_offset = curr_figure->calculateOffset(curr_pos);
                    setCursor(Qt::PointingHandCursor);
                }
            }
            else{
                curr_action = Action::None;
            }
        }
    }
    else if(event->button() == Qt::RightButton){
        setCursor(Qt::ArrowCursor);
        curr_connector.reset();
        curr_figure = nullptr;
        curr_action = Action::None;
        update();
    }
}

void PaintZone::mouseMoveEvent(QMouseEvent *event)
{
    if(curr_action != Action::None){
        if(curr_action == Action::Draw){
            curr_figure->updateEndFigPoint(event->pos());
        }
        else if(curr_action == Action::Connect){
            curr_connector.setInterimPoint(event->pos());
        }
        else if(curr_action == Action::Move){
            curr_figure->translate(event->pos(), moving_offset);
        }
        update();
    }
}

void PaintZone::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(curr_action != Action::None){
            if(curr_action == Action::Draw){
                curr_figure->updateEndFigPoint(event->pos());
                curr_figure->updateFigCoords();
                figures.append(curr_figure);
            }
            else if(curr_action == Action::Connect){
                QPointF curr_pos = event->pos();
                int figure_idx = getFigureIdxByPoint(curr_pos);
                if(figure_idx > -1){
                    curr_connector.setSecondFigure(figure_idx, figures[figure_idx]);
                    if(!curr_connector.isConnectingSameFigure()){
                        figures_connectors.emplace_back(curr_connector);
                    }
                }
            }
            setCursor(Qt::ArrowCursor);
            curr_connector.reset();
            curr_figure = nullptr;
            curr_action = Action::None;
            update();
        }
    }
}

void PaintZone::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(curr_action == Action::Draw){
        curr_figure->updateFigCoords();
        curr_figure->draw(painter);
    }
    else if(curr_action == Action::Connect){
        curr_connector.paintInterimConnector(painter);
    }
    for(const auto& figure : figures){
        figure->draw(painter);
    }

    for(const auto& connector : figures_connectors){
        connector.paintFullConnector(painter);
    }
}


void PaintZone::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        setCursor(Qt::ArrowCursor);
        curr_connector.reset();
        curr_figure = nullptr;
        curr_action = Action::None;
        update();
    }
}

PaintZone::~PaintZone()
{
    figures_connectors.clear();
    figures.clear();
}
