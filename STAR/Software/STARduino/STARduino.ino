
/* Include header */
#include "STARduino.h"

/* Instantiate objects */
ADXL375 accel;
MAX31725 tempSensor;
//VoltageSense voltageSensor;
//CurrentSense currentSensor;
BMX055_ACCEL bmxAccel;
BMX055_GYRO bmxGyro;
BMX055_MAG bmxMag;
HoneywellPressureI2C pres_sens;
//CFF_ChipCap2 chip;

/* Global variables */
char filename[16];
File dataFile;
uint32_t cycleStartTime = 0;
#define STEP_PIN 2
#define BIAS_PIN A2
uint32_t sampleRate = 5; //sample rate of the sine wave in Hertz, how many times per second the TC5_Handler() function gets called per second basically

/* Define Functions */
void setup() {
  /*
     Initalizes the STAR payload. Opens the serial connections, opens log files,
     loads queued commands, and initializes sensors.
     Inputs:
       none
     Output:
       none
     Return:
       none
  */
  SERIAL_DEBUG.begin(9600);
  Wire.begin();
  
  SERIAL_DEBUG.println("Began");
  
  // Initalize ADXL375 accel
  accel.begin();   // Not all sensors require begin() functions
  
  // Initalize MAX31725 tempSensor
  
  // Initalize VoltageSense voltageSensor
  
  // Initalize CurrentSense currentSensor
  
  // Initalize BMX055_ACCEL bmxAccel
  
  // Initalize BMX055_GYRO bmxGyro
  
  // Initalize BMX055_MAG bmxMag
  bmxMag.begin(); // Not all sensors require begin() functions

  // Initalize HoneywellPressureI2C pres_sens
  
  // Initalize CFF_ChipCap2 chip

  // Initialize Motor Timer
  pinMode(STEP_PIN, OUTPUT);
  tcConfigure(sampleRate); //configure the timer to run at <sampleRate>Hertz
  tcStartCounter(); //starts the timer

  // Initialize Bias Reader
  pinMode(BIAS_PIN, INPUT);
  analogReadResolution(12);

  // Initalize SD card
  SERIAL_DEBUG.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(PIN_SD_CS)) {
    SERIAL_DEBUG.println("Card failed, or not present");
  }
  else
  {
    SERIAL_DEBUG.println("card initialized.");
  }

  /* Find a filename that's not yet been used */
  getFreeFilename(filename);

  SERIAL_DEBUG.print("Filename: "); SERIAL_DEBUG.println(filename);
  
  /* open the file to write to it */
  dataFile = SD.open(filename, FILE_WRITE);

  if (dataFile) {
    /* Print file header */
    dataFile.println("MET [sec],Flag,Flag,Flag,Flag,Volt [V],Curr [A],AccelX,AccelY,AccelZ,Temp[C],AccelX,AccelY,AccelZ,BMXTemp,GyroX,GyroY,GyroZ,MagX,MagY,MagZ,Hall");
  }
  else {
    SERIAL_DEBUG.println("error opening datalog.txt");
  }

}

