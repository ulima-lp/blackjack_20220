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
	Deck(int numeroBarajas);
	void AgregarCarta(Carta* carta); // agregar carta en posicion random
	Carta* ObtenerCarta(); // obtener la ultima carta de la pila
	void Imprimir();
};

class Jugador
{
public:
	string nombre;
	int sumaCartas;
	int cantidadGanadas;
	Jugador* siguienteJugador;
	Jugador(string nombre);
	void Imprimir();
};

class Mesa
{
public:
	int cantidadJugadores;
	Jugador* primerJugador;
	Jugador* ultimoJugador;
	int sumaCartasCrupier;
	Mesa();
	void AgregarJugador(string nombre);
	void RepartirCarta(Deck* deck);
	void RepartirCartaCrupier(Deck* deck);
	void RepartirCartasJugador(Deck* deck);
	void RepartirCartasCrupier(Deck* deck);
	void Imprimir();
	void VerificarGanadores();
	Jugador* ObtenerJugadorMasGanador();
};

class Juego
{
	Mesa* mesa;
public:
	Juego();
	void AgregarJugador();
	void Iniciar();
	void MostrarJugadorMayor();
	void MostrarMenu();
};