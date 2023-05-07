// pf 1: Commercial
// pf 2: Residential
// pf 3: Industrial

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define BUTTON_PIN 8

#define SAMPLES 300   //Number of samples you want to take everytime you loop
#define ACS_Pin A15    //ACS712 data pin analong input
// #define ACS_Pin2 A8    //ACS712 data pin analong input
// #define ACS_Pin3 A9    //ACS712 data pin analong input

#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

  float Amps_Peak_Peak_Array[101];
  float Amps_Peak_Peak2_Array[101];
  float Amps_Peak_Peak3_Array[101];

   int ni1 = 0;
    int ni2 = 0;
       int ni3 = 0;
float power1array[1];
float power2array[1];
float power3array[1];

float High_peak,Low_peak;         //Variables to measure or calculate
float High_peak2,Low_peak2;         //Variables to measure or calculate
float High_peak3,Low_peak3;         //Variables to measure or calculate

float Amps_Peak_Peak, Amps_RMS;
float Amps_Peak_Peak2, Amps_RMS2;
float Amps_Peak_Peak3, Amps_RMS3;

int rmsanalogPinVoltageRead = A3;             // Which pin to measure voltage Value (Pin A0 is reserved for button function)
        float rmsvoltageSampleRead  = 0;               /* to read the value of a sample in analog including voltageOffset1 */
        float rmsvoltageLastSample  = 0;               /* to count time for each sample. Technically 1 milli second 1 sample is taken */
        float rmsvoltageSampleSum   = 0;               /* accumulation of sample readings */
        float rmsvoltageSampleCount = 0;               /* to count number of sample. */
        float rmsvoltageMean ;                         /* to calculate the average value from all samples, in analog values*/ 
        float rmsRMSVoltageMean ;                      /* square roof of voltageMean without offset value, in analog value*/
        float rmsadjustRMSVoltageMean;
        float rmsFinalRMSVoltage;                      /* final voltage value with offset value*/
   
        
        int rmsanalogPinVoltageRead2 = A0;             // Which pin to measure voltage Value (Pin A0 is reserved for button function)
        float rmsvoltageSampleRead2  = 0;               /* to read the value of a sample in analog including voltageOffset1 */
        float rmsvoltageLastSample2  = 0;               /* to count time for each sample. Technically 1 milli second 1 sample is taken */
        float rmsvoltageSampleSum2   = 0;               /* accumulation of sample readings */
        float rmsvoltageSampleCount2 = 0;               /* to count number of sample. */
        float rmsvoltageMean2 ;                         /* to calculate the average value from all samples, in analog values*/ 
        float rmsRMSVoltageMean2 ;                      /* square roof of voltageMean without offset value, in analog value*/
        float rmsadjustRMSVoltageMean2;
        float rmsFinalRMSVoltage2;                      /* final voltage value with offset value*/
   
        
        int rmsanalogPinVoltageRead3 = A1;             // Which pin to measure voltage Value (Pin A0 is reserved for button function)
        float rmsvoltageSampleRead3  = 0;               /* to read the value of a sample in analog including voltageOffset1 */
        float rmsvoltageLastSample3  = 0;               /* to count time for each sample. Technically 1 milli second 1 sample is taken */
        float rmsvoltageSampleSum3   = 0;               /* accumulation of sample readings */
        float rmsvoltageSampleCount3 = 0;               /* to count number of sample. */
        float rmsvoltageMean3 ;                         /* to calculate the average value from all samples, in analog values*/ 
        float rmsRMSVoltageMean3 ;                      /* square roof of voltageMean without offset value, in analog value*/
        float rmsadjustRMSVoltageMean3;
        float rmsFinalRMSVoltage3;                      /* final voltage value with offset value*/
   
        
        /* 1.1- AC Voltage Offset */
        
              float rmsvoltageOffset1 =0.00 ;          // to Offset deviation and accuracy. Offset any fake current when no current operates. 
                                                    // Offset will automatically callibrate when SELECT Button on the LCD Display Shield is pressed.
                                                    // If you do not have LCD Display Shield, look into serial monitor to add or minus the value manually and key in here.
                                         
                                                    // 26 means add 26 to all analog value measured.
              float rmsvoltageOffset2 = 0.00;          // too offset value due to calculation error from squared and square root 
              
              float rmsvoltageOffset3 =0.00 ;          // to Offset deviation and accuracy. Offset any fake current when no current operates. 
                                                    // Offset will automatically callibrate when SELECT Button on the LCD Display Shield is pressed.
                                                    // If you do not have LCD Display Shield, look into serial monitor to add or minus the value manually and key in here.
                                         
                                                    // 26 means add 26 to all analog value measured.
              float rmsvoltageOffset4 = 0.00;          // too offset value due to calculation error from squared and square root 
              
              float rmsvoltageOffset5 =0.00 ;          // to Offset deviation and accuracy. Offset any fake current when no current operates. 
                                                    // Offset will automatically callibrate when SELECT Button on the LCD Display Shield is pressed.
                                                    // If you do not have LCD Display Shield, look into serial monitor to add or minus the value manually and key in here.
                                         
                                                    // 26 means add 26 to all analog value measured.
              float rmsvoltageOffset6 = 0.00;          // too offset value due to calculation error from squared and square root 
 
