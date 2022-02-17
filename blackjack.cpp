#include "blackjack.h"

// ****************** Carta **************************************
Carta::Carta(int numero)
{
	this->numero = numero;
	siguienteCarta = nullptr;
}
void Carta::Imprimir()
{
	cout << "<Carta numero=" << numero << " />" << endl;
}

// ****************** Deck **************************************
Deck::Deck()
{
	cantidad = 0;
	primeraCarta = nullptr;
}
void Deck::AgregarCarta(Carta* carta)
{
	if (primeraCarta == nullptr)
	{
		primeraCarta = carta;
	}
	else
	{
		// [1]-> nullptr
		// 
		// [2] -> [1] -> nullptr
		// 
		// [2] -> [1] -> [3] -> nullptr
		// [2] -> [1] -> [4] -> [3] -> nullptr
		int posAleatoria = rand() % (cantidad + 1);

		int cont = 0;
		Carta* pCarta = primeraCarta;
		Carta* pCartaAnterior = nullptr;
		while (pCarta != nullptr)
		{
			if (cont == posAleatoria)
			{
				if (cont == 0)
				{
					carta->siguienteCarta = primeraCarta;
					primeraCarta = carta;
				}
				else
				{
					pCartaAnterior->siguienteCarta = carta;
					carta->siguienteCarta = pCarta;
				}
				break;
			}
			pCartaAnterior = pCarta;
			pCarta = pCarta->siguienteCarta;
			cont++ ;
		}
		if (posAleatoria == cantidad)
		{
			pCartaAnterior->siguienteCarta = carta;
		}
	}

	cantidad++;
}
Carta* Deck::ObtenerCarta()
{
	return nullptr;
}
void Deck::Imprimir()
{
	Carta* pCarta = primeraCarta;

	while (pCarta != nullptr)
	{
		pCarta->Imprimir();
		pCarta = pCarta->siguienteCarta;
	}
}