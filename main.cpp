#include <iostream>
#include <omp.h>
#include <chrono>

namespace  ch=std::chrono;

#define NUMERO_ITERACIONES 1000000000

double pi_serial(){
    double respuesta = 0.0;
    bool esIndicePar = true;
    for(long indice =0; indice <= NUMERO_ITERACIONES; indice++){
        if (esIndicePar == true){
            respuesta += 4.0 / (2.0 * indice + 1.0);
        } else{
            respuesta -= 4.0 / (2.0 * indice + 1.0);
        }
        esIndicePar = !esIndicePar;
    }
    return respuesta;
}

double pi_opm1(){

    int num_hilos = omp_get_num_threads();  //obtiene el numero de hilos

#pragma omp parallel
    {
        #pragma omp master  //ejecuta en el hilo 0
        num_hilos = omp_get_num_threads();
    }

    std::printf("Thread counts: %d\n", num_hilos);

    double sumas_parciales[num_hilos];

#pragma omp parallel shared(sumas_parciales)    //shared: variables compartidas
    {
        int thead_id = omp_get_thread_num();    //id del hilo
        //bool esIndicePar = thead_id%2==0;
        for(long indice = thead_id; indice <= NUMERO_ITERACIONES; indice += num_hilos){
            if (indice%2==0){
                sumas_parciales[thead_id] += 4.0 / (2.0 * indice + 1.0);
            } else{
                sumas_parciales[thead_id] -= 4.0 / (2.0 * indice + 1.0);
            }
            //esIndicePar = !esIndicePar;
        }
    }

    double respuesta = 0;
    for (int i = 0; i < num_hilos; i++) {
        respuesta = respuesta + sumas_parciales[i];
    }

    return respuesta;
}

int main() {

    //omp_set_num_threads(8);
/*
#pragma omp parallel default(none)
    {
        if (omp_get_thread_num() == 0){
            std::printf("I have %d thread(s) \n", omp_get_num_threads());
            std::printf("I have %d thread(s)\n", omp_get_num_threads());
        }

        int thread_id = omp_get_thread_num();
        std::printf("My thread_id is %d\n", thread_id);


        int nthreads = omp_get_num_threads();   //obtiene num hilos
        int thread_id = omp_get_thread_num();     //Id del hilo actual

        std::printf("Hello OMP\n");
        std::printf("I have %d thread(s) and my thread_id is %d\n", nthreads, thread_id);
    }


    return 0;
*/

    double pii;

    auto start = ch::high_resolution_clock::now();
    {
        //pii = pi_serial();
        pii = pi_opm1();

    }
    auto end = ch::high_resolution_clock :: now();
    ch::duration<double, std::milli> duration = end - start;

    //std::printf("Tiempo serial: %lf, pi=%.10lf\n", duration.count(),pii);
    std::printf("Tiempo parallel: %lf, pi=%.10lf\n", duration.count(),pii);

    return 0;

}


