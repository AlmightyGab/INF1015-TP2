#include <iostream>
#include <fstream>
#include "include/cppitertools/range.hpp"
#include "include/bibliotheque_cours.hpp"
#include "include/gsl/span"
#include "include/verification_allocation.hpp"
#include "include/debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du
#include "ListeJeux.hpp"
#include "Developpeur.hpp"
#include "ListeDeveloppeurs.hpp"

using namespace std;
using namespace iter;
using namespace gsl;

// Voici toutes les fonctions utiles implementees lors de la partie 1 dans main.cpp
#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion


//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.  Devrait utiliser span.
Designer* trouverDesigner(span<Jeu*> listeJeux, const string& nomDesignerRecherche)
{
	for (Jeu* jeu : listeJeux) {
		for (unsigned i = 0; i < jeu->designers.nElements; ++i) {
			Designer* designer = jeu->designers.elements[i];
			if (designer->nom == nomDesignerRecherche) {
				return designer;
			}
		}
	}
	return nullptr; //return nullptr si le designer n’est pas trouvé
}

Designer* lireDesigner(istream& fichier)
{
	Designer designer = {};
    designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);

	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du designer est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Designer* ptrDesigner = new Designer;
	ptrDesigner->nom = designer.nom;
	ptrDesigner->anneeNaissance = designer.anneeNaissance;
	ptrDesigner->pays = designer.pays;
	cout << "l'allocation du designer est réussie pour aider au débogage: " << ptrDesigner->nom << endl;


	cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return ptrDesigner; //TODO: Retourner le pointeur vers le designer crée.
}

//TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
void agrandirListeJeux(ListeJeux& listeJeux)
{
	// Si capacite initiale nulle
	if (listeJeux.capacite == 0) {
		listeJeux.capacite = 1;
		listeJeux.elements = new Jeu * [listeJeux.capacite];
		return;
	}

	// Si capacite insuffisante
	if (listeJeux.nElements >= listeJeux.capacite) {
		unsigned nouvelleCapacite = listeJeux.capacite * 2;
		// Boucle de reallocation
		Jeu** tableauAgrandi = new Jeu * [nouvelleCapacite];
		// Copie des jeux dans le nouveau tableau
		for (unsigned i = 0; i < listeJeux.nElements; ++i)
			tableauAgrandi[i] = listeJeux.elements[i];
		delete[] listeJeux.elements;
		// Mise a jour 
		listeJeux.elements = tableauAgrandi;
		listeJeux.capacite = nouvelleCapacite;
	}
}

//TODO: Fonction pour ajouter un Jeu à ListeJeux.
void ajouterJeu(ListeJeux& listeJeux, Jeu* jeu)
{
	// Verification de la taille du tableau et ajustement
	agrandirListeJeux(listeJeux);
	// Ajout du jeu au tableau
	listeJeux.elements[listeJeux.nElements++] = jeu;
}

//TODO: Fonction qui enlève un jeu de ListeJeux.
void enleverJeu(ListeJeux& listeJeux, Jeu* target)
{
 	// Trouver l'index du jeu en question
 	for (unsigned i = 0; i < listeJeux.nElements; i++) {
 		Jeu* jeu = listeJeux.elements[i];
 		if (jeu == target) {
 			for (auto j = i; j < listeJeux.nElements -1; j++) 
 				listeJeux.elements[j] = listeJeux.elements[j + 1];
 			listeJeux.nElements--;
			break;	
 		}
    }
}

Jeu* lireJeu(istream& fichier)
{
	Jeu jeu = {};
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);

	//TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du jeu est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Jeu* targetJeu = new Jeu(jeu);
	cout << targetJeu->titre << " added" << endl;

	for ([[maybe_unused]] int i : iter::range(jeu.designers.nElements)) {
		Designer* designer = lireDesigner(fichier);  //TODO: Mettre le designer dans la liste des designer du jeu.
		targetJeu->designers.elements[i] = designer;
		targetJeu->designers.nElements++;
		//TODO: Ajouter le jeu à la liste des jeux auquel a participé le designer.
		ajouterJeu(designer->listeJeuxParticipes, targetJeu);
	}
	return targetJeu; //TODO: Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};
	for ([[maybe_unused]] int n : iter::range(nElements))
	{
		lireJeu(fichier); //TODO: Ajouter le jeu à la ListeJeux.
	}

	return {}; //TODO: Renvoyer la ListeJeux.
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	creerListeJeux("jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
    cout << "Voici maintenant la partie 2 du TD." << endl;

    


	cout << ligneSeparation << endl;
}