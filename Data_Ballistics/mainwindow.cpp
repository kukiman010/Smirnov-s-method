#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    num_clic = 0;
    shooting = 0;
    sum_2 = 0;
    E = 0.6745;
    M = 0.95;
    f = 0;
    distance = new float[shooting];
    distance_2 = new float[shooting_2];

//    ui->pushButton_3->setEnabled(false);
//    ui->pushButton_4->setEnabled(false);
    show_label(false);
}

MainWindow::~MainWindow()
{
    delete[] distance;
    delete[] distance_2;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString num;

    distance[shooting]= ui->doubleSpinBox->value();
    num= distance[shooting];
    //distance[shooting]= ui->spinBox->value();
    ui->listWidget->addItem(QString::number(distance[shooting]));

    shooting++;
    num_clic++;
    ui->label_2->setText(QString::number(num_clic));

//    if(num_clic<2)
//        ui->pushButton_3->setEnabled(false);
//    else if(num_clic>=2)
//        ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(num_clic>0)
    {
       ui->listWidget->removeItemWidget(ui->listWidget->takeItem(num_clic-1));
       num_clic--;
    }
    if(shooting>0)
       shooting=shooting-1;

    if(shooting_2>0)
       shooting_2--;

    ui->label_2->setText(QString::number(num_clic));

//    if(num_clic<2)
//        ui->pushButton_3->setEnabled(false);
//    //else
//    else if(num_clic>=)
//        ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->statusBar->showMessage("");
    double sd[5][24] = { {0,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
                         {0.1,16.8,7.35,5.78,5.18,4.87,4.71,4.60,4.52,4.48,4.44,4.42,4.40,4.39,4.39,4.38,4.38,4.38,4.38,4.38,4.38,4.39,4.39,4.39},
                         {0.05,32.3,10.7,7.54,6.43,5.89,5.58,5.38,5.24,5.15,5.08,5.02,4.98,4.94,4.92,4.90,4.89,4.87,4.86,4.85 ,4.85,4.84,4.84,4.85},
                         {0.025,105,15.0,9.65,7.87,7.02,6.52,6.20,5.99,5.84,5.72,5.62,5.56,5.50,5.45,5.42,5.38,5.36,5.34,5.32,5.31,5.29,5.28,5.27},
                         {0.010,105,23.6,13.3,10.2,8.70,7.89,7.38,7.03,6.79,6.60,6.45,6.34,6.24,6.17,6.10,6.05,6.00,5.97,5.93,5.90,5.88,5.86,5.84}};
    sum = 0;
    sum_2 = 0;

    shooting_2 = shooting;
    shooting_2--;

    DELET= ui->spinBox_2->value();

    if(DELET>shooting_2)
    {
        QMessageBox::critical(this,"Ошибка! n-1","Отсчет \"n\" начинается с 0.\nВведите элемент n-1.");
        return;
    }
    cache= distance[DELET];
    for (int i = 0; i < shooting_2; i++)
            distance_2[i] = distance[i];

    for (int i = DELET, j = DELET + 1; i < shooting_2; i++, j++)
        {
            if (DELET == shooting_2)
                break;

            distance_2[i] = distance[j];
        }
    ////////////////////////////////////////////////////////
    for (int i = 0; i < shooting_2; i++)
        {
            sum += distance_2[i];
        }
        sum = sum / shooting_2;


    ui->label_3->setText(QString::number(sum));
    ////////////////////////////////////////////////////////
    for (int i = 0; i < shooting_2; i++)
        sum_2 += pow((distance_2[i] - sum), 2);

    //shooting_2--;
    Bg = E * sqrt(sum_2 / --shooting_2);
    ui->label_7->setText(QString::number(Bg));
    ////////////////////////////////////////////////////////
    if (sum < cache)
            Tn = (cache - sum) / Bg;
        else if(sum > cache)
            Tn = (sum - cache) / Bg;
    ui->label_9->setText(QString::number(Tn));
    ////////////////////////////////////////////////////////

    for (int i = 0; i < 24; i++)
        {
            if (sd[0][i] == shooting)
            {
                line = i;
                break;
            }
        }

    for (int i = 1; i < 5; i++)
    {
        if ((Tn > sd[i][line])&&(Tn<sd[4][line]))
        {
            B1 = sd[i][line];
            P2 = sd[i][0];

//            if(Tn>sd[i][line])
//            {
//                B2 = sd[i + 1][line];
//                P1 = sd[i + 1][0];
//            }
//            else if(Tn<sd[i][line])
//            {
//                if(i>1)
//                {
//                B2 = sd[i - 1][line];
//                P1 = sd[i - 1][0];
//                }else
//                    break;
//            }
            B2 = sd[i + 1][line];
            P1 = sd[i + 1][0];
            //break;
        }else if(Tn < sd[1][line])
        {
            //ui->label_11->setText("Не брак! (вышел не входя в линию)");
            ui->label_11->setText("Входит в генеральную совокупность");
            ui->statusBar->showMessage("Не брак! (вышел не входя в линию)");
            return;
        }else if(Tn>sd[4][line])
        {
            //ui->label_11->setText("Точно брак! (слишком большой Tn)");
            ui->label_11->setText("Не входит в генеральную совокупность");
            ui->statusBar->showMessage("Точно брак! (слишком большой Tn)");
            //ui->pushButton_4->setEnabled(false);

            //show_label(false);
            return;
        }
    }

    B = Tn;


        yl = P2 - P1;

        P = (P1*(B - B1)) / (B2 - B1) + yl;

        //P = P * 100;
        alpha = P*2;
        alpha = alpha * 100;

        M = ui->doubleSpinBox_2->value();

        float malfunction;
        malfunction = (1 - M) * 100;

        if (malfunction > alpha)
        {
            //ui->label_11->setText("Брак!");
            //ui->pushButton_4->setEnabled(true);
            ui->label_11->setText("Не входит в генеральную совокупность");
            ui->statusBar->showMessage("Брак!");
        }
        if (malfunction < alpha)
        {
            //ui->label_11->setText("Не брак!");
            //ui->pushButton_4->setEnabled(true);
            //show_label(true);
            ui->label_11->setText("Входит в генеральную совокупность");
            ui->statusBar->showMessage("Не брак!");
        }



}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
    ui->label_3->clear();
    ui->label_7->clear();
    ui->label_9->clear();
    ui->label_2->clear();
    ui->label_11->clear();

    num_clic = 0;
    shooting = 0;
    sum = 0;
    sum_2 = 0;

    show_label(false);
    ui->statusBar->showMessage("");
}

