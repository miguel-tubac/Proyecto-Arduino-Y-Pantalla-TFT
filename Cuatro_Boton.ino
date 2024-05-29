// Horientacion Landscape:

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

//Libreria de la hora:
#include <TimeLib.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Definiciones para el panel táctil y calibración en rotación 1
const int XP = 8, XM = A2, YP = A3, YM = 9; //320x480 ID=0x9486
const int TS_LEFT=966, TS_RT=82, TS_TOP=917, TS_BOT=119; // Ajustados para rotación 1

// Inicialización del touch screen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn, ch_btn, mas_btn, menos_btn, consola_btn, stanBay_btn;

int pixel_x, pixel_y; // Variables globales actualizadas por Touch_getXY()

int tiempo = 300; //Se agregan leds
int pin;

int numeroDecimal;
int numeroBinario;
int numero_inicial = 0;

// variable de incio del programa
bool inicio = true;

// Función para obtener coordenadas del touch
bool Touch_getXY(void) {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT); // Restaurar pines compartidos
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH); // Debido a los pines de control del TFT
    digitalWrite(XM, HIGH);

    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        // Ajustar mapeo para la rotación 1
        pixel_x = map(p.y, TS_TOP, TS_BOT, 0, tft.width());
        pixel_y = map(p.x, TS_LEFT, TS_RT, 0, tft.height());
    }
    return pressed;
}

// Definición de colores
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

void setup(void) {
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // Para shields write-only
    tft.begin(ID);
    tft.setRotation(1); // Cambiar a rotación 1
    imagenInicio(); // Llamada a la imagen de incio
    tft.fillScreen(BLACK);

    // Ajustar coordenadas y tamaños de los botones para rotación 1
    on_btn.initButton(&tft, 280, 95, 100, 40, WHITE, CYAN, BLACK, "-->", 2);
    ch_btn.initButton(&tft, 280, 155, 100, 40, WHITE, CYAN, BLACK, "CHANGE", 2);
    off_btn.initButton(&tft, 280, 215, 100, 40, WHITE, CYAN, BLACK, "<--", 2);
    mas_btn.initButton(&tft, 410, 95, 100, 40, WHITE, CYAN, BLACK, "++", 2);
    menos_btn.initButton(&tft, 410, 215, 100, 40, WHITE, CYAN, BLACK, "--", 2);
    consola_btn.initButton(&tft, 118, 15, 245, 50, BLUE, WHITE, BLACK, "CONSOLA", 2);
    stanBay_btn.initButton(&tft, 360, 15, 245, 50, BLUE, WHITE, BLACK, "STAN BYE", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);
    ch_btn.drawButton(false);
    menos_btn.drawButton(false);
    mas_btn.drawButton(false);
    consola_btn.drawButton(false);
    stanBay_btn.drawButton(false);

    // Dibujo inicial del rectángulo
    tft.fillRect(40, 75, 160, 160, RED); // Ajustar dimensiones y posición para rotación 1

    // Establece los pines para los leds
    for(pin = 46; pin <= 50; pin++){
    pinMode(pin, OUTPUT);
    }

    // Establece los pines para el display
    for(pin = 22; pin <= 25; pin++){
    pinMode(pin, OUTPUT);
    }

    //Estblece la hora:
    setTime(0,0,0,29,9,2024);//hr,mm,s,d,m,y
}

// Array de botones para manejar en lista
Adafruit_GFX_Button *buttons[] = { &on_btn, &off_btn, &ch_btn, &mas_btn, &menos_btn, NULL };
Adafruit_GFX_Button *buttonsGeneral[] = { &consola_btn, &stanBay_btn, NULL };

// Actualización del estado de un botón y redibujar si es necesario
bool update_button(Adafruit_GFX_Button *b, bool down) {
    b->press(down && b->contains(pixel_x, pixel_y));
    if (b->justReleased()) b->drawButton(false);
    if (b->justPressed()) b->drawButton(true);
    return down;
}