int decimalPrecision = 2;                   // decimal places for all values shown in LED Display & Serial Monitor
int expectedFrequency = 60;                 // Key in frequency for main grid (50 / 60 hz)
int analogPinVoltageRead = A3;                 // input pin voltage sensor 
int analogPinCurrentRead = A12;                 // input pin - current sensor 
int rmscanalogPinCurrentRead = A12;                 // input pin - current sensor 
float voltageAnalogOffset = 0;               // This is to offset analog value for analogInput1
float currentAnalogOffset = 0;             // This is to offset analog value for analogInput2
unsigned long startMicrosPA;                /* start counting time for Phase Angle and Period (in micro seconds)*/
unsigned long vCurrentMicrosPA;             /* current time for analogInput1 (voltage) (in micro seconds). AnalogInput1 is used for reference for phase angle*/
unsigned long iCurrentMicrosPA;             /* current time for analogInput2 (current/voltage) (in micro seconds).*/
unsigned long periodMicrosPA;               /* current time for record period of wave */
float vAnalogValue =0;                      /* is the analog value for voltage sensor / analogInput1 and center at 0 value */
float iAnalogValue =0;                      /* is the analog value for current sensor / analogInput2 and center at 0 value */
float previousValueV =0;                    /* use to record peak value for voltage sensor*/
float previousValueI =0;                    /* use to record peak value for current sensro*/
float previousphaseAngleSample=0;           /* previous sample reading to replace false value less than 100 micro seconds*/
float phaseAngleSample =0;                  /* is the time difference between 2 sensor values (in micro seconds) */
float phaseAngleAccumulate =0;              /* is the accumulate time difference for accumulate samples*/
float periodSample=0;                       /* is the time difference for a period of wave for a sample (in micro seconds)*/
float periodSampleAccumulate = 0;           /* is the accumulate time difference for accumulate samples */
float phaseDifference =0;                   /* is the averaged set of time difference of 2 sensors*/
float phaseAngle =0;                        /* is the phase angle in degree (out of 360)*/
float frequency = 0;                        /* is the frequency of the voltage sensor wave*/
float voltagePhaseAngle=0;                  /* is the time recorded from begining to reach peak value for analogInput1 in micro seconds*/
float currentPhaseAngle=0;                  /* is the time recorded from begining to reach peak value for analogInput2 in micro seconds*/
float averagePeriod =0;                     /* is the average set of time recorded for a period of wave */
int sampleCount = 0;                        /* to count how many set of samples */
int a = 3;                                  /* use for switching operation*/
float powerFactor;     

int decimalPrecision2 = 2;                   // decimal places for all values shown in LED Display & Serial Monitor
int expectedFrequency2 = 60;                 // Key in frequency for main grid (50 / 60 hz)
int analogPinVoltageRead2 = A0;                 // input pin voltage sensor 
int analogPinCurrentRead2 = A8;                 // input pin - current sensor 
int rmscanalogPinCurrentRead2 = A8;                 // input pin - current sensor 
float voltageAnalogOffset2 = 0;               // This is to offset analog value for analogInput1
float currentAnalogOffset2 = 0;             // This is to offset analog value for analogInput2
unsigned long startMicrosPA2;                /* start counting time for Phase Angle and Period (in micro seconds)*/
unsigned long vCurrentMicrosPA2;             /* current time for analogInput1 (voltage) (in micro seconds). AnalogInput1 is used for reference for phase angle*/
unsigned long iCurrentMicrosPA2;             /* current time for analogInput2 (current/voltage) (in micro seconds).*/
unsigned long periodMicrosPA2;               /* current time for record period of wave */
float vAnalogValue2 =0;                      /* is the analog value for voltage sensor / analogInput1 and center at 0 value */
float iAnalogValue2 =0;                      /* is the analog value for current sensor / analogInput2 and center at 0 value */
float previousValueV2 =0;                    /* use to record peak value for voltage sensor*/
float previousValueI2 =0;                    /* use to record peak value for current sensro*/
float previousphaseAngleSample2=0;           /* previous sample reading to replace false value less than 100 micro seconds*/
float phaseAngleSample2 =0;                  /* is the time difference between 2 sensor values (in micro seconds) */
float phaseAngleAccumulate2 =0;              /* is the accumulate time difference for accumulate samples*/
float periodSample2=0;                       /* is the time difference for a period of wave for a sample (in micro seconds)*/
float periodSampleAccumulate2 = 0;           /* is the accumulate time difference for accumulate samples */
float phaseDifference2 =0;                   /* is the averaged set of time difference of 2 sensors*/
float phaseAngle2 =0;                        /* is the phase angle in degree (out of 360)*/
float frequency2 = 0;                        /* is the frequency of the voltage sensor wave*/
float voltagePhaseAngle2=0;                  /* is the time recorded from begining to reach peak value for analogInput1 in micro seconds*/
float currentPhaseAngle2=0;                  /* is the time recorded from begining to reach peak value for analogInput2 in micro seconds*/
float averagePeriod2 =0;                     /* is the average set of time recorded for a period of wave */
int sampleCount2 = 0;                        /* to count how many set of samples */
int a2 = 3;                                  /* use for switching operation*/
float powerFactor2;         


int decimalPrecision3 = 2;                   // decimal places for all values shown in LED Display & Serial Monitor
int expectedFrequency3 = 60;                 // Key in frequency for main grid (50 / 60 hz)
int analogPinVoltageRead3 = A1;                 // input pin voltage sensor 
int analogPinCurrentRead3 = A9;                 // input pin - current sensor
int rmscanalogPinCurrentRead3 = A9;                 // input pin - current sensor 