void MainWindow::on_pushButton_4_clicked()
{
   if(f==1)
   {
       show_label(false);
   }
   else if(f==0)
   {
       show_label(true);
   }
}

void MainWindow::show_label(bool li)
{
    if(li == false)
    {
        ui->label_12->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->label_15->hide();
        ui->label_16->hide();
        ui->label_17->hide();
        ui->label_18->hide();
        ui->label_19->hide();
        ui->label_20->hide();
        ui->label_21->hide();
        ui->label_22->hide();
        ui->label_23->hide();
        ui->label_24->hide();
        ui->label_25->hide();
        ui->label_26->hide();
        ui->label_27->hide();
        ui->label_28->hide();
        ui->label_29->hide();
        ui->label_30->hide();

        f =0;
    }
    else if(li == true)
    {
        ui->label_15->setText(QString::number(B));
        ui->label_13->setText(QString::number(B1));
        ui->label_17->setText(QString::number(B2));
        ui->label_30->setText(QString::number(yl));
        ui->label_23->setText(QString::number(P));
        ui->label_19->setText(QString::number(P1));
        ui->label_21->setText(QString::number(P2));
        ui->label_28->setText(QString::number(alpha));

        ui->label_12->show();
        ui->label_13->show();
        ui->label_14->show();
        ui->label_15->show();
        ui->label_16->show();
        ui->label_17->show();
        ui->label_18->show();
        ui->label_19->show();
        ui->label_20->show();
        ui->label_21->show();
        ui->label_22->show();
        ui->label_23->show();
        ui->label_24->show();
        ui->label_25->show();
        ui->label_26->show();
        ui->label_27->show();
        ui->label_28->show();
        ui->label_29->show();
        ui->label_30->show();

        f =1;
    }
}
