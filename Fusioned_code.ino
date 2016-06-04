//Codigo para accionar Relevador con contador de pulsos

//Variables
volatile byte billPulseCount = 0;  // a counter to see how many times the pin has changed - which coin inserted
volatile unsigned long pulseTime;  //this stores the time of the last pulse.
volatile unsigned long billTime;   //This stores the time of the last time a bill was saved
byte newBillInserted; // a place to put our last bill pulse count
byte coinValue = 0;      // number of pulses required to dispence each coin type.
//***********************************************************************************************
byte pulseThreshold = 500;  //EDIT THIS VALUE TO CHANGE DELAY BETWEEN DETECTING BANK OF PULSES
//***********************************************************************************************

byte cmd=0;//For Serial Input tests via Arduino
int relayPin=11;//11=$10,10=$5,9=$2,8=$1,
volatile byte hopperCount=0;
byte billValue=0;
byte outputValue=0;
// A:30 & B :20 (x1) A:50 & B:50 (x9++)
byte VarDelayA=0;
byte VarDelayB=0;

int billSelectorPin = 0;  // pin0 as optical count input para NV10USB


void setup() {
  Serial.begin(9600);
  while (!Serial) {
   ; // wait for serial port to connect. Needed for Leonardo only
  }
  //Pin Mode
  pinMode(8,OUTPUT);pinMode(9,OUTPUT);pinMode(10,OUTPUT);pinMode(11,OUTPUT);
  //pinMode(relayPin, OUTPUT);
  //pinMode(1, INPUT_PULLUP);pinMode(2, INPUT_PULLUP);pinMode(3, INPUT_PULLUP);pinMode(4, INPUT_PULLUP);
  pinMode(billSelectorPin, INPUT_PULLUP); //set pin 3 as optical input

  //Apagamos todos los relevadores por default 
  digitalWrite(8, HIGH);digitalWrite(9, HIGH);digitalWrite(10, HIGH);digitalWrite(11, HIGH);
  
  digitalWrite(1, HIGH);digitalWrite(2, HIGH);digitalWrite(3, HIGH);digitalWrite(7, HIGH);
  //use the internal pullup resistor on the hopper optical input    
  attachInterrupt(3, hopper, FALLING);attachInterrupt(1, hopper, FALLING);attachInterrupt(0, hopper, FALLING);attachInterrupt(4, hopper, FALLING);
  // Hopper - attach a PinChange Interrupt to our pin on the falling edge - link to hopper function
  digitalWrite(0,HIGH);
  attachInterrupt(2, billacceptor, FALLING); // CoinAcceptor - attach a PinChange Interrupt to our on the rising edge - link to coinacceptor function
 
  /*Serial.println("Codigo para Relay ON/Off con CMD & contador de pulsos por Hopper");
  Serial.println("INPUT> p=prendes Relay, a=apagar Relay, 2 = $20, 3=$50, 4=$100, 5=$200, 6=$500");
  Serial.print("CMD:");*/
}

