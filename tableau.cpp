#include "tableau.h"

Tableau::Tableau(){
    //initialisation du background
}
void Tableau::paintEvent(QPaintEvent *){
    QPainter pinceau(&background);
    pinceau.drawLine(ligne);
    pinceau.end();
    this->setPixmap(background);
}

void Tableau::dessiner(double x1,double y1,double x2,double y2){
    ligne.setLine(x1,y1,x2,y2);
}
