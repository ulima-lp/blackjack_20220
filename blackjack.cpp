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

Deck::Deck(int numeroBarajas)
{
	for (int i = 0; i < numeroBarajas; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			Carta* carta = new Carta(j);
			AgregarCarta(carta);
		}
	}
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
		// [2] -> [1] -> nullptr
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
	if (primeraCarta == nullptr)
	{
		return nullptr;
	}

	Carta* pCarta = primeraCarta;
	primeraCarta = pCarta->siguienteCarta;

	pCarta->siguienteCarta = nullptr;
	cantidad--;

	return pCarta;
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

// ****************** Jugador ***********************************
Jugador::Jugador(string nombre)
{
	this->nombre = nombre;
	sumaCartas = 0;
	cantidadGanadas = 0;
	siguienteJugador = nullptr;
}

void Jugador::Imprimir()
{
	cout << "<Jugador nombre=" << nombre
		<< " sumaCarta=" << sumaCartas
		<< " cantidadPartidasGanadas=" << cantidadGanadas
		<< " />" << endl;
}

// ****************** Mesa **************************************
Mesa::Mesa()
{
	cantidadJugadores = 0;
	primerJugador = nullptr;
	ultimoJugador = nullptr;
}
void Mesa::AgregarJugador(string nombre)
{
	Jugador* nuevoJugador = new Jugador(nombre);
	
	if (cantidadJugadores == 0)
	{
		primerJugador = nuevoJugador;
		ultimoJugador = nuevoJugador;
	}
	else
	{
		ultimoJugador->siguienteJugador = nuevoJugador;
		ultimoJugador = nuevoJugador;
	}

	cantidadJugadores++;
}

void Mesa::Imprimir()
{
	cout << "<Mesa>" << endl;
	Jugador* pJugador = primerJugador;
	while (pJugador != nullptr)
	{
		pJugador->Imprimir();
		pJugador = pJugador->siguienteJugador;
	}
	cout << "</Mesa>" << endl;
}

// ****************** Juego *************************************
Juego::Juego()
{
	mesa = new Mesa();
}
void Juego::AgregarJugador()
{
	cout << "Ingrese el nombre del nuevo Jugador: ";

	string nombre;
	cin >> nombre;
	mesa->AgregarJugador(nombre);
	mesa->Imprimir();
}