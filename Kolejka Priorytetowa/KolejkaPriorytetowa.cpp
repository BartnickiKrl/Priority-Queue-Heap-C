#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"
#include "global.h"

PQINFO* AllocInfo( int key, int a, int b );
void freeInfo( const void* p );
void printInfo( const void* p );
int compare(const void* a, const void* b);

int main()
{
    printf( "Test 1:" );
    printf( "Wykreowac kolejke 20-sto elementowa\n" );
    PQueue* Myqueue = PQInit( 20 );

    printf( "\ndodac 6 elementow z roznymi priorytetami i w roznej kolejnosci priorytetow - wydrukowac" );
    PQINFO* newInfo = 0;
    for( int i = 1; i < 7; i++ )
    {
        if( !( newInfo = AllocInfo(i + 1, i + 5, i + 10) ) )
        {
            printf( "newInfo allocation error" );
            return 1;
        }
        if( !PQEnqueue( Myqueue, newInfo, i ) ) return -5;
    }
    printf( "\n" );
    PQPrint( Myqueue, 0, printInfo );
    printf( "\n" );

    printf( "\nusunac z kolejki (z najwiekszym priorytetem)  - wydrukowac" );
    freeInfo( PQDequeue( Myqueue ) );
    printf( "\n" );
    PQPrint( Myqueue, 0, printInfo );
    printf( "\n" );

    printf( "\ndodac dwa elementy - wydrukowac" );
    for( int i = 1; i < 3; i++ )
    {
        if( !( newInfo = AllocInfo(i + 6, i + 2, i + 5) ) )
        {
            printf( "newInfo allocation error" );
            return 2;
        }
        if( !PQEnqueue( Myqueue, newInfo, i + 10 ) ) return -6;
    }
    printf( "\n" );
    PQPrint( Myqueue, 0, printInfo );

    printf( "\nwyszukac jeden element" );
    PQINFO* element = AllocInfo( 8, 4, 7 );
    int index = PQFind( Myqueue, element, compare );
    printf( "\nindex = %d\n", index );

    printf( "\nzwiekszyc mu priorytet (na 15) - wydrukowac" );
    PQsetPrior( Myqueue, index, 15 );
    printf( "\n" );
    PQPrint( Myqueue, 0, printInfo );

    printf( "\nzmniejszyc priorytet innemu elementowi (na 0) - wydrukowac" );
    if( !( element = AllocInfo(7, 3, 2) ) )
    {
        printf( "element allocation error" );
        return 3;
    }
    PQSetPrior( Myqueue, element, 0, compare ); 
    printf( "\n" );
    PQPrint( Myqueue, 0, printInfo );

    printf( "usunac cala kolejke" );
    PQRelease( &Myqueue, freeInfo );


    printf( "\n\n\nTest 2:  przetestowac jak bedzie sie zachowywac modul jesli powtorza sie priorytety niektorych elementow" );
    PQueue* Myqueue2 = PQInit( 5 );

    for( int i = 1; i < 4; i++ )
    {
        if( !( newInfo = AllocInfo(i, i + 1, i + 4) ) )
        {
            printf( "newInfo allocation error" );
            return 4;
        }
        if( !PQEnqueue( Myqueue2, newInfo, 8 - i ) ) return -7;
    }
    printf( "\n" );
    PQPrint( Myqueue2, 0, printInfo );
    printf( "\n" );

    printf( "zmienic priorytet np na maksymalny - powtorzy sie" );
    if( !( element = AllocInfo(3, 4, 7) ) )
    {
        printf( "element allocation error" );
        return 5;
    }
    PQSetPrior( Myqueue2, element, PQMaxPrior( Myqueue2 ), compare );
    printf( "\n" );
    PQPrint( Myqueue2, 0, printInfo );
    printf( "\n" );

    printf( "sciagam, drukowanie" );
    freeInfo( PQDequeue( Myqueue2 ) );
    printf( "\n" );
    PQPrint( Myqueue2, 0, printInfo );
    printf( "sciagam, drukowanie)" );
    freeInfo( PQDequeue( Myqueue2 ) );
    printf( "\n" );
    PQPrint( Myqueue2, 0, printInfo );

    PQRelease( &Myqueue2, freeInfo );
    free( element );
    printf( "\n\n" );
	return 0;
}

PQINFO* AllocInfo( int key, int a, int b )
{
    PQINFO* NewInfo = NULL;
    NewInfo = (PQINFO*)calloc( 1, sizeof( PQINFO ) );
    if( !NewInfo ) 
    {
        printf("AllocInfo: Alocation error");
        return NULL;
    }

    NewInfo->pTab = (int*)calloc( 2, sizeof( int ) );
    if( !(NewInfo->pTab) )
    {
        printf("AllocInfo: Alocation error");
        free(NewInfo);
        return NULL;
    }
    NewInfo->key = key;
    NewInfo->pTab[0] = a;
    NewInfo->pTab[1] = b;

    return NewInfo;
}

void freeInfo( const void* p )
{
    PQINFO* pInfo = (PQINFO*)p;
    free( pInfo->pTab );
    free( pInfo );
}

void printInfo( const void* p )
{
    const PQINFO* pInfo = (const PQINFO*)p;
    printf( "(key=%d, t0=%d, t1=%d)  ", pInfo->key, pInfo->pTab[0], pInfo->pTab[1] );
}

int compare(const void* a, const void* b)
{
    PQINFO* x = (PQINFO*)a;
    PQINFO* y = (PQINFO*)b;
    if( x->key < y->key ) return -1;
    return ( x->key > y->key );
}