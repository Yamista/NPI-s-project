#ifndef TABLEAU_H
#define TABLEAU_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class Tableau : public QWidget
{
    Q_OBJECT

    QPixmap* background;
public:
    explicit Tableau(QWidget *parent = 0);
    void paintEvent();
    void dessiner();

signals:

public slots:

};

#endif // TABLEAU_H
