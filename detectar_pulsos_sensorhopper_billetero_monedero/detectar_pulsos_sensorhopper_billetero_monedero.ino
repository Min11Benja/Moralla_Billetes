  /*Variables Globales*/
  /*Lo pongo como variables de tipo constante para guardar espacio en memoria*/
  /***********************************************************************************************/
    const int limite_pulsos = 500; /* EDITAR ESTE VALOR PARA CAMBIAR EL DELAY ENTRE DETECCION DE PULSOS-nesecito poner un DELAY es como una pausa entre la deteccion de pulsos para que el arduino me lea los pulsos sin arrojar basura, eh calado multiples valores y 500 es el mas estable*/
  /***********************************************************************************************/
    const int coin_pin = 21; /*Asigno el valor de 2 para la variable donde conectare el pin que va a recibir los pulsos del monedero*/
    const int bill_pin=20;
    const int hopper_pin=19;
  /* Una variable debe ser declarada como "volátil" cuando su valor puede ser cambiado por algo fuera del control de la sección de código en el que aparece, como un hilo al mismo tiempo de ejecución. En el Arduino, el único lugar que es probable que ocurra en secciones de código asociados a las interrupciones, llama una rutina de servicio de interrupción.*/
    volatile byte cont_pulsos_moneda = 0;/*Variable para guardar el valor de los pulsos contados*/
    volatile byte cont_moneda_expulsada=0;
    volatile unsigned long tiempo_pulso; /*Variable para guardar el tiempo en el que se leyo e pulso*/
    byte pulsos_total; /* lugar para guardar el total de pulsos detectados*/
    byte nueva_moneda=0;/* lugar para guardar el valor de la moneda basandme en el total de pulsos detectados*/
   int credito=0;
   void setup(){
    Serial.begin(9600);/* Establece la velocidad de datos en bits por segundo (baudios) para la transmisión de datos en serie. Para comunicarse con la pc*/
    Serial.println("Cargando Setup, por favor esperar...");/*Para mostrar en consola que ya inicio la funcion setup()*/
  
  /*pinMode: Configura el pin especificado para comportarse ya sea como una entrada o una salida: pines digitales se pueden utilizar como entrada, INPUT_PULLUP o SALIDA. Cambiar el pin con la funcion pinMode () cambia el comportamiento eléctrico de la clavija.
  input: de afuera hacia el arduino - output*del arduino ahcia afuera - a pull-up* es la resistecia interna del arduino, que asegura que el pin este ya sea en un estado ALTO o BAJO, mientras emplea un nivel bajo de corriente.*/
  
    pinMode(coin_pin, INPUT_PULLUP);/*establecemos el pin 2 (coin_pin) como tipo INPUT y le adjuntamos una resistencia interna para evitar rebotes*/
  
  /* El procesador en el corazón de cualquier Arduino tiene dos tipos diferentes de interrupciones: "externo" y "Cambiar PIN".
  Si usted quiere asegurarse de que un programa siempre capte los pulsos de un encoder rotativo, de manera que nunca se pierde un pulso, seria difícil escribir un programa que no hiciera 
  otra cosa mas que eso, ya que el programa tendría que sondear constantemente las líneas de sensores para el codificador, con el fin de detectar pulsos solo cuando ocurran emplearemos la funcion de AtachInterrupts()*
  Las interrupciones son útiles formas de hacer que las cosas sucedan de forma automática en los programas de microcontroladores, y puede ayudar a resolver problemas de tiempo.
  Estas interrupciones pueden configurarse para activar una función específica en flancos ascendentes o descendentes de la señal, o bajo nivel.
  * OJO: Dentro de la función de "attachInterrupt()", la funcion "delay()" no funcionará y el valor devuelto por "millis()" no se incrementará. 
  Los datos recibidos mientras dentro de la funcion podran ser perdidos. Usted debe declarar como volátiles cualquier variable que modifique dentro de la función adjunta. 
  Vea la sección de ISR a continuación para obtener más información.*/
  /*attachInterrupt(0, sumar_contador_moneda, RISING);*/
  /*UNO (PIN2:0,PIN3:1) MEGA (PIN2;0,PIN3;1,PIN21;2,PIN20;3,PIN19;4,PIN18;5) */
  attachInterrupt(digitalPinToInterrupt(coin_pin), sumar_contador_moneda, RISING);
  attachInterrupt(digitalPinToInterrupt(bill_pin), sumar_contador_moneda, RISING);
  attachInterrupt(digitalPinToInterrupt(hopper_pin), sumar_expulsada, RISING);
  
  /*SYNTAXIS: attachInterrupt(pin,ISR,mode);
  pin: parametro para decir a la funcion que pin desea adjuntar el interruptor (Arduino_MEGA cuenta con x6 pins que admiten esta posibilidad de actuar como interuptores estos son [2, 3, 18, 19, 20, 21] ) los pins específicos con capacidad para interrupciones, y su mapeo para interrumpir llevan un número diferente a su numero de pin, estos numeros varían segunn el modelo de arduino, por esta razon empleamos la funcion "digitalPinToInterrupt()" para obtener este valor para el pin en especifico y evitar confusiones
  ISR: funcion a invocar cuando se produce una interrupcion; esta funcion no debe recibir parametros y debe regresar nada
  mode: define cuando se debe de producri una interrupcion, hay 4 constantes predefinidas como valores y estos son;
    LOW: acciona la interrupcion cuando el pin se encuentre en estado bajo (0v)
    CHANGE: acciona la interrupcion cada vez que el pin cambie de valor
    RISING: acciona la interrupcion cuando el pin vaya de estado bajo a estado alto (0v a 5v)
    FALLING: acciona la interrupcion cuando el pin vaya de estado alto a estado bajo (5v a 0v)*/
    Serial.println("Morralla Setup Cargado correctamente.");/*Imprimo en consola para notificarme que la funcion setup() llego a su fin*/
  }/*fin de void setup()*/
  
    void sumar_contador_moneda() /*funcion invocada para incrementar el contador cont_pulsos_moneda*/
  {
    cont_pulsos_moneda++;
    tiempo_pulso = millis();/*guardo el tiempo ACTUAL y se lo asigno a la variable como el tiempo cuando leyo el pulso*/
  }/*fin sumar_cont_moneda()*/
  void sumar_expulsada(){
      cont_moneda_expulsada++;
      //Serial.println("OUT:");
      //Serial.println(cont_moneda_expulsada);
     // credito=credito-valor;
    }
  void loop() {
  /*dejar de contar pulsos si hubo una interrupcion y el contador se incremento entonces hubo una moneda detectada (cont_pulsos_moneda>0) && si el tiempo actual menos el tiempo del ultimo pulso es mayor a los 500 milisegundos entonces hacer lo siguiente*/
    if (cont_pulsos_moneda >0 && millis()-tiempo_pulso > limite_pulsos){
    cli();/*disable interrupts*/
    nueva_moneda = cont_pulsos_moneda; /*Guardo el valor del total de pulsos en esta variable para liberar espacio en la variable cont_pulsos_moneda*/
    sei();/*enable interrupts*/
    Serial.print("PULSOS: ");/*me alerta en consola que hubo una moneda detectada*/
    Serial.println(nueva_moneda); /* imprime en consola el valor de esa moneda*/
    cli();/*disable interrupts*/
    cont_pulsos_moneda = 0; /*reseteo a 0 el contador de pulsos del interruptor*/
    sei();/*enable interrupts*/  
  }
    
    switch (nueva_moneda) {
    
    case 3:/*$1.00*/
    cli();/*disable interrupts*/
    Serial.println("$1.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=1;
    sei();/*enable interrupts*/
    break;
    
    case 2:/*$20.00*/
    cli();/*disable interrupts*/
    Serial.println("$20.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=18;
    sei();/*enable interrupts*/
    break;
    
    case 4:/*$2.00*/
    cli();/*disable interrupts*/
    Serial.println("$2.00 "); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=2;
    sei();/*enable interrupts*/
    break;

    case 5:/*$50.00*/
    cli();/*disable interrupts*/
    Serial.println("$50.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=45;
    sei();/*enable interrupts*/
    break;
    
    case 7:/*$5.00*/
    cli();/*disable interrupts*/
    Serial.println("$5.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=4;
    sei();/*enable interrupts*/
    break;
    
    case 8:/*$10.00*/
    cli();/*disable interrupts*/
    Serial.println("$10.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=9;
    sei();/*enable interrupts*/    
    break;

    case 10:/*$100.00*/
    cli();/*disable interrupts*/
    Serial.println("$100.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=190;
    sei();/*enable interrupts*/
    break;    

    case 20:/*$1.00*/
    cli();/*disable interrupts*/
    Serial.println("$200.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=180;
    sei();/*enable interrupts*/
    break;    
 
    case 50:/*$500.00*/
    cli();/*disable interrupts*/
    Serial.println("$500.00"); /*muestro en consola el valor de la moneda segun los pulsos leidos*/
    nueva_moneda = 0; /*reseteo*/
    credito=450;
    sei();/*enable interrupts*/
    break;
    }/*fin de switch*/
  }/*fin de void loop()*/
  

