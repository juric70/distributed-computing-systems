/*
Napravite program koji izračunava zbroj prilagođenih prefiksa dan
u nastavku za 4 različita niza i nakon toga ih sve zbrojiti.
Upotrijebite OpenMP directive za paralelno izvršavanje.
 A(1) = A(1)
 A(2) = A(2) + A(1)
 A(i) = A(i-2) + A(i-1)
*/
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    const int N = 4;
    const int M = 100;
    int trh_numb;
    vector<vector<int>> A(N, vector<int>(M, 1));

    omp_set_num_threads(10);
double start = omp_get_wtime();


    #pragma omp parallel for
    for(int n = 0; n < N; ++n) {
        for(int i = 2; i < M; ++i) {
            if(i == 2) {
                A[n][i] = A[n][i] + A[n][i-1];
            } else if(i==1){
            A[n][i] = A[n][i];
            }
            else {
                A[n][i] = A[n][i-2] + A[n][i-1];
            }
             trh_numb = omp_get_num_threads();
        }

    }
    int total_sum = 0;
    #pragma omp parallel for reduction(+:total_sum)
    for(int n = 0; n < N; ++n) {
        for(int i = 0; i < M; ++i) {
            total_sum += A[n][i];
        }
    }
    double end = omp_get_wtime();

cout << start <<"  "<< end << " razlika je : "<< end-start<<endl;
    cout << "Ukupni zbroj je: " << total_sum <<" Broj paralelnih procesa je "<< trh_numb <<endl;

    return 0;
}
