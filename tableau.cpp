#include "tableau.h"

Tableau::Tableau(QWidget *parent) :
    QWidget(parent)
{
    //initialisation du background
    background = new QPixmap(this->size());
    this->update();
}
void Tableau::paintEvent(){
    QPainter painter;
    painter.drawLine(100,200,300,400);
}

void Tableau::dessiner(QPainter *_pinceau){
    pinceau = _pinceau;
    this->update();
}