float voltageAnalogOffset3 = 0;               // This is to offset analog value for analogInput1
float currentAnalogOffset3 = 0;             // This is to offset analog value for analogInput2
unsigned long startMicrosPA3;                /* start counting time for Phase Angle and Period (in micro seconds)*/
unsigned long vCurrentMicrosPA3;             /* current time for analogInput1 (voltage) (in micro seconds). AnalogInput1 is used for reference for phase angle*/
unsigned long iCurrentMicrosPA3;             /* current time for analogInput2 (current/voltage) (in micro seconds).*/
unsigned long periodMicrosPA3;               /* current time for record period of wave */
float vAnalogValue3 =0;                      /* is the analog value for voltage sensor / analogInput1 and center at 0 value */
float iAnalogValue3 =0;                      /* is the analog value for current sensor / analogInput2 and center at 0 value */
float previousValueV3 =0;                    /* use to record peak value for voltage sensor*/
float previousValueI3 =0;                    /* use to record peak value for current sensro*/
float previousphaseAngleSample3=0;           /* previous sample reading to replace false value less than 100 micro seconds*/
float phaseAngleSample3 =0;                  /* is the time difference between 2 sensor values (in micro seconds) */
float phaseAngleAccumulate3 =0;              /* is the accumulate time difference for accumulate samples*/
float periodSample3=0;                       /* is the time difference for a period of wave for a sample (in micro seconds)*/
float periodSampleAccumulate3 = 0;           /* is the accumulate time difference for accumulate samples */
float phaseDifference3 =0;                   /* is the averaged set of time difference of 2 sensors*/
float phaseAngle3 =0;                        /* is the phase angle in degree (out of 360)*/
float frequency3 = 0;                        /* is the frequency of the voltage sensor wave*/
float voltagePhaseAngle3=0;                  /* is the time recorded from begining to reach peak value for analogInput1 in micro seconds*/
float currentPhaseAngle3=0;                  /* is the time recorded from begining to reach peak value for analogInput2 in micro seconds*/
float averagePeriod3 =0;                     /* is the average set of time recorded for a period of wave */
int sampleCount3 = 0;                        /* to count how many set of samples */
int a3 = 3;                                  /* use for switching operation*/
float powerFactor3;     

double count=0;

bool p1bool = false;
bool p2bool = false;
bool p3bool = false;

float power1;
float power2;
float power3;
float totalpower;
float com_ind_power;

void setup() 
{
  Serial.begin(2000000);
  lcd.begin(16, 2); 
  pinMode(BUTTON_PIN, INPUT);

  #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
#endif

  // pinMode(ACS_Pin,INPUT);        //Define pin mode
  // pinMode(ACS_Pin2,INPUT);        //Define pin mode
  // pinMode(ACS_Pin3,INPUT);        //Define pin mode

}

