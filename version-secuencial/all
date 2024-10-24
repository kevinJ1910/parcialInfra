#!/usr/bin/env bash
#
# Este script se encarga de invocar los tres programas que permiten la 
# conversion de un PNG a secuencia de pixeles, se procesan esos pixeles y
# posteriormente se convierte esa secuencia de pixeles a un archivo en formato
# PNG
#
# Autor: Kevin Jordan Alzate - kevin.jordan@correounivalle.edu.co
# Fecha: 2024-10-24
#
# Este script procesará todas las imágenes PNG de la carpeta png_images
for image in png_images/*.png; do
    echo "Procesando $image..."
    INPUT_PNG="$image"
    TEMP_FILE="${image%.*}.bin"
    python3 fromPNG2Bin.py ${INPUT_PNG}
    ./main ${TEMP_FILE}
    python3 fromBin2PNG.py ${TEMP_FILE}.new
done


