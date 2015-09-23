#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TESTMEM(s) if (s == NULL) {\
fprintf(stderr, "(0x45) Erro detetado: Memory Access Error!");      \
exit(2);                                                       \
}

void printUsage() {
  puts("Utilizacao: \n"
  "     ./lab5a <matriz de input>.adj");
}

int readMatrixFromFile(char * name, int *** matriz_adj, int * N) {
  int i, j;
  int ** M = NULL;
  FILE * fin = NULL;

  fin = fopen(name, "r");
  if (fin == NULL) {
    printf("Não foi possível abrir o ficheiro '%s'!", name);
    return 3;
  }

  fscanf(fin,"%d", N);
  if (*N<=1) {
    printf("Valor inválido para N (%d)!", *N);
    return 1;
  }

  M = (int **) malloc(sizeof(int *) * (*N));
  memset(M,0,sizeof(int*) * (*N));
  TESTMEM(M);
  for (i=0;i<*N;i++) {
    M[i] = malloc(sizeof(int)*(*N));
    TESTMEM(M[i]);
    memset(M[i], -1, sizeof(int)*(*N));
  }

  for (i=0; i<*N; i++) {
    for (j=0; j<*N; j++) {
      fscanf(fin, "%d", &(M[i][j]));
    }
  }

  *matriz_adj = M;
  fclose(fin);
  return 0;
}

int getEdgeCount(int ** M, int N) {
  int i,j;
  int D=0;
  for (i=0; i<N; i++) {
    for (j=i+1; j<N; j++) {
      if (i!=j && M[i][j] != 0)
        D++;
    }
  }
  return D;
}

double getGraphDensity(int ** M, int N) {
  return (double) ((2.0*getEdgeCount(M,N)) / (double)N);
}

int getGraphHighRank(int ** M, int N) {
  int i,j;
  int ans = 0;
  int rn;
  for (i=0; i<N; i++) {
    rn=0;
    for (j=0; j<N; j++) {
      if (i!=j && M[i][j] != 0)
        rn++;
    }
    ans = rn > ans ? rn : ans;
  }
  return ans;
  return 1;
}



int writeMatrixToFile(char * oldname, int **M, int N) {
  int i,j;
  FILE * fout= NULL;
  i = strlen(oldname);
  oldname[i-3]='r';
  oldname[i-2]='a';
  oldname[i-1]='m';
  fout = fopen(oldname, "w");
  if (fout == NULL) {
    printf("Não foi possível abrir o ficheiro '%s'!", oldname);
    return 3;
  }
  fprintf(fout, "%d\n", N);
  fprintf(fout, "%d\n", getEdgeCount(M,N));
  for (i=0; i<N; i++) {
    for (j=i+1; j<N; j++) {
      if (i!=j && M[i][j] != 0)
        fprintf(fout, "%d %d %d\n", i, j, M[i][j]);
    }
  }

  fclose(fout);

  i = strlen(oldname);
  oldname[i-3]='a';
  oldname[i-2]='d';
  oldname[i-1]='j';
  return 1;
}

int main(int argc, char **argv, char **envp) {
  int ** matriz_adj = NULL;
  int N;
  int i;
  if (argc != 2) {
    printUsage();
    exit(1);
  }
  if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".adj") != 0) {
    printUsage();
    exit(1);
  }

  if (readMatrixFromFile(argv[1], &matriz_adj, &N)) {
    printf("Erro na leitura da matriz do ficheiro!!!\n");
    exit(3);
  }

  printf("Densidade do grafo: %.4f\n", getGraphDensity(matriz_adj, N));
  printf("Grau maximo do grafo: %d\n", getGraphHighRank(matriz_adj, N));
  writeMatrixToFile(argv[1], matriz_adj, N);

  for (i=0;i<N;i++)
    free(matriz_adj[i]);
  free(matriz_adj);
  return 0;
}
