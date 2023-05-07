#include <LiquidCrystal.h>
#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// HM-10 Bluetooth Module control states
char blue_input[] = {-1,-1,-1,-1}; // stores inforamtion from Bluetooth
// {(D or e), (pin)}
char state = '0';
//end of bluetooth 

int RelayControl1 = 2;
int RelayControl2 = 3;
int RelayControl3 = 4;
int RelayControl4 = 5;
int RelayControl5 = 6;
int RelayControl6 = 7;
int RelayControl7 = 8;
int RelayControl8 = 9;

bool Indicator1 = false;
bool Indicator2 = false;
bool Indicator3 = false;
bool Indicator4 = false;
bool Indicator5 = false;
bool Indicator6 = false;
bool Indicator7 = false;
bool Indicator8 = false;

#define input_0 A0
#define input_1 A1
#define input_2 A2
#define input_3 A3
#define input_4 A4
#define input_5 A5
#define input_6 A6
#define input_7 A7
#define input_8 A8
#define input_9 A9
#define input_10 A10
#define input_11 A11
#define input_12 A12
#define input_13 A13
#define input_14 A14
#define input_15 A15

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int AnalogValue1 = 0;
int AnalogValue2 = 0;
int AnalogValue3 = 0;
int AnalogValue4 = 0;
int AnalogValue5 = 0;
int AnalogValue6 = 0;
int AnalogValue7 = 0;
int AnalogValue8 = 0;

int PeakVoltage1 = 0;
int PeakVoltage2 = 0;
int PeakVoltage3 = 0;
int PeakVoltage4 = 0;
int PeakVoltage5 = 0;
int PeakVoltage6 = 0;
int PeakVoltage7 = 0;
int PeakVoltage8 = 0;

float AverageVoltage1 = 0;
float AverageVoltage2 = 0;
float AverageVoltage3 = 0;
float AverageVoltage4 = 0;
float AverageVoltage5 = 0;
float AverageVoltage6 = 0;
float AverageVoltage7 = 0;
float AverageVoltage8 = 0;

float input_A0 = 0;
float input_A1 = 0;
float input_A2 = 0;
float input_A3 = 0;
float input_A4 = 0;
float input_A5 = 0;
float input_A6 = 0;
float input_A7 = 0;
float input_A8 = 0;
float input_A9 = 0;
float input_A10 = 0;
float input_A11 = 0;
float input_A12 = 0;
float input_A13 = 0;
float input_A14 = 0;
float input_A15 = 0;

float current1 = 0;
float current2 = 0;
float current3 = 0;
float current4 = 0;
float current5 = 0;
float current6 = 0;
float current7 = 0;
float current8 = 0;

float power1 = 0;
float power2 = 0;
float power3 = 0;
float power4 = 0;
float power5 = 0;
float power6 = 0;
float power7 = 0;
float power8 = 0;

float Resolution = 0.00488;
unsigned long sample = 0;
int threshold = 1000;