void loop() {
  
    if(Serial.available() > 0){
   Serial.println('Serial On');
 }

  if (billPulseCount > 0 && millis() - pulseTime > 500 && millis() - pulseTime !=0)  
  //if there is a coin count & the time between last pulse and this is greater than 1/4 stop counting
  {
    billTime = millis() - pulseTime;
    newBillInserted = billPulseCount;  //new variable to free up coinPulseCount on the interrupt.
    //Serial.println(".");
    //Serial.print("Last Time: ");Serial.println(millis());
    //Serial.print("Last PulseTime: ");Serial.println(pulseTime);
    //Serial.print("Time Dif: ");Serial.println(billTime);
    //Serial.println(".");
   //Serial.print("Billete detectado Cantidad de pulsos: ");
   //Serial.println(newBillInserted);         // print the pulses of the new coin inserted
    billPulseCount = 0;
  }//end of IF

  
  switch (newBillInserted) 
  {
       
    case 2://$20.00 Introducidos
    newBillInserted=0;
    //Serial.print("2 Pulsos detectados -> $20.00");
    billValue=19;//20-2 Cobramos 2 pesos de cuota
    //Serial.print("Bill Value = ");Serial.println(billValue);
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    //Serial.print("Accionando Relay:");Serial.println(relayPin);
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    outputValue=1;//0+$10=$10
    //Serial.print("Output Value:");Serial.println(outputValue);
    VarDelayA=30;
    VarDelayB=20;
    dispence();   
    //Serial.println("Changing Relay 11->10");
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    //Serial.print("Accionando Relay:");Serial.println(relayPin);
    outputValue=1;//$10+$5=$15
    //Serial.print("Output Value:");Serial.println(outputValue);
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    //Serial.println("Changing Relay 10->9");
    
    relayPin=9;//11=$10,10=$5,9=$2,8=$1
    //Serial.print("Accionando Relay:");Serial.println(relayPin);
    outputValue=2;//$2+$2+$10+$5=$17
    //Serial.print("Output Value:");Serial.println(outputValue);
    //hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1    
    VarDelayA=38;
    VarDelayB=30;
    dispence(); 
    //Serial.println("Last Relay");
 
    break;    

    case 5://$50.00 Introducidos
    newBillInserted=0;
    billValue=48;//50-2 Cobramos dos pesos de cuota
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    outputValue=4;//0+$40=$40
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=35;
    VarDelayB=30;
    dispence();    
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$40+$5=$45
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    
    relayPin=9;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$45+$2=$47
    //hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;    
    dispence();     
    
    relayPin=8;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$47+$1=$48
    //hopperSensorPin=9;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;    
    dispence();         
    break;  
    
    case 10://$100.00 Introducidos
    newBillInserted=0;
    billValue=97;//100-3 Cobramos tres pesos de cuota
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    outputValue=9;//0+$90=$90
    VarDelayA=45;
    VarDelayB=45;
    dispence();    
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$90+$5=$95
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    
    relayPin=9;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$95+$2=$97
    //hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=40;
    VarDelayB=25;
    dispence();      
    break;  
    
     case 11://$100.00 Introducidos
    newBillInserted=0;
    billValue=97;//100-3 Cobramos tres pesos de cuota
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    outputValue=9;//0+$90=$90
    VarDelayA=45;
    VarDelayB=45;
    dispence();    
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$90+$5=$95
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    
    relayPin=9;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$95+$2=$97
    //hopperSensorPin=6;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=40;
    VarDelayB=25;
    dispence();      
    break;   
    
    case 20://$200.00 Introducidos
    newBillInserted=0;
    billValue=196;//200-3 Cobramos tres pesos de cuota
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    outputValue=19;//0+$190=$190
    VarDelayA=50;
    VarDelayB=50;
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$190+$5=$195
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    
    relayPin=8;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$195+$1=$196
    //hopperSensorPin=9;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;    
    dispence();         
    break;      
 
     case 21://$200.00 Introducidos
    newBillInserted=0;
    billValue=196;//200-3 Cobramos tres pesos de cuota
    relayPin=11;//11=$10,10=$5,9=$2,8=$1
    outputValue=19;//0+$190=$190
    VarDelayA=50;
    VarDelayB=50;
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=10;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$190+$5=$195
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;
    dispence(); 
    
    relayPin=8;//11=$10,10=$5,9=$2,8=$1
    outputValue=1;//$195+$1=$196
    //hopperSensorPin=9;//-3=$10,-5=$5,-6=$2,-9=$1
    VarDelayA=30;
    VarDelayB=20;    
    dispence();         
    break; 
    
    /*case '50'://$500.00 Introducidos
    billValue=495;//500-5 Cobramos cinco pesos de cuota
    relayPin=4;//4=$10,7=$5,8=$2,12=$1
    outputValue=49;//0+$490=$490
    //hopperSensorPin=3;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();    
    
    relayPin=7;//4=$10,7=$5,8=$2,12=$1
    outputValue=1;//$490+$5=$495 
    //hopperSensorPin=5;//-3=$10,-5=$5,-6=$2,-9=$1
    dispence();       
    break;    */  
  }

}

void billacceptor()  
{
   pulseTime = millis();   //store current time in pulseTime
   billPulseCount++;
   //Serial.print("b:");Serial.print(billPulseCount);
}//End of billacceptor()

void hopper()           //function called when a coin is ejected from the hopper
{
  hopperCount++ ;
  //Serial.print("<H:");
  //Serial.println(hopperCount);
}

void dispence()
{
  hopperCount =0;
  digitalWrite(relayPin, LOW);   //turn on relay - active LOW.
  //Serial.println("-RELAY ON");
  //delay(50);    //wait 
  delay(VarDelayA);
  while (hopperCount < outputValue)     
  {
    //do nothing and wait with the relay on dispencing coins until it hits the "coinValue"
     if(hopperCount==outputValue){break;}//just in case this breaks out of the loop
  }
  delay(VarDelayB);
  //delay(50);    //wait to ensure the coin has enough momentum to leave hopper but not long enough for another coins to dispence!
  digitalWrite(relayPin, HIGH);   //turn off relay - active LOW. 
  //Serial.print("-RELAY OFF"); 
  //**************************************************************************************  
  delay(180);
  billPulseCount=0;
  // Reseteo de contadorPulsoBilletes aqui billCount = 0;   // ERROR IN SPIKES - hopper pulsing effects coin acceptor pulse line!
  //************************************************************************************** 
}
/*Arduino services one interrupt at a time. It suspends pending interrupts while it deals with an interrupt that has happened. Code to handle in- terrupts (called the interrupt handler, or interrupt service routine) should be brief to prevent undue delays to pending interrupts. An interrupt routine that takes too much time can cause other interrupt handlers to miss events. Activities that take a relatively long time, such as blinking an LED or even serial printing, should be avoided in an interrupt handler.*/
