#ifndef PILE_H
#define PILE_H

#include <QTextEdit>


template <typename T>
class Pile{
    private:
        unsigned int tailleMax;
        unsigned int sommet;
        T * pile;
    public:
        Pile(unsigned int =128);
        Pile(const Pile&);
        inline ~Pile() {delete[] pile;}

        inline unsigned int compter() const {return sommet;}
        void afficher(QTextEdit*) const;
        void empiler(const T &);
        T depiler();
};

template <typename T>
Pile<T>::Pile(unsigned int _tailleMax)
:tailleMax(_tailleMax),sommet(0u),pile(NULL)
{
    pile=new T[tailleMax];
}

template <typename T>
Pile<T>::Pile(const Pile& origin)
:tailleMax(origin.tailleMax),sommet(origin.sommet),pile(NULL)
{
    pile=new T[tailleMax];
    for(unsigned int i=0u;i<tailleMax;i++){
        pile[i]=origin.pile[i];
    }
}

template <typename T>
void Pile<T>::afficher(QTextEdit* os) const{
    os->setText(os->toPlainText()+'\n'+'[');
    for(unsigned int i=0u;i<sommet;i++)
        os->setText(os->toPlainText()+pile[i]+' ');
    os->setText(os->toPlainText()+']');
}

template <typename T>
void Pile<T>::empiler(const T & c){
    if(sommet==tailleMax){
        //std::cerr<<"Pile pleine ... réallocation ..."<<endl;
        T* pileBig=new T [tailleMax * 2];
        for(unsigned int i=0u;i<sommet;i++)
            pileBig[i]=pile[i];
        delete [] pile;
        pile=pileBig;
    }
    //else{
        pile[sommet++]=c;
    //}
}

template <typename T>
T Pile<T>::depiler(){
    if(sommet==0u){
        //std::cerr<<"Non ! Pile vide"<<endl;
        return 0;
        //throw runtime_error("Pile vide");
    }
    else{
        return pile[--sommet];
    }
}
#endif // PILE_H
