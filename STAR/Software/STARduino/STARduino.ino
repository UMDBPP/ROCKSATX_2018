
/* Include header */
#include "STARduino.h"

/* Instantiate objects */
ADXL375 accel;
MAX31725 tempSensor;
VoltageSense voltageSensor;
CurrentSense currentSensor;
BMX055_ACCEL bmxAccel;
BMX055_GYRO bmxGyro;
BMX055_MAG bmxMag;
HoneywellPressureI2C pres_sens;
CFF_ChipCap2 chip;

/* Global variables */
char filename[16];
File dataFile;
uint32_t cycleStartTime = 0;

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
  //adxl.begin();   // Not all sensors require begin() functions
  
  // Initalize MAX31725 tempSensor
  
  // Initalize VoltageSense voltageSensor
  
  // Initalize CurrentSense currentSensor
  
  // Initalize BMX055_ACCEL bmxAccel
  
  // Initalize BMX055_GYRO bmxGyro
  
  // Initalize BMX055_MAG bmxMag
  //bmxMag.begin(); // Not all sensors require begin() functions

  // Initalize HoneywellPressureI2C pres_sens
  
  // Initalize CFF_ChipCap2 chip


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

      OUTCLR_A = (1 << PIN_LED);
      OUTCLR_A = (1 << PIN_EXTKILL);
      OUTCLR_A = (1 << PIN_BIAS);
          
      uint16_t adcVoltageReading = voltageSensor.read_voltage();
      uint16_t adcCurrentReading = currentSensor.read_current();
    
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
  
      chip.readSensor();
      
      /*
      uint32_t portADir = PORT->Group[0].DIR.reg;
      uint32_t portBDir = PORT->Group[1].DIR.reg;
      uint32_t portAOut = PORT->Group[0].OUTSET.reg; // TODO HACK
      uint32_t portBOut = PORT->Group[1].OUTSET.reg; // TODO HACK
      */
      
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
        dataFile.print(",");
        dataFile.print(adcVoltageReading);
        dataFile.print(",");
        dataFile.print(adcCurrentReading);
        dataFile.print(",");
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
        dataFile.println();
        dataFile.close();
        
      }
      // if the file isn't open, pop up an error:
      else {
        SERIAL_DEBUG.println("error opening datalog.txt");
      }
  }

  
}





