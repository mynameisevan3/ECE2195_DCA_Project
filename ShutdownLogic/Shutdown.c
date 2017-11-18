
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

  // Handle Incorrect Input Arguements
  if ( argc != 5 ) {
    printf( "ERROR: Input parameters incorrect (%d).\n", argc );
    printf( "  Usage:    ./Shutdown <tempFile> <thresholdFile> <maxChar> <outputFile>\n" );
    printf( "  Example:  ./Shutdown temp.txt threshold.txt 256 out.txt\n" );
    return -1;
  }

  // Temperature filepath is argv[1].
  // Threshold filepath is argv[2].
  int  maxChar = atoi( argv[3] );
  // Output filepath is argv[4].

  // Check Filenames and Open Files  
  printf( "Temperature filepath is: %s\n", argv[1] );
  printf( "Threshold filepath is:   %s\n", argv[2] );
  printf( "Output filepath is:      %s\n", argv[4] );
  FILE *tempFile      = fopen( argv[1], "r" );
  FILE *thresholdFile = fopen( argv[2], "r" );
  FILE *outputFile    = fopen( argv[4], "w" );

  char   buffer[maxChar];
  char   *upperElem;
  char   *lowerElem;
  int    linNum = 0;
  double temp   = 48.26;

  // Get Number of Devices from Threshold File
  fgets( buffer, maxChar, (FILE*)thresholdFile );
  int numDev = atoi( buffer );
  printf("The number of devices is: %d\n", numDev );

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
      printf( "Device Range:  %f, ", upperThreshold[linNum] );
      printf( "%f\n", lowerThreshold[linNum] );
      linNum++;	
    };
  };
  printf( "Number of lines read in is: %d\n", linNum );

  // Read Temperatures from File
  while ( !feof ( tempFile ) ) {
    fgets( buffer, maxChar, (FILE*)tempFile );
    if ( !feof( tempFile ) ) {
      upperElem = strtok( buffer, "," );
      lowerElem = strtok( NULL, "," );
      temp      = atof( lowerElem );
      shutdown( &temp, upperThreshold, lowerThreshold, &numDev, outputFile );
    };
  };
  
  printf( "The output can be found as a matrix stored in: %s\n", argv[4] );\
  printf( "  1 == ON, 0 == OFF\n" );
  return 0;
};


// Local Function Implementations

// shutdown - given current temperature and thresholds for each device, output device states.
void shutdown( double *temp, double highThreshold[], double lowThreshold[], int *numDev, FILE *outputFile ) {
  int state;
  printf( "Calculating States of %d Devices at Temperature %lf\n", *numDev, *temp );
  // Loop Through Devices
  for (int i = 0; i < *numDev; i++) {
    // Check Temperatures
    if ( ( *temp > highThreshold[i] ) || ( *temp < lowThreshold[i] ) ) {
      state = 0;  // Device Offline
    } else {
      state = 1;  // Device Online
    }
    fprintf( outputFile, "%d", state );
  };
  fprintf( outputFile, "\n" );
};



// END Shutdown.c  - ETK

