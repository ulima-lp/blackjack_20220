#include "blackjack.h"

int main()
{
	Deck* deck = new Deck();
	Carta* carta1 = new Carta(1);
	Carta* carta2 = new Carta(2);
	Carta* carta3 = new Carta(3);
	Carta* carta4 = new Carta(4);
	Carta* carta5 = new Carta(5);

	deck->AgregarCarta(carta1);
	deck->AgregarCarta(carta2);
	deck->AgregarCarta(carta3);
	deck->AgregarCarta(carta4);
	deck->AgregarCarta(carta5);

	deck->Imprimir();

	return 0;
}