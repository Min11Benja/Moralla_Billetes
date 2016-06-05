//morralla_v_3

//variables
volatile int iCreditos;
volatile int input_pulse;
volatile int output_pulse;

volatile unsigned long tiempo_pulso;
int iExpell;
//constantes
const int NV10USB_pin=3;
const int coin_acc_pin=2;
const int time_limit_pulsos = 500;
/*const int hopper_A1_pin=21;
const int hopper_B2_pin=20;
const int hopper_C3_pin=19;
const int hopper_D10_pin=18;*/

//constructor
void setup() {
  Serial.begin(9600);
  Serial.println("Cargando Setup, por favor esperar...");
  
  //pin modes
  pinMode(coin_acc_pin, INPUT_PULLUP);
  pinMode(NV10USB_pin, INPUT_PULLUP);
  
  //Interupts
    /*UNO (PIN2:0,PIN3:1) MEGA (PIN2;0,PIN3;1,PIN21;2,PIN20;3,PIN19;4,PIN18;5) */
  attachInterrupt(digitalPinToInterrupt(coin_acc_pin), addCredits, LOW);
  attachInterrupt(digitalPinToInterrupt(NV10USB_pin), addCredits, LOW);
  //attachInterrupt(digitalPinToInterrupt(hopper_A1_pin), delCredits, LOW);

  //resets
  iCreditos=0;
  tiempo_pulso=0;
  iExpell=0;
  input_pulse=0;
  output_pulse=0;
  Serial.println("Morralla Setup Cargado correctamente.");
}

//loop
void loop() {

if ( input_pulse > 0 &&  (millis()-tiempo_pulso) > time_limit_pulsos){
    cli();/*disable interrupts*/
    iCreditos = iCreditos+input_pulse; /*Guardo el valor del total de pulsos en esta variable para liberar espacio en la variable cont_pulsos_moneda*/
    input_pulse = 0; /*reseteo a 0 el contador de pulsos del interruptor*/
    sei();/*enable interrupts*/  
  }
  
}

//sumar creditos
void addCredits() {
  input_pulse++;
  tiempo_pulso = millis();
}

//restar creditos
void delCredits() {
  output_pulse++;
  iCreditos--;
}

//
void resetCredits() {
iCreditos=0;
}

//display credits
void showCredits() {
  Serial.println("Creditos:");
  Serial.println(iCreditos);
}

//disppence
void dispence(int iRelay, int iDelay, int iExpell){
  //delay(iDelay);
    digitalWrite(iRelay, LOW);   //turn on relay - active LOW.
  while (output_pulse < (iExpell+1))     
  {
    //do nothing and wait with the relay on dispencing coins until it hits the "coinValue"
  }
  //delay(iDelay);   
  digitalWrite(iRelay, HIGH); 
  output_pulse=0;
 }

