//Authro: Roy Flores Flores
//Dispensar monedas con hopper, utilizando una variable definida
//en el codigo, la variable monedas indica la cantidad de monedas que seran
//vomitadas por el hopper
//- En esta versión se añade una pantalla LCD.

//- El pin de I2C es 20 para SDA y 21 para SCL

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int sensor_pin = 2;

byte controlRelevador = 0; //controla el estado del relevador
const int ctrl_relv = 8; //pin 8 conectado al relevador
//declaración de variables
volatile unsigned long limiteDeTiempo_pulso = 3;
volatile unsigned long tiempoPulso_inicial;
volatile unsigned long tiempoPulso_final;

//declarar variables
volatile unsigned cont_pulsos_moneda = 0;
//cantidad de monedas que se van a disensar
int monedas = 13;

//objetos
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode( sensor_pin, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( sensor_pin), PULSE_CO, RISING);

  lcd.begin(16, 2); //Inicializar LCD para 16 caracteres y 2 lineas

  for(int i=0; i<3; i++){
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();

  lcd.setCursor(0,0);lcd.print("CREDITOS:");
  lcd.setCursor(0,1);lcd.print(monedas);

  //pin de control para el relevador
  pinMode( ctrl_relv, OUTPUT);
  digitalWrite( ctrl_relv, OUTPUT);
}

void loop() {
  //Se muestra cuantas monedas quedan por tirar en la pantalla LCD
  lcd.setCursor(0,0);lcd.print("CREDITOS:");
  lcd.setCursor(0,1);lcd.print(monedas);
  delay(200);

  //control para pruebas: si se presiona a en el teclado seran expulsadas las monedas
  //hasta que monedas sea menor o igual a cero, la variabla monedas es decrementada
  //en la función PULSE_CO invocada por el attachInterrupt
  //una vez vomitadas todas las variables ctrl_rel cambia a HIGH para detener
  //el hopper
  controlRelevador = Serial.read();
  if ( controlRelevador == 'a' && monedas >= 0 ){
    digitalWrite( ctrl_relv, LOW );
  } 
  if ( controlRelevador == 's' || monedas <=0){
    digitalWrite( ctrl_relv, HIGH );
    monedas = 13;
  }
  
}

void PULSE_CO(){
  
  tiempoPulso_inicial = micros();

  if( digitalRead( sensor_pin) == HIGH ){
     tiempoPulso_final = micros();

     if( tiempoPulso_final - tiempoPulso_inicial > limiteDeTiempo_pulso ){
      cont_pulsos_moneda++;
      monedas--;
     }
  }
Serial.println( tiempoPulso_final - tiempoPulso_inicial );
Serial.println( monedas);
}
