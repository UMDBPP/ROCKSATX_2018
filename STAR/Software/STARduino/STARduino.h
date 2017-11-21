#ifndef _starduino_h_
#define _starduino_h_

/* Include built-in libraries */
/* These can be installed via the arduino IDE library manager */
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

/* Include project libraries */
#include "src/Sensors/ADXL375.h"
#include "src/Sensors/MAX31725Temp.h"
#include "src/Sensors/PowerSensors.h"
#include "src/Sensors/BMX055.h"
#include "src/Sensors/ChipCap2.h"
#include "src/CCSDS/CCSDS.h"
#include "src/CCSDS/ccsds_utilities.h"
#include "EZGPIO.h"

/* Define Parameters */


/* Define aliases */
// Software Reset Register
#define RESET_REGISTER *(unsigned int volatile *)0xE000ED0C

// Serials
#define SERIAL_DEBUG Serial // FIXME

// Pins
#define PIN_SD_CS 22 // FIXME
#define PIN_LED 9 // FIXME
#define PIN_BIAS 28 // FIXME
#define PIN_CUTOFF 14 // FIXME
#define PIN_PIKILL 16 // FIXME
#define PIN_EXTKILL 13 // FIXME
#define PIN_FLASH_CS 13 // FIXME

// Filenames1
#define FILENAME_INTERFACE_LOG "intf_log.txt"
#define FILENAME_SENSOR_LOG "sens_log.txt"
#define FILENAME_SYNC_LOG "sync_log.txt"
#define FILENAME_CMDSEQ "cmds.cmd"

// Errors
#define ERROR_SDLOAD_OPENFILE -1
#define ERROR_SDLOAD_CMDCHKSUM -3

// Status
#define STATUS_INITALIZED 1

#endif _starduino_h_
