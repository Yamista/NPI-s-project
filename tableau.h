#ifndef TABLEAU_H
#define TABLEAU_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>

class Tableau : public QLabel
{
    Q_OBJECT

    QPixmap* background;
    QLineF ligne;
public:
    explicit Tableau();
    void paintEvent(QPaintEvent*);
    void dessiner(double x1, double y1, double x2, double y2);

signals:

public slots:

};

#endif // TABLEAU_H
