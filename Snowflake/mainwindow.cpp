#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPen>
#include <QBrush>

using namespace std;

QBrush br(Qt::black);
QPen whitePen(Qt::black);

struct Point{
    double x, y;

    Point(double x0 = 0, double y0 = 0) {
        x = x0;
        y = y0;
    }
};

ostream& operator << (ostream& out, Point a) {
    return out << a.x << " " << a.y << " ";
}

Point a1{-100, 100}, a2{350, 100}, a3{125, 100 - 225 * sqrt(3)};

vector<vector<pair<Point, Point>>> segs{{{a1, a2}, {a2, a3}, {a3, a1}}};

void dos(int i, vector<pair<Point, Point>>& nw) {
    auto [x1, y1] = segs.back()[i].first;
    auto [x2, y2] = segs.back()[i].second;
    Point p1 = {(2 * x1 + x2) / 3, (2 * y1 + y2) / 3};
    Point p2 = {(x1 + 2 * x2) / 3, (y1 + 2 * y2) / 3};
    double a1 = -(y2 - y1) * sqrt(3) / 6.0;
    double a2 = (x2 - x1) * sqrt(3) / 6.0;
    Point p3 = {(x1 + x2) / 2 + a1, (y1 + y2) / 2 + a2};
    nw.push_back({{x1, y1}, p1});
    nw.push_back({p1, p3});
    nw.push_back({p3, p2});
    nw.push_back({p2, {x2, y2}});
}

void step() {
    vector<pair<Point, Point>> nw;
    for (int i = 0; i < (int)segs.back().size(); ++i) {
        dos(i, nw);
    }
    segs.push_back(nw);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    for (int i = 0; i < (int)segs.back().size(); ++i) {
        scene->addLine(segs.back()[i].first.x, segs.back()[i].first.y, segs.back()[i].second.x, segs.back()[i].second.y, whitePen);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_N) {
        if (cnt >= 10) {
            return;
        }
        scene->clear();
        step();
        whitePen.setWidth(2 - 0.3 * cnt);
        for (int i = 0; i < (int)segs.back().size(); ++i) {
            scene->addLine(segs.back()[i].first.x, segs.back()[i].first.y, segs.back()[i].second.x, segs.back()[i].second.y, whitePen);
        }
        ++cnt;
    }
    if (event->key() == Qt::Key_D) {
        if (segs.size() > 1) {
            scene->clear();
            segs.pop_back();
            whitePen.setWidth(2 - 0.3 * cnt);
            for (int i = 0; i < (int)segs.back().size(); ++i) {
                scene->addLine(segs.back()[i].first.x, segs.back()[i].first.y, segs.back()[i].second.x, segs.back()[i].second.y, whitePen);
            }
            --cnt;
        }
    }
    if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
            ui->graphicsView->scale(1.05, 1.05);
        } else if (event->key() == Qt::Key_Minus || event->key() == Qt::Key_Dead_Lowline) {
            ui->graphicsView->scale(0.95, 0.95);
        }
}


