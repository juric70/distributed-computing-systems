/*
Napisati program u kojem će svi procesi generirati jedan nasumičan broj,
nakon čega će jedan od procesa načiniti aritmetiču sredinu brojeva, koristeći
operaciju redukcije, te će dobivenu aritmetičku srednju vrijednost poslati
svim ostalim procesima. Procesi će nakon toga izračunati odstupanje u postocima
u odnosu na dobivenu srednju vrijednost.

Koristiti isključivo kolektivnu komunikaciju. Program napisati isključivo
korištenjem C++ funkcija.
*/

#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

int main (int argc, char* argv[]) {

    MPI::Init(argc, argv);
    int rank;
    int size;
    double c, d;
    float prosjek = 0;
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();

    srand((unsigned)time(NULL)+rank*size+rank);
    c = rand()%100;

    MPI::COMM_WORLD.Reduce(&c,&d,1,MPI::DOUBLE,MPI::SUM,0);
    if(rank == 0){
		prosjek=(float)d/size;
	}

    MPI::COMM_WORLD.Bcast(&prosjek, 1, MPI::FLOAT, 0);
    cout<<"Proces rang: " << rank << " generirani random broj je: " << c << " prosjek je: " << prosjek << " odstupanje je: " << abs(100-(c/prosjek*100)) << "% " << endl;
    MPI::Finalize();
    return 0;
}