#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintzone.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_triangleButton_clicked();

    void on_rectangleButton_clicked();

    void on_moveButton_clicked();

    void on_removeButton_clicked();

    void on_ellipseButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_connectorButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<PaintZone> paint_zone;
};
#endif // MAINWINDOW_H
