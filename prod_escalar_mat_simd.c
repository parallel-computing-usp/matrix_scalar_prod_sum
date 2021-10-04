#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc,char **argv){
    double inicio = omp_get_wtime();

    // Declara as matrizes
    int *A,*B;
    // Declara as variáveis de índice
    int i,j,dim;
    // Declara o acumulador para o produto escalar global
    long resultado=0;

    // Declara um vetor para os produtos escalares locais
    long *prod_escalar;
    
    fscanf(stdin, "%d\n", &dim); // Lê a dimensão das matrizes
    
    // Aloca as matrizes
    A=(int *)malloc(dim *dim * sizeof(int));
    B=(int *)malloc(dim *dim * sizeof(int)); 

    // Aloca um vetor para armazenar os produtos escalares de cada linha
    prod_escalar=(long *)malloc(dim * sizeof(long));

     // Lê a matriz A
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            fscanf(stdin, "%d ",&(A[i*dim+j]));
        }
    }

    // Lê a matriz B
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            fscanf(stdin, "%d ",&(B[i*dim+j])); 
        }
    }
    
    ///////////////////////////////////////////////////////
    // início da região paralela utilizando 
    ///////////////////////////////////////////////////////   
    // #pragma omp parallel 
    {

        // Calcula o produto escalar de cada linha
        // #pragma omp simd 
        #pragma omp parallel for private(i, j)
        for(i=0;i<dim;i++){
            for(j=0;j<dim;j++){
                prod_escalar[j]+=A[i*dim+j]*B[i*dim+j]; // race condition
            }
        }
    }

        // Acumula os produtos das linhas
        // #pragma omp for private(i)
        for(i=0;i<dim;i++){
            resultado+=prod_escalar[i];
        }
    
    // Imprime o resultado
    printf("%ld",resultado); 

    // Libera as matrizes
    free(A);
    free(B);

    // Libera o vetor
    free(prod_escalar);

    double fim = omp_get_wtime();
    printf("\nTempo decorrido: %f segundos\n", fim - inicio);
}
