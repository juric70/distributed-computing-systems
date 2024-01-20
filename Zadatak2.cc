#include <iostream>
#include <mpi.h>

using namespace std;

int main (int argc, char* argv[]) {

    int rang, velicina;

    MPI::Init(argc, argv);
    rang = MPI::COMM_WORLD.Get_rank();

 for(int i = 0; i<rang;i++){
    cout << "Rang " << rang << ": Hello World!\n";
}

    MPI::Finalize();
    return 0;

}
