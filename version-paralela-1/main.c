#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>
// Funciones placeholder para la carga y guardado de imágenes
void cargarImagen(int *imagen, int width, int height);
void guardarImagen(int *imagen, int width, int height);

// Función para aplicar un filtro simple
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height);

// Función para calcular la suma de los píxeles (como una estadística)
int calcularSumaPixeles(int *imagen, int width, int height);

char *filename;

int main(int argc, char* argv[]) {
    int width = 1024, height = 1024;
    int *imagen = (int *)malloc(width * height * sizeof(int));
    int *imagenProcesada = (int *)malloc(width * height * sizeof(int));

    if (argc != 2) {
      fprintf(stderr, "Dar un nombre de archivo de entrada");
      exit(1);
    }

    filename = argv[1];
    // Cargar la imagen (no paralelizable)
    cargarImagen(imagen, width, height);

    // Aplicar filtro (paralelizable)
    aplicarFiltro(imagen, imagenProcesada, width, height);

    // Calcular suma de píxeles (parte paralelizable)
    int sumaPixeles = calcularSumaPixeles(imagenProcesada, width, height);

    printf("Suma de píxeles: %d\n", sumaPixeles);

    // Guardar la imagen (no paralelizable)
    guardarImagen(imagenProcesada, width, height);

    free(imagen);
    free(imagenProcesada);
    return 0;
}

// Carga una imagen desde un archivo binario
void cargarImagen(int *imagen, int width, int height) {
    FILE *archivo = fopen(filename, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para cargar la imagen");
        return;
    }

    size_t elementosLeidos = fread(imagen, sizeof(int), width * height, archivo);
    if (elementosLeidos != width * height) {
        perror("Error al leer la imagen desde el archivo");
    }

    fclose(archivo);
}

// Guarda una imagen en un archivo binario
void guardarImagen(int *imagen, int width, int height) {
    char *output_filename;

    output_filename = (char*)malloc(sizeof(char)*(strlen(filename) + 4));
    sprintf(output_filename,"%s.new",filename);
    FILE *archivo = fopen(output_filename, "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para guardar la imagen");
        return;
    }
    size_t elementosEscritos = fwrite(imagen, sizeof(int), width * height, archivo);
    if (elementosEscritos != width * height) {
        perror("Error al escribir la imagen en el archivo");
    }

    fclose(archivo);
}


int calcularSumaPixeles(int *imagen, int width, int height) { 
    int suma = 0;
    #pragma omp parallel 
    {
        int sumaLocal = 0; // Variable local por hilo
        #pragma omp for
        for (int i = 0; i < width * height; i++) {
            sumaLocal += imagen[i];
        }
        #pragma omp atomic // Asegura la suma atómica
        suma += sumaLocal;
    }
    return suma;
}



/**
 * Función que aplica el filtro Sobel a una imagen de entrada y genera una imagen procesada.
 * Esta función paraleliza el proceso utilizando OpenMP. Cada hilo procesa
 * un bloque de píxeles para maximizar la eficiencia. La distribución del
 * trabajo se hace para asegurar
 * que la carga de trabajo se distribuya equitativamente entre los hilos, evitando
 * que algunos hilos se queden inactivos si ciertas áreas son más costosas de procesar.
 */
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height) {
    // Máscaras de Sobel
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Paralelización del bucle externo con distribución dinámica para mejorar el balance de carga
    #pragma omp parallel for schedule(static)
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            // Aplicación de las máscaras de Sobel (Gx y Gy)
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += imagen[(y + ky) * width + (x + kx)] * Gx[ky + 1][kx + 1];
                    sumY += imagen[(y + ky) * width + (x + kx)] * Gy[ky + 1][kx + 1];
                }
            }

            // Cálculo de la magnitud del gradiente
            int magnitude = abs(sumX) + abs(sumY);
            imagenProcesada[y * width + x] = (magnitude > 255) ? 255 : magnitude;
        }
    }
}
