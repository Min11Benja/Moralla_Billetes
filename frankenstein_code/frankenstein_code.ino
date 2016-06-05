
//*************Variables Globales**********************************************************************************
volatile byte billPulseCount = 0;  // a counter to see how many times the pin has changed - which coin inserted
volatile byte hopperPulseCount =0;
volatile unsigned long pulseTime;  //this stores the time of the last pulse.
volatile unsigned long hopperpulseTime;
volatile unsigned long billTime;   //This stores the time of the last time a bill was saved
byte newBillInserted; // a place to put our last bill pulse count
byte coinValue = 0;      // number of pulses required to dispence each coin type.
//***********************************************************************************************
byte pulseThreshold = 500;  //EDIT THIS VALUE TO CHANGE DELAY BETWEEN DETECTING BANK OF PULSES
//***********************************************************************************************

//************Pins arduino uno *******************
int billSelectorPin = 3;  // pin3 as optical count input para NV10USB
int hopperPin = 2; //pin 2 as optical count input para el sensor del hopper
int relayPin=4;// variable para poner que relevador esta prendido, esta alternara entre los siguientes valores 4=$10,7=$5,8=$2,12=$1

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(12, OUTPUT);
  digitalWrite(4, HIGH);digitalWrite(7, HIGH);digitalWrite(8, HIGH);digitalWrite(12, HIGH);

  pinMode(billSelectorPin, INPUT_PULLUP); //set pin 3 as optical input
  pinMode(hopperPin, INPUT_PULLUP); //set pin 3 as optical input
  digitalWrite(hopperPin, HIGH); //use the internal pullup resistor on the optical input
  attachInterrupt(0, hopper, FALLING); // attach a PinChange Interrupt to our pin on the rising edge
  attachInterrupt(1, billacceptor, FALLING); // CoinAcceptor - attach a PinChange Interrupt to our on the rising edge - link to coinacceptor function
  Serial.println("Test Detector de Pulsos Billetero");
}

