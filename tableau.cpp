#include "tableau.h"

Tableau::Tableau(){
    //initialisation du background
    //this->resize(500,500);
    this->setFixedSize(500,500);
    fenDessin = new QLabel();
    fenDessin->resize(this->size());
    couleur = Qt::black;

    background = new QPixmap(this->size());
}
void Tableau::paintEvent(QPaintEvent *){
    loadBackground();
    QPainter pinceau(this);
    pinceau.setPen(couleur);
    pinceau.save();
    pinceau.drawLine(ligne);
    pinceau.restore();

}

void Tableau::dessiner(double x1,double y1,double x2,double y2){
    ligne.setLine(x1,y1,x2,y2);
    delete background;
    background = new QPixmap(this->size());
    this->render(background);
    this->update();
}

void Tableau::loadBackground(){
    if(background != NULL ){
        //background->load("example.png");
        QPalette p;
        p = palette();
        p.setBrush(QPalette::Window, QBrush(QPixmap(*background)));
        setPalette(p);
    }
}

void Tableau::setCouleur(int _couleur){
    QColor tabCouleur[] = {Qt::black,Qt::white,Qt::red,Qt::green,Qt::blue,Qt::cyan,Qt::magenta,Qt::yellow};
    couleur = tabCouleur[_couleur];
}
