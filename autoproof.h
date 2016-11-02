#ifndef AUTOPROOF_H
#define AUTOPROOF_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include "pythagorasproof.h"

namespace Ui {
class AutoProof;
}

class TrangleView : public QLabel
{
public:
    TrangleView()
    {
        step = 1;
    }

    TrangleView( int ab, int ae )
    {
        step = 1;
        AB = ab;
        AE = ae;
    }

protected:
    virtual void paintEvent(QPaintEvent* e)
    {
        QWidget::paintEvent(e);

        QPainter p(this);

        int marginLR = ( this->width() - (AE+AB) ) / 2;
        int marginTB = ( this->height() - AB ) / 2 + 10;

        QPoint A(marginLR, marginTB+AB);
        QPoint B(marginLR, marginTB);
        QPoint C(marginLR+AE+AB, marginTB+AB-AE);
        QPoint D(marginLR+AE+AB,marginTB+AB);
        QPoint E(marginLR+AE, marginTB+AB);


        p.setPen(Qt::green);
        p.drawLine(A, B);
        p.drawLine(A, E);
        p.drawLine(B, E);

        p.setPen(Qt::blue);
        p.drawText(A.x(), A.y()+15, "A");
        p.drawText(B.x(), B.y()-10, "B");
        p.drawText(E.x(), E.y()+15, "E");

        if( step >= 2 )
        {
            p.setPen(Qt::yellow);
            p.drawLine(D, E);
            p.drawLine(C, D);
            p.drawLine(C, E);

            p.setPen(Qt::blue);
            p.drawText(C.x(), C.y()-10, "C");
            p.drawText(D.x(), D.y()+15, "D");
        }

        if( step >= 3 )
        {
            p.setPen(Qt::red);
            p.drawLine(B, C);
            p.drawLine(C, E);
            p.drawLine(B, E);
        }
    }
public:
    void setABAE( int ab , int ae )
    {
        AB = ab;
        AE = ae;
        repaint();
    }

    void setStep( int _step )
    {
        step = _step;
        repaint();
    }

private:
    int AB;
    int AE;
    int step;
};

class AutoProof : public QWidget
{
    Q_OBJECT

public:
    explicit AutoProof(QWidget *parent = 0);
    ~AutoProof();

private slots:
    void on_bSend_clicked();
    void viewTriangle();

    void on_bRender_clicked();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void view( QString str );

    void on_bAuto_clicked();

private:
    Ui::AutoProof *ui;
    TrangleView * triangle;
    PythagorasProof * proof;
    int step;
};

#endif // AUTOPROOF_H
