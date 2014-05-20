#include <iostream>
using namespace std;

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
		void afficher(ostream& = cout) const;
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
void Pile<T>::afficher(ostream& os) const{
	os<<'[';
	for(unsigned int i=0u;i<sommet;i++)
		os<<pile[i]<<' ';
	os<<']';
}

template <typename T>
void Pile<T>::empiler(const T& c){
	if(sommet==tailleMax){
		cerr<<"Pile pleine ... réallocation ..."<<endl;
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
		cerr<<"Non ! Pile vide"<<endl;
		return '!';
	}
	else{
		return pile[--sommet];
	}
}
