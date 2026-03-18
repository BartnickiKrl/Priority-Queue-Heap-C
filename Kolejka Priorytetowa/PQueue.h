#ifndef PQUEUE_H
#define PQUEUE_H

#include "global.h"
//b³êdy
#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct
{
	PQINFO* pInfo;   // Ptr to user info
	int nPrior;      // prior value (int) for the user info  
} PQItem;


typedef struct
{
	PQItem** pPQueue; // kolejka realizowana w postaci stogu  (dynamiczna tablica wskazników na PQItem)
	int nPQMaxSize;   // maksymalny rozmiar calkowity kolejki priorytetowej
	int nPQCurrSize;  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsca w kolejce) 

} PQueue;


PQueue* PQInit(int nSize);     

int		PQisEmpty(PQueue* q);  
// zwraca 0 lub 1 - kolejka pusta/nie pusta

int		PQSize(PQueue* q);     
// zwraca ilosc elementow w kolejce

int		PQMaxPrior(PQueue* q); 
// zwraca element o najwiekszym priorytecie w kolejce (z zerowej pozycji) lub PRIOR_ERROR

int		PQEnqueue(PQueue * q, PQINFO * pInfo, int nPrior);
// wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)
// wskaznik na kolejke, element dodawany, priorytet

PQINFO*	PQDequeue( PQueue* q );
// zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie

void	PQClear( PQueue* q, void( _cdecl* freeMem )( const void* ) );
// czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info)

void	PQRelease( PQueue** q, void( _cdecl* freeMem )( const void* ) );
// zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto wczesniej (czyszczenie kolejki)

void	PQPrint( PQueue* pQueue, int index, void ( _cdecl* printInfo )( const void* ) );
// drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika przekazac 
// trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach oraz pozycje w 
// kolejce w kwadratowych nawiasach

int		PQSetPrior( PQueue* q, PQINFO* pInfo, int newPrior, int( _cdecl* compareInfo )( const void*, const void* )  ); 
// ustawia nowy priorytet dla zadanej informacji uzytkownika, zwraca poprzedni priorytet lub PRIOR_ERROR 

int		PQsetPrior( PQueue* q, int index, int newPrior); 
// ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce (indeks w tablicy),
// Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 

int		PQGetPrior( PQueue* q, PQINFO* pInfo, int( _cdecl* compareInfo )( const void*, const void* )  );
// zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR

int		PQgetPrior( PQueue* q, int index ); 
// zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR

int		PQFind( PQueue* q, PQINFO* pInfo, int( _cdecl* compareInfo )( const void*, const void* )  );     
// zwraca indeks wyszukiwanej informacji uzytkownika lub POS_ERROR jesli nie ma info w kolejce

#endif
