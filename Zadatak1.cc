#include <iostream>
#include <mpi.h>

using namespace std;
int main (int argc, char* argv[]) {

    int rang, velicina;

    MPI::Init(argc, argv);
    rang = MPI::COMM_WORLD.Get_rank();
    velicina = MPI::COMM_WORLD.Get_size();
 if(rang%2 == 0){
    cout << "Procesor " << rang << " od " << velicina << ": Hello World" << endl;
}
    MPI::Finalize();
    return 0;

}
