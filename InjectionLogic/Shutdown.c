
//========================//
//  Shutdown Logic        //
//  Shutdown.c            //
//  ECE 2195 DCA Project  //
//  Evan Kain             //
//========================//


// Inclusions
#include "Shutdown.h"


// MAIN
int main( int argc, char *argv[ ] ) {

  // Handle Incorrect Input Arguments
  if ( argc != 5 ) {
    printf( "ERROR: Input parameters incorrect (%d).\n", argc );
    printf( "  Usage:    ./Shutdown <tempFile> <thresholdFile> <maxChar> <outputFile>\n" );
    printf( "  Example:  ./Shutdown temp.txt threshold.txt 256 out.txt\n" );
    return -1;
  }

  // Input Depictions:
  //   Temperature filepath is argv[1].
  //   Threshold filepath is argv[2].
  int  maxChar = atoi( argv[3] );
  //   Output filepath is argv[4].

  // Execution Time with Prints:            0.1125
  // Execution Time without Prints:         0.0444
  // Execution Time w/o Prints w/ 1M Loop:  2.0177

  // Check Filenames and Open Files
//printf( "Temperature filepath is: %s\n", argv[1] );
//printf( "Threshold filepath is:   %s\n", argv[2] );
//printf( "Output filepath is:      %s\n", argv[4] );
  FILE         *tempFile      = fopen( argv[1], "r" );
  FILE         *thresholdFile = fopen( argv[2], "r" );
  FILE         *outputFile    = fopen( argv[4], "w" );
  char         buffer[maxChar];
  char         *upperElem;
  char         *lowerElem;
  double       temp           = 0.0;  // Temperature
  register int linNum         = 0;    // Threshold File Line Number
  register int numDev         = 0;    // Number of Devices
  register int i              = 0;    // Loop Iterator

  // Registered State Values - Increased Likelihood of Injection Hit
  //   Note: defaulted to invalid values to increase fault likelihood.
  register int dev0State      = 10;   // Device 0 State
  register int dev1State      = 11;   // Device 1 State
  register int dev2State      = 12;   // Device 2 State
  register int dev3State      = 13;   // Device 3 State
  register int dev4State      = 14;   // Device 4 State
  register int dev5State      = 15;   // Device 5 State
  register int dev6State      = 16;   // Device 6 State

  // Get Number of Devices from Threshold File
  fgets( buffer, maxChar, (FILE*)thresholdFile );
  numDev = atoi( buffer );
//printf("The number of devices is: %d\n", numDev );

  // Build Upper and Lower Threshold Arrays from Threshold File
  double upperThreshold[numDev];
  double lowerThreshold[numDev];
  while ( !feof ( thresholdFile ) ) {
    fgets( buffer, maxChar, (FILE*)thresholdFile );
    if ( !feof( thresholdFile ) ) {
      upperElem = strtok( buffer, "," );
      lowerElem = strtok( NULL, "," );
      upperThreshold[linNum] = atof( upperElem );
      lowerThreshold[linNum] = atof( lowerElem );
    //printf( "Device Range:  %f, %f\n", upperThreshold[linNum], lowerThreshold[linNum] );
      linNum++;
    };
  };
//printf( "Number of lines read in is: %d\n", linNum );

  // Read Temperatures from File
  while ( !feof ( tempFile ) ) {
    fgets( buffer, maxChar, (FILE*)tempFile );
    if ( !feof( tempFile ) ) {
      upperElem = strtok( buffer, "," );
      lowerElem = strtok( NULL, "," );
      temp      = atof( lowerElem );
      // Function Call Deactivated (shutdown( temp, upperThreshold, lowerThreshold, numDev, outputFile ); )

      // Check Temperatures - Cycle 0 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[0] ) || ( temp < lowerThreshold[0] ) ) {
        dev0State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[0] ) || ( temp >= lowerThreshold[0] ) ) {
        dev0State = 1;  // Device Online
      } else {
        dev0State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 0 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev0State = dev0State;
      }

      // Check Temperatures - Cycle 1 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[1] ) || ( temp < lowerThreshold[1] ) ) {
        dev1State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[1] ) || ( temp >= lowerThreshold[1] ) ) {
        dev1State = 1;  // Device Online
      } else {
        dev1State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 1 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev1State = dev1State;
      }

      // Check Temperatures - Cycle 2 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[2] ) || ( temp < lowerThreshold[2] ) ) {
        dev2State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[2] ) || ( temp >= lowerThreshold[2] ) ) {
        dev2State = 1;  // Device Online
      } else {
        dev2State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 2 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev2State = dev2State;
      }

      // Check Temperatures - Cycle 3 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[3] ) || ( temp < lowerThreshold[3] ) ) {
        dev3State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[3] ) || ( temp >= lowerThreshold[3] ) ) {
        dev3State = 1;  // Device Online
      } else {
        dev3State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 3 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev3State = dev3State;
      }

      // Check Temperatures - Cycle 4 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[4] ) || ( temp < lowerThreshold[4] ) ) {
        dev4State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[4] ) || ( temp >= lowerThreshold[4] ) ) {
        dev4State = 1;  // Device Online
      } else {
        dev4State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 4 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev4State = dev4State;
      }

      // Check Temperatures - Cycle 5 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[5] ) || ( temp < lowerThreshold[5] ) ) {
        dev5State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[5] ) || ( temp >= lowerThreshold[5] ) ) {
        dev5State = 1;  // Device Online
      } else {
        dev5State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 5 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev5State = dev5State;
      }

      // Check Temperatures - Cycle 6 - Unrolled to Register State Variables
      if ( ( temp > upperThreshold[6] ) || ( temp < lowerThreshold[6] ) ) {
        dev6State = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[6] ) || ( temp >= lowerThreshold[6] ) ) {
        dev6State = 1;  // Device Online
      } else {
        dev6State = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 6 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev6State = dev6State;
      }

      // Effective Loop to Increase Execution Time and Extend Vulnerability
      //for( i = 1; i < 1000000; i++ ) { 
      //  dev0State = dev0State;
      //  dev1State = dev1State;
      //  dev2State = dev2State;
      //  dev3State = dev3State;
      //  dev4State = dev4State;
      //  dev5State = dev5State;
      //  dev6State = dev6State;
      //}

    };

    fprintf( outputFile, "%d %d %d %d %d %d %d\n", dev0State, dev1State, dev2State, dev3State, dev4State, dev5State, dev6State );

  };

//printf( "The output can be found as a matrix stored in: %s\n  1 == ON, 0 == OFF\n", argv[4] );
  return 0;
};


// Local Function Implementations - Deactivated - System Self-Contained in Main

// shutdown - given current temperature and thresholds for each device, output device states.
//void shutdown( double temp, double highThreshold[], double lowThreshold[], register int numDev, FILE *outputFile ) {
//  register int i     = 0;
//  register int state = 0;
//printf( "Calculating States of %d Devices at Temperature %lf\n", *numDev, *temp );
  // Loop Through Devices
//  for ( i = 0; i < numDev; i++) {
    // Check Temperatures
//    if ( ( temp > highThreshold[i] ) || ( temp < lowThreshold[i] ) ) {
//      state = 0;  // Device Offline
//    } else {
//      state = 1;  // Device Online
//    }
//    fprintf( outputFile, "%d", state );
//  };
//  fprintf( outputFile, "\n" );
//};



// END Shutdown.c  - ETK

