#pragma once

// Declaration avancee
class Developpeur; 

class ListeDeveloppeurs
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
public: 
	// Constructeur
	ListeDeveloppeurs();
	// Destructeur
	virtual ~ListeDeveloppeurs();

	// Methodes publiques
	void afficher() const;

	void ajouterDeveloppeur(Developpeur* dev);

	void retirerDeveloppeur(Developpeur* dev);
	
private:
	// Methode privees
	int trouverIndexDev(const Developpeur* dev) const;
	void agrandirListe();

	// Attributs prives de la liste 
	unsigned nElements_;
	unsigned capacite_;
	Developpeur** elements_;
};
