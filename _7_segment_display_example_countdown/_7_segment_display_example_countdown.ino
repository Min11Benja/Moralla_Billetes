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

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);
}

void loop() {
  zero();
  one();
  two();
  three();
  four();
  five();
  six();
  seven();
  eight();
  nine();
}

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