// Actualización de todos los botones en la lista
bool update_button_list(Adafruit_GFX_Button **pb) {
    bool down = Touch_getXY();
    for (int i = 0; pb[i] != NULL; i++) {
        update_button(pb[i], down);
    }
    return down;
}

// Inicio de las secuancias
void secuencia_uno(){
  for(pin = 46; pin <= 50; pin++){
    digitalWrite(pin, HIGH);
    delay(tiempo);
    digitalWrite(pin, LOW);
    delay(tiempo);
  }
}

void secuencia_dos(){
  for(pin = 50; pin >= 46; pin--){
    digitalWrite(pin, HIGH);
    delay(tiempo);
    digitalWrite(pin, LOW);
    delay(tiempo);
  }
}
// Fin de las secuancias

// Convercion a binario
int binario(int x){
  digitalWrite(22, bitRead(x,0)); //Escribimos el valor del bit 0
  digitalWrite(23, bitRead(x,1)); //Escribimos el valor del bit 1
  digitalWrite(24, bitRead(x,2)); //Escribimos el valor del bit 2
  digitalWrite(25, bitRead(x,3)); //Escribimos el valor del bit 3
}
// Fin binario

// Suma de numeros en el display
void mas(){
  if(numero_inicial == 9){
    numero_inicial = 0;
    binario(numero_inicial);
    secuencia_uno();
  }
  else{
    numero_inicial ++;
    binario(numero_inicial);
  }
  delay(200);
}

// Resta de numeros en el display
void menos(){
  if(numero_inicial == 0){
    numero_inicial = 9;
    binario(numero_inicial);
    secuencia_dos();
  }
  else{
    numero_inicial --;
    binario(numero_inicial);
  }
  delay(200);
}
// Fin metodos del display

// Aca incia los metodos para agregar la hora y fecha a la pantalla
void reloj(){
  String tiempo = String(hour()) + ":" + dato(minute()) + ":" + dato(second());
  hora(10, 280, tiempo);
  String fecha = dato(day()) + "-" + dato(month()) + "-" + String(year());
  hora(295, 280, fecha);
}

void hora(int x, int y, String texto){
  tft.setCursor(x, y);
  tft.setTextSize(3);
  tft.setTextColor(WHITE, BLACK); // Establece el color del texto y el color de fondo
  tft.println(texto);
}

String dato(int digit){
  String dt = String("0") + digit;
  return dt.substring(dt.length()-2);
}
//Fin de agregar fecha y hora

//Metodo para agregar una imagen:
void imagenFondo(){
  tft.fillScreen(BLACK);
  //Agrarrar la imagen:
  extern const uint8_t fondoPaisajeRio[];
  tft.setAddrWindow(180, 150, 180+120, 150+66); // x0, y0, x1, y1
  tft.pushColors(fondoPaisajeRio, 120*66, 1);
}

void imagenInicio(){
  tft.fillScreen(WHITE);
  //Agrarrar la imagen:
  hora(165, 100, "BIENVENIDO");
  extern const uint8_t fondoPaisajeBlancoYNegro[];
  tft.setAddrWindow(180, 150, 180+150, 150+82); // x0, y0, x1, y1
  tft.pushColors(fondoPaisajeBlancoYNegro, 150*82, 1);
  delay(5000);
}

//Fin de imagenes

//Metodo general de los botones
void metodoGeneral(){
  reloj();
  update_button_list(buttonsGeneral);
  update_button_list(buttons); // Usar la función auxiliar para actualizar botones
  if (on_btn.justPressed()) {
      tft.fillRect(40, 75, 160, 160, GREEN); // Ajustar dimensiones y posición para rotación 1
      secuencia_uno();
  }
  if (off_btn.justPressed()) {
      tft.fillRect(40, 75, 160, 160, RED); // Ajustar dimensiones y posición para rotación 1
      secuencia_dos();
  }
  if (ch_btn.justPressed()) {
      tft.fillRect(40, 75, 160, 160, MAGENTA); // Ajustar dimensiones y posición para rotación 1
      for(numeroDecimal = 0; numeroDecimal <= 9; numeroDecimal++){
        numeroBinario = binario(numeroDecimal);
        delay(1000);
      }
      binario(0);// Regresamos a cero
      delay(1000);
  }
  if (mas_btn.justPressed()) {
      mas();// Llamanda al metodo mas
  }
  if (menos_btn.justPressed()) {
      menos(); // Llamanda al metodo menos
  }
}
//Fin del metod general

