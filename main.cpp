// //test commentaire
// #include "Jeu.hpp"
// #include <iostream>
// #include <fstream>
// #include <span>
// #include "ListeJeux.hpp"
// #include "include/cppitertools/range.hpp"
// #include "include/bibliotheque_cours.hpp"
// #include "include/verification_allocation.hpp"
// #include "include/debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

// using namespace std;
// using namespace iter;

// #pragma region "Fonctions de base pour vous aider"
// typedef uint8_t UInt8;
// typedef uint16_t UInt16;
// UInt8 lireUint8(istream& fichier)
// {
// 	UInt8 valeur = 0;
// 	fichier.read((char*)&valeur, sizeof(valeur));
// 	return valeur;
// }
// UInt16 lireUint16(istream& fichier)
// {
// 	UInt16 valeur = 0;
// 	fichier.read((char*)&valeur, sizeof(valeur));
// 	return valeur;
// }
// string lireString(istream& fichier)
// {
// 	string texte;
// 	texte.resize(lireUint16(fichier));
// 	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
// 	return texte;
// }
// #pragma endregion

// //TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.  Devrait utiliser span.
// Designer* trouverDesigner(span<Jeu*> listeJeux, const string& nomDesignerRecherche)
// {
// 	for (Jeu* jeu : listeJeux){
// 		for (unsigned i = 0; i < jeu->designers.nElements; i++) {
// 			Designer* designer = jeu->designers.elements[i];
// 			if (designer->nom == nomDesignerRecherche){
// 				return designer;
// 			}
// 		}
// 	}
// 	return nullptr; //return nullptr si le designer n’est pas trouvé
// }


// Designer* lireDesigner(istream& fichier)
// {
// 	Designer designer = {};
// 	designer.nom = lireString(fichier);
// 	designer.anneeNaissance = lireUint16(fichier);
// 	designer.pays = lireString(fichier);

// 	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
// 	// TIP: Afficher un message lorsque l'allocation du designer est réussie pour aider au débogage.
// 	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
// 	Designer* ptrDesigner = new Designer;
// 	ptrDesigner->nom = designer.nom;
// 	ptrDesigner->anneeNaissance = designer.anneeNaissance;
// 	ptrDesigner->pays = designer.pays;
// 	//cout << "l'allocation du designer est réussie pour aider au débogage: " << ptrDesigner->nom << endl;

// 	//cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
// 	return ptrDesigner; //TODO: Retourner le pointeur vers le designer crée.
// }


// //TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
// void agrandirListeJeux(ListeJeux& listeJeux)
// {
//     // Si capacite initiale nulle
//     if (listeJeux.capacite == 0) {
//         listeJeux.capacite = 1;
//         listeJeux.elements = new Jeu*[listeJeux.capacite];
//         return;
//     }

//     // Si capacite insuffisante
//     if (listeJeux.nElements >= listeJeux.capacite) {
//         unsigned nouvelleCapacite = listeJeux.capacite * 2;
// 		// Boucle de reallocation
//         Jeu** tableauAgrandi = new Jeu*[nouvelleCapacite];
// 		// Copie des jeux dans le nouveau tableau
//         for (unsigned i = 0; i < listeJeux.nElements; ++i)
//             tableauAgrandi[i] = listeJeux.elements[i];
//         delete[] listeJeux.elements;
// 		// Mise a jour 
//         listeJeux.elements = tableauAgrandi;
//         listeJeux.capacite = nouvelleCapacite;
//     }
// }

// //TODO: Fonction pour ajouter un Jeu à ListeJeux.
// void ajouterJeu(ListeJeux& listeJeux, Jeu* jeu)
// {
// 	// Verification de la taille du tableau et ajustement
// 	agrandirListeJeux(listeJeux);
// 	// Ajout du jeu au tableau
// 	listeJeux.elements[listeJeux.nElements++] = jeu;
// }


