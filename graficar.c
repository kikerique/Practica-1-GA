#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define NUM_COMANDOS 6
void ordenar(double*,double*,int);
int main(){
    int numPuntos=0;
    char cadena[100]="set xlabel \"----";
    char valor[30];
    // X, Y valores de los puntos a graficar
    system("clear");
    printf("Ingrese el numero de parejas de datos que desea ingresar al histograma:");
    scanf("%d",&numPuntos);
    printf("Ingrese el rasgo a representar en el histograma\n");
    scanf("%s",valor);
    double* valoresX=(double*)malloc(sizeof(double)*numPuntos);
    double* valoresY=(double*)malloc(sizeof(double)*numPuntos);
    for(int k=0;k<numPuntos;k++)
    {
      printf("\nIngrese la frecuencia correspondiente a la pareja de datos %i\n",k+1);
      getchar();
      scanf("%lf",&valoresY[k]);
      printf("\nIngrese la el valor correspondiente a la pareja de datos %i\n",k+1);
      getchar();
      scanf("%lf",&valoresX[k]);
    }
    //Los valores en x tienen que estar ordenados de menor a mayor para una correcta lectura del histograma
    ordenar(valoresX,valoresY,numPuntos);
    for(int j=0;j<numPuntos;j++)
      printf("%lf\n", valoresX[j]);
    /* se crea y se abre el archivo puntosGraficar.txt en modo escritura 
     * para almacenar los valores de x y y que están declarados en los arreglos
     * valoresX y valoresY*/
    FILE * archivoPuntos = fopen("puntosGraficar.txt", "w");

    /*Guardar los puntos x,y en el archivo de texto creado y abierto previamente*/
    for (int i=0;i<numPuntos+1;i++){
      if(i==0)
      {
        fprintf(archivoPuntos, "%lf %d \n", valoresX[0]-1, 0);
      /*}else if(i==numPuntos){
        fprintf(archivoPuntos, "%lf %d \n", valoresX[numPuntos-1]+10, 0);*/
      }else{
        fprintf(archivoPuntos, "%lf %lf \n", valoresX[i-1], valoresY[i-1]);
      }
    }
    strcat(cadena,valor);
    strcat(cadena,"--->\"");
    
    /*lista de comandos para ejecutar y configurar la visualización que tendrán
     * los puntos en la gráfica con gnuplot*/
    char * configGnuplot[] = {"set title \"Histograma\"", 
                                "set ylabel \"----Frecuencia--->\"",
                                cadena,
                                "set style data histogram",
                                "set style histogram cluster gap 1",
                                "plot \"puntosGraficar.txt\" using 1:2 with linespoints"
                               };

    /*Se crea una archivo de tipo poen, es una tubería IPC que se usa, para
     * ejecutar gnuplot y enviarle el archivo a graficar*/
    FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
    // Ejecuta los comandos de configGnuPlot 1 por 1
    for (int i=0;i<NUM_COMANDOS;i++){
      fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
    }
   fclose(archivoPuntos);
      return 0;
}

//ordena las parejas a graficar en el histograma dependiendo del valor de la variable
void ordenar(double *puntosX,double *puntosY,int tamanio)
{
  double temp1,temp2;
  for(int i=1; i<tamanio;i++){
    for(int j=0;j<tamanio-1;j++){
      if(puntosX[j]>puntosX[j+1])
      {
        temp1=puntosX[j];
        temp2=puntosY[j];
        puntosX[j]=puntosX[j+1];
        puntosY[j]=puntosY[j+1];
        puntosX[j+1]=temp1;
        puntosY[j+1]=temp2;
      }
    }
  }
}