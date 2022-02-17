#include <cstdlib>
#include <iostream>

using namespace std;

class Carta
{
public:
	int numero;
	Carta* siguienteCarta;
	Carta(int numero);
	void Imprimir();
};

class Deck
{
public:
	int cantidad;
	Carta* primeraCarta;
	Deck();
	void AgregarCarta(Carta* carta); // agregar carta en posicion random
	Carta* ObtenerCarta(); // obtener la ultima carta de la pila
	void Imprimir();
};