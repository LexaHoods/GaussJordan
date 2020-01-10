#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float* Normalization(float * vect1, float coef,int dim);
float* Simplification(float * vect1, float * vect2, float valeur, int dim);
float* Diagonalization(float * vect1,float valeur,float * vect2,int dim);
float Diagonalization2(float vect1,float valeur,float * vect2,int dim);
void FillMatrix(float *** matrix, int dim);
void FillVector(float ** vect, int dim);
void DisplayMatrix(float ** matrix, int dim);
void DisplayVector(float * vector, int dim);
void DivVector(float *** matrix ,float coef, int dim,float * vect);
void FreeTab(float ** matrix,float * vect,int dim);

int main(){
 int dim = 0;
 float max = 0;
 float ** matrixA;
 float ** matrixAcopy;
 float * temp;
 float temp2;
 float * vectB;
 //Size of matrix :
 printf("Ordre n de la matrice carrée A ? \n");
 scanf(" %d",&dim);
 matrixA = (float**)calloc(dim,sizeof(float*));
 vectB = (float*)calloc(dim,sizeof(float));
 FillMatrix(&matrixA,dim);
 FillVector(&vectB,dim);
 DisplayMatrix(matrixA,dim);
 DisplayVector(vectB,dim);
 //Choice of pivot at line K :
 int r = -1, j = 0, i = 0, k = 0;
 for (int j = 0 ; j < dim; j++){
   max = matrixA[r+1][j];
   k=r+1;
   // looking for max :
   for (int i =r+1; i < dim; i++){
     if (matrixA[i][j] > max){
       max = matrixA[i][j];
       k = i;
     }
  //   printf("max = %f , k = %d \n",max,k );
   }
   // if pivot not null :
   if (matrixA[k][j] != 0){
        r++;
     // Normalization of the line to get echelon form :
      matrixA[k] = Normalization(matrixA[k],matrixA[k][j],dim);
      // printf("après Normalization: r = %d, k = %d \n",r,k );
      // DisplayMatrix(matrixA,dim);
    //  DisplayVector(vectB,dim);
     if(k!=r){
       temp = matrixA[k];
       matrixA[k] = matrixA[r];
       matrixA[r] = temp;
       temp2 = vectB[k];
       vectB[k] = vectB[r];
       vectB[r] = temp2;
     }
     /*
       printf("Avant Simplification :\n");
       DisplayMatrix(matrixA,dim);
       DisplayVector(vectB,dim);*/

       // Simplification of other lines :
       for (int i = 0 ; i < dim; i++){
         if(i!=r){
              vectB[i] = vectB[i]-(vectB[r]*matrixA[i][j]);
              matrixA[i] = Simplification(matrixA[i],matrixA[r],matrixA[i][j],dim);
         }
       }
    /*   printf("Après Simplification :\n");
       DisplayMatrix(matrixA,dim);
       DisplayVector(vectB,dim);*/

   }
   printf("Avant Diagonalization :\n");
   DisplayMatrix(matrixA,dim);
   DisplayVector(vectB,dim);
   //Diagonalization : #TODO : corriger la diagonalisation ? vérifier les valeurs de b.
   for(int i = dim-1; i>=1 ; i--) {
     for (int j = i-1 ; j>=0;j--) {
        matrixA[j] = Diagonalization(matrixA[j],matrixA[j][i],matrixA[i],dim);
        vectB[j] = Diagonalization2(vectB[j],vectB[i],matrixA[i],dim);
     }
   }
   printf("Après Diagonalization :\n");
   DisplayMatrix(matrixA,dim);
   DisplayVector(vectB,dim);

 }
 printf("\n Fin : \n");
 DisplayMatrix(matrixA,dim);
 printf("\n");
 DisplayVector(vectB,dim);
 FreeTab(matrixA,vectB,dim);
 return 0;
}

float* Diagonalization(float * vect1,float valeur,float * vect2,int dim){
  for (int i = 0 ; i <dim ; i++){
    vect1[i] = vect1[i]-(valeur*vect2[i]);
    }
  return vect1;
}
float Diagonalization2(float vect1,float valeur,float * vect2,int dim){
  for (int i = 0 ; i <dim ; i++){
    vect1=vect1-(valeur*vect2[i]);
    }
  return vect1;
}

float* Simplification(float * vect1, float * vect2, float valeur, int dim){
  for (int i = 0 ; i <dim ; i++){
    vect1[i] = vect1[i]-(vect2[i]*valeur);
    }
  return vect1;
}

float * Normalization(float * vect1,float coef, int dim){
  for (int i = 0 ; i <dim ; i++){
    vect1[i] = vect1[i]/coef;
    }
  return vect1;

}

void FillMatrix(float *** matrix, int dim){
  float val;
  srand (time (NULL));
  for (int i=0 ; i < dim ; i++) {
    (*matrix)[i] = (float*)calloc(dim,sizeof(float));
  }
  for (int i = 0 ; i < dim ; i++){
    for(int j = 0 ; j < dim ; j++){
      //printf("valeur de la matrice A [%d][%d] ? : \n",i,j);
    //  scanf(" %f",&val);
        val = rand()%100;
      (*matrix)[i][j] = val;
    }
  }
}

void FillVector(float ** vect, int dim){
  float val;
  for (int i = 0 ; i < dim ; i++){
      printf("valeur du vecteur b [%d] ? : \n",i);
      scanf(" %f",&val);
      (*vect)[i] = val;
    }
}

void DisplayMatrix(float ** matrix, int dim){
  for (int i = 0 ; i < dim ; i++){
    for (int j = 0 ; j < dim ; j++){
      printf(" %f \t",matrix[i][j]);
    }
    printf("\n");
  }
}

void DisplayVector(float * vector, int dim){
  printf("\nValeur du vecteur b :\n");
  for (int i = 0 ; i < dim ; i++){
      printf(" %f \t",vector[i]);
    printf("\n");
  }
}

void FreeTab(float ** matrix,float * vect,int dim){
  for (int i = 0 ; i < dim ; i++){
    free(matrix[i]);
  }
  free(matrix);
  free(vect);
}
