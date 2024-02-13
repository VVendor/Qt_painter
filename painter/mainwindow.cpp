#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), paint_zone(new PaintZone)
{
    ui->setupUi(this);

    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    ui->gridLayout->addWidget(paint_zone.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_triangleButton_clicked()
{
    paint_zone->setAction(Action::Draw);
    paint_zone->setCurrFigure(std::make_shared<Triangle>());
}

void MainWindow::on_rectangleButton_clicked()
{
    paint_zone->setAction(Action::Draw);
    paint_zone->setCurrFigure(std::make_shared<Rectangle>());
}

void MainWindow::on_ellipseButton_clicked()
{
    paint_zone->setAction(Action::Draw);
    paint_zone->setCurrFigure(std::make_shared<Ellipse>());
}

void MainWindow::on_connectorButton_clicked()
{
    paint_zone->setAction(Action::Connect);
}

void MainWindow::on_moveButton_clicked()
{
    paint_zone->setAction(Action::Move);
}

void MainWindow::on_removeButton_clicked()
{
    paint_zone->setAction(Action::Remove);
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file"), "", tr("Saved files (*.dat)"));
     if (!fileName.isEmpty())
     {
         QFile file(fileName);
         if (file.open(QIODevice::ReadOnly))
         {
             QDataStream in(&file);
             paint_zone->deserialize(in);
             file.close();
             update();
         }
     }
}

void MainWindow::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), tr("Save files (*.dat)"));
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            paint_zone->serialize(out);
            file.close();
        }
    }
}

