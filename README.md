## Descripción del Proyecto
En este proyecto se busca desarrollar los conocimientos de Arduino, en el cual se implementa un Arduino Mega con la utilización de una Pantalla Touch TFT 3.5". En el código se realiza una interfaz grafica que permite comunicarse con componentes electrónicos externos. Así mismo se incorporó imágenes personalizadas en la interfaz del proyecto.

## Materiales 
* 1 Arduino Mega.
* 1 Pantalla Touch TFT 3.5".
* 2 Protoboard.
* 1 Decoder 74LS48.
* 1 Display de 7 segmentos.
* 5 Leds.
* Resistencias de 1 Khom.
* Cables Jumper.

---
## Elaboración del Proyecto 
Iniciaremos calibrando la pantalla, para la cual necesitamos instalar la librería de MCUFRIEND_kbv, esta instalación se realiza desde las propias herramientas del IDE de Arduino. Posteriormente se procederá a ir a los ejemplos que se encuentran en el entorno de desarrollo, como se muestra acontinuacion:
![Memexd](https://i.ibb.co/hR7000b/image.png)


Cargaremos el ejemplo seleccionado a la placa de Arduino, con la cual se nos mostrara una pantalla con indicadores de donde debemos presionar. Así como se muestra en la siguiente imagen:
![Memexd](https://i.ibb.co/C0mVhXG/20240529-105851-1.jpg)

Posteriormente se nos mostrara la información de la calibración de la imagen, con los datos necesarios para el funcionamiento correcto de la pantalla:
![Memexd](https://i.ibb.co/fNZ0HH6/image.png)


Procederemos a realizar las conexiones necesarias para el funcionamiento del proyecto. Para este caso se eligieron las terminales digitales del 22 al 25 en los cuales se conectan a las entras del integrado 74LS48 respectivamente. A los pines digitales del 46 al 50 se conectan los leds para realizar la secuencia de iluminación. Quedando la conexión de la siguiente manera:
![Memexd](https://i.ibb.co/tXvMDBf/20240529-105155-1.jpg)


Se cargará el ejemplo denominado Cuatro_Boton.ino, en el cual se encuentra el código para la interfaz. El dispositivo iniciara con un mensaje de bienvenido y así mismo con una imagen:
![Memexd](https://i.ibb.co/mzXjckV/20240529-094801-1.jpghttps://i.ibb.co/qpstt90/20240529-094634-1.jpg)

El mensaje de inicio se mostrará durante 5 segundos, posteriormente se mostrara la interfaz gráfica con los siguientes botones:
* CONSOLA
    * -->
    * CHANGE
    * <--
    * ++
    * --
* STAN BYE

Además, en la parte de la CONSOLA se muestra un cuadrado que cambia de color con respecto de que botón se presiones. También se muestra la hora y la fecha, iniciando la hora a las 00 horas
![Memexd](https://i.ibb.co/8cvGvM7/20240529-094640-1.jpg)

---
## Funcionalidades 
### CONSOLA:

Procederemos presionando el botón **-->** el cual encenderá los ledes en una secuencia lineal: 
![Memexd](https://i.ibb.co/bWnYt6h/20240529-094652-1.jpg)

Procederemos presionando el botón **CHANGE** el cual empezara una secuencia ascendente del número 0 al 9 de manera automática, al finalizar el diplay regresara al estado inicial es decir el numero 0:
![Memexd](https://i.ibb.co/d03HxCp/20240529-094703-1.jpg)

Presionando el botón **<--** se iniciara la secuencia descendente de los ledas, es decir los leds se encenderán de derecha hacia la izquierda de manera automática: 
![Memexd](https://i.ibb.co/9H9t7k2/20240529-094717-1.jpg)

Al presionar el botón de **++** se nos incrementara el número del diplay en una unidad: 
![Memexd](https://i.ibb.co/HPBDzRN/20240529-094730-1.jpg)

Al presionar el botón de **--** se nos decrementara el número del diplay en una unidad: 
![Memexd](https://i.ibb.co/TcKzdk6/20240529-094748-1.jpg)

### STAN BYE:

Al posicionarnos en la ventana de STAN BYE se nos mostrara una imagen personalizada, así mismo como la hora y fecha. En la misma ventana se tiene los botones para volver a regresar a la ventana de la CONSOLA: 
![Memexd](https://i.ibb.co/tHfS0S8/20240529-094801-1.jpg)

---
En este proyecto se utilizaron los ejemplos ya dispuestos en el IDE de Arduino, los cuales son: **button_simple y graphictest_kbv** los cuales vienen instalados en la librería de MCUFRIEND_kbv.h. Además en la utilización de las imágenes se empleó el siguiente tutorial:  [ADC49 - Imágenes en TFT 3.5](https://www.youtube.com/watch?v=XTnLl6UMd6U&list=WL&index=1&t=1100s). 

---

Información del desarrollador::
| Nombre             | Puesto | 
| --                     | -- |
| Miguel Adrian Tubac Agustin     | Desarrollador Arduino|