void loop() 
{
  p1bool = false;
  p2bool = false;
  p3bool = false;
  byte buttonState = digitalRead(BUTTON_PIN);



  // read_Amps_2();                               //Launch the read_Amps function
  // Amps_RMS2 = (Amps_Peak_Peak2*0.3536*0.06)/sqrt(2);     //Now we have the peak to peak value normally the formula requires only multiplying times 0.3536
  // if (Amps_RMS2 < 0.1){
  // Amps_RMS2 = 0;}
  // read_Amps_3();                               //Launch the read_Amps function
  // Amps_RMS3 = (Amps_Peak_Peak3*0.3536*0.06)/sqrt(2);     //Now we have the peak to peak value normally the formula requires only multiplying times 0.3536
  // if (Amps_RMS3 < 0.1){
  // Amps_RMS3 = 0;}
                                             //but since the values will be very big you should multiply by 0.06, you can first not use it, 
                                             //do your calculations and compare them to real values measured by an Ammeter. eg: 0.06=Real value/Measured value
  // Serial.println("     ");                                  
  // Serial.print("Transformer 1 current = ");
  // Serial.println(Amps_RMS2);                    //Here I show the RMS value and the peak to peak value, you can print what you want and add the "A" symbol...
  // Serial.print("Transformer 2 current = ");
  // Serial.println(Amps_RMS3);
  // Serial.print("Substation 1 current = ");
  // Serial.println(Amps_RMS);
  // Serial.println("     ");
  // Serial.print("\t");
  // Serial.println(Amps_Peak_Peak);
  // delay(200);



   if(micros() >= rmsvoltageLastSample + 1000 )                                                                      /* every 0.2 milli second taking 1 reading */
    {
      rmsvoltageSampleRead = (analogRead(rmsanalogPinVoltageRead)- 512)+ rmsvoltageOffset1;                             /* read the sample value including offset value*/
      rmsvoltageSampleSum = rmsvoltageSampleSum + sq(rmsvoltageSampleRead) ;                                             /* accumulate total analog values for each sample readings*/
            
      rmsvoltageSampleRead2 = (analogRead(rmsanalogPinVoltageRead2)- 512)+ rmsvoltageOffset3;                             /* read the sample value including offset value*/
      rmsvoltageSampleSum2 = rmsvoltageSampleSum2 + sq(rmsvoltageSampleRead2) ;                                             /* accumulate total analog values for each sample readings*/
            
      rmsvoltageSampleRead3 = (analogRead(rmsanalogPinVoltageRead3)- 512)+ rmsvoltageOffset5;                             /* read the sample value including offset value*/
      rmsvoltageSampleSum3 = rmsvoltageSampleSum3 + sq(rmsvoltageSampleRead3) ; 

      rmsvoltageSampleCount = rmsvoltageSampleCount + 1;                                                              /* to move on to the next following count */
      rmsvoltageLastSample = micros() ;                                                                            /* to reset the time again so that next cycle can start again*/ 
          
      rmsvoltageSampleCount2 = rmsvoltageSampleCount2 + 1;                                                              /* to move on to the next following count */
      rmsvoltageLastSample2 = micros() ;  
          
      rmsvoltageSampleCount3 = rmsvoltageSampleCount3 + 1;                                                              /* to move on to the next following count */
      rmsvoltageLastSample3 = micros() ;  
    }
        
        if(rmsvoltageSampleCount == 1000)                                                                                /* after 4000 count or 800 milli seconds (0.8 second), do the calculation and display value*/
          {
            rmsvoltageMean = rmsvoltageSampleSum/rmsvoltageSampleCount;                                                        /* calculate average value of all sample readings taken*/
            rmsRMSVoltageMean = (sqrt(rmsvoltageMean))*1.5;                                                                 // The value X 1.5 means the ratio towards the module amplification.      
            rmsadjustRMSVoltageMean = rmsRMSVoltageMean + rmsvoltageOffset2;                                                   /* square root of the average value including offset value */                                                                                                                                                       /* square root of the average value*/                                                                                                             
            rmsFinalRMSVoltage = (rmsRMSVoltageMean + rmsvoltageOffset2)/4.54;  //4.54 is just a calibration mult.                                       /* this is the final RMS voltage*/
            if(rmsFinalRMSVoltage <= 2.5)                                                                                /* to eliminate any possible ghost value*/
            {rmsFinalRMSVoltage = 0;}
            // Serial.print(" The Voltage RMS 1 value is: ");
            // Serial.print(rmsFinalRMSVoltage,decimalPrecision);
            // Serial.println(" V ");
            rmsvoltageSampleSum =0;                                                                                      /* to reset accumulate sample values for the next cycle */
            rmsvoltageSampleCount=0;                                                                                     /* to reset number of sample for the next cycle */
          }

        if(rmsvoltageSampleCount2 == 1000)                                                                                /* after 4000 count or 800 milli seconds (0.8 second), do the calculation and display value*/
          {
            rmsvoltageMean2 = rmsvoltageSampleSum2/rmsvoltageSampleCount2;                                                        /* calculate average value of all sample readings taken*/
            rmsRMSVoltageMean2 = (sqrt(rmsvoltageMean2))*1.5;                                                                 // The value X 1.5 means the ratio towards the module amplification.      
            rmsadjustRMSVoltageMean2 = rmsRMSVoltageMean2 + rmsvoltageOffset4;                                                   /* square root of the average value including offset value */                                                                                                                                                       /* square root of the average value*/                                                                                                             
            rmsFinalRMSVoltage2 = rmsRMSVoltageMean2 + rmsvoltageOffset4;                                                        /* this is the final RMS voltage*/
            if(rmsFinalRMSVoltage2 <= 2.5)                                                                                /* to eliminate any possible ghost value*/
            {rmsFinalRMSVoltage2 = 0;}
            // Serial.print(" The Voltage RMS 2 value is: ");
            // Serial.print(rmsFinalRMSVoltage2,decimalPrecision);
            // Serial.println(" V ");
            rmsvoltageSampleSum2 =0;                                                                                      /* to reset accumulate sample values for the next cycle */
            rmsvoltageSampleCount2=0;                                                                                     /* to reset number of sample for the next cycle */
          }

          if(rmsvoltageSampleCount3 == 1000)                                                                                /* after 4000 count or 800 milli seconds (0.8 second), do the calculation and display value*/
          {
            rmsvoltageMean3 = rmsvoltageSampleSum3/rmsvoltageSampleCount3;                                                        /* calculate average value of all sample readings taken*/
            rmsRMSVoltageMean3 = (sqrt(rmsvoltageMean3))*1.5;                                                                 // The value X 1.5 means the ratio towards the module amplification.      
            rmsadjustRMSVoltageMean3 = rmsRMSVoltageMean3 + rmsvoltageOffset6;                                                   /* square root of the average value including offset value */                                                                                                                                                       /* square root of the average value*/                                                                                                             
            rmsFinalRMSVoltage3 = (rmsRMSVoltageMean3 + rmsvoltageOffset6);                                                        /* this is the final RMS voltage*/
            if(rmsFinalRMSVoltage3 <= 2.5)                                                                                /* to eliminate any possible ghost value*/
            {rmsFinalRMSVoltage3 = 0;}
            // Serial.print(" The Voltage RMS 3 value is: ");
            // Serial.print(rmsFinalRMSVoltage3,decimalPrecision);
            // Serial.println(" V ");
            rmsvoltageSampleSum3 =0;                                                                                      /* to reset accumulate sample values for the next cycle */
            rmsvoltageSampleCount3=0;                                                                                     /* to reset number of sample for the next cycle */
          }


        /* 1 - Phase Angle, Frequency and Power Factor measurement */



vAnalogValue =0;
iAnalogValue =0;

vAnalogValue2 =0;
iAnalogValue2 =0;

vAnalogValue3 =0;
iAnalogValue3 =0;


        for(int i=0; i<10; i++)
        {
        vAnalogValue = vAnalogValue + analogRead(analogPinVoltageRead)-512 + voltageAnalogOffset;       /* read analogInput1 with center adjusted*/
        iAnalogValue = iAnalogValue + analogRead(analogPinCurrentRead)-512 + currentAnalogOffset;       /* read analogInput2 with center adjusted*/


        vAnalogValue2 = vAnalogValue2 + analogRead(analogPinVoltageRead2)-512 + voltageAnalogOffset2;       /* read analogInput1 with center adjusted*/
        iAnalogValue2 = iAnalogValue2 + analogRead(analogPinCurrentRead2)-512 + currentAnalogOffset2;       /* read analogInput2 with center adjusted*/

        vAnalogValue3 = vAnalogValue3 + analogRead(analogPinVoltageRead3)-512 + voltageAnalogOffset3;       /* read analogInput1 with center adjusted*/
        iAnalogValue3 = iAnalogValue3 + analogRead(analogPinCurrentRead3)-512 + currentAnalogOffset3;       /* read analogInput2 with center adjusted*/
        }

        
vAnalogValue =vAnalogValue/10;
iAnalogValue =iAnalogValue/10;

        
vAnalogValue2 =vAnalogValue2/10;
iAnalogValue2 =iAnalogValue2/10;

        
vAnalogValue3 =vAnalogValue3/10;
iAnalogValue3 =iAnalogValue3/10;


        if((vAnalogValue>0) && a == 3)                                          /* initial begining stage of measurement when analogInput1 wave larger than 0 */
        {
          a=0;                                                                  /* allow to change to the next stage */
        }

        if((vAnalogValue2>0) && a2 == 3)                                          /* initial begining stage of measurement when analogInput1 wave larger than 0 */
        {
          a2=0;                                                                  /* allow to change to the next stage */
        }
        
         if((vAnalogValue3>0) && a3 == 3)                                          /* initial begining stage of measurement when analogInput1 wave larger than 0 */
        {
          a3=0;                                                                  /* allow to change to the next stage */
        }

        if((vAnalogValue<=0) && a ==0)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          startMicrosPA = micros();                                             /* start counting time for all*/
          a=1;                                                                  /* allow to change to the next stage */
        }
        
        if((vAnalogValue2<=0) && a2 ==0)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          startMicrosPA2 = micros();                                             /* start counting time for all*/
          a2=1;                                                                  /* allow to change to the next stage */
        }

        if((vAnalogValue3<=0) && a3 ==0)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          startMicrosPA3 = micros();                                             /* start counting time for all*/
          a3=1;                                                                  /* allow to change to the next stage */
        }

        if((vAnalogValue>0) && a ==1)                                           /* when analog value of analogInput1 larger than 0*/
        {
          a = 2;                                                                /* allow to change to the next stage */
          previousValueV = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput1 */
          previousValueI = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput2 */
        }  
     
        if((vAnalogValue2>0) && a2 ==1)                                           /* when analog value of analogInput1 larger than 0*/
        {
          a2 = 2;                                                                /* allow to change to the next stage */
          previousValueV2 = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput1 */
          previousValueI2 = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput2 */
        }  

         if((vAnalogValue3>0) && a3 ==1)                                           /* when analog value of analogInput1 larger than 0*/
        {
          a3 = 2;                                                                /* allow to change to the next stage */
          previousValueV3 = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput1 */
          previousValueI3 = 0;                                                   /* reset value. This value to be compared to measure peak value for analogInput2 */
        }  

        if((vAnalogValue > previousValueV ) && a==2)                            /* if current measured value larger than previous peak value of analogInput1 */
        {
          previousValueV = vAnalogValue ;                                       /* record current measure value replace previous peak value */
          vCurrentMicrosPA = micros();                                          /* record current time for analogInput1 */
        }
        
        if((vAnalogValue2 > previousValueV2 ) && a2==2)                            /* if current measured value larger than previous peak value of analogInput1 */
        {
          previousValueV2 = vAnalogValue2 ;                                       /* record current measure value replace previous peak value */
          vCurrentMicrosPA2 = micros();                                          /* record current time for analogInput1 */
        }

        if((vAnalogValue3 > previousValueV3 ) && a3==2)                            /* if current measured value larger than previous peak value of analogInput1 */
        {
          previousValueV3 = vAnalogValue3 ;                                       /* record current measure value replace previous peak value */
          vCurrentMicrosPA3 = micros();                                          /* record current time for analogInput1 */
        }

        if((iAnalogValue > previousValueI) && a==2)                             /* if current measured value larger than previous peak value of analogInput2 */
        {
          previousValueI = iAnalogValue ;                                       /* record current measure value replace previous peak value */
          iCurrentMicrosPA = micros();                                          /* record current time for analogInput2 */
        }

        if((iAnalogValue2 > previousValueI2) && a2==2)                             /* if current measured value larger than previous peak value of analogInput2 */
        {
          previousValueI2 = iAnalogValue2 ;                                       /* record current measure value replace previous peak value */
          iCurrentMicrosPA2 = micros();                                          /* record current time for analogInput2 */
        }

        if((iAnalogValue3 > previousValueI3) && a3==2)                             /* if current measured value larger than previous peak value of analogInput2 */
        {
          previousValueI3 = iAnalogValue3 ;                                       /* record current measure value replace previous peak value */
          iCurrentMicrosPA3 = micros();                                          /* record current time for analogInput2 */
        }

  
        if((vAnalogValue <=0) && a==2)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          periodMicrosPA = micros();                                            /* record current time for 1 period */
          periodSample = periodMicrosPA - startMicrosPA;                        /* period wave is the current time minus the starting time (for 1 sample)*/
          periodSampleAccumulate = periodSampleAccumulate + periodSample;       /* accumulate or add up time for all sample readings of period wave */
          voltagePhaseAngle = vCurrentMicrosPA - startMicrosPA;                 /* time taken for analogInput1 from 0 (down wave) to peak value (up wave)*/
          currentPhaseAngle = iCurrentMicrosPA - startMicrosPA;                 /* time taken for analogInput2 from 0 (down wave) to peak value (up wave)*/
          phaseAngleSample = currentPhaseAngle - voltagePhaseAngle;             /* time difference between analogInput1 peak value and analogInput2 peak value*/
          if(phaseAngleSample>=100)                                             /* if time difference more than 100 micro seconds*/
          {
          previousphaseAngleSample = phaseAngleSample;                          /* replace previous value using new current value */ 
          }
          if(phaseAngleSample<100)                                              /* if time difference less than 100 micro seconds (might be noise or fake values)*/
          {
          phaseAngleSample = previousphaseAngleSample;                          /* take previous value instead using low value*/
          }
          phaseAngleAccumulate = phaseAngleAccumulate + phaseAngleSample;       /* accumulate or add up time for all sample readings of time difference */
          sampleCount = sampleCount + 1;                                        /* count sample number */
          startMicrosPA = periodMicrosPA;                                       /* reset begining time */
          a=1;                                                                  /* reset stage mode */
          previousValueV = 0;                                                   /* reset peak value for analogInput1 for next set */
          previousValueI = 0;                                                   /* reset peak value for analogInput2 for next set */
        }

        if((vAnalogValue2 <=0) && a2==2)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          periodMicrosPA2 = micros();                                            /* record current time for 1 period */
          periodSample2 = periodMicrosPA2 - startMicrosPA2;                        /* period wave is the current time minus the starting time (for 1 sample)*/
          periodSampleAccumulate2 = periodSampleAccumulate2 + periodSample2;       /* accumulate or add up time for all sample readings of period wave */
          voltagePhaseAngle2 = vCurrentMicrosPA2 - startMicrosPA2;                 /* time taken for analogInput1 from 0 (down wave) to peak value (up wave)*/
          currentPhaseAngle2 = iCurrentMicrosPA2 - startMicrosPA2;                 /* time taken for analogInput2 from 0 (down wave) to peak value (up wave)*/
          phaseAngleSample2 = currentPhaseAngle2 - voltagePhaseAngle2;             /* time difference between analogInput1 peak value and analogInput2 peak value*/
          if(phaseAngleSample2>=100)                                             /* if time difference more than 100 micro seconds*/
          {
          previousphaseAngleSample2 = phaseAngleSample2;                          /* replace previous value using new current value */ 
          }
          if(phaseAngleSample2<100)                                              /* if time difference less than 100 micro seconds (might be noise or fake values)*/
          {
          phaseAngleSample2 = previousphaseAngleSample2;                          /* take previous value instead using low value*/
          }
          phaseAngleAccumulate2 = phaseAngleAccumulate2 + phaseAngleSample2;       /* accumulate or add up time for all sample readings of time difference */
          sampleCount2 = sampleCount2 + 1;                                        /* count sample number */
          startMicrosPA2 = periodMicrosPA2;                                       /* reset begining time */
          a2=1;                                                                  /* reset stage mode */
          previousValueV2 = 0;                                                   /* reset peak value for analogInput1 for next set */
          previousValueI2 = 0;                                                   /* reset peak value for analogInput2 for next set */
        }

 if((vAnalogValue3 <=0) && a3==2)                                          /* when analog value of analogInput1 smaller or equal than 0*/
        {
          periodMicrosPA3 = micros();                                            /* record current time for 1 period */
          periodSample3 = periodMicrosPA3 - startMicrosPA3;                        /* period wave is the current time minus the starting time (for 1 sample)*/
          periodSampleAccumulate3 = periodSampleAccumulate3 + periodSample3;       /* accumulate or add up time for all sample readings of period wave */
          voltagePhaseAngle3 = vCurrentMicrosPA3 - startMicrosPA3;                 /* time taken for analogInput1 from 0 (down wave) to peak value (up wave)*/
          currentPhaseAngle3 = iCurrentMicrosPA3 - startMicrosPA3;                 /* time taken for analogInput2 from 0 (down wave) to peak value (up wave)*/
          phaseAngleSample3 = currentPhaseAngle3 - voltagePhaseAngle3;             /* time difference between analogInput1 peak value and analogInput2 peak value*/
          if(phaseAngleSample3>=100)                                             /* if time difference more than 100 micro seconds*/
          {
          previousphaseAngleSample3 = phaseAngleSample3;                          /* replace previous value using new current value */ 
          }
          if(phaseAngleSample3<100)                                              /* if time difference less than 100 micro seconds (might be noise or fake values)*/
          {
          phaseAngleSample3 = previousphaseAngleSample3;                          /* take previous value instead using low value*/
          }
          phaseAngleAccumulate3 = phaseAngleAccumulate3 + phaseAngleSample3;       /* accumulate or add up time for all sample readings of time difference */
          sampleCount3 = sampleCount3 + 1;                                        /* count sample number */
          startMicrosPA3 = periodMicrosPA3;                                       /* reset begining time */
          a3=1;                                                                  /* reset stage mode */
          previousValueV3 = 0;                                                   /* reset peak value for analogInput1 for next set */
          previousValueI3 = 0;                                                   /* reset peak value for analogInput2 for next set */
        }




        if (sampleCount == expectedFrequency){
        averagePeriod = periodSampleAccumulate/sampleCount;                         /* average time for a period of wave from all the sample readings*/
        frequency = 1000000 / averagePeriod;                                        /* the calculated frequency value */
        phaseDifference = phaseAngleAccumulate / sampleCount;                       /* average time difference between 2 sensor peak values from all the sample readings */
        phaseAngle = (((phaseDifference*360) / averagePeriod));                       /* the calculated phase angle in degree (out of 360)*/
        powerFactor = abs(cos(phaseAngle*0.017453292));    
      
                                      /* power factor. Cos is in radian, the formula on the left has converted the degree to rad. */
          Serial.println("  "); 
          Serial.print("Phase Angle 1: ");
          Serial.print(phaseAngle,decimalPrecision);
          Serial.print("°  ");
          Serial.print("Frequency 1: ");
          Serial.print(frequency,decimalPrecision);
          Serial.print("Hz  ");
          Serial.print("Power Factor 1: ");
          Serial.println(powerFactor,decimalPrecision);          
          Serial.print("Commercial Power: "); 
          Serial.print(power1);
          Serial.println("  "); 

// pf 1: Commercial
// pf 2: Residential
// pf 3: Industrial

          
  read_Amps();                             
  Amps_RMS = (Amps_Peak_Peak*0.3536*0.06)/sqrt(2);    
  if (Amps_RMS < 0.1){
  Amps_RMS = 0;}
  power1=abs(Amps_RMS*24*powerFactor);
  p1bool = true;
  if(power1>=1 && power1<=15){power1=12;}
  else if(power1<1){power1=0;}
//thresholds


 if(count==4){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Commercial");
        lcd.setCursor(0,1);
        lcd.print("PF:");
        lcd.setCursor(4,1);

        lcd.print(powerFactor);
        lcd.setCursor(11,1);
}
                                                  /* reset the accumulated time for time difference from all samples*/
        
        sampleCount = 0;                                                            /* reset the sample counting quantity */
        periodSampleAccumulate = 0;                                                 /* reset the accumulated time for period wave from all samples */
        phaseAngleAccumulate =0;
        }


        if (sampleCount2 == expectedFrequency2){
          averagePeriod2 = periodSampleAccumulate2/sampleCount2;                         /* average time for a period of wave from all the sample readings*/
          frequency2 = 1000000 / averagePeriod2;                                        /* the calculated frequency value */
          phaseDifference2 = phaseAngleAccumulate2 / sampleCount2;                       /* average time difference between 2 sensor peak values from all the sample readings */
          phaseAngle2 = (((phaseDifference2*360) / averagePeriod2) - 90);                       /* the calculated phase angle in degree (out of 360)*/
          powerFactor2 = abs(cos(phaseAngle2*0.017453292));                                  /* power factor. Cos is in radian, the formula on the left has converted the degree to rad. */
          Serial.println("  "); 
          Serial.println("  "); 
          Serial.print("Phase Angle 2: ");
          Serial.print(phaseAngle2,decimalPrecision2);
          Serial.print("°  ");
          Serial.print("Frequency 2: ");
          Serial.print(frequency2,decimalPrecision2);
          Serial.print("Hz  ");
          Serial.print("Power Factor 2: ");
          Serial.println(powerFactor2,decimalPrecision2);
          Serial.print("Residential Power: "); 
          Serial.print(power2);
          Serial.println("  "); 

          Serial.println("  ");
          Serial.println("  ");
          Serial.print("Total Power: "); 
          Serial.println(totalpower);
          Serial.println("  ");
// pf 1: Commercial
// pf 2: Residential
// pf 3: Industrial


  read_Amps_2();                               //Launch the read_Amps function
  Amps_RMS2 = (Amps_Peak_Peak2*0.3536*0.06)/sqrt(2);     //Now we have the peak to peak value normally the formula requires only multiplying times 0.3536
  if (Amps_RMS2 < 0.1){
  Amps_RMS2 = 0;}
  power2=abs(Amps_RMS2*12*powerFactor2);
  p2bool = true;
  if(power2>=0 && power2<8){power2=0;}
  else if(power2>=8 && power2<=15){power2=28.5;}
  else if(power2>15 && power2<=54){power2=54;}
//thresholds


if (count==1) {
         lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Residential Real");
        lcd.setCursor(0,1);
        lcd.print("Power:");
        lcd.setCursor(7,1);

        lcd.print(power2);
        lcd.setCursor(11,1);
        lcd.print("W");
}



  if (count==3) {
 lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Residentail");
        lcd.setCursor(0,1);
        lcd.print("PF:");
        lcd.setCursor(4,1);

        lcd.print(powerFactor2);
        lcd.setCursor(11,1);
  }  


          sampleCount2 = 0;                                                            /* reset the sample counting quantity */
          periodSampleAccumulate2 = 0;                                                 /* reset the accumulated time for period wave from all samples */
          phaseAngleAccumulate2 =0;                                                    /* reset the accumulated time for time difference from all samples*/
        }
        
        if (sampleCount3 == expectedFrequency3){
          averagePeriod3 = periodSampleAccumulate3/sampleCount3;                         /* average time for a period of wave from all the sample readings*/
          frequency3 = 1000000 / averagePeriod3;                                        /* the calculated frequency value */
          phaseDifference3 = phaseAngleAccumulate3 / sampleCount3;                       /* average time difference between 2 sensor peak values from all the sample readings */
          phaseAngle3 = (((phaseDifference3*360) / averagePeriod3) - 90);                       /* the calculated phase angle in degree (out of 360)*/
          powerFactor3 = abs(cos(phaseAngle3*0.017453292));                                  /* power factor. Cos is in radian, the formula on the left has converted the degree to rad. */
          Serial.println("  "); 
          Serial.print("Phase Angle 3: ");
          Serial.print(phaseAngle3,decimalPrecision3);
          Serial.print("°  ");
          Serial.print("Frequency 3: ");
          Serial.print(frequency3,decimalPrecision3);
          Serial.print("Hz ");
          Serial.print("Power Factor 3: ");
          Serial.println(powerFactor3,decimalPrecision3);
          Serial.print("Industrial Power: "); 
          Serial.print(power3);

// pf 1: Commercial
// pf 2: Residential
// pf 3: Industrial



  read_Amps_3();                               //Launch the read_Amps function
  Amps_RMS3 = (Amps_Peak_Peak3*0.3536*0.06)/sqrt(2);     //Now we have the peak to peak value normally the formula requires only multiplying times 0.3536
  if (Amps_RMS3 < 0.1){
  Amps_RMS3 = 0;}
  power3=abs(Amps_RMS3*12*powerFactor3);
  p3bool = true;
  if(power3>=0 && power3<2){power3=0;}
  else if(power3>=2 & power3<=12){power3=27.6;}
  else if(power3>12 & power3<=51.5){power3=55.2;}
//thresholds

if (count==5) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Industrial");
        lcd.setCursor(0,1);
        lcd.print("PF:");
        lcd.setCursor(4,1);

        lcd.print(powerFactor3);
        lcd.setCursor(11,1);
}
          sampleCount3 = 0;                                                            /* reset the sample counting quantity */
          periodSampleAccumulate3 = 0;                                                 /* reset the accumulated time for period wave from all samples */
          phaseAngleAccumulate3 =0;        
        }