void loop() {
  if (billPulseCount > 0 && millis() - pulseTime > pulseThreshold && millis() - pulseTime !=0)  
  //if there is a coin count & the time between last pulse and this is greater than 1/4 stop counting
  {
    billTime = millis() - pulseTime;
    newBillInserted = billPulseCount;  //new variable to free up coinPulseCount on the interrupt.
    //Serial.println(".");
    //Serial.print("Last Time: ");Serial.println(millis());
    //Serial.print("Last PulseTime: ");Serial.println(pulseTime);
    //Serial.print("Time Dif: ");Serial.println(billTime);
    Serial.println(".");
    Serial.print("Billete detectado Cantidad de pulsos: ");
    Serial.println(newBillInserted);         // print the pulses of the new coin inserted
    billPulseCount = 0;
  }//end of IF

  //Code to Proccess the coin inserted
  switch (newBillInserted) {
    
    case 2://Billete de $20.0
      Serial.println("$20.00");//2 pulsos del NV10USB significa que leyo un billete de $20
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      coinValue = 1;        //hopper dispense 1 pulse/coins
      Serial.println("Accionando el Relevador de $10 por 1 pulso");
      relayPin=4;//4=$10,7=$5,8=$2,12=$1
      dispence();
      Serial.println("Accionando el Relevador de $5 por 1 pulso");
      relayPin=7;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence(); 
      Serial.println("Accionando el Relevador de $2 por 2 pulso");
      relayPin=8;//4=$10,7=$5,8=$2,12=$1,
      coinValue=2;//$2+$2+$10+$5=$19
      dispence();
      Serial.println("SE FERIO $19 CON EXITO!");
      break;
      
    case 5://Billete de $50
      Serial.println("$50.00");   //5 pulsos del NV10USB significa que leyo un billete de $50
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      coinValue = 4;        //hopper dispense 4 pulse/coins
      Serial.println("Accionando el Relevador de $10 por 4 pulso");
      relayPin=4;//4=$10,7=$5,8=$2,12=$1
      dispence();
      Serial.println("Accionando el Relevador de $5 por 1 pulso");
      relayPin=7;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence(); 
      Serial.println("Accionando el Relevador de $2 por 1 pulso");
      relayPin=8;//4=$10,7=$5,8=$2,12=$1,
      coinValue=2;//$2+$2+$10+$5=$19
      dispence();
      Serial.println("Accionando el Relevador de $1 por 1 pulso");
      relayPin=12;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence();
      Serial.println("SE FERIO $48 CON EXITO!");
      break;
      
    case 10://billete de $100
      Serial.println("$100.00");   //10 pulsos del NV10USB significa que leyo un billete de $100
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      coinValue = 9;        //hopper dispense 4 pulse/coins
      Serial.println("Accionando el Relevador de $10 por 9 pulso");
      relayPin=4;//4=$10,7=$5,8=$2,12=$1
      dispence();
      Serial.println("Accionando el Relevador de $5 por 1 pulso");
      relayPin=7;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence(); 
      Serial.println("Accionando el Relevador de $2 por 1 pulso");
      relayPin=8;//4=$10,7=$5,8=$2,12=$1,
      coinValue=2;//$2+$2+$10+$5=$19
      dispence();
      Serial.println("SE FERIO $97 CON EXITO!");
      break;
      
    case 20://Billete de $200
      Serial.println("$200.00");   //5 pulsos del NV10USB significa que leyo un billete de $200
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      coinValue = 19;        //hopper dispense 4 pulse/coins
      Serial.println("Accionando el Relevador de $10 por 19 pulso");
      relayPin=4;//4=$10,7=$5,8=$2,12=$1
      dispence();
      Serial.println("Accionando el Relevador de $5 por 1 pulso");
      relayPin=7;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence(); 
      Serial.println("Accionando el Relevador de $1 por 1 pulso");
      relayPin=12;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence();
      Serial.println("SE FERIO $196 CON EXITO!");
      break;
    case 50://Billete de $500
      Serial.println("$500.00");   //50 pulsos del NV10USB significa que leyo un billete de $500
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      coinValue = 4;        //hopper dispense 4 pulse/coins
      Serial.println("Accionando el Relevador de $10 por 49 pulso");
      relayPin=4;//4=$10,7=$5,8=$2,12=$1
      dispence();
      Serial.println("Accionando el Relevador de $5 por 1 pulso");
      relayPin=7;//4=$10,7=$5,8=$2,12=$1,
      coinValue=1;//$2+$2+$10+$5=$19
      dispence(); 
      Serial.println("SE FERIO $450 CON EXITO!");
      break;
      
  }//End of Switch
     
   
}//End of void loop()

//*****INTERUPT detecting pulses from the coin acceptor
void billacceptor()  
{
   pulseTime = millis();   //store current time in pulseTime
   billPulseCount++;
   Serial.print("b:");Serial.print(billPulseCount);
}//End of billacceptor()
//*****INTERUPT detecting pulses from the coin acceptor
void hopper()  
{
   hopperpulseTime = millis();   //store current time in pulseTime
   hopperPulseCount++;
   Serial.print("h:");Serial.print(hopperPulseCount);
}//End of billacceptor()

void dispence()//Funcion para prender el relevador hasta que detecte el arduino pulsos del sensor del hopper menor o igual a los indicados por coinValue
{
  digitalWrite(relayPin, LOW);   //turn on relay - active LOW.
  //delay(VarDelayA);  
  hopperPulseCount =0;//Variable para
  while (hopperPulseCount < coinValue)     
  {
    //do nothing and wait with the relay on dispencing coins until it hits the "coinValue"
  }
  //delay(VarDelayB);    //wait to ensure the coin has enough momentum to leave hopper but not long enough for another coins to dispence!
  digitalWrite(relayPin, HIGH);   //turn off relay - active LOW.  
  //**************************************************************************************  
  delay(180);
  hopperPulseCount = 0;   // ERROR IN SPIKES - hopper pulsing effects coin acceptor pulse line!
  //************************************************************************************** 
}