void loop() {
       
    if(time_for_cycle(cycleStartTime))
    {
      /* Record start of cycle */
      cycleStartTime = get_MET();

      //OUTCLR_A = (1 << PIN_LED);
      //OUTCLR_A = (1 << PIN_EXTKILL);
      //OUTCLR_A = (1 << PIN_BIAS);
          
      //uint16_t adcVoltageReading = voltageSensor.read_voltage();
      //uint16_t adcCurrentReading = currentSensor.read_current();
    
      accel.recieve_data();
      int16_t adxlAccelerometerXReading = accel.get_x_accel();
      int16_t adxlAccelerometerYReading = accel.get_y_accel();
      int16_t adxlAccelerometerZReading = accel.get_z_accel();
      
      tempSensor.recieve_data();
      uint16_t maximTemperatureReading = tempSensor.get_temperature();
      
      bmxAccel.recieve_data();
      int16_t bmxAccelerometerXReading = bmxAccel.get_x_accel();
      int16_t bmxAccelerometerYReading = bmxAccel.get_y_accel();
      int16_t bmxAccelerometerZReading = bmxAccel.get_z_accel();
      int16_t bmxAccelerometerTemperatureReading = bmxAccel.get_temp();
  
      bmxGyro.recieve_data();
      int16_t bmxGyroscopeXReading = bmxGyro.get_x_gyro();
      int16_t bmxGyroscopeYReading = bmxGyro.get_y_gyro();
      int16_t bmxGyroscopeZReading = bmxGyro.get_z_gyro();
  
      bmxMag.recieve_data();
      int16_t bmxMagnetometerXReading = bmxMag.get_x_mag();
      int16_t bmxMagnetometerYReading = bmxMag.get_y_mag();
      int16_t bmxMagnetometerZReading =  bmxMag.get_z_mag();
      uint16_t bmxMagnetometerHallReading = bmxMag.get_hall();
  
      //chip.readSensor();
      
      /*
      uint32_t portADir = PORT->Group[0].DIR.reg;
      uint32_t portBDir = PORT->Group[1].DIR.reg;
      uint32_t portAOut = PORT->Group[0].OUTSET.reg; // TODO HACK
      uint32_t portBOut = PORT->Group[1].OUTSET.reg; // TODO HACK
      */

      uint16_t biasVoltage = analogRead(A2);
      
      // if the file is available, write to it:
      if (dataFile) {
        dataFile.print(cycleStartTime);
        dataFile.print(",");
        /*
        dataFile.print(portADir);
        dataFile.print(",");
        dataFile.print(portBDir);
        dataFile.print(",");
        dataFile.print(portAOut);
        dataFile.print(",");
        dataFile.print(portBOut);
        */
        //dataFile.print(",");
        //dataFile.print(adcVoltageReading);
        //dataFile.print(",");
        //dataFile.print(adcCurrentReading);
        //dataFile.print(",");
        dataFile.print(adxlAccelerometerXReading);
        dataFile.print(",");
        dataFile.print(adxlAccelerometerYReading);
        dataFile.print(",");
        dataFile.print(adxlAccelerometerZReading);
        dataFile.print(",");
        dataFile.print(maximTemperatureReading);
        dataFile.print(",");
        dataFile.print(bmxAccelerometerXReading);
        dataFile.print(",");
        dataFile.print(bmxAccelerometerYReading);
        dataFile.print(",");
        dataFile.print(bmxAccelerometerZReading);
        dataFile.print(",");
        dataFile.print(bmxAccelerometerTemperatureReading);
        dataFile.print(",");
        dataFile.print(bmxGyroscopeXReading);
        dataFile.print(",");
        dataFile.print(bmxGyroscopeYReading);
        dataFile.print(",");
        dataFile.print(bmxGyroscopeZReading);
        dataFile.print(",");
        dataFile.print(bmxMagnetometerXReading);
        dataFile.print(",");
        dataFile.print(bmxMagnetometerYReading);
        dataFile.print(",");
        dataFile.print(bmxMagnetometerZReading);
        dataFile.print(",");
        dataFile.print(bmxMagnetometerHallReading);
        dataFile.print(",");
        dataFile.print(biasVoltage);
        dataFile.println();
        dataFile.close();
        
      }
      // if the file isn't open, pop up an error:
      else {
        SERIAL_DEBUG.println("error opening datalog.txt");
        Serial.print(cycleStartTime);
        Serial.print(",");
        Serial.print(adxlAccelerometerXReading);
        Serial.print(",");
        Serial.print(adxlAccelerometerYReading);
        Serial.print(",");
        Serial.print(adxlAccelerometerZReading);
        Serial.print(",");
        Serial.print(maximTemperatureReading);
        Serial.print(",");
        Serial.print(bmxAccelerometerXReading);
        Serial.print(",");
        Serial.print(bmxAccelerometerYReading);
        Serial.print(",");
        Serial.print(bmxAccelerometerZReading);
        Serial.print(",");
        Serial.print(bmxAccelerometerTemperatureReading);
        Serial.print(",");
        Serial.print(bmxGyroscopeXReading);
        Serial.print(",");
        Serial.print(bmxGyroscopeYReading);
        Serial.print(",");
        Serial.print(bmxGyroscopeZReading);
        Serial.print(",");
        Serial.print(bmxMagnetometerXReading);
        Serial.print(",");
        Serial.print(bmxMagnetometerYReading);
        Serial.print(",");
        Serial.print(bmxMagnetometerZReading);
        Serial.print(",");
        Serial.print(bmxMagnetometerHallReading);
        Serial.print(",");
        Serial.print(biasVoltage);
        Serial.println();
      }
  }

  
}


/***********************************************************************************************/
// Motor Driver Interrupt Functions
// Thanks to https://gist.github.com/nonsintetic/ad13e70f164801325f5f552f84306d6f

//this function gets called by the interrupt at <sampleRate>Hertz
void TC5_Handler (void) {
  //YOUR CODE HERE 
  static bool pos = 0;
  digitalWrite(STEP_PIN, pos);
  pos = !pos;
  // END OF YOUR CODE
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; //don't change this, it's part of the timer code
}

/* 
 *  TIMER SPECIFIC FUNCTIONS FOLLOW
 *  you shouldn't change these unless you know what you're doing
 */

//Configures the TC to generate output events at the sample frequency.
//Configures the TC in Frequency Generation mode, with an event output once
//each time the audio sample frequency period expires.
 void tcConfigure(int sampleRate)
{
 // Enable GCLK for TCC2 and TC5 (timer counter input clock)
 GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
 while (GCLK->STATUS.bit.SYNCBUSY);

 tcReset(); //reset TC5

 // Set Timer counter Mode to 16 bits
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
 // Set TC5 mode as match frequency
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
 //set prescaler and enable TC5
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_ENABLE;
 //set TC5 timer counter based off of the system clock and the user defined sample rate or waveform
 TC5->COUNT16.CC[0].reg = (uint16_t) (SystemCoreClock / sampleRate - 1);
 while (tcIsSyncing());
 
 // Configure interrupt request
 NVIC_DisableIRQ(TC5_IRQn);
 NVIC_ClearPendingIRQ(TC5_IRQn);
 NVIC_SetPriority(TC5_IRQn, 0);
 NVIC_EnableIRQ(TC5_IRQn);

 // Enable the TC5 interrupt request
 TC5->COUNT16.INTENSET.bit.MC0 = 1;
 while (tcIsSyncing()); //wait until TC5 is done syncing 
} 

//Function that is used to check if TC5 is done syncing
//returns true when it is done syncing
bool tcIsSyncing()
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}

//This function enables TC5 and waits for it to be ready
void tcStartCounter()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
  while (tcIsSyncing()); //wait until snyc'd
}

//Reset TC5 
void tcReset()
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}

//disable TC5
void tcDisable()
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}





