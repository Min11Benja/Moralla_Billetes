//Codigo para accionar Relevadores x4 con input del CMD y detenerlos con contador de pulsos del hopper

//Variables
volatile byte billPulseCount = 0;  // a counter to see how many times the pin has changed - which coin inserted
volatile unsigned long pulseTime;  //this stores the time of the last pulse.
volatile unsigned long billTime;   //This stores the time of the last time a bill was saved
byte newBillInserted; // a place to put our last bill pulse count
byte billValue = 0;      // number of pulses required to dispence each coin type.
//***********************************************************************************************
byte pulseThreshold = 500;  //EDIT THIS VALUE TO CHANGE DELAY BETWEEN DETECTING BANK OF PULSES
//***********************************************************************************************
byte cmd=0;//For Serial Input tests via Arduino
int relayPin=4;// variable para poner que relevador esta prendido, esta alternara entre los siguientes valores 4=$10,7=$5,8=$2,12=$1
int hopperSensorPin=2;//Pin que leera los pulsos del sensor
int billSensorPin=3;//Pin que leera los pulsos del billetero
byte hopperCount=0;//Variable para contar los pulsos del hopper
byte billCont=0;//Variable para contar los pulsos del Billetero
byte coinValue=0;//Variable para poner cuantas monedas saldran del hopper

void setup() {
  Serial.begin(9600);
  //Ponemos todos los Relays como outputs
  pinMode(4, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(12, OUTPUT);
  //Usamos el INPUT_PULLUP para el pin que contara lso pulsos del sensor del Hopper
  pinMode(hopperSensorPin, INPUT_PULLUP);//el pin #2
  
  //Apagamos todos los relevadores por default 
  digitalWrite(4, HIGH);digitalWrite(7, HIGH);digitalWrite(8, HIGH);digitalWrite(12, HIGH);
  
  //digitalWrite(relayPin, HIGH);
  digitalWrite(hopperSensorPin, HIGH); //use the internal pullup resistor on the hopper optical input #2  
  digitalWrite(billSensorPin, HIGH);//para el lector de billetes
  attachInterrupt(1, hopper, FALLING); // Hopper - attach a PinChange Interrupt to our pin on the falling edge - link to hopper function
  attachInterrupt(0, billacceptor, FALLING);//para el lector de billetes
  
  Serial.println("Codigo para accionar Relevadores x4 con input del CMD y detenerlos con contador de pulsos del hopper");
  Serial.println("INPUT DE CONSOLA> s= set Relay, p=prendes Relay (#4 por default), a=apagar Relay, Pulsos:2=$20,5=$50,10=$100,20=$200,50=$500");
  Serial.print("CMD:");
}

void loop() {
    if (billPulseCount > 0 && millis() - pulseTime > pulseThreshold && millis() - pulseTime !=0)  
  //if there is a coin count & the time between last pulse and this is greater than 1/4 stop counting
  {
    billTime = millis() - pulseTime;
    newBillInserted = billPulseCount;  //new variable to free up coinPulseCount on the interrupt.
    Serial.println(".");
    Serial.print("Last Time: ");Serial.println(millis());
    Serial.print("Last PulseTime: ");Serial.println(pulseTime);
    Serial.print("Time Dif: ");Serial.println(billTime);
    Serial.print("new Bill Inserted pulses: ");
    Serial.println(newBillInserted);         // print the pulses of the new coin inserted
    billPulseCount = 0;
  }//end of IF

  // Comand input code
 /* cmd= Serial.read();
    switch (cmd) 
  {
    case 's'://Set Relay
    Serial.print("Current Relay:");Serial.println(relayPin);
    Serial.print("Set RELAY TO:");
    Serial.print("New Relay ->"); Serial.println(relayPin);
    break;
    
    case 'p'://Prender
    digitalWrite(relayPin, LOW);
    Serial.println("RELAY ON");
    break;
    
    case 'a'://Apagar
    digitalWrite(relayPin, HIGH);
    Serial.println("RELAY OFF");
    break;
  }*/
  
switch(newBillInserted)
{
    case 2://$20.00 Introducidos - $1.00 de Comission
    Serial.println("Billetes de $20.00");
    billValue=19;//20-1 Cobramos un peso de cuota
    Serial.println("Accionando el Relevador de $10");
    relayPin=4;//4=$10,7=$5,8=$2,12=$1
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    coinValue=1;//0+$10=$10
    dispence();    
    Serial.println("Accionando el Relevador de $5");
    relayPin=7;//4=$10,7=$5,8=$2,12=$1,
    coinValue=1;//$10+$5=$15
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence(); 
    Serial.println("Accionando el Relevador de $2");
    relayPin=8;//4=$10,7=$5,8=$2,12=$1,
    coinValue=2;//$2+$2+$10+$5=$19
    //hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence(); 
    Serial.print("$19.00 Expendidos exitosamente!");
    break;    

    case 5://$50.00 Introducidos - $2.00 de Comission
    billValue=48;//50-2 Cobramos dos pesos de cuota
    relayPin=2;//2=$10,4=$5,7=$2,8=$1,
    coinValue=4;//0+$40=$40
    hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=4;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$40+$5=$45
    hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence(); 
    
    relayPin=7;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$45+$2=$47
    hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();     
    
    relayPin=8;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$47+$1=$48
    hopperSensorPin=9;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();         
    break;  
    
    case 10://$100.00 Introducidos - $3.00 de Comission
    billValue=97;//100-3 Cobramos tres pesos de cuota
    relayPin=2;//2=$10,4=$5,7=$2,8=$1,
    coinValue=9;//0+$90=$90
    hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=4;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$90+$5=$95
    hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence(); 
    
    relayPin=7;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$95+$2=$97
    hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();      
    break;  
    
    case 20://$200.00 Introducidos - $4.00 de Comission
    billValue=196;//200-3 Cobramos tres pesos de cuota
    relayPin=2;//2=$10,4=$5,7=$2,8=$1,
    coinValue=19;//0+$190=$190
    hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=4;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$190+$5=$195
    hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence(); 
    
    relayPin=8;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$195+$1=$196
    hopperSensorPin=9;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();         
    break;      
    
    case 50://$500.00 Introducidos - $5.00 de Comission
    billValue=495;//500-5 Cobramos cinco pesos de cuota
    relayPin=2;//2=$10,4=$5,7=$2,8=$1,
    coinValue=49;//0+$490=$490
    hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=4;//2=$10,4=$5,7=$2,8=$1,
    coinValue=1;//$490+$5=$495 
    hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();       
    break;      
  }

}
//*****INTERUPT detecting pulses from the coin acceptor
void billacceptor()//function called when a bill is inserted  
{
   pulseTime = millis();   //store current time in pulseTime
   billPulseCount++;
   Serial.print(billPulseCount);
}
//*****INTERUPT detecting pulses from the hopper sensor
void hopper()//function called when a coin is ejected from the hopper
{
  hopperCount++ ;
  Serial.print(hopperCount);
}

void dispence()
{
  digitalWrite(relayPin, LOW);   //turn on relay - active LOW.
  //delay(VarDelayA);  
  hopperCount =0;
  while (hopperCount < coinValue)     
  {
    //do nothing and wait with the relay on dispencing coins until it hits the "coinValue"
  }
  //delay(VarDelayB);    //wait to ensure the coin has enough momentum to leave hopper but not long enough for another coins to dispence!
  digitalWrite(relayPin, HIGH);   //turn off relay - active LOW.  
  //**************************************************************************************  
  delay(180);
  hopperCount = 0;   // ERROR IN SPIKES - hopper pulsing effects coin acceptor pulse line!
  //************************************************************************************** 
}