// C R I

  if(p1bool == true || p3bool == true){
  com_ind_power = power1 + power3;

  //Serial.println(com_ind_power);
    if (count==2) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Com. & Ind. Real");
        lcd.setCursor(0,1);
        lcd.print("Power:");
        lcd.setCursor(7,1);

        lcd.print(com_ind_power);
        lcd.setCursor(11,1);
        lcd.print("W");

  }
  }
        
  
    if(p1bool == true || p2bool == true || p3bool == true){

  totalpower = power1 + power2 + power3;
  //Serial.println(totalpower);
  if (count==0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Total Real");
        lcd.setCursor(0,1);
        lcd.print("Power:");
        lcd.setCursor(7,1);

        lcd.print(totalpower);
        // lcd.setCursor(11,1);
        lcd.print("W");

  }  
    }





if(buttonState == HIGH){
  delay(200);
  count++;
  if(count>6){count=0;}
}

else{
double num=0;
}




 
}







 void read_Amps()          
 {                        
  int cnt;            
  High_peak = 0;      
  Low_peak = 1024;
  float sum1=0;
    
  for(cnt=0 ; cnt<SAMPLES ; cnt++)         
  {
    float ACS_Value = analogRead(rmscanalogPinCurrentRead); 
    if(ACS_Value > High_peak)          
    {
      High_peak = ACS_Value;         
    }
        
    if(ACS_Value < Low_peak)        
    {
      Low_peak = ACS_Value;             
    }                                     
      
  Amps_Peak_Peak = High_peak - Low_peak;    
  Amps_Peak_Peak_Array[cnt]=Amps_Peak_Peak;
  sum1 +=Amps_Peak_Peak_Array[cnt];
  }
  sum1=sum1/101;
 }

