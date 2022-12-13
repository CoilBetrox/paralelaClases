#include <iostream>
#include <omp.h>

int main() {

    //omp_set_num_threads(8);

#pragma omp parallel default(none)
    {
        if (omp_get_thread_num() == 0){
            std::printf("I have %d thread(s) \n", omp_get_num_threads());
            std::printf("I have %d thread(s)\n", omp_get_num_threads());
        }

        int thread_id = omp_get_thread_num();
        std::printf("My thread_id is %d\n", thread_id);

        /*
        int nthreads = omp_get_num_threads();   //obtiene num hilos
        int thread_id = omp_get_thread_num();     //Id del hilo actual

        std::printf("Hello OMP\n");
        std::printf("I have %d thread(s) and my thread_id is %d\n", nthreads, thread_id);

         */
    }


    return 0;
}