// //TODO: Fonction qui enlève un jeu de ListeJeux.
// void enleverJeu(ListeJeux& listeJeux, Jeu* target)
// {
// 	// Trouver l'index du jeu en question
// 	for (unsigned i = 0; i < listeJeux.nElements; i++) {
// 		Jeu* jeu = listeJeux.elements[i];
// 		if (jeu == target) {
// 			for (auto j = i; j < listeJeux.nElements -1; j++) 
// 				listeJeux.elements[j] = listeJeux.elements[j + 1];
// 			listeJeux.nElements--;
// 			break;	
// 		}
// 	}
// }


// Jeu* lireJeu(istream& fichier)
// {
// 	Jeu jeu = {};
// 	jeu.titre = lireString(fichier);
// 	jeu.anneeSortie = lireUint16(fichier);
// 	jeu.developpeur = lireString(fichier);
// 	jeu.designers.nElements = lireUint8(fichier);

// 	//TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
// 	// TIP: Afficher un message lorsque l'allocation du jeu est réussie pour aider au débogage.
// 	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
// 	Jeu* ptrJeu = new Jeu(jeu);
// 	cout << ptrJeu->titre << " added" << endl;

// 	for ([[maybe_unused]] int i : iter::range(jeu.designers.nElements)) {
// 		Designer* designer = lireDesigner(fichier);  //TODO: Mettre le designer dans la liste des designer du jeu.
// 		ptrJeu->designers.elements[i] = designer;
// 		ptrJeu->designers.nElements++;
// 		//TODO: Ajouter le jeu à la liste des jeux auquel a participé le designer.
// 		ajouterJeu(designer->listeJeuxParticipes, ptrJeu);
// 	}
// 	return ptrJeu; //TODO: Retourner le pointeur vers le nouveau jeu.
// }


// ListeJeux creerListeJeux(const string& nomFichier)
// {
// 	ifstream fichier(nomFichier, ios::binary);
// 	fichier.exceptions(ios::failbit);
// 	int nElements = lireUint16(fichier);
// 	ListeJeux listeJeux = {};
// 	for ([[maybe_unused]] int n : iter::range(nElements)) {
// 		//TODO: Ajouter le jeu à la ListeJeux.
// 		Jeu* jeu = lireJeu(fichier);
// 		ajouterJeu(listeJeux, jeu);
// 	}

// 	return listeJeux; //TODO: Renvoyer la ListeJeux.
// }


// //TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// // TIP: Afficher un message lorsque le jeu est détruit pour aider au débogage.
// // Vous pouvez enlever l'affichage une fois que le tout fonctionne.
// void detruireJeu(Jeu* jeu) {
// 	for (unsigned i = 0; i < jeu->designers.nElements; i++) {
// 		Designer* designer = jeu->designers.elements[i];
// 		enleverJeu(designer->listeJeuxParticipes, jeu);
// 		//désallouer le designer s’il n’est plus dans aucun jeu
// 		if (designer->listeJeuxParticipes.nElements == 0) {
// 			//La mémoire liée à un designer doit être aussi libérée
// 			delete[] designer->listeJeuxParticipes.elements;
// 			delete designer;
// 		}
// 	}
// 	delete[] jeu->designers.elements; //incluant le tableau dynamique de designers
// 	delete jeu;
// }


// //TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
// void detruireListeJeux(ListeJeux& listeJeu) {
// 	for (unsigned i = 0; i < listeJeu.nElements; i++) {
// 		detruireJeu(listeJeu.elements[i]);
// 	}
//     delete[] listeJeu.elements;
// }



// //TODO: Fonction pour afficher les infos d'un designer.
// void afficherInfoDesigner(const Designer* designer){
// 	cout << "Nom: " << designer->nom << "\n";
// 	cout << "Annee de naissance: " << designer->anneeNaissance << "\n";
// 	cout << "Pays: " << designer->pays << "\n";
// 	cout << "Liste des jeux participes: " << "\n";
// 	for (unsigned i = 0; i < designer->listeJeuxParticipes.nElements; i++) {
// 		Jeu* jeu = designer->listeJeuxParticipes.elements[i];
// 		cout << " - " << jeu->titre << endl;
// 	}
// }


