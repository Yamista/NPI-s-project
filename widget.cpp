#include "widget.h"

Interprete::Interprete(QWidget *parent)
    : QWidget(parent)
{
    generalDisplay=new QTextEdit(this);
        generalDisplay->setReadOnly(true);
        //generalDisplay->setTextInteractionFlags(0);
        generalDisplay->setFocusPolicy(Qt::NoFocus);
    input=new QLineEdit(this);

    dessin=new QWidget();
        dessin->resize(500,500);

    //initialisation de QMap
    reference["+"] = &Interprete::addition;
    reference["-"] = &Interprete::soustraction;
    reference["*"] = &Interprete::multiplication;
    reference["/"] = &Interprete::division;
    reference["push"] = &Interprete::push;
    reference["pushstr"] = &Interprete::pushstr;
    reference["pop"] = &Interprete::pop;
    reference["popstr"] = &Interprete::popstr;
    reference["copy"] = &Interprete::copy;
    reference["copystr"] = &Interprete::copystr;
    reference["print"] = &Interprete::print;
    reference["printstr"] = &Interprete::printstr;
    reference["display"] = &Interprete::display;
    reference["displaystr"] = &Interprete::displaystr;
    reference["count"] = &Interprete::count;
    reference["countstr"] = &Interprete::countstr;
    reference["swap"]= &Interprete::swap;
    reference["swapstr"]=&Interprete::swapString;
    reference["sin"]=&Interprete::sinus;
    reference["cos"]=&Interprete::cosinus;
    reference["tan"]=&Interprete::tangente;
    reference["sqrt"]=&Interprete::racineCarre;
    reference["trunc"]=&Interprete::tronque;
    reference["line"]=&Interprete::line;

    QVBoxLayout* vLayout1=new QVBoxLayout(this);
        vLayout1->addWidget(generalDisplay);
        vLayout1->addWidget(input);

    this->setLayout(vLayout1);

    connect(input,SIGNAL(editingFinished()),this,SLOT(doInput()));

}

Interprete::~Interprete()
{

}

void Interprete::doInput(){
    if(input->isActiveWindow()){
        generalDisplay->setText(generalDisplay->toPlainText()+'\n'+input->text());

        // Exécution
        execute();

        // Affichage du résultat
        // generalDisplay->setText(generalDisplay->toPlainText()+'\n'+QString::number(numPile.depiler()));

        input->clear();
    }
}

void Interprete::execute(){

    // Liste des mots de l'instruction
    instruction = input->text().split(" ");

    curseur=0;
    do{
    // Si le mot clef existe
        if(reference.find(instruction[curseur]) != reference.end()){
            (this->*reference.value(instruction[curseur]))(); // Appelle de la fonction
        }
        else{
            //int test = instruction[curseur].toDouble();
            numPile.empiler(instruction[curseur].toDouble());
        }
        ++curseur;
    }while(curseur< instruction.count());

}

// +
void Interprete::addition() {
    double a = numPile.depiler();
    double b = numPile.depiler();
    numPile.empiler(a+b);
}

// -
void Interprete::soustraction() {
    double a = numPile.depiler();
    double b = numPile.depiler();
    numPile.empiler(a-b);
}

// *
void Interprete::multiplication() {
    double a = numPile.depiler();
    double b = numPile.depiler();
    numPile.empiler(a*b);
}

// /
void Interprete::division() {
    double a = numPile.depiler();
    double b = numPile.depiler();
    if(b != 0 )
        numPile.empiler(a/b);
    else
        qDebug("division par 0");
}

// push [valeur_numerique]
void Interprete::push() {
    numPile.empiler(instruction[++curseur].toDouble());
}

// pushstr  "chaine_de_caractere"
void Interprete::pushstr() {
    QString chaine = instruction[curseur+1];
    chaine.remove(0,1);
    chaine.remove(chaine.length()-1,1);
    strPile.empiler(chaine);
}

// pop
void Interprete::pop() {
    numPile.depiler();
}

// popstr
void Interprete::popstr() {
    strPile.depiler();
}

// copy
void Interprete::copy() {
    unsigned i = unsigned(numPile.depiler());
    if(i < numPile.compter())
    {
        double* stock  = new double[i+1];
        for( unsigned j=0 ; j <= i ; ++j )
            stock[i-j-1] = numPile.depiler();
        double nombreCopy = stock[0];
        for( unsigned j=0 ; j<=i ; ++j )
            numPile.empiler(stock[j]);
        numPile.empiler(nombreCopy);
    }
    else
        qDebug("copy impossible : pile trop petite");
}

// copystr
void Interprete::copystr() {
    unsigned i = unsigned(numPile.depiler());
    if(i < strPile.compter())
    {
        QString* stock  = new QString[i+1];
        for( unsigned j=0 ; j <= i ; ++j )
            stock[i-j-1] = strPile.depiler();
        QString chaineCopy = stock[0];
        for( unsigned j=0 ; j<=i ; ++j )
            strPile.empiler(stock[j]);
        strPile.empiler(chaineCopy);
    }
    else
        qDebug("copy impossible : pile trop petite");
}

// print
void Interprete::print() {
    generalDisplay->setText(generalDisplay->toPlainText()+'\n'+QString::number(numPile.depiler()));
}

// printstr
void Interprete::printstr() {
    generalDisplay->setText(generalDisplay->toPlainText()+'\n'+strPile.depiler());
}

// display
void Interprete::display() {
    numPile.afficher(generalDisplay);
}

// displaystr
void Interprete::displaystr() {
    strPile.afficher(generalDisplay);
}

// count
void Interprete::count() {
    numPile.empiler(numPile.compter());
}

// countstr
void Interprete::countstr() {
    numPile.empiler(strPile.compter());
}

// swap
void Interprete::swap(){
    double a = numPile.depiler();
    double b = numPile.depiler();
    numPile.empiler(b);
    numPile.empiler(a);
}

// swapstr
void Interprete::swapString(){
    QString a = strPile.depiler();
    QString b = strPile.depiler();
    strPile.empiler(b);
    strPile.empiler(a);
}

#define PI 3.14159265358979323846

// sin
void Interprete::sinus(){
    double rad(PI*(numPile.depiler())/180);
    rad=sin(rad);
    numPile.empiler(180*rad*PI);
}

// cos
void Interprete::cosinus(){
    double rad(PI*(numPile.depiler())/180);
    rad=cos(rad);
    numPile.empiler(180*rad*PI);
}

// tan
void Interprete::tangente(){
    double rad(PI*(numPile.depiler())/180);
    rad=tan(rad);
    numPile.empiler(180*rad*PI);
}

// sqrt
void Interprete::racineCarre(){
    numPile.empiler(sqrt(numPile.depiler()));
}

// trunc
void Interprete::tronque(){
    numPile.empiler(double(int(numPile.depiler())));
}

// line
void Interprete::line(){
    dessin->show();
    //QPainter pinceau(this);
    //pinceau.drawLine(pere->numPile.depiler(),pere->numPile.depiler(),pere->numPile.depiler(),pere->numPile.depiler());
}
