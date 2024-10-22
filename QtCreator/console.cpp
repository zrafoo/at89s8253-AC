#include "console.h"
#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QBitArray>
#include <bitset>
#include <iostream>
#include <QCharRef>

Console::Console(QWidget *parent) :
    QPlainTextEdit(parent)
{
    count = 0;
    N = 0;
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);
}


void Console::putData(const QVector<unsigned int>& dataValues, QCustomPlot &Graph)
{
    int N = dataValues.size();
    QVector<double> x(N), y(N);

    for (int i = 0; i < N; ++i)
    {
        x[i] = i;
        y[i] = static_cast<double>(dataValues[i]) / 1000.0;
    }

    Graph.clearGraphs();
    Graph.addGraph();
    Graph.graph(0)->setData(x, y);

    Graph.xAxis->setLabel("x");
    Graph.yAxis->setLabel("y");

    Graph.xAxis->setRange(0, N);
    Graph.yAxis->setRange(0, 4.5);

    Graph.replot();
}


void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}