// //TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
// void afficherJeu(const Jeu* jeu)
// {
// 	cout << "Titre: " << jeu->titre << "\n";
// 	cout << "Annee de sortie: " << jeu->anneeSortie << "\n";
// 	cout << "Developpeur: " << jeu->developpeur << "\n";
// 	cout << "List des designers: " << "\n";
// 	for (unsigned i = 0; i < jeu->designers.nElements; i++) {
// 		Designer* designer = jeu->designers.elements[i];
// 		cout << " - " << designer->nom << endl;
// 	}
// }


// //TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// // Votre ligne de séparation doit être différent de celle utilisée dans le main.
// void afficherListeJeux(const ListeJeux& liste)
// {
// 	const string separateur = "\n\033[36m────────────────────────────────────────\033[0m\n";
// 	for (unsigned i = 0; i < liste.nElements; i++) {
// 		cout << "Jeu #" << i + 1 << "\n";
// 		afficherJeu(liste.elements[i]);
// 		if (i != liste.nElements) 
// 			cout << separateur;
// 	}
// }


// int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
// {
// #pragma region "Bibliothèque du cours"
// 	// Permet sous Windows les "ANSI escape code" pour changer de couleur
// 	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
// 	// les supportent normalement par défaut.
// 	// bibliotheque_cours::activerCouleursAnsi();
// #pragma endregion

// 	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

// 	ListeJeux listeJeux = creerListeJeux("jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.
	
// 	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
// 	cout << ligneSeparation << endl;
// 	cout << "Premier jeu de la liste :" << endl;
// 	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.
// 	afficherJeu(listeJeux.elements[0]);
// 	cout << ligneSeparation << endl;

// 	//TODO: Appel à votre fonction d'affichage de votre liste de jeux.
// 	afficherListeJeux(listeJeux);



// 	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
// 	Designer* designer = trouverDesigner(span(listeJeux.elements, listeJeux.nElements), "Rob Pardo"); //existe
// 	afficherInfoDesigner(designer);
// 	cout << ligneSeparation << endl;
// 	trouverDesigner(span(listeJeux.elements, listeJeux.nElements), "Ab Cde"); //existe pas
// 	Jeu* target = listeJeux.elements[listeJeux.nElements -1];
// 	enleverJeu(listeJeux, target);
// 	detruireJeu(target);
// 	cout << ligneSeparation << endl;
// 	detruireListeJeux(listeJeux);	

// 	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
// }

#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include "ListeJeux.hpp"
#include "include/cppitertools/range.hpp"
#include "include/gsl/span"
#include "include/bibliotheque_cours.hpp"
#include "include/verification_allocation.hpp"

#include "include/debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;
using namespace gsl;

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
		for (unsigned i = 0; i < jeu->designers.nElements; i++) {
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
	ptrDesigner->listeJeuxParticipes.nElements = 0;
	ptrDesigner->listeJeuxParticipes.capacite = 0;
	ptrDesigner->listeJeuxParticipes.elements = nullptr;
	cout << "l'allocation du designer est réussie - débogage: " << ptrDesigner->nom << endl;


	//cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
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
	targetJeu->designers.elements = new Designer* [jeu.designers.nElements];
	cout << "l'allocation du jeu est réussie - débogage" << targetJeu->titre << endl;

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
 	for ([[maybe_unused]] int n : iter::range(nElements)) {
 		//TODO: Ajouter le jeu à la ListeJeux.
 		Jeu* jeu = lireJeu(fichier);
		//nous voulons qu’en mémoire l’allocation soit faite une seule fois par designer différent
		for (unsigned i = 0; i < jeu->designers.nElements; i++) {
	 		Designer* designer = jeu->designers.elements[i];
	 		Designer* designerTrouve = trouverDesigner(span(listeJeux.elements, listeJeux.nElements), designer->nom); //existe 
			if (designerTrouve != nullptr){ //si designer existe deja
				jeu->designers.elements[i] = designerTrouve;
				ajouterJeu(designerTrouve->listeJeuxParticipes, jeu);
				delete[] designer->listeJeuxParticipes.elements;
                delete designer;
			}
		}
 		ajouterJeu(listeJeux, jeu);
 	}

 	return listeJeux; //TODO: Renvoyer la ListeJeux.
 }

