#include "tableau.h"

Tableau::Tableau(){
    //initialisation du background
    //this->resize(500,500);
    this->setFixedSize(500,500);
    fenDessin = new QLabel();
    fenDessin->resize(this->size());
    couleur = Qt::black;
    ligne.setLine(0,0,0,0);
    background = new QPixmap(this->size());
    x = 0;
    y = 0;
}
void Tableau::paintEvent(QPaintEvent *){
    loadBackground();
    QPainter pinceau(this);
    pinceau.setPen(couleur);
    pinceau.save();
    pinceau.drawLine(ligne);
    pinceau.drawText(QPoint(x,y),texte);
    //pinceau.drawText(QPoint(150,150),"bite");
    pinceau.restore();

}

void Tableau::setLigne(double x1,double y1,double x2,double y2){
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

void Tableau::afficheTexte(int _x, int _y, QString _texte){
    x = _x;
    y = _y;
    texte = _texte;
    delete background;
    background = new QPixmap(this->size());
    this->render(background);
    this->update();
}
