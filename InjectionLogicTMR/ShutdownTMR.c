
//========================//
//  Shutdown TMR Logic    //
//  ShutdownTMR.c         //
//  ECE 2195 DCA Project  //
//  Evan Kain/Gretok      //
//========================//


// Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
  int          voteCountOn    = 0;    // Vote Count Variable - On Decision
  int          voteCountOff   = 0;    // Vote Count Variable - Off Decision
  // Registered State Values - Increased Likelihood of Injection Hit
  //   Note: defaulted to invalid values to increase fault likelihood.
  register int dev0StateA     = 10;   // Device 0 State Registers
  register int dev0StateB     = 10;
  register int dev0StateC     = 10;
  register int dev1StateA     = 11;   // Device 1 State Registers
  register int dev1StateB     = 11;
  register int dev1StateC     = 11;
  register int dev2StateA     = 12;   // Device 2 State Registers
  register int dev2StateB     = 12;
  register int dev2StateC     = 12;
  register int dev3StateA     = 13;   // Device 3 State Registers
  register int dev3StateB     = 13;
  register int dev3StateC     = 13;
  register int dev4StateA     = 14;   // Device 4 State Registers
  register int dev4StateB     = 14;
  register int dev4StateC     = 14;
  register int dev5StateA     = 15;   // Device 5 State Registers
  register int dev5StateB     = 15;
  register int dev5StateC     = 15;
  register int dev6StateA     = 16;   // Device 6 State Registers
  register int dev6StateB     = 16;
  register int dev6StateC     = 16;
  register int dev0VoterOut   = 10;   // Device State Voting Result Values
  register int dev1VoterOut   = 11;
  register int dev2VoterOut   = 12;
  register int dev3VoterOut   = 13;
  register int dev4VoterOut   = 14;
  register int dev5VoterOut   = 15;
  register int dev6VoterOut   = 16;
  

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

      // Check Temperatures - Cycle 0 - Unrolled to Register State Variables
      // Device 0 State Register A Check
      if ( ( temp > upperThreshold[0] ) || ( temp < lowerThreshold[0] ) ) {
        dev0StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[0] ) && ( temp >= lowerThreshold[0] ) ) {
        dev0StateA = 1;  // Device Online
      } else {
        dev0StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 0 State Register B Check
      if ( ( temp > upperThreshold[0] ) || ( temp < lowerThreshold[0] ) ) {
        dev0StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[0] ) && ( temp >= lowerThreshold[0] ) ) {
        dev0StateB = 1;  // Device Online
      } else {
        dev0StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 0 State Register C Check
      if ( ( temp > upperThreshold[0] ) || ( temp < lowerThreshold[0] ) ) {
        dev0StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[0] ) && ( temp >= lowerThreshold[0] ) ) {
        dev0StateC = 1;  // Device Online
      } else {
        dev0StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 0 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev0StateA = dev0StateA;
        dev0StateB = dev0StateB;
        dev0StateC = dev0StateC;
      }

      // Check Temperatures - Cycle 1 - Unrolled to Register State Variables
      // Device 1 State Register A Check
      if ( ( temp > upperThreshold[1] ) || ( temp < lowerThreshold[1] ) ) {
        dev1StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[1] ) && ( temp >= lowerThreshold[1] ) ) {
        dev1StateA = 1;  // Device Online
      } else {
        dev1StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 1 State Register B Check
      if ( ( temp > upperThreshold[1] ) || ( temp < lowerThreshold[1] ) ) {
        dev1StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[1] ) && ( temp >= lowerThreshold[1] ) ) {
        dev1StateB = 1;  // Device Online
      } else {
        dev1StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 1 State Register C Check
      if ( ( temp > upperThreshold[1] ) || ( temp < lowerThreshold[1] ) ) {
        dev1StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[1] ) && ( temp >= lowerThreshold[1] ) ) {
        dev1StateC = 1;  // Device Online
      } else {
        dev1StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 1 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev1StateA = dev1StateA;
        dev1StateB = dev1StateB;
        dev1StateC = dev1StateC;
      }

      // Check Temperatures - Cycle 2 - Unrolled to Register State Variables
      // Device 2 State Register A Check
      if ( ( temp > upperThreshold[2] ) || ( temp < lowerThreshold[2] ) ) {
        dev2StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[2] ) && ( temp >= lowerThreshold[2] ) ) {
        dev2StateA = 1;  // Device Online
      } else {
        dev2StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 2 State Register B Check
      if ( ( temp > upperThreshold[2] ) || ( temp < lowerThreshold[2] ) ) {
        dev2StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[2] ) && ( temp >= lowerThreshold[2] ) ) {
        dev2StateB = 1;  // Device Online
      } else {
        dev2StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 2 State Register C Check
      if ( ( temp > upperThreshold[2] ) || ( temp < lowerThreshold[2] ) ) {
        dev2StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[2] ) && ( temp >= lowerThreshold[2] ) ) {
        dev2StateC = 1;  // Device Online
      } else {
        dev2StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 2 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev2StateA = dev2StateA;
        dev2StateB = dev2StateB;
        dev2StateC = dev2StateC;
      }

      // Check Temperatures - Cycle 3 - Unrolled to Register State Variables
      // Device 3 State Register A Check
      if ( ( temp > upperThreshold[3] ) || ( temp < lowerThreshold[3] ) ) {
        dev3StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[3] ) && ( temp >= lowerThreshold[3] ) ) {
        dev3StateA = 1;  // Device Online
      } else {
        dev3StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 3 State Register B Check
      if ( ( temp > upperThreshold[3] ) || ( temp < lowerThreshold[3] ) ) {
        dev3StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[3] ) && ( temp >= lowerThreshold[3] ) ) {
        dev3StateB = 1;  // Device Online
      } else {
        dev3StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 3 State Register C Check
      if ( ( temp > upperThreshold[3] ) || ( temp < lowerThreshold[3] ) ) {
        dev3StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[3] ) && ( temp >= lowerThreshold[3] ) ) {
        dev3StateC = 1;  // Device Online
      } else {
        dev3StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 3 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev3StateA = dev3StateA;
        dev3StateB = dev3StateB;
        dev3StateC = dev3StateC;
      }

      // Check Temperatures - Cycle 4 - Unrolled to Register State Variables
      // Device 4 State Register A Check
      if ( ( temp > upperThreshold[4] ) || ( temp < lowerThreshold[4] ) ) {
        dev4StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[4] ) && ( temp >= lowerThreshold[4] ) ) {
        dev4StateA = 1;  // Device Online
      } else {
        dev4StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 4 State Register B Check
      if ( ( temp > upperThreshold[4] ) || ( temp < lowerThreshold[4] ) ) {
        dev4StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[4] ) && ( temp >= lowerThreshold[4] ) ) {
        dev4StateB = 1;  // Device Online
      } else {
        dev4StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 4 State Register C Check
      if ( ( temp > upperThreshold[4] ) || ( temp < lowerThreshold[4] ) ) {
        dev4StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[4] ) && ( temp >= lowerThreshold[4] ) ) {
        dev4StateC = 1;  // Device Online
      } else {
        dev4StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 4 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev4StateA = dev4StateA;
        dev4StateB = dev4StateB;
        dev4StateC = dev4StateC;
      }

      // Check Temperatures - Cycle 5 - Unrolled to Register State Variables
      // Device 5 State Register A Check
      if ( ( temp > upperThreshold[5] ) || ( temp < lowerThreshold[5] ) ) {
        dev5StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[5] ) && ( temp >= lowerThreshold[5] ) ) {
        dev5StateA = 1;  // Device Online
      } else {
        dev5StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 5 State Register B Check
      if ( ( temp > upperThreshold[5] ) || ( temp < lowerThreshold[5] ) ) {
        dev5StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[5] ) && ( temp >= lowerThreshold[5] ) ) {
        dev5StateB = 1;  // Device Online
      } else {
        dev5StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 5 State Register C Check
      if ( ( temp > upperThreshold[5] ) || ( temp < lowerThreshold[5] ) ) {
        dev5StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[5] ) && ( temp >= lowerThreshold[5] ) ) {
        dev5StateC = 1;  // Device Online
      } else {
        dev5StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 5 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev5StateA = dev5StateA;
        dev5StateB = dev5StateB;
        dev5StateC = dev5StateC;
      }

      // Check Temperatures - Cycle 6 - Unrolled to Register State Variables
      // Device 6 State Register A Check
      if ( ( temp > upperThreshold[6] ) || ( temp < lowerThreshold[6] ) ) {
        dev6StateA = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[6] ) && ( temp >= lowerThreshold[6] ) ) {
        dev6StateA = 1;  // Device Online
      } else {
        dev6StateA = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 6 State Register B Check
      if ( ( temp > upperThreshold[6] ) || ( temp < lowerThreshold[6] ) ) {
        dev6StateB = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[6] ) && ( temp >= lowerThreshold[6] ) ) {
        dev6StateB = 1;  // Device Online
      } else {
        dev6StateB = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }
      // Device 6 State Register C Check
      if ( ( temp > upperThreshold[6] ) || ( temp < lowerThreshold[6] ) ) {
        dev6StateC = 0;  // Device Offline
      } else if ( ( temp <= upperThreshold[6] ) && ( temp >= lowerThreshold[6] ) ) {
        dev6StateC = 1;  // Device Online
      } else {
        dev6StateC = 2;  // Defaults to an Invalid State - Increased Likelihood of Data Error
      }

      // Execution Time Extension Loop for Cycle 6 for Vulnerability
      for( i = 1; i < 100000; i++ ) { 
        dev6StateA = dev6StateA;
        dev6StateB = dev6StateB;
        dev6StateC = dev6StateC;
      }

      // Device State Voting Logic
      //   Note: cannot just add values as incorrectly processed device state variables will
      //   have value 2 or higher (10-16 at initialization).  Instead must check each device
      //   and add to count of "on" and "off" decisions, letting the majority of that count
      //   decide.  We still count any nonzero value as on, but that is factored as a count
      //   towards the final decision, not the final decision itself.  For example, if two
      //   device state variables show 0 for off, and a single one has a value of 2 due to
      //   a logic processing fault, adding all three and seeing two of three would make a
      //   typical binary TMR voter output an on state.  In this system, this scenario is
      //   counted as two votes on and one vote off, still resulting in the correct on
      //   decision in the case of a single fault.

      // Device 0 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev0StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev0StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev0StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev0VoterOut = 1;
      } else {
        dev0VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 1 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev1StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev1StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev1StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev1VoterOut = 1;
      } else {
        dev1VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 2 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev2StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev2StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev2StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev2VoterOut = 1;
      } else {
        dev2VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 3 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev3StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev3StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev3StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev3VoterOut = 1;
      } else {
        dev3VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 4 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev4StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev4StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev4StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev4VoterOut = 1;
      } else {
        dev4VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 5 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev5StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev5StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev5StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev5VoterOut = 1;
      } else {
        dev5VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

      // Device 6 Voter
      voteCountOn  = 0;
      voteCountOff = 0;
      if( dev6StateA ) {  // If State Decision is Nonzero
        voteCountOn++;    // Add to On Final Decision Counter
      } else {            // Otherwise
        voteCountOff++;   // Add to Off Final Decision Counter
      }                   // Do this for each state variable A, B, C.
      if( dev6StateB ) {  
        voteCountOn++;
      } else {
        voteCountOff++;
      }
      if( dev6StateC ) {
        voteCountOn++;
      } else {
        voteCountOff++;
      } 
      if( voteCountOn > voteCountOff ) {  // Then conduct voting.  
        dev6VoterOut = 1;
      } else {
        dev6VoterOut = 0; // Note if there is ever an even match, which should only happen in the case of a particularly unlucky fault,
      }                   //   we default to the off state to protect the device in case we are indeed outside of the temperature range.

    };

    fprintf( outputFile, "%d %d %d %d %d %d %d\n", dev0VoterOut, dev1VoterOut, dev2VoterOut, 
             dev3VoterOut, dev4VoterOut, dev5VoterOut, dev6VoterOut );
    
    // Debug Voter Operation
    //printf( "%d%d%d-%d %d%d%d-%d %d%d%d-%d %d%d%d-%d %d%d%d-%d %d%d%d-%d %d%d%d-%d\n",
    //        dev0StateA, dev0StateB, dev0StateC, dev0VoterOut,
    //        dev1StateA, dev1StateB, dev1StateC, dev1VoterOut,
    //        dev2StateA, dev2StateB, dev2StateC, dev2VoterOut,
    //        dev3StateA, dev3StateB, dev3StateC, dev3VoterOut,
    //        dev4StateA, dev4StateB, dev4StateC, dev4VoterOut,
    //        dev5StateA, dev5StateB, dev5StateC, dev5VoterOut,
    //        dev6StateA, dev6StateB, dev6StateC, dev6VoterOut );

  };

//printf( "The output can be found as a matrix stored in: %s\n  1 == ON, 0 == OFF\n", argv[4] );
  return 0;
};



// END Shutdown.c  - ETK

