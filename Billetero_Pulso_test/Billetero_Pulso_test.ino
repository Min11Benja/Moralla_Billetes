//codigo para testear pulsos de monedero con diferentes Thresholds y para evitar que se resete los pulsos antes de que termine de contar a en especifico monedas de $10
//***********************************************************************************************
volatile byte billPulseCount = 0;  // a counter to see how many times the pin has changed - which coin inserted
volatile unsigned long pulseTime;  //this stores the time of the last pulse.
volatile unsigned long billTime;   //This stores the time of the last time a bill was saved
byte newBillInserted; // a place to put our last bill pulse count
byte billValue = 0;      // number of pulses required to dispence each coin type.
//***********************************************************************************************
byte pulseThreshold = 500;  //EDIT THIS VALUE TO CHANGE DELAY BETWEEN DETECTING BANK OF PULSES
//***********************************************************************************************

//************Pins Used *******************
int billSelectorPin = 3;  // pin3 as optical count input

void setup() {
  Serial.begin(9600);

  pinMode(billSelectorPin, INPUT_PULLUP); //set pin 3 as optical input
  attachInterrupt(1, billacceptor, FALLING); // CoinAcceptor - attach a PinChange Interrupt to our on the rising edge - link to coinacceptor function
  Serial.println("Test Detector de Pulsos Billetero Threshold de 500 editing IF code");
}

void loop() {
//if (coinPulseCount > 0 && millis() - pulseTime > pulseThreshold && millis() - pulseTime != 0)   
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

  //Proccess the coin inserted

  switch (newBillInserted) {
    
    case 2://Billete de $20.0
      Serial.print("$20.00");   //1 pulse from validator - £1 INSERTED
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      billValue = 19;        //hopper dispense 10 pulses/coins
      Serial.println("DSIPENSE 19");
      break;
      
    case 5://Billete de $50
      Serial.print("$50.00");   //1 pulse from validator - £1 INSERTED
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      billValue = 48;        //hopper dispense 10 pulses/coins
      Serial.println("DSIPENSE 48");
      break;
      
    case 10://billete de $100
      Serial.print("$100.00");   //1 pulse from validator - £1 INSERTED
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      billValue = 97;        //hopper dispense 10 pulses/coins
      Serial.println("DSIPENSE 97");
      break;
      
    case 20://Billete de $200
      Serial.print("$200.00");   //1 pulse from validator - £1 INSERTED
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      billValue = 196;        //hopper dispense 10 pulses/coins
      Serial.println("DSIPENSE 196");
      break;
    case 50://Billete de $500
      Serial.print("$500.00");   //1 pulse from validator - £1 INSERTED
      newBillInserted = 0;   //reset - ALTHOUGH DO I NEED TO DO THIS?
      billValue = 495;        //hopper dispense 10 pulses/coins
      Serial.println("DSIPENSE 495");
      break;
      
  }//End of Switch
     
   
}//End of void loop()

//*****INTERUPT detecting pulses from the coin acceptor
void billacceptor()  
{
   pulseTime = millis();   //store current time in pulseTime
   billPulseCount++;
   Serial.print(billPulseCount);
}

