//       CA1 G  F  A  B
//        |  |  |  |  |      -> pins and segments they control
//   ---------    ---------
//   |   A   |    |   A   |
//  F|       |B  F|       |B
//   |---G---|    |---G---|
//  E|       |C  E|       |C
//   |   D   |    |   D   |
//   ---------    ---------
//        |  |  |  |  |      -> pins and segments they control
//        D  DP E  C CA2         

const byte numbers[10]={
// bpEDGFABC
  0b10010000,//0
  0b11111100,//1
  0b10001001,//2
  0b11001000,//3
  0b11100100,//4
  0b11000010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b11100000//9
};

// Arduino digital pins used to light up
// corresponding segments on the LED display
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7//dp
// Pins driving common anodes
#define CA1 3
#define CA2 2

// Pins for A B C D E F G, in sequence
const int segs[8] = { A, B, C, D, E, F, G, H };

//Pin connected to latch pin (ST_CP) of 74HC595
#define latchPin 5
#define clockPin 4
#define dataPin 6


// Segments that make each number

void setup() {
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

int n = 60;

void loop() {
//  registerWrite(n++,HIGH);
  int digit1 = n % 10;
  int digit2 = n / 10;

for(int i = 0; i < 50;i++){
  lightDigit1(numbers[digit1]);
  delay(5);
  lightDigit2(numbers[digit2]);
  delay(5);
}

  n--;
  if(n < 0)
    n = 60;
  Serial.println(digit2);
}

void lightDigit1(byte number) {
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, HIGH);
  lightSegments(number);
}

void lightDigit2(byte number) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  lightSegments(number);
}

void lightSegments(byte number){
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST,number);
  digitalWrite(latchPin,HIGH);
}

