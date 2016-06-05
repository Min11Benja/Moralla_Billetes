//   G F + A B
//   | | | | |   -> pins and segments they control
//   ---------
//  F|   A   |B
//   |---G---|   -> segments
//  E|   D   |C
//   ---------
//   | | | | |   -> pins and segments they control
//   E D + C DP

// Segments that make each number when lit:
// 0 => ABCDEF
// 1 => BC
// 2 => ABDEG
// 3 => ABCDG
// 4 => BCFG
// 5 => ACDFG
// 6 => ACDEFG
// 7 => ABC
// 8 => ABCDEFG
// 9 => ABCDFG

// Arduino digital pins used to light up
// corresponding segments on the LED display
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F_SEG 7
#define G 8

// Common anode;
// on when pin is low
// and off when pin is high
#define ON LOW
#define OFF HIGH

int ms = 1000;
const int buttonPin = 11;     // the number of the pushbutton pin
// variables will change:
int buttonState;         // variable for reading the pushbutton status
int credits = 9;
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // the debounce time; increase if the output flickers
int lastButtonState = LOW;   // the previous reading from the input pin

void setup() {

  pinMode(buttonPin, INPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);
  Serial.println("SETUP LOADED SUCESFULY!");
  Serial.println("CREDITOS:"); Serial.print(credits);

}//end setp()

void loop() {
  Serial.begin(9600);

  // read the state of the switch into a local variable:
  buttonState = digitalRead(buttonPin);

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH && credits > 0) {
        credits--;
        Serial.println("Button Presionado");
      }

  //show credits on display
  switch (credits) {
    case 0:
      Serial.println("0 CREDITOS");
      zero();
      break;

    case 1:
      Serial.println("MOSTRAR EN LCD EL 1");
      one();
      break;

    case 2:
      Serial.println("MOSTRAR EN LCD EL 2");
      two();
      break;

    case 3:
      Serial.println("MOSTRAR EN LCD EL 3");
      three();
      break;

    case 4:
      Serial.println("MOSTRAR EN LCD EL 4");
      four();
      break;

    case 5:
      Serial.println("MOSTRAR EN LCD EL 5");
      five();
      break;

    case 6:
      Serial.println("MOSTRAR EN LCD EL 6");
      six();
      break;

    case 7:
      Serial.println("MOSTRAR EN LCD EL 7");
      seven();
      break;

    case 8:
      Serial.println("MOSTRAR EN LCD EL 8");
      eight();
      break;

    case 9:
      Serial.println("MOSTRAR EN LCD EL 9");
      nine();
      break;

  }//end switch
}//end loop()

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
