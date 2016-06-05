#define A 3
#define B 4
#define C 5
#define D 6
#define E 7
#define F_SEG 8
#define G 9

// Common anode;
// on when pin is low
// and off when pin is high
#define ON LOW
#define OFF HIGH

const int ms = 500;
const int buttonPin = 11;     // the number of the pushbutton pin
const int coin_pin = 2; /*Asigno el valor de 2 para la variable donde conectare el pin que va a recibir los pulsos del monedero*/
const int limite_pulsos = 250; /* EDITAR ESTE VALOR PARA CAMBIAR EL DELAY ENTRE DETECCION DE PULSOS-nesecito poner un DELAY es como una pausa entre la deteccion de pulsos para que el arduino me lea los pulsos sin arrojar basura, eh calado multiples valores y 500 es el mas estable*/

// variables will change:
int buttonState;         // variable for reading the pushbutton status
int credits = 0;
/* Una variable debe ser declarada como "volátil" cuando su valor puede ser cambiado por algo fuera del control de la sección de código en el que aparece, como un hilo al mismo tiempo de ejecución. En el Arduino, el único lugar que es probable que ocurra en secciones de código asociados a las interrupciones, llama una rutina de servicio de interrupción.*/
volatile byte cont_pulsos_moneda = 0;/*Variable para guardar el valor de los pulsos contados*/
volatile unsigned long tiempo_pulso; /*Variable para guardar el tiempo en el que se leyo e pulso*/
byte pulsos_total; /* lugar para guardar el total de pulsos detectados*/
byte nueva_moneda = 0; /* lugar para guardar el valor de la moneda basandme en el total de pulsos detectados*/


void setup() {

  pinMode(coin_pin, INPUT_PULLUP);/*establecemos el pin 2 (coin_pin) como tipo INPUT y le adjuntamos una resistencia interna para evitar rebotes*/

  pinMode(buttonPin, INPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(coin_pin), sumar_contador_moneda, RISING);

}//end setp()

void loop() {
  Serial.begin(9600);

  // read the state of the switch into a local variable:
  cli();
  buttonState = digitalRead(buttonPin);
  sei();
  // only toggle the LED if the new button state is HIGH
  if (buttonState == HIGH && credits > 0) {
    cli();
    credits--;
    sei();
   // Serial.println("Button Presionado");
  } else if (buttonState == HIGH && credits == 0) {
    Serial.println("Creditos Induficientes!");
  }
  
 /*dejar de contar pulsos si hubo una interrupcion y el contador se incremento entonces hubo una moneda detectada (cont_pulsos_moneda>0) && si el tiempo actual menos el tiempo del ultimo pulso es mayor a los 500 milisegundos entonces hacer lo siguiente*/
    if (cont_pulsos_moneda > 0 && (millis()-tiempo_pulso) > limite_pulsos){
    cli();/*disable interrupts*/
    nueva_moneda = cont_pulsos_moneda; /*Guardo el valor del total de pulsos en esta variable para liberar espacio en la variable cont_pulsos_moneda*/
    sei();/*enable interrupts*/
    
    cli();/*disable interrupts*/
    cont_pulsos_moneda = 0; /*reseteo a 0 el contador de pulsos del interruptor*/
    sei();/*enable interrupts*/  
  }
 switch (nueva_moneda) {
    
    case 3:/*$1.00*/
    Serial.println("$1.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    cli();/*disable interrupts*/
    credits = credits + 1; 
    nueva_moneda = 0; /*reseteo*/
    sei();/*enable interrupts*/
    break;
    
    case 4:/*$2.00*/
    //Serial.println("$2.00 "); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    cli();/*disable interrupts*/
    credits = credits + 2; 
    nueva_moneda = 0; /*reseteo*/
    sei();/*enable interrupts*/
    break;
    
    case 7:/*$5.00*/
    //Serial.println("$5.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    cli();/*disable interrupts*/
    credits = credits + 5;
    nueva_moneda = 0; /*reseteo*/
    sei();/*enable interrupts*/
    break;
    
    case 8:/*$10.00*/
    //Serial.println("$10.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    cli();/*disable interrupts*/
    credits = credits + 9;
    nueva_moneda = 0; /*reseteo*/
    sei();/*enable interrupts*/    
    break;
    
    }/*fin de switch*/
  
 
  //show credits on display
  switch (credits) {
    case 0:
      //Serial.println("0 CREDITOS");
      zero();
      break;

    case 1:
      //Serial.println("MOSTRAR EN LCD EL 1");
      one();
      break;

    case 2:
      //Serial.println("MOSTRAR EN LCD EL 2");
      two();
      break;

    case 3:
      //Serial.println("MOSTRAR EN LCD EL 3");
      three();
      break;

    case 4:
      //Serial.println("MOSTRAR EN LCD EL 4");
      four();
      break;

    case 5:
      //Serial.println("MOSTRAR EN LCD EL 5");
      five();
      break;

    case 6:
      //Serial.println("MOSTRAR EN LCD EL 6");
      six();
      break;

    case 7:
      //Serial.println("MOSTRAR EN LCD EL 7");
      seven();
      break;

    case 8:
      //Serial.println("MOSTRAR EN LCD EL 8");
      eight();
      break;

    case 9:
      //Serial.println("MOSTRAR EN LCD EL 9");
      nine();
      break;

  }//end switch
}//end loop()


void sumar_contador_moneda() /*funcion invocada para incrementar el contador cont_pulsos_moneda*/
{
  cont_pulsos_moneda++;
  tiempo_pulso = millis();/*guardo el tiempo ACTUAL y se lo asigno a la variable como el tiempo cuando leyo el pulso*/
}/*fin sumar_cont_moneda()*/

// 0 => ABCDEF
void zero() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, OFF);
  delay(ms);
}

// 1 => BC
void one() {
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
  delay(ms);
}

// 2 => ABDEG
void two() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, OFF);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
  delay(ms);
}

// 3 => ABCDG
void three() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
  delay(ms);
}

// 4 => BCFG
void four() {
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
  delay(ms);
}

// 5 => ACDFG
void five() {
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
  delay(ms);
}

// 6 => ACDEFG
void six() {
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
  delay(ms);
}

// 7 => ABC
void seven() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
  delay(ms);
}

// 8 => ABCDEFG
void eight() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
  delay(ms);
}

// 9 => ABCDFG
void nine() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
  delay(ms);
}
