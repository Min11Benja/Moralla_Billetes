volatile byte burp=0;    // a counter to see how many times the pin has changed
byte cmd=0;     // a place to put our serial data
int hopperPin = 2; //pin 2 as optical count input para el sensor del hopper
int relayPin=4;// variable para poner que relevador esta prendido, esta alternara entre los siguientes valores 4=$10,7=$5,8=$2,12=$1

void setup() 
{
  Serial.begin(9600);
  
  pinMode(hopperPin, INPUT_PULLUP);     //optical count is an input for hopper sensor
  digitalWrite(hopperPin, HIGH); //use the internal pullup resistor on the optical input
  
  pinMode(4, OUTPUT);
  //pinMode(7, OUTPUT);pinMode(8, OUTPUT);pinMode(12, OUTPUT);
  digitalWrite(4, HIGH);
  //digitalWrite(7, HIGH);digitalWrite(8, HIGH);digitalWrite(12, HIGH);
  attachInterrupt(0, burpcount, RISING); // attach a PinChange Interrupt to our pin on the rising edge
  
  Serial.println();
  Serial.print("Test prender relay:4 y contar pulsos del Hopper");

}

void loop()
{  
// Comand input code
  cmd= Serial.read();
    switch (cmd) 
  {
    case 'c'://current -no se como Set Relay lo hare manualmente desde la inicializacion de la variable
    Serial.print("Current Relay:");Serial.println(relayPin);
    //Serial.print("Set RELAY TO:");
    //Serial.print("New Relay ->"); Serial.println(relayPin);
    break;
    
    case 'p'://Prender
    digitalWrite(relayPin, LOW);
    Serial.println("relay ON");
    break;
    
    case 'a'://Apagar
    digitalWrite(relayPin, HIGH);
    Serial.println("relay OFF");
    break;
    
    case 'r'://reset contador de pulsos del hopper burp
    burp=0;
    Serial.println("hopper pulse cont reseted");
    break;
  }
  cmd=0;
  delay(100);
}
void burpcount()
{
  burp++;
  Serial.print("h:");Serial.print(burp);
}