void read_Amps_2()            //read_Amps function calculate the difference between the high peak and low peak 
{                           //get peak to peak value
  int cnt;            //Counter

  High_peak2 = 0;      //We first assume that our high peak is equal to 0 and low peak is 1024, yes inverted
  Low_peak2 = 1024;
 float sum2=0;

  
      for(cnt=0 ; cnt<SAMPLES ; cnt++)          //everytime a sample (module value) is taken it will go through test
      {
        float ACS_Value2 = analogRead(rmscanalogPinCurrentRead2); //We read a single value from the module

        if(ACS_Value2 > High_peak2)                //If that value is higher than the high peak (at first is 0)
            {
              High_peak2 = ACS_Value2;            //The high peak will change from 0 to that value found
            }
        
        if(ACS_Value2 < Low_peak2)                //If that value is lower than the low peak (at first is 1024)
            {
              Low_peak2 = ACS_Value2;             //The low peak will change from 1024 to that value found
            }
                                             //We keep looping until we take all samples and at the end we will have the high/low peaks values
      
  Amps_Peak_Peak2 = High_peak2 - Low_peak2;      //Calculate the difference
Amps_Peak_Peak2_Array[cnt]=Amps_Peak_Peak2;
  sum2 +=Amps_Peak_Peak2_Array[cnt];
      }
          sum2=sum2/101;

    }


