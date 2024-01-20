/*
Za slanje ranga procesa 0 upotrijebljen je MPI::Comm.Bcast svim
procesima unutar komunikatora. Nakon primitka procesi vraćaju
procesu 0 naziv računala koje je primilo poruku. Proces 0 prima
poruku od ostalih procesa MPI::Comm.Irecv. Ispisati na zaslon da
su primljene poruke na strani procesa 0. Program napisati
korištenjem C++ funkcija.
*/

#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
  MPI::Init(argc, argv);
  MPI::Request request;
  MPI::Status status;
  int size, rank;
  rank = MPI::COMM_WORLD.Get_rank();
  size = MPI::COMM_WORLD.Get_size();

  if (size < 2) {
    cout << "Potrebna su barem dva procesa za ovaj program.\n";
  } else {
    int data;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int len;

    if (rank == 0) {
      data = 0;
      MPI::COMM_WORLD.Bcast(&data, 1, MPI::INT, 0);
    } else {
      MPI::COMM_WORLD.Bcast(&data, 1, MPI::INT, 0);
      MPI_Get_processor_name(hostname, &len);
    }

    if (data == 0) {
      if (rank != 0) {
        request=MPI::COMM_WORLD.Isend(hostname, len + 1, MPI::CHAR, 0, 0);
        request.Wait(status);
      } else {
        vector<string> messages;

        for (int i = 1; i < size; i++) {
            request=MPI::COMM_WORLD.Irecv(hostname,MPI_MAX_PROCESSOR_NAME, MPI::CHAR,i,0);
            request.Wait(status);
            messages.push_back(hostname);
        }
        cout << "Primljene poruke na strani procesa 0:"<<endl;
        for (const string& message : messages) {
          cout << message << endl;
        }
      }
    }
  }

  MPI::Finalize();
  return 0;
}
