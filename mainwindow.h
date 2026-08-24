#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPen>
#include <QBrush>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;
    int cnt = 0;
private slots:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
