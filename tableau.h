#ifndef TABLEAU_H
#define TABLEAU_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QLabel>

class Tableau : public QWidget
{
    Q_OBJECT
    QPixmap* background;
    QLineF ligne;
    QLabel* fenDessin;
    QColor couleur;
    int x;
    int y;
    QString texte;
public:
    explicit Tableau();
    void paintEvent(QPaintEvent*);
    void setLigne(double x1, double y1, double x2, double y2);
    void loadBackground();
    void setCouleur(int);
    void afficheTexte(int _x, int _y, QString _texte);

signals:

public slots:

};

#endif // TABLEAU_H
