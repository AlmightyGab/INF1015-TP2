//test commit
#pragma once
#include <string>
#include <utility>
#include "ListeJeux.hpp"
#include "Jeu.hpp"


class Developpeur
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	//TODO: Les méthodes à faire...
public:
	// Conctructeur
	Developpeur(const std::string& nom, const ListeJeux& listeJeux);
	// Destructeur
	virtual ~Developpeur();

	// Methodes publiques
	inline std::string obtenirNom() const {return nom_;};

	inline unsigned obtenirNombreJeux() const {return jeux_.nElements;}
	unsigned obtenirNombreJeux(const ListeJeux& listeJeux) const;

	void miseAJourJeux(const ListeJeux& listeJeux);
	
	void afficherJeux() const;


private:
	// Attributs privés
	std::pair<std::string, ListeJeux> paireNomJeux_;

	/* Je ne suis pas sur de comprendre l'utilite de cette paire etant donne qu'on traite toujours les 
    attributs du nom et de la liste de jeux du dev separement. J'ai donc choisi d'avoir ces attributs 
    independants puisque c'est une bien meilleur pratique (universellement reconnue) en OOP. */
	std::string nom_;
	ListeJeux jeux_;
};
