#include <iostream>
using namespace std;

const int t = 3;

class nodo{
    public:
    int clave [t - 1];
    nodo* hijo[t];
    int n;
    bool hoja;

    nodo(bool eshoja){
        hoja = eshoja;
        n = 0;
        for (int i = 0; i < t; i++)
            hijo[i] = nullptr;
    }
};

class arbolB {
    private:
    nodo* raiz;

    bool buscar(nodo* x, int legajo){
        int i = 0;

        while (i < x -> n && legajo > x->clave[i])
        i++;

        if (i < x -> n && x -> clave[i] == legajo)
        return true;

        if (x -> hoja)
        return false;

        return buscar(x->hijo[i], legajo);
    }

    public:
    arbolB(){
        raiz = new nodo(true);
    }
    bool buscarlegajo(int legajo){
        return buscar(raiz, legajo);
    }
};