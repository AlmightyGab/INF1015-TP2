#include <string>
#include <iostream>
#include "include/gsl/span"
#include "Developpeur.hpp"
#include "ListeJeux.hpp"

using namespace std;


Developpeur::Developpeur(const string& nom, const ListeJeux& listeJeux)
    : nom_(nom), jeux_(listeJeux)
{
    // Paire nom-jeux
    paireNomJeux_ = make_pair(nom, jeux_);
}

Developpeur::~Developpeur()
{
    delete [] jeux_.elements;
}

unsigned Developpeur::obtenirNombreJeux(const ListeJeux& listeJeux) const
{
    const gsl::span<Jeu*> spanJeux(listeJeux.elements, listeJeux.nElements);
    unsigned count = 0;
    for (auto jeu : spanJeux) {
        if (jeu->developpeur == nom_) 
            ++count;
    }
    return count;
}

void Developpeur::miseAJourJeux(const ListeJeux& listeJeux)
{
    jeux_.nElements = 0;
    jeux_.capacite = obtenirNombreJeux(listeJeux);

    Jeu** jeuxTemp = new Jeu*[jeux_.capacite];
    const gsl::span<Jeu*> spanJeux(listeJeux.elements, listeJeux.nElements);

    for (auto jeu : spanJeux) {
        if (jeu->developpeur == nom_)
            jeuxTemp[jeux_.nElements++] = jeu;
    }

    jeux_.elements = jeuxTemp;
    delete [] jeuxTemp;
}

void Developpeur::afficherJeux() const
{
    const string separateur = "\n\033[36m────────────────────────────────────────\033[0m\n";

    cout << separateur;
    cout << "Voici les jeux de " << nom_ << " :\n";
    for (unsigned i = 0; i < jeux_.nElements; ++i) 
        cout << " -> " << jeux_.elements[i]->titre << "\n";
    cout << separateur;
}