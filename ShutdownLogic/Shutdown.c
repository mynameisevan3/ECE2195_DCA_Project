
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
  if ( argc != 6 ) {
    printf( "ERROR: Input parameters incorrect (%d).\n", argc );
    printf( "  Usage:    ./Shutdown <tempFile> <thresholdFile> <maxChar> <outputFile>\n" );
    printf( "  Example:  ./Shutdown temp.txt threshold.txt 256 out.txt\n" );
    return -1;
  }

  // Temperature filepath is argv[1].
  // Threshold filepath is argv[2].
  int  maxChar = atoi( argv[3] );
  int redundancy = atoi (argv[5] );
  // Output filepath is argv[4].

  // Check Filenames and Open Files  
  printf( "Temperature filepath is: %s\n", argv[1] );
  printf( "Threshold filepath is:   %s\n", argv[2] );
  printf( "Output filepath is:      %s\n", argv[4] );
  //FILE *tempFile      = fopen( argv[1], "r" );
  FILE *thresholdFile = fopen( argv[2], "r" );
  FILE *outputFile    = fopen( argv[4], "w" );
  char *outputFilename = argv[4]; // used in time redundancy loop
  char   buffer[maxChar];
  char   *upperElem;
  char   *lowerElem;
  int    linNum = 0;
  int	 numTemps = -1;
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
  
  char *fileVector[redundancy];
  //Time redundancy loop
  for (int i=0; i < redundancy; i++) {
	  //FILE *outputFile    =
	  char strHolder[256];
	  char *strRoot=argv[4];
	  //printf("%s \n", argv[4]);
	  sprintf(strHolder, "Run-%d-", i);
	  //printf("%s \n",strcat(strHolder,strRoot ));
	  strcat(strHolder,strRoot);
	  FILE *runFile    = fopen( strHolder, "w" );
	  FILE *tempFile      = fopen( argv[1], "r" );
	  // Read Temperatures from File
	  while ( !feof ( tempFile ) ) {
	    numTemps++;
	    fgets( buffer, maxChar, (FILE*)tempFile );
	    if ( !feof( tempFile ) ) {
	      upperElem = strtok( buffer, "," );
	      lowerElem = strtok( NULL, "," );
	      temp      = atof( lowerElem );
		//printf("%s \n", strHolder);
		//printf("\n\n");
	      	shutdown( &temp, upperThreshold, lowerThreshold, &numDev, runFile );//outputFile );
	    };
	  };
	  //fileVector[i]=strHolder;
	  //printf("HHHHIIIIIIIIIIIII  %d \n", i);
	  //printf("%s \n", fileVector[i]);
	  fclose (tempFile);
  };
  numTemps=numTemps/redundancy;
printf("\n\n\n\n");
//printf("%s \n", fileVector[0]);
//printf("%s \n", fileVector[1]);
//printf("%s \n", fileVector[2]);
//////////////////////////////////////////////////////////////////////////////
			
	int decisionMat[numDev][numTemps][redundancy];
	char buff[maxChar];
	int k = 0;
	//create matrix with shutdown control for 
	for (int j=0; j<redundancy; j++) {
	char strHolder[256];
	char *strRoot=argv[4];
	char * inter;
	sprintf(strHolder, "Run-%d-", j);
	strcat(strHolder,strRoot);
	printf("%s\n", strHolder);
	FILE *tmpFile = fopen( strHolder, "r" );
		printf("J is %d\n",j);
		while ( !feof ( tmpFile ) ) {
		    numTemps++;
		    fgets( buff, numDev, (FILE*)tmpFile );
			inter=strtok(buff, "");//if (buff){
			printf("%s", inter);	
			//};
		   // if ( !feof( tmpFile ) ) {		     
			for (int l=0; l < numTemps; l++) {
				decisionMat[k][l][j]=atoi(&buff[k]);
				//printf("%d\n",decisionMat[k][l][j]);
		    	};
			k++;
			//printf("%d", k);
		   // };
		};
		
	};
//////////////////////////////////////////////////////////////////////////
  //voter( fileVector, &redundancy, &numDev, &numTemps, &maxChar, outputFile);	  
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

/*void voter(FILE *fileVector[], int *redundancy, int *numDev, int *numTemps, int * maxChar, FILE *outputFile) {
	int decisionMat[*numDev][*numTemps][*redundancy];

	char buff[*maxChar];
	int k = 0;
	//create matrix with shutdown control for 
	for (int j=0; j<*redundancy; j++) {
		FILE *tmpFile      = fopen( fileVector[j], "r" );
		printf("J is %d\n",j);
		while ( !feof ( tmpFile ) ) {
		    numTemps++;
		     printf("boop?");
		    fgets( buff, maxChar, (FILE*)tmpFile );
		    if ( !feof( tmpFile ) ) {	
	    
			for (int l=0; l < *numTemps; l++) {
				decisionMat[k][l][j]=atoi(buff[k]);
printf("boop");
				printf("%d", atoi(buff[k]));
		    	};
			k++;
		    };
		};
		
	};
	printf("numDev is %d\n", *numDev);
	printf("numTemps is %d\n", *numTemps);
	printf("%f\n", 3/2);	
};*/


// END Shutdown.c  - ETK

