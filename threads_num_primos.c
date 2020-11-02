#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define qtd 99999 // quantidade de numeros a serem verificados
#define num_threads 5 // numeros de threads para fazer a veriicaçao


// para o numero ser primo, ele tem q ter dois divisores, ou seja, ele
// eh divisivel por 1 e por ele mesmo
void primos(void *threadid){
    int resto, check, a;
    long i = (long)threadid;

    // while que vai veririca se os numeros de 0 até qtd sao primos
    while(i < qtd){
        check = 0;

        // nesse for sera pego o resto da divisao entre o valor i por a, sendo que
        // a vai ate o num de qtd.
        for(a = 1; a <= qtd; a++){
            resto = i%a; // onde sera armazenado o resto do modulo de i por a

            if(resto == 0) // no caso de for divisivel
                check++; // o check incrementara
        }

        // se o check for igual a 2 quer dizer entao que o numero eh primo
        // ou seja, so eh divisivel por 1 e por ele msm
        if(check == 2){
            printf("o numero %d eh primo\n",i);
        }
        //else
         // printf("o numero %d nao eh primo\n",i);

        i+=num_threads;
    }
}

int main(int argc, char *argv[]) {

  // Conjunto de threads
  pthread_t threads[num_threads];

  // Contador para as threads
  long cont = 0;

  // Contador para o for
  int contd;


  for (contd = 1; contd <= num_threads; contd++) {
    printf("PROCESSO THREAD #%ld\n", contd);

    // &threads[cont]: Endereço onde será armazenado o id único para a thread
    // NULL: Opção para a execução da thread, exemplo, prioridade
    // primos: a rotina/procedimento/segmento que será executado
    // (void *)cont: argumento para a rotina primos
    pthread_create(&threads[cont], NULL, primos, (void *)cont);

    pthread_join(threads[cont], NULL);

    cont++;
    printf("\n");
  }
  pthread_exit(NULL);
}
