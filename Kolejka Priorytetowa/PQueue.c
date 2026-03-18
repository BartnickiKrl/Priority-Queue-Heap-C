#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>

void UpdateDown( PQueue* q, int l, int p );  // update heap down between index l and p  <--- modified Update() from HeapSort 
void UpdateUp( PQueue* q, int l, int p );    // update heap up between index l and p 


PQueue* PQInit( int nSize )
{
	if( nSize < 0 ) return NULL;

	PQueue* q = NULL;
	q = (PQueue*)calloc( 1, sizeof( PQueue ) );
    if ( !q ) return NULL;

	q->pPQueue = (PQItem**)calloc( nSize, sizeof( PQItem* ) );
	if( !q->pPQueue ) return NULL;
	
	q->nPQMaxSize = nSize;
	q->nPQCurrSize = 0;
	return q;
}

int		PQisEmpty( PQueue* q )
{
	return !q || !(q->nPQCurrSize);
}

int		PQSize( PQueue* q )
{
	return ( !q )? PRIOR_ERROR : q->nPQCurrSize ;
}

int		PQMaxPrior( PQueue* q )
{
	return ( PQisEmpty( q ) )? PRIOR_ERROR : q->pPQueue[0]->nPrior;
}

int		PQEnqueue( PQueue* q, PQINFO* pInfo, int nPrior )
{
	if( !q || q->nPQCurrSize >= q->nPQMaxSize ) return 0;

	PQItem* newItem = (PQItem*)calloc( 1, sizeof( PQItem ) );
	if( !newItem ) return 0;

	newItem->pInfo = pInfo;
	newItem->nPrior = nPrior;
	q->pPQueue[q->nPQCurrSize] = newItem;

	
	if( q->nPQCurrSize ) UpdateUp(q, 0, q->nPQCurrSize  );

	q->nPQCurrSize++;
	return 1;
}

PQINFO* PQDequeue( PQueue* q )
{
	if( PQisEmpty( q ) ) return NULL;

	PQINFO* oldItem = q->pPQueue[0]->pInfo;
	int index = --q->nPQCurrSize; 
	
	if( index>0 )
	  q->pPQueue[0] = q->pPQueue[index]; 
	
	q->pPQueue[index] = NULL; 
	
	if( index > 1 )
	  UpdateDown( q, 0, index - 1 );

	return oldItem;
}

void	PQClear( PQueue* q, void( _cdecl* freeMem )( const void* ) )
{
	if( !q && !freeMem ) 
	{
		printf( "PQClear: Queue does not exist or wrong function given" );
		return;
	}
	while( q->nPQCurrSize )
	{
		freeMem( PQDequeue( q ) );
	}
}

void	PQRelease( PQueue** q, void( _cdecl* freeMem )( const void*) )
{
	if( !q || !(*q)  ) 
	{
		printf( "PQRelease: Queue does not exist" );
		return;
	}
	PQClear( *q, freeMem );
	free( ( *q )->pPQueue );
	free( *q );
}

void	PQPrint( PQueue* q, int index, void ( _cdecl* printInfo )( const void* ) )
{
    if( PQisEmpty( q ) ) 
	{
		printf( "PQPrint: Queue does not exist or empty" );
		return;
	}
	if( index < 0 || index > q->nPQCurrSize || !q->pPQueue[index] ) 
		return;
    PQItem* item = q->pPQueue[index];

    // Drukowanie informacji u¿ytkownika
    printInfo( ( const void* )item->pInfo );

    // Dodanie priorytetu i pozycji
    printf( "(%d) [%d]\n", item->nPrior, index );

    PQPrint( q, 2 * index + 1, printInfo );   // lewe dziecko
    PQPrint( q, 2 * index + 2, printInfo );  // prawe dziecko
}


void	UpdateDown( PQueue* q, int l, int p ) 
{
    if( l >= p ) return;
    int i = l;
    int j = 2 * i + 1;
    PQItem* x = q->pPQueue[i];
    while( j <= p ) 
	{
 
        if( j < p && q->pPQueue[j]->nPrior < q->pPQueue[j + 1]->nPrior ) j++;

        if( x->nPrior >= q->pPQueue[j]->nPrior ) break;
		q->pPQueue[i] = q->pPQueue[j];
		i = j;
		j = 2 * i + 1;
    }
	q->pPQueue[i] = x;
}

void	UpdateUp( PQueue* q, int l, int p ) 
{
    if( l >= p ) return;
    int i = p;
    int j = (i - 1)/ 2; // indeks rodzica
	PQItem* x = q->pPQueue[i];
    while( j >= l && q->pPQueue[j]->nPrior < x->nPrior ) 
	{
		q->pPQueue[i] = q->pPQueue[j];
		i = j;
		j = (i + 1) / 2 - 1 ;
    }
	q->pPQueue[i] = x;
}


int		PQSetPrior( PQueue* q, PQINFO* pInfo, int newPrior, int( _cdecl* compareInfo )( const void*, const void* )  )
{
	return PQsetPrior( q, PQFind( q, pInfo, compareInfo ) , newPrior );
}

int		PQsetPrior( PQueue* q, int index, int newPrior )
{
	int oldPrior = PQgetPrior( q, index );
	if( newPrior != oldPrior )
		q->pPQueue[index]->nPrior = newPrior;

	if( newPrior < oldPrior )
	  UpdateDown( q, 0, PQSize( q ) - 1);
	else if( newPrior > oldPrior ) 
	  UpdateUp( q, 0, index );

	return oldPrior;
}

int		PQGetPrior( PQueue* q, PQINFO* pInfo, int( _cdecl* compareInfo )( const void*, const void* )  )
{
	return PQgetPrior( q, PQFind( q, pInfo, compareInfo ) );
}

int		PQgetPrior( PQueue* q, int index )
{
	if( index == POS_ERROR || index == PRIOR_ERROR ) return PRIOR_ERROR;
	if( PQisEmpty( q ) ) return PRIOR_ERROR;
	if( index < 0 || index >= q->nPQCurrSize || !q->pPQueue[index] ) return PRIOR_ERROR;

	return q->pPQueue[index]->nPrior;
}

int		PQFind(  PQueue* q, PQINFO* pInfo, int( _cdecl* compareInfo )( const void*, const void* ) )
{
	if( !q ) return POS_ERROR;
	if( !compareInfo  ) return PRIOR_ERROR;

    for( int i = 0; i < q->nPQCurrSize; i++ )
    {
        if( !( compareInfo( ( const void* )q->pPQueue[i]->pInfo, ( const void* )pInfo) ) )
            return i;
    }

	return POS_ERROR;
}
