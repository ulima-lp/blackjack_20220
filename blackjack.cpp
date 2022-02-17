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
	sumaCartasCrupier = 0;
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

void Mesa::RepartirCarta(Deck* deck)
{
	Jugador* pJugador = primerJugador;
	while (pJugador != nullptr)
	{
		Carta* cartaSacada = deck->ObtenerCarta();
		pJugador->sumaCartas += cartaSacada->numero;
		delete cartaSacada;

		pJugador = pJugador->siguienteJugador;
	}
}

void Mesa::RepartirCartaCrupier(Deck* deck)
{
	Carta* cartaSacada = deck->ObtenerCarta();
	sumaCartasCrupier += cartaSacada->numero;
	delete cartaSacada;
}

void Mesa::RepartirCartasJugador(Deck* deck)
{
	Jugador* pJugador = primerJugador;
	while (pJugador != nullptr)
	{
		while (pJugador->sumaCartas < 17)
		{
			Carta* cartaSacada = deck->ObtenerCarta();
			pJugador->sumaCartas += cartaSacada->numero;
			delete cartaSacada;
		}
		pJugador = pJugador->siguienteJugador;
	}
}
void Mesa::RepartirCartasCrupier(Deck* deck)
{
	while (sumaCartasCrupier < 17)
	{
		Carta* cartaSacada = deck->ObtenerCarta();
		sumaCartasCrupier += cartaSacada->numero;
		delete cartaSacada;
	}
}

void Mesa::VerificarGanadores()
{
	Jugador* pJugador = primerJugador;
	while (pJugador != nullptr)
	{
		if (sumaCartasCrupier > 21)
		{
			pJugador->cantidadGanadas++;
		}
		else
		{
			if (pJugador->sumaCartas <= 21)
			{
				if (pJugador->sumaCartas >= sumaCartasCrupier)
				{
					pJugador->cantidadGanadas++;
				}
			}
		}
		pJugador->sumaCartas = 0; // reinicio sumaCartas para una nueva partida
		pJugador = pJugador->siguienteJugador;
	}
	sumaCartasCrupier = 0;
}

Jugador* Mesa::ObtenerJugadorMasGanador()
{
	Jugador* jugadorMasGanador = primerJugador;
	Jugador* pJugador = primerJugador;

	while (pJugador != nullptr)
	{
		if (pJugador->cantidadGanadas > jugadorMasGanador->cantidadGanadas)
		{
			jugadorMasGanador = pJugador;
		}
		pJugador = pJugador->siguienteJugador;
	}
	return jugadorMasGanador;
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
}

void Juego::Iniciar()
{
	// 0. Crear el deck
	Deck* deck = new Deck(6);
	// Mientras cantidadCartas >= 20:
	while (deck->cantidad >= 20)
	{
		// 1. Repartir una carta del deck a cada uno de los jugadores y crupier
		mesa->RepartirCarta(deck);
		mesa->RepartirCartaCrupier(deck);

		// 2. Comenzamos a jugar uno x uno con cada jugador:
		//  2.1 Entregar un carta hasta que se cumpla condicion >= 17
		mesa->RepartirCartasJugador(deck);
		// 3. Entregar cartas al crupier hasta que se cumpla condicion >= 17
		mesa->RepartirCartasCrupier(deck);

		// 4. Verificar ganadores
		mesa->VerificarGanadores();
	}
}

void Juego::MostrarJugadorMayor()
{
	Jugador* jugadorMasGanador = mesa->ObtenerJugadorMasGanador();
	cout << "Jugador Mas Ganador: ";
	jugadorMasGanador->Imprimir();

}
void Juego::MostrarMenu()
{
	bool deseoSalir = false;
	int opcion;

	while (!deseoSalir)
	{
		cout << "Menu de opciones:" << endl;
		cout << "(1): Agregar un jugador" << endl;
		cout << "(2): Iniciar partida" << endl;
		cout << "(3): Ver jugador mas ganador" << endl;
		cout << "(4): Ver mesa" << endl;
		cout << "(0): Salir" << endl;
		cout << "> ";
		cin >> opcion;

		if (opcion == 0)
		{
			deseoSalir = true;
		}
		else if (opcion == 1)
		{
			AgregarJugador();
		}
		else if (opcion == 2)
		{
			Iniciar();
		}
		else if (opcion == 3)
		{
			MostrarJugadorMayor();
		}
		else if (opcion == 4)
		{
			mesa->Imprimir();
		}
		else {
			cout << "Opcion incorrecta" << endl;
		}

	}
}