void setup()
{

    // bluetooth code
lcd.begin(16,2);
//Serial.begin(115200); // old baud rate
  Serial.begin(9600);  // Start serial communication for debugging
  Serial1.begin(9600); // Start serial communication for HM-10 module

 int start ;
  int i ;
  
#if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
#endif

  //Serial.print("ADCTEST: ") ;
  start = millis() ;
  for (i = 0 ; i < 1000 ; i++)
    analogRead(0) ;
  //Serial.print(millis() - start) ;
  //Serial.println(" msec (1000 calls)") ;

    pinMode(RelayControl1,OUTPUT);
    digitalWrite(RelayControl1,HIGH);
    
    pinMode(RelayControl2,OUTPUT);
    digitalWrite(RelayControl2,HIGH);
   
    
    pinMode(RelayControl3,OUTPUT);
    digitalWrite(RelayControl3,HIGH);
    
    
    pinMode(RelayControl4,OUTPUT);
    digitalWrite(RelayControl4,HIGH);
  
    
    pinMode(RelayControl5,OUTPUT);
    digitalWrite(RelayControl5,HIGH);

    
    pinMode(RelayControl6,OUTPUT);
    digitalWrite(RelayControl6,HIGH);
   
    pinMode(RelayControl7,OUTPUT);
    digitalWrite(RelayControl7,HIGH);

    
    pinMode(RelayControl8,OUTPUT);
    digitalWrite(RelayControl8,HIGH);
   
}
void loop()
{

 if (Serial1.available() > 0) // Checks whether data is coming from the serial port
  {                         
    state = Serial1.read(); // Reads the data from the serial port
    Serial1.write(state);
    //Serial.println(state); // D#e#
    if (state == 'D' || state == 'e') // Digital input detected
    {
      //Serial.println("D or e has be read");
      blue_input[0] = state;
    }
    else if(blue_input[0] == 'D' && blue_input[1] == -1) // get the pin
    {
      Serial.print("pin: ");
      Serial.println(state);
      blue_input[1] = state;
    }
    else if (blue_input[1] >= 2 && state == '0')
    {
      int pinval = blue_input[1] - 48; // convert char to int
      digitalWrite(pinval, HIGH); // Set Relay CLOSED
      Serial.println("Relay: OPEN"); // Send back the String "Relay: OPEN"
      blue_input[0] = -1;
      blue_input[1] = -1;
    }
    else if (blue_input[1] >= RelayControl1 && state == '1')
    {
      int pinval = blue_input[1] - 48; // convert char to int
      digitalWrite(pinval, LOW);    // Set Relay OPEN
      Serial.println("Relay: CLOSED"); // Send back the String "Relay: CLOSED"
      blue_input[0] = -1;
      blue_input[1] = -1;
    }
  }
  // end bluetooth code

PeakVoltage1 = 0;
PeakVoltage2 = 0;
PeakVoltage3 = 0;
PeakVoltage4 = 0;
PeakVoltage5 = 0;
PeakVoltage6 = 0;
PeakVoltage7 = 0;
PeakVoltage8 = 0;

for(sample = 0; sample < 250; sample ++)
{
AnalogValue1 = analogRead(input_0);
AnalogValue2 = analogRead(input_2);
AnalogValue3 = analogRead(input_4);
AnalogValue4 = analogRead(input_6);
AnalogValue5 = analogRead(input_8);
AnalogValue6 = analogRead(input_10);
AnalogValue7 = analogRead(input_12);
AnalogValue8 = analogRead(input_14);

if(PeakVoltage1 < AnalogValue1)
{
PeakVoltage1 = AnalogValue1;
}
else
{
delayMicroseconds(7);
}



if(PeakVoltage2 < AnalogValue2)
{
PeakVoltage2 = AnalogValue2;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage3 < AnalogValue3)
{
PeakVoltage3 = AnalogValue3;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage4 < AnalogValue4)
{
PeakVoltage4 = AnalogValue4;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage5 < AnalogValue5)
{
PeakVoltage5 = AnalogValue5;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage6 < AnalogValue6)
{
PeakVoltage6 = AnalogValue6;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage7 < AnalogValue7)
{
PeakVoltage7 = AnalogValue7;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage8 < AnalogValue8)
{
PeakVoltage8 = AnalogValue8;
}
else
{
delayMicroseconds(7);
}

}

input_A0 = PeakVoltage1 * Resolution;
input_A2 = PeakVoltage2 * Resolution;
input_A4 = PeakVoltage3 * Resolution;
input_A6 = PeakVoltage4 * Resolution;
input_A8 = PeakVoltage5 * Resolution;
input_A10 = PeakVoltage6 * Resolution;
input_A12 = PeakVoltage7 * Resolution;
input_A14 = PeakVoltage8 * Resolution;

PeakVoltage1 = 0;
PeakVoltage2 = 0;
PeakVoltage3 = 0;
PeakVoltage4 = 0;
PeakVoltage5 = 0;
PeakVoltage6 = 0;
PeakVoltage7 = 0;
PeakVoltage8 = 0;

for(sample = 0; sample < 250; sample ++)
{
AnalogValue1 = analogRead(input_1);
AnalogValue2 = analogRead(input_3);
AnalogValue3 = analogRead(input_5);
AnalogValue4 = analogRead(input_7);
AnalogValue5 = analogRead(input_9);
AnalogValue6 = analogRead(input_11);
AnalogValue7 = analogRead(input_13);
AnalogValue8 = analogRead(input_15);

if(PeakVoltage1 < AnalogValue1)
{
PeakVoltage1 = AnalogValue1;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage2 < AnalogValue2)
{
PeakVoltage2 = AnalogValue2;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage3 < AnalogValue3)
{
PeakVoltage3 = AnalogValue3;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage4 < AnalogValue4)
{
PeakVoltage4 = AnalogValue4;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage5 < AnalogValue5)
{
PeakVoltage5 = AnalogValue5;
}
else
{
delayMicroseconds(7);
}


if(PeakVoltage6 < AnalogValue6)
{
PeakVoltage6 = AnalogValue6;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage7 < AnalogValue7)
{
PeakVoltage7 = AnalogValue7;
}
else
{
delayMicroseconds(7);
}

if(PeakVoltage8 < AnalogValue8)
{
PeakVoltage8 = AnalogValue8;
}
else
{
delayMicroseconds(7);
}

}

input_A1 = PeakVoltage1 * Resolution;
input_A3 = PeakVoltage2 * Resolution;
input_A5 = PeakVoltage3 * Resolution;
input_A7 = PeakVoltage4 * Resolution;
input_A9 = PeakVoltage5 * Resolution;
input_A11 = PeakVoltage6 * Resolution;
input_A13 = PeakVoltage7 * Resolution;
input_A15 = PeakVoltage8 * Resolution;

current1 = (input_A0 - input_A1) * 100;
current1 = current1 * 1.6; // 1.6 is just a calibration mult.

current2 = (input_A2 - input_A3) * 100;
current2 = current2 * 1.6;

current3 = (input_A4 - input_A5) * 100;
current3 = current3 * 1.6;

current4 = (input_A6 - input_A7) * 100;
current4 = current4 * 1.6;

current5 = (input_A8 - input_A9) * 100;
current5 = current5 * 1.6;

current6 = (input_A10 - input_A11) * 100;
current6 = current6 * 1.6;

current7 = (input_A12 - input_A13) * 100;
current7 = current7 * 1.6;

current8 = (input_A14 - input_A15) * 100;
current8 = current8 * 1.6;



// threshholds for currents
// if current < 10mA, then set to 0mA

// int power1 = abs(current1*12)/1000;
// int power2 = abs(current2*12)/1000;
// int power3 = abs(current3*12)/1000;
// int power4 = abs(current4*12)/1000;
// int power5 = abs(current5*12)/1000;
// int power6 = abs(current6*12)/1000;
// int power7 = abs(current7*12)/1000;
// int power8 = abs(current8*12)/1000;


// int residentialpower = power1+power2;

// int industcommpower = power3+power4+power5+power6+power7+power8;

// int totalpower = power1+power2+power3+power4+power5+power6+power7+power8;

// Serial.print("Current 1 = ");
// Serial.print(abs(current1));
// Serial.println(" mA  ");

// Serial.print("Current 2 = ");
// Serial.print(abs(current2));
// Serial.println(" mA  ");

// Serial.print("Current 3 = ");
// Serial.print(abs(current3));
// Serial.println(" mA  ");

// Serial.print("Current 4 = ");
// Serial.print(abs(current4));
// Serial.println(" mA  ");

// Serial.print("Current 5 = ");
// Serial.print(abs(current5));
// Serial.println(" mA  ");

// Serial.print("Current 6 = ");
// Serial.print(abs(current6));
// Serial.println(" mA  ");

// Serial.print("Current 7 = ");
// Serial.print(abs(current7));
// Serial.println(" mA  ");

// Serial.print("Current 8 = ");
// Serial.print(abs(current8));
// Serial.println(" mA  ");


// Serial.print("Current 1 = ");
// Serial.print(abs(current1));
// Serial.print(" mA  ");
// Serial.print("Power 1 = ");
// Serial.print(power1);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 2 = ");
// Serial.print(abs(current2));
// Serial.print(" mA  ");
// Serial.print("Power 2 = ");
// Serial.print(power2);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 3 = ");
// Serial.print(abs(current3));
// Serial.print(" mA  ");
// Serial.print("Power 3 = ");
// Serial.print(power3);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 4 = ");
// Serial.print(abs(current4));
// Serial.print(" mA  ");
// Serial.print("Power 4 = ");
// Serial.print(power4);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 5 = ");
// Serial.print(abs(current5));
// Serial.print(" mA  ");
// Serial.print("Power 5 = ");
// Serial.print(power5);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 6 = ");
// Serial.print(abs(current6));
// Serial.print(" mA  ");
// Serial.print("Power 6 = ");
// Serial.print(power6);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 7 = ");
// Serial.print(abs(current7));
// Serial.print(" mA  ");
// Serial.print("Power 7 = ");
// Serial.print(power7);
// Serial.print(" W  ");
// Serial.println("  ");

// Serial.print("Current 8 = ");
// Serial.print(abs(current8));
// Serial.print(" mA  ");
// Serial.print("Power 8 = ");
// Serial.print(power8);
// Serial.print(" W  ");
// Serial.println("  ");






// Serial.print("Residential Power = ");
// Serial.print(residentialpower);
// Serial.println(" W  ");
// Serial.println("  ");

// Serial.print("Ind. & Com. DC Power = ");
// Serial.print(industcommpower);
// Serial.println(" W  ");
// Serial.println("  ");

// Serial.print("Total DC Power = ");
// Serial.print(totalpower);
// Serial.println(" W  ");
// Serial.println("  ");

//

//current 1
 if(abs(current1)>1000){
  digitalWrite(RelayControl1,LOW);
  Indicator1=true;
 }

//current 2
if(abs(current2)>1000){
  digitalWrite(RelayControl2,LOW);
   Indicator2=true;
}

//current 3
if(abs(current3)>1000){
  digitalWrite(RelayControl3,LOW);
    Indicator3=true;
}

//current 4
if(abs(current4)>1000){
  digitalWrite(RelayControl4,LOW);
    Indicator4=true;
}

//current 5
if(abs(current5)>1000){
  digitalWrite(RelayControl5,LOW);
    Indicator5=true;
}

//current 6
if(abs(current6)>1000){
  digitalWrite(RelayControl6,LOW);
    Indicator6=true;
}

//current 7
if(abs(current7)>1000){
  digitalWrite(RelayControl7,LOW);
    Indicator7=true;
}

//current 8
if(abs(current8)>1000){
  digitalWrite(RelayControl8,LOW);
    Indicator8=true;
}



if(Indicator1==true){
Serial.println("RELAY 1 HAS TRIPPED!");
}

if(Indicator2==true){
Serial.println("RELAY 2 HAS TRIPPED!");
}

if(Indicator3==true){
Serial.println("RELAY 3 HAS TRIPPED!");
}

if(Indicator4==true){
Serial.println("RELAY 4 HAS TRIPPED!");
}

if(Indicator5==true){
Serial.println("RELAY 5 HAS TRIPPED!");
}

if(Indicator6==true){
Serial.println("RELAY 6 HAS TRIPPED!");
}

if(Indicator7==true){
Serial.println("RELAY 7 HAS TRIPPED!");
}

if(Indicator8==true){
Serial.println("RELAY 8 HAS TRIPPED!");
}

}