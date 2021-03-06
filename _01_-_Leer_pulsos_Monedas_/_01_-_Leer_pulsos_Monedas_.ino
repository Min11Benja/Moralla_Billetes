//Leer pulsos del Monedero multiple y sumarlos como creditos por min11benja para Morralla
//Variables Globales
////Lo pongo como variables de tipo constante para guardar espacio en memoria
//***********************************************************************************************
volatile unsigned long limite_pulsos = 3;
  // EDITAR ESTE VALOR PARA CAMBIAR EL DELAY ENTRE DETECCION DE PULSOS-nesecito poner un DELAY es como una pausa entre la deteccion de pulsos para que el arduino me lea los pulsos sin arrojar basura, eh calado multiples valores y 500 es el mas estable
//***********************************************************************************************
const int coin_pin = 2; //Asigno el valor de 2 para la variable donde conectare el pin que va a recibir los pulsos del monedero
////// Una variable debe ser declarada como "volátil" cuando su valor puede ser cambiado por algo fuera del control de la sección de código en el que aparece, como un hilo al mismo tiempo de ejecución. En el Arduino, el único lugar que es probable que ocurra en secciones de código asociados a las interrupciones, llama una rutina de servicio de interrupción.
volatile byte credit = 0;//Variable para guardar el valor de los pulsos contados
volatile unsigned long tiempo_pulso_inicial; //Variable para guardar el tiempo en el que se leyo e pulso
volatile unsigned long tiempo_pulso_final; //Variable para guardar el tiempo en el que se leyo e pulso
byte cmd=0; //Esta variable guardara la letra que tecles en consola del ide del arduino

void setup() {
  Serial.begin(9600);// Establece la velocidad de datos en bits por segundo (baudios) para la transmisión de datos en serie. Para comunicarse con la pc
  Serial.println("Cargando Setup, por favor esperar...");//Para mostrar en consola que ya inicio la funcion setup()
//pinMode: Configura el pin especificado para comportarse ya sea como una entrada o una salida: pines digitales se pueden utilizar como entrada, INPUT_PULLUP o SALIDA. Cambiar el pin con la funcion pinMode () cambia el comportamiento eléctrico de la clavija.////*input: de afuera hacia el arduino - output*del arduino ahcia afuera - a pull-up* es la resistecia interna del arduino, que asegura que el pin este ya sea en un estado ALTO o BAJO, mientras emplea un nivel bajo de corriente.
  pinMode(coin_pin, INPUT_PULLUP);//establecemos el pin 2 (coin_pin) como tipo INPUT y le adjuntamos una resistencia interna para evitar rebotes
//// El procesador en el corazón de cualquier Arduino tiene dos tipos diferentes de interrupciones: "externo" y "Cambiar PIN".
//// Si usted quiere asegurarse de que un programa siempre capte los pulsos de un encoder rotativo, de manera que nunca se pierde un pulso, seria difícil escribir un programa que no hiciera otra cosa mas que eso, ya que el programa tendría que sondear constantemente las líneas de sensores para el codificador, con el fin de detectar pulsos solo cuando ocurran emplearemos la funcion de AtachInterrupts()*
//// Las interrupciones son útiles formas de hacer que las cosas sucedan de forma automática en los programas de microcontroladores, y puede ayudar a resolver problemas de tiempo.
//// Estas interrupciones pueden configurarse para activar una función específica en flancos ascendentes o descendentes de la señal, o bajo nivel.
//// * OJO: Dentro de la función de "attachInterrupt()", la funcion "delay()" no funcionará y el valor devuelto por "millis()" no se incrementará. Los datos recibidos mientras dentro de la funcion podran ser perdidos. Usted debe declarar como volátiles cualquier variable que modifique dentro de la función adjunta. Vea la sección de ISR a continuación para obtener más información.
  attachInterrupt(digitalPinToInterrupt(coin_pin), sumar_contador_moneda, FALLING);
//SYNTAXIS: attachInterrupt(pin,ISR,mode);
//*pin: parametro para decir a la funcion que pin desea adjuntar el interruptor (Arduino_MEGA cuenta con x6 pins que admiten esta posibilidad de actuar como interuptores estos son [2, 3, 18, 19, 20, 21] ) los pins específicos con capacidad para interrupciones, y su mapeo para interrumpir llevan un número diferente a su numero de pin, estos numeros varían segunn el modelo de arduino, por esta razon empleamos la funcion "digitalPinToInterrupt()" para obtener este valor para el pin en especifico y evitar confusiones
//*ISR: funcion a invocar cuando se produce una interrupcion; esta funcion no debe recibir parametros y debe regresar nada
//*mode: define cuando se debe de producri una interrupcion, hay 4 constantes predefinidas como valores y estos son;
////*LOW: acciona la interrupcion cuando el pin se encuentre en estado bajo (0v)
////*CHANGE: acciona la interrupcion cada vez que el pin cambie de valor
////*RISING: acciona la interrupcion cuando el pin vaya de estado bajo a estado alto (0v a 5v)
////*FALLING: acciona la interrupcion cuando el pin vaya de estado alto a estado bajo (5v a 0v)
  Serial.println("Morralla Setup Cargado correctamente.");//Imprimo en consola para notificarme que la funcion setup() llego a su fin
}

void loop() {
 
 //Si hubo un pulso y este es mayor a la diferencia de tiempo entonces lo sumo como pulso si es menor es ruido y no lo sumo

  tiempo_pulso_inicial = micros();
  
  if(digitalRead( coin_pin ) == HIGH ){//si el pin de Monedero recibe una señal de 0 a 5 v
    
    tiempo_pulso_final = micros();//guarda ese tiempo como tiempo final
    
    if( tiempo_pulso_final - tiempo_pulso_inicial > limite_pulsos){
      credit++;
    }
  }

// Codigo para leer lo que introducimos en consola y tomar los valores “p” o “a”
  cmd= Serial.read();
  
  switch (cmd) 
  {
    case 'c': //Muestra los creditos
    Serial.println("CREDITOS:");
    Serial.print(credit); 
    break;
    
    case 'r': //Resetea los creditos
    credit=0;
    break;
    
  } //fin de switch

  
}//fin de loop

//*****INTERUPCION al detectar pulsos del monedero
void sumar_contador_moneda() //funcion invocada para incrementar el contador cont_pulsos_moneda
{
  credit++;
}


