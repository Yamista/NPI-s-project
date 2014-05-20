#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMap>
#include "pile.h"
#include "tableau.h"
#include <stdexcept>
#include <iostream>
#include <math.h>

class Interprete : public QWidget
{
    Q_OBJECT
private:
    QTextEdit* generalDisplay;
    QLineEdit* input;
    QStringList instruction;
    int curseur;

    Pile<QString> strPile;
    Pile<double> numPile;
    QMap<QString,void(Interprete::*)()>reference;

    Tableau* dessin;
    QPainter* pinceau;

public:
    Interprete(QWidget *parent = 0);
    ~Interprete();
    void execute();
    void addition();
    void soustraction();
    void multiplication();
    void division();
    void push();
    void pushstr();
    void pop();
    void popstr();
    void copy();
    void copystr();
    void print();
    void printstr();
    void display();
    void displaystr();
    void count();
    void countstr();
    void swap();
    void swapString();
    void sinus();
    void cosinus();
    void tangente();
    void racineCarre();
    void tronque();
    void line();
    void exit();

public slots:
    void doInput();
};

#endif // WIDGET_H
