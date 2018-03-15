#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void show_label(bool li);

private:
    Ui::MainWindow *ui;

    int num_clic;
    float *distance;
    float *distance_2;
    int shooting, shooting_2;


    int f;//flag для кнопки подробнее
    //bool flaG;
    //int uu;
    float sum, sum_2;
    int DELET;
    float E;
    float M;
    float Bg, Tn;
    int line;
    float yl;
    float alpha;
    float P1, P2, P;
    float B1, B2, B;
    int cache;
};

#endif // MAINWINDOW_H
