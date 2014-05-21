#include "tableau.h"

Tableau::Tableau(){
    //initialisation du background
    background = new QPixmap(this->size());
}
void Tableau::paintEvent(QPaintEvent *){
    QPainter pinceau(background);
    pinceau.setBrush(Qt::black);
    pinceau.drawLine(ligne);
    this->setPixmap(*background);

}

void Tableau::dessiner(double x1,double y1,double x2,double y2){
    ligne.setLine(x1,y1,x2,y2);
}
