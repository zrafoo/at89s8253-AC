#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>
#include "qcustomplot.h"

class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = nullptr);
    void putData(const QVector<unsigned int>& dataValues, QCustomPlot &Graph);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    long N;
    QVector<double> Y;
    int count;
    QByteArray firstbyte;

};

#endif // CONSOLE_H