//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// TIP: Afficher un message lorsque le jeu est détruit pour aider au débogage.
// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
 void detruireJeu(Jeu* jeu) {
 	for (unsigned i = 0; i < jeu->designers.nElements; i++) {
 		Designer* designer = jeu->designers.elements[i];
 		enleverJeu(designer->listeJeuxParticipes, jeu);
 		//désallouer le designer s’il n’est plus dans aucun jeu
 		if (designer->listeJeuxParticipes.nElements == 0) {
 			//La mémoire liée à un designer doit être aussi libérée
 			delete[] designer->listeJeuxParticipes.elements;
 			delete designer;
 		}
 	}
 	delete[] jeu->designers.elements; //incluant le tableau dynamique de designers
 	delete jeu;
 }

//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
 void detruireListeJeux(ListeJeux& listeJeu) {
 	for (unsigned i = 0; i < listeJeu.nElements; i++) {
 		detruireJeu(listeJeu.elements[i]);
 	}
     delete[] listeJeu.elements;
 }

//TODO: Fonction pour afficher les infos d'un designer.
 void afficherInfoDesigner(const Designer* designer){
 	cout << "Nom: " << designer->nom << "\n";
 	cout << "Annee de naissance: " << designer->anneeNaissance << "\n";
 	cout << "Pays: " << designer->pays << "\n";
 	cout << "Liste des jeux participes: " << "\n";
 	for (unsigned i = 0; i < designer->listeJeuxParticipes.nElements; i++) {
 		Jeu* jeu = designer->listeJeuxParticipes.elements[i];
 		cout << " - " << jeu->titre << endl;
 	}
 }

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
 void afficherJeu(const Jeu* jeu)
 {
 	cout << "Titre: " << jeu->titre << "\n";
 	cout << "Annee de sortie: " << jeu->anneeSortie << "\n";
 	cout << "Developpeur: " << jeu->developpeur << "\n";
 	cout << "List des designers: " << "\n";
 	for (unsigned i = 0; i < jeu->designers.nElements; i++) {
 		Designer* designer = jeu->designers.elements[i];
 		cout << " - " << designer->nom << endl;
 	}
 }


//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Votre ligne de séparation doit être différent de celle utilisée dans le main.
 void afficherListeJeux(const ListeJeux& liste)
 {
 	const string separateur = "\n\033[36m────────────────────────────────────────\033[0m\n";
 	for (unsigned i = 0; i < liste.nElements; i++) {
 		cout << "Jeu #" << i + 1 << "\n";
 		afficherJeu(liste.elements[i]);
 		if (i != liste.nElements) 
 			cout << separateur;
 	}
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

	ListeJeux listeJeux = creerListeJeux("jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.
 	afficherJeu(listeJeux.elements[0]);

	cout << ligneSeparation << endl;

	//TODO: Appel à votre fonction d'affichage de votre liste de jeux.
 	afficherListeJeux(listeJeux);

	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	Designer* designer = trouverDesigner(span(listeJeux.elements, listeJeux.nElements), "Rob Pardo"); //existe
	afficherInfoDesigner(designer);
	cout << ligneSeparation << endl;
	trouverDesigner(span(listeJeux.elements, listeJeux.nElements), "Ab Cde"); //existe pas
	Jeu* target = listeJeux.elements[listeJeux.nElements -1];
	enleverJeu(listeJeux, target);
	detruireJeu(target);
	cout << ligneSeparation << endl;
	detruireListeJeux(listeJeux);	

	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
}
