#include <string>
#include <iostream>
#include "include/gsl/span"
#include "ListeDeveloppeurs.hpp"
#include "Developpeur.hpp"

using namespace std;


ListeDeveloppeurs::ListeDeveloppeurs()
{
    nElements_ = 0;
    capacite_ = 1;
    elements_ = new Developpeur* [capacite_];
}

ListeDeveloppeurs::~ListeDeveloppeurs()
{
    delete [] elements_;
}

void ListeDeveloppeurs::afficher() const
{
    const string separateur = "\n\033[36m────────────────────────────────────────\033[0m\n";
    const gsl::span<Developpeur*> spanDevs(elements_, nElements_);

    for (auto dev : spanDevs) {
        cout << separateur;
        cout << "Voici le developpeur #" << (&dev - &spanDevs[0]) + 1 << " :\n";
        cout << "Nom: " << dev->obtenirNom() << "\n";
        cout << "Nombre de jeux: " << dev->obtenirNombreJeux() << "\n";
        cout << "Jeux:\n";
        dev->afficherJeux();
    }
    cout << separateur;
}

int ListeDeveloppeurs::trouverIndexDev(const Developpeur* dev) const
{
    const gsl::span<Developpeur*> spanDevs(elements_, nElements_);

    // Boucle de lookup
    for (unsigned i = 0; i < spanDevs.size(); ++i) {
        if (spanDevs[i]->obtenirNom() == dev->obtenirNom())
            return i;
    }
    // S'il n'existe pas deja dans la liste
    return -1;
}

void ListeDeveloppeurs::agrandirListe()
{
    if (capacite_ == nElements_ - 1) {
        capacite_ *= 2;
        Developpeur** elementsTemp = new Developpeur* [capacite_];
        
        // Boucle de reallocation
        for (unsigned i = 0; i < nElements_; ++i)
            elementsTemp[i] = elements_[i];
    
    // Reset de la liste
    delete [] elements_;
    // Mise a jour de la liste
    elements_ = elementsTemp;
    delete [] elementsTemp;
    }
}

void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur* dev)
{
    const int index = trouverIndexDev(dev);

    // Verification de l'existence du dev (s'il existe deja on ne fait rien)
    if (index != -1) {
        return; 
    }

    // Ajout
   agrandirListe();
   elements_[nElements_++] = dev;
}

void ListeDeveloppeurs::retirerDeveloppeur(Developpeur* dev)
{
    const int index = trouverIndexDev(dev);
    
    // Verification de l'existence du dev (s'il n'existe pas on ne fait rien)
    if (index == -1) {
        return; 
    }

    // Retrait
    for (unsigned i = index; i < nElements_ - 1; ++i)
        elements_[i] = elements_[i + 1];
    nElements_--;
}