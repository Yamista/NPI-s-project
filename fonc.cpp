

// LISTE DES FONCTIONS ASSOCIES AU MOTS CLEFS

// +
void addition(Interprete * interpreteur) {
    double a = interpreteur->numPile.depiler();
    double b = interpreteur->numPile.depiler();
    interpreteur->numPile.empiler(a+b);
}
// -
void soustraction(Interprete * interpreteur) {
    double a = interpreteur->numPile.depiler();
    double b = interpreteur->numPile.depiler();
    interpreteur->numPile.empiler(a-b);
}
// *
void multiplication(Interprete * interpreteur) {
    double a = interpreteur->numPile.depiler();
    double b = interpreteur->numPile.depiler();
    interpreteur->numPile.empiler(a*b);
}
// /
void division(Interprete * interpreteur) {
    double a = interpreteur->numPile.depiler();
    double b = interpreteur->numPile.depiler();
    if(b != 0 )
        interpreteur->numPile.empiler(a/b);
    else
        qDebug("division par 0");
}


void execute(Interprete * interpreteur){
    // Initialise notre map si elle est vide
    if(interpreteur->reference.isEmpty()){
        interpreteur->reference["+"] = addition;
        interpreteur->reference["-"] = soustraction;
        interpreteur->reference["*"] = multiplication;
        interpreteur->reference["/"] = division;
    }
    // Si on appelle un fichier
    // Si on veut mettre un commentaire

    // Liste des mots de l'instruction
    QStringList instruction = interpreteur->input->text().split(" ");

    int i=0;
    do{
    // Si le mot clef existe
        if(interpreteur->reference.find(instruction[i]) != interpreteur->reference.end()){
            interpreteur->reference.value(instruction[i])(interpreteur);
        }
        else{
            interpreteur->numPile.empiler(instruction[i].toInt());
        }
    }while(i++ < instruction.count());

}

