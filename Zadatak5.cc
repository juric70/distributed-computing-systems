/*                                                                                                                                                                                                /*
Generirati proizvoljnu matricu. Distribuirati pojedni redak
pojedinom računalu(procesu). Formirati donju trokutastu matricu
sa ispisom naziva računala(procesa) koji je ispisao pojedini redak.
Program napisati korištenjem C++ funkcija.
*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <mpi.h>
using namespace std;

vector<int> triangular_matrix(int redNumb, vector<vector<int>> matrica){
      for (int i = redNumb + 1; i <  matrica[redNumb].size(); i++){
      matrica[redNumb][i] = 0;
   }
   return matrica[redNumb];
}

int main(int argc, char** argv){

  MPI::Init(argc, argv);
  MPI::Request request;
  MPI::Status status;
  int size, rank;
  rank = MPI::COMM_WORLD.Get_rank();
  size = MPI::COMM_WORLD.Get_size();
  int dest_rank;
    vector<vector<int>> matrix = {
        {1,2,3,4},
        {4,5,6,7},
        {9,8,7,6},
        {5,4,7,6}
    };
    int red;
    vector<int> used;
    vector<int> nizMatrice;
    if(size < matrix.size()){
        cout<<"Mora biti više  procesa od redova matrice!";
    }else{
     if(rank == 0){
        for (int i = 0; i < matrix.size(); ++i) {
            do{
                dest_rank = (rank + rand() % size) + 1;
            }while(find(used.begin(), used.end(), dest_rank) != used.end());
                used.push_back(dest_rank);

            request = MPI::COMM_WORLD.Isend(&i, 1, MPI::INT, dest_rank, 0);
            request.Wait();
        }
     }
     else{

        request = MPI::COMM_WORLD.Irecv(&red, 1, MPI::INT, 0, 0);
        request.Wait(status);
        nizMatrice = triangular_matrix(red, matrix);
        cout<<"proces: "<< rank << " obradjuje red: "<<red<<" red nakon obrade je:  ";
        for (const auto &element : nizMatrice) {
            cout << element << "  ";
        }
        cout << endl;
    }
    }

    MPI::Finalize();
    return 0;
}





