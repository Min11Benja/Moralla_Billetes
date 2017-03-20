//Dispensar monedas con hopper, utilizando una variable definida
//en el codigo, la variable monedas indica la cantidad de monedas que seran
//vomitadas por el hopper

//Configuración:
///Sensor de monedas de hopper a pin 2 de arduino.
///Control de relevador a pin 8

//25-Feb-2017
//Prueba de circuito inversor 74ls14 (usando 74ls04)
//04-Mar-2017
//Arduino-shield

const int sensor_pin = 20;

byte controlRelevador = 0; //controla el estado del relevador
const int ctrl_relv = 14; //pin 8 conectado al relevador
//declaración de variables
volatile unsigned long limiteDeTiempo_pulso = 3;
volatile unsigned long tiempoPulso_inicial;
volatile unsigned long tiempoPulso_final;

//declarar variables
volatile unsigned cont_pulsos_moneda = 0;

//cantidad de monedas que se van a disensar
int monedas = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode( sensor_pin, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( sensor_pin), PULSE_CO, RISING);

  //pin de control para el relevador
  pinMode( ctrl_relv, OUTPUT);
  digitalWrite( ctrl_relv, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

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
    monedas = 2;
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
Serial.print("Pulsos:   ");
Serial.println( cont_pulsos_moneda);
}

