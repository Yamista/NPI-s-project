#include "widget.h"

Interprete::Interprete(QWidget *parent)
    : QWidget(parent)
{
    generalDisplay=new QTextEdit(this);
        generalDisplay->setReadOnly(true);
        //generalDisplay->setTextInteractionFlags(0);
        generalDisplay->setFocusPolicy(Qt::NoFocus);
    input=new QLineEdit(this);

    //initialisation de la fenetre de dessin
    dessin = new QGraphicsScene;
    tableau = new QGraphicsView(dessin);

        numPile.empiler(500);
        numPile.empiler(500);

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
    reference["color"]=&Interprete::color;
    reference["drawstr"]=&Interprete::drawstr;
    reference["quit"]=&Interprete::quit;


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

// traitement du fichier .npi
void Interprete::executeFichier(){

    QFile file(QApplication::applicationDirPath() + "/script/" + instruction[curseur] + ".npi");
    QString ligne;
    input->clear();
    if(file.open(QIODevice::ReadOnly))
    {
        do
        {
            ligne = file.readLine();
            int i = ligne.indexOf('#');
            ligne = ligne.remove(i,ligne.size()-i);
            if(ligne.count() != 0){
                input->setText(ligne);
                execute();
            }
        }while(!file.atEnd());
    }
    file.close();
    input->clear();
}

void Interprete::execute(){

    // Liste des mots de l'instruction
    instruction = input->text().split(" ");
    instruction[instruction.count()-1].remove("\n");
    if(instruction[0].at(0) == '\"'){
        --curseur;
        pushstr();
    }
    curseur=0;
    do{
    // Si le mot clef existe
        if(reference.find(instruction[curseur]) != reference.end())
            (this->*reference.value(instruction[curseur]))(); // Appelle de la fonction

        else if(instruction[curseur] == "" && instruction.count() != 0){
            instruction.removeAt(curseur);
            --curseur;
        }
        else if(QFile::exists(QApplication::applicationDirPath() + "/script/" + instruction[curseur] + ".npi")){
            strPile.empiler(input->text());
            executeFichier();
        }
        else{
            //int test = instruction[curseur].toDouble();
            //numPile.empiler(instruction[curseur].toDouble());
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
    numPile.empiler(b-a);
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
    QString chaine = instruction[++curseur];
    while(instruction[curseur].at(instruction[curseur].length()-1) != '\"')
    {
        chaine += ' ' + instruction[++curseur];
    }
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
    int i = int(numPile.depiler());
    if(unsigned(i) < numPile.compter())
    {
        double* stock  = new double[i+1];
        for( int j=0 ; j <= i ; ++j )
            stock[j] = numPile.depiler();
        double nombreCopy = stock[i];
        for( int j=i ; j>=0 ; --j )
            numPile.empiler(stock[j]);
        numPile.empiler(nombreCopy);

        delete [] stock;
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
    double nombre = 0;
    Pile<double> pileTemp;
    do
    {
        pileTemp.empiler(numPile.depiler());
    }while(numPile.compter() != 0);
    generalDisplay->setText(generalDisplay->toPlainText()+"\n[");
    do
    {
        nombre = pileTemp.depiler();
        generalDisplay->setText(generalDisplay->toPlainText()+QString::number(nombre) + ' ');
        numPile.empiler(nombre);
    }while(pileTemp.compter() != 0);
    generalDisplay->setText(generalDisplay->toPlainText().remove(generalDisplay->toPlainText().size()-1));
    generalDisplay->setText(generalDisplay->toPlainText()+']');
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
    dessin->addLine(numPile.depiler(),numPile.depiler(),numPile.depiler(),numPile.depiler());
    //dessin->render(background);
    tableau->show();
    //QPainter pinceau(this);
    //pinceau.drawLine(pere->numPile.depiler(),pere->numPile.depiler(),pere->numPile.depiler(),pere->numPile.depiler());
}

// color
void Interprete::color(){
    //dessin->setCouleur(int(numPile.depiler()));
}

// drawstr
void Interprete::drawstr(){
    QGraphicsTextItem* text = new QGraphicsTextItem;
    text->setPos(numPile.depiler(),numPile.depiler());
    text->setPlainText(strPile.depiler());

    dessin->addItem(text);
    tableau->show();
}

// quit
void Interprete::quit(){
    qApp->exit();
}
