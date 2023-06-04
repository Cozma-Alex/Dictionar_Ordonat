#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	prim();
}

void Iterator::prim(){
    nod_curent = dict.radacina;
    stack = std::stack<Nod *>{};

    while(nod_curent != nullptr)
    {
        stack.push(nod_curent);
        nod_curent = nod_curent->stanga;
    }

    if(!stack.empty())
        nod_curent = stack.top();
    else nod_curent = nullptr;
}

void Iterator::urmator(){
    if (!valid())
        throw std::exception();

    Nod *nod = stack.top();
    stack.pop();

    if(nod->dreapta != nullptr)
    {
        nod = nod->dreapta;
        while(nod != nullptr)
        {
            stack.push(nod);
            nod = nod->stanga;
        }
    }

    if(!stack.empty())
        nod_curent = stack.top();
    else nod_curent = nullptr;
}

bool Iterator::valid() const{
    return nod_curent != nullptr;
}

TElem Iterator::element() const{
	if(!valid())
        throw std::exception();

    TElem elem;
    elem.first = nod_curent->cheie;
    elem.second = nod_curent->valoare;

    return elem;
}
