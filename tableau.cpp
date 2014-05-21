#include "tableau.h"

Tableau::Tableau(QWidget *parent) :
    QWidget(parent)
{
    //initialisation du background
    background = new QPixmap(this->size());
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawLine(100,200,300,400);
}
void Tableau::paintEvent(){

}

void Tableau::dessiner(){
    this->update();
}