void read_Amps_3()            //read_Amps function calculate the difference between the high peak and low peak 
{                           //get peak to peak value
  int cnt;            //Counter
  High_peak3 = 0;      //We first assume that our high peak is equal to 0 and low peak is 1024, yes inverted
  Low_peak3 = 1024;
 float sum3=0;
  
      for(cnt=0 ; cnt<SAMPLES ; cnt++)          //everytime a sample (module value) is taken it will go through test
      {
        float ACS_Value3 = analogRead(rmscanalogPinCurrentRead3); //We read a single value from the module

      
        if(ACS_Value3 > High_peak3)                //If that value is higher than the high peak (at first is 0)
            {
              High_peak3 = ACS_Value3;            //The high peak will change from 0 to that value found
            }
        
        if(ACS_Value3 < Low_peak3)                //If that value is lower than the low peak (at first is 1024)
            {
              Low_peak3 = ACS_Value3;             //The low peak will change from 1024 to that value found
            }
                                              //We keep looping until we take all samples and at the end we will have the high/low peaks values
      
  Amps_Peak_Peak3 = High_peak3 - Low_peak3;      //Calculate the difference

Amps_Peak_Peak3_Array[cnt]=Amps_Peak_Peak3;
  sum3 +=Amps_Peak_Peak3_Array[cnt];
    }
    sum3=sum3/101;
}