//Metodo de stan bay
void metodoStanBay(){
  imagenFondo();
  for (int i = 0; buttonsGeneral[i] != NULL; i++) {
      buttonsGeneral[i]->drawButton(false); // Redibuja botones generales
  }
}
//Fin del metodo



void loop() {
  if(inicio == true){
    metodoGeneral(); //Se muestran los botones de incio
  }
  else if(inicio == false){//en esta parte se muestra la parte cuando se accede a stanbye
    reloj();
    update_button_list(buttonsGeneral); //Se actualizan los botones principales
  }
  if (consola_btn.justPressed()) {//Aca es cuando se preciona el boton de la consola
    tft.fillScreen(BLACK);//Se actauliza el fondo de pantalla
    for (int i = 0; buttonsGeneral[i] != NULL; i++) {
      buttonsGeneral[i]->drawButton(false); // Redibuja botones generales
    }
    for (int i = 0; buttons[i] != NULL; i++) {
      buttons[i]->drawButton(false); // Redibuja botones de la pantalla principal
    }
    tft.fillRect(40, 75, 160, 160, RED);//Redibuja el cuadrado de color rojo
    inicio = true;
  }
  if (stanBay_btn.justPressed()) {//Cuando se preciona el boton de stanbye
    metodoStanBay();
    inicio = false;
  }  
}




/*
//Horinetacion Portrain

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// Definiciones para el panel táctil y calibración
const int XP=8, XM=A2, YP=A3, YM=9; //320x480 ID=0x9486
const int TS_LEFT=119, TS_RT=917, TS_TOP=966, TS_BOT=82;

// Inicialización del touch screen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x, pixel_y;     // Variables globales actualizadas por Touch_getXY()

// Función para obtener coordenadas del touch
bool Touch_getXY(void) {
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      // Restaurar pines compartidos
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   // Debido a los pines de control del TFT
    digitalWrite(XM, HIGH);

    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

// Definición de colores
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void) {
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // Para shields write-only
    tft.begin(ID);
    tft.setRotation(1);            // Modo retrato
    tft.fillScreen(BLACK);

    // Inicialización de botones
    on_btn.initButton(&tft, 60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
    off_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);
    on_btn.drawButton(false);
    off_btn.drawButton(false);

    // Dibujo inicial del rectángulo
    tft.fillRect(40, 80, 160, 80, RED);
}

// Array de botones para manejar en lista
Adafruit_GFX_Button *buttons[] = {&on_btn, &off_btn, NULL};

// Actualización del estado de un botón y redibujar si es necesario
bool update_button(Adafruit_GFX_Button *b, bool down) {
    b->press(down && b->contains(pixel_x, pixel_y));
    if (b->justReleased()) b->drawButton(false);
    if (b->justPressed()) b->drawButton(true);
    return down;
}

// Actualización de todos los botones en la lista
bool update_button_list(Adafruit_GFX_Button **pb) {
    bool down = Touch_getXY();
    for (int i = 0; pb[i] != NULL; i++) {
        update_button(pb[i], down);
    }
    return down;
}

void loop(void) {
    update_button_list(buttons);  // Usar la función auxiliar para actualizar botones
    if (on_btn.justPressed()) {
        tft.fillRect(40, 80, 160, 80, GREEN);
    }
    if (off_btn.justPressed()) {
        tft.fillRect(40, 80, 160, 80, RED);
    }
}
*/
