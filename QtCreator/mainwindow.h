#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include <QComboBox>
#include <QLabel>
#include "console.h"
#include <QSerialPort>
#include "qcustomplot.h"

//Предварительное объявление классов
class QPushButton;
class QLCDNumber;
class MainWindow : public QWidget
{
    Q_OBJECT
public :
    QSerialPort *port = nullptr;
    explicit MainWindow ( QWidget * parent = 0 );
    ~MainWindow();

private slots:
    void writeData(const QByteArray &data);
    void readData();
    void OpenPort();
    void ClosePort();


private :
    //Отдельный метод для создания интерфейса программы
    void createwidgets ( );
    void initActionsConnections();

private :
    //Цифровые кнопки
    QPushButton *pushButtonConnect;
    QPushButton *pushButtonDisconnect;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QComboBox *Comname;
    QComboBox *Baudrate;
    QComboBox *Databits;
    QComboBox *Stopbits;
    QCustomPlot *Graph;
    Console *m_console;
};
