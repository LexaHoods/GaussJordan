#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Normalization(float ** Ak,float Akj, int n);
void Simplification(float ** vect1, float ** vect2, float valeur, int n);
void DiagonalizationMat(float ** Aj, float * Aji, float ** Ai, int n);
void DivVector(float *** matrix ,float coef, int n,float * vect);

void FillRandomMatrix(float *** matrix, int n);
void FillVector(float ** vect, int n);
void FillRandomVector(float ** vect, int n);
void FreeTab(float ** matrix,float * vect,int n);

void DisplayMatrix(float ** matrix, int n);
void DisplayVector(float * vector, int n);



int main(void) {
    int n = 0;
    float max = 0;
    float ** A;
    float * temp;
    float temp2;
    float * b;


		//Step 0: Matrix initialization
    printf("Ordre n de la matrice carrée A ? \n");
    scanf(" %d",&n);

	A = (float**)calloc(n,sizeof(float*));
    b = (float*)calloc(n,sizeof(float));
    FillRandomMatrix(&A,n);
    FillRandomVector(&b,n);

    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;

    b[0] = 5;
    b[1] = 6;

    printf("Initial system:\n");
	DisplayMatrix(A, n);
    DisplayVector(b, n);


		//Step 1: Solving system
    int r = -1, k = 0;
    for (int j=0; j<n; j++) {

		max = A[r+1][j];
        k=r+1;

		//Looking for max
        for (int i=r+1; i<n; i++) {
            if (A[i][j] > max) {
                max = A[i][j];
                k = i;
            }
        }

		//If pivot not null
        if (A[k][j] != 0) {
            r++;

            // Normalization of the line to get reduced row echelon form
            b[k] = b[k] / A[k][j];

            Normalization( &(A[k]), A[k][j], n );

            if(k!=r) {
                temp = A[k];
                A[k] = A[r];
                A[r] = temp;
                temp2 = b[k];
                b[k] = b[r];
                b[r] = temp2;
            }

            // Simplification of other lines
            for (int i = 0 ; i < n; i++) {
                if(i != r) {
                    b[i] = b[i] - b[r] * A[i][j];

                    Simplification(&(A[i]), &(A[r]), A[i][j], n);
                }
            }
        }
    }

    printf("Solution:\n");
    DisplayMatrix(A, n);
    DisplayVector(b, n);

    FreeTab(A, b, n);

	return 0;
}



void DiagonalizationMat(float ** Aj, float * Aji, float ** Ai, int n) {
    for (int k = 0 ; k<n ; k++) {
        *(Aj[k]) = *(Aj[k]) - *(Ai[k]) * (*Aji);
    }
}



void Simplification(float ** Ai, float ** Ar, float Aij, int n) {
    for (int i = 0; i<n; i++) {
        (*Ai)[i] = (*Ai)[i] - (*Ar)[i] * Aij;
    }
}



void Normalization(float ** Ak, float Akj, int n) {
    for (int i = 0; i < n; i++) {
        (*Ak)[i] = (*Ak)[i] / Akj;
    }
}



void FillRandomMatrix(float *** matrix, int n) {
    float val;
    srand (time (NULL));

    for (int i=0 ; i < n ; i++) {
        (*matrix)[i] = (float*)calloc(n,sizeof(float));
    }

    for (int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            val = rand()%100;
            (*matrix)[i][j] = val;
        }
    }
}



void FillVector(float ** vect, int n) {
    float val;
    for (int i = 0 ; i < n ; i++) {
        printf("Value of b [%d] ? : \n",i);
        scanf(" %f",&val);
        (*vect)[i] = val;
    }
}



void FillRandomVector(float ** vect, int n) {
    float val;

    (*vect) = (float*)calloc(n,sizeof(float));

    for(int i = 0 ; i < n ; i++) {
        val = rand()%100;
        (*vect)[i] = val;
    }
}



void DisplayMatrix(float ** matrix, int n) {
    printf("Matrix A :\n");
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            printf(" %f \t",matrix[i][j]);
        }
        printf("\n");
    }
}



void DisplayVector(float * vector, int n) {
    printf("Vector b :\n");
    for (int i = 0 ; i < n ; i++) {
        printf(" %f \t",vector[i]);
        printf("\n");
    }
    printf("\n");
}



void FreeTab(float ** matrix,float * vect,int n) {
    for (int i = 0 ; i < n ; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vect);
}
