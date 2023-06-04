#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) {
	size = 0;
    radacina = nullptr;
    rel = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    Nod* nod_curent = radacina;
    Nod* parinte = nullptr;

    while(nod_curent != nullptr)
    {
        parinte = nod_curent;
        if(c == nod_curent->cheie)
        {
            auto val = nod_curent->valoare;
            nod_curent->valoare = v;
            return val;
        }
        else if(rel(c,nod_curent->cheie))
            nod_curent = nod_curent->stanga;
        else nod_curent = nod_curent->dreapta;
    }

    auto nod_nou = new Nod{c,v, nullptr, nullptr};
    if(radacina == nullptr)
        radacina = nod_nou;
    else if(rel(c,parinte->cheie))
        parinte->stanga = nod_nou;
    else parinte->dreapta = nod_nou;

    size++;
    return NULL_TVALOARE;
}


//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    auto nod = radacina;
    while(nod != nullptr and nod->cheie != c)
        if(rel(c,nod->cheie))
            nod=nod->stanga;
        else nod=nod->dreapta;
    if(nod == nullptr)
        return NULL_TVALOARE;
    return nod->valoare;
}

Nod *DO::getMaxim(Nod *nod) {
    auto curent = radacina;
    auto max_nod = radacina;

    while(curent != nullptr)
    {
        max_nod = curent;
        curent = curent->dreapta;
    }
    return max_nod;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	auto val = cauta(c);
    auto sters = false;
    radacina = sterge_rec(radacina,c,sters);
    if(sters)
        size--;
    return val;
}

Nod* DO::sterge_rec(Nod *nod,TCheie c,bool &sters) {
    if(nod == nullptr)
        return nod;

    if(c == nod->cheie)
    {
        sters = true;
        if (nod->stanga == nullptr)
        {
            Nod *dreapta = nod->dreapta;
            delete nod;
            return dreapta;
        }
        else if(nod->dreapta == nullptr)
        {
            Nod* stanga = nod->stanga;
            delete nod;
            return stanga;
        }
        else{
            Nod *nod_max = getMaxim(nod->stanga);
            nod->cheie = nod_max->cheie;
            nod->valoare = nod_max->valoare;
            nod->stanga = sterge_rec(nod->stanga,nod_max->cheie,sters);
        }
    }
    else if(rel(c,nod->cheie))
        nod->stanga = sterge_rec(nod->stanga,c,sters);
    else{
        nod->dreapta = sterge_rec(nod->dreapta,c,sters);
    }
    return nod;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    return size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
    return size == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	/* de adaugat */
}
