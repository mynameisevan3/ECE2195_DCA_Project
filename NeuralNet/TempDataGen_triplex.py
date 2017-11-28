
#===================================#
# Temperature Sensor Data Generator #
#   ECE2195 Project - Team Two      #
#   v2.0.0                          #
#===================================#


# Imports
import math;
import random;


# Variable Initialization
SENSOR_TMIN = -50 # trained sensor minimum temp, if these are changed, retrain network
SENSOR_TMAX = 50 # trained sensor max temp, if these are changed, retrain network
SENSOR_VMAX = 3.3
filename = "file";
length   = 500;
pattern  = 1;
minTemp  = 0;
maxTemp  = 100;

tempSAF1  = 0;
tempSAF2  = 0;
tempSAF3  = 0;

SAFValue1 = 0;
SAFStart1 = 0;
SAFEnd1   = 0;

SAFValue2 = 0;
SAFStart2 = 0;
SAFEnd2   = 0;

SAFValue3 = 0;
SAFStart3 = 0;
SAFEnd3   = 0;

noise    = 0;
noiseMax = 0;
v_max    = 3.3;


# Evaluation Functions

def linFall( dif, size, n, maximum ):
  return ( ( -dif / size ) * n ) + maximum;

def linRise( dif, size, n, minimum ):
  return ( ( dif / size ) * n ) + minimum;

def fall( dif, size, n, minimum ):
  return ( dif / 2 ) * math.cos( ( math.pi / size ) * n ) + ( minimum + ( dif / 2 ) );

def rise( dif, size, n, minimum ):
  return ( dif / 2 ) * math.cos( ( math.pi / size ) * ( n + size ) ) + ( minimum + ( dif / 2 ) );

def dip( dif, size, n, minimum ):
  return ( dif / 2 ) * math.cos( ( ( 2 * math.pi ) / size ) * n ) + ( minimum + ( dif / 2 ) );

def hump( dif, size, n, minimum ):
  return ( dif / 2 ) * math.cos( ( ( 2 * math.pi ) / size ) * ( n + ( size / 2 ) ) ) + ( minimum + ( dif / 2 ) );


# Start Display
print( "\n\n===================================\n Temperature Sensor Data Generator \n===================================\n\n" );

# Gathering Input
filename      =        input( " Enter a Filename:              " );
length        = int(   input( " Number of Data Points:         " ) );
print( " Data Patterns\n  (1) Linear Fall\n  (2) Linear Rise\n  (3) Sine Fall\n  (4) Sine Rise\n  (5) Sine Dip\n  (6) Sine Hump" );
pattern       = int(   input( " Select a Data Pattern:         " ) );
minTemp       = float( input( " Minimum Temperature:           " ) );
maxTemp       = float( input( " Maximum Temperature:           " ) );


tempSAF1       =        input( " Insert Stuck-At Error? (Y/N):  TempSensor_1" );
if tempSAF1 == 'Y':
  SAFValue1    = float( input( "  Stuck-At Error Value:         " ) );
  SAFStart1    = int(   input( "  Stuck-At Error Start:         " ) );
  SAFEnd1      = int(   input( "  Stuck-At Error End:           " ) );

tempSAF2       =        input( " Insert Stuck-At Error? (Y/N):  TempSensor_2" );
if tempSAF2 == 'Y':
  SAFValue2    = float( input( "  Stuck-At Error Value:         " ) );
  SAFStart2    = int(   input( "  Stuck-At Error Start:         " ) );
  SAFEnd2      = int(   input( "  Stuck-At Error End:           " ) );

tempSAF3       =        input( " Insert Stuck-At Error? (Y/N):  TempSensor_3" );
if tempSAF3 == 'Y':
  SAFValue3    = float( input( "  Stuck-At Error Value:         " ) );
  SAFStart3    = int(   input( "  Stuck-At Error Start:         " ) );
  SAFEnd3      = int(   input( "  Stuck-At Error End:           " ) );

noise         =        input( " Insert Noise? (Y/N):           " );
if noise == 'Y':
  noiseMax    = float( input( "  Maximum Noise Variation:      " ) );

# Performing Auxiliary Calculations/Operations/Safeguards
random.seed( );
filename = filename + ".txt";
dataFile = open( filename, 'w' );
avgTemp  = ( maxTemp + minTemp ) / 2;
tempDif  = maxTemp - minTemp;
noiseMax = math.fabs( noiseMax );

if SAFEnd1 > ( length ):
  SAFEnd1 = length;

if SAFEnd2 > ( length ):
  SAFEnd2 = length;

if SAFEnd3 > ( length ):
  SAFEnd3 = length;

print( "\nGenerating Temperature Data File...\n\n" );

# Data Calculations
x    = range( length );
data1 = [];
data2 = [];
data3 = [];

if pattern == 1:
  for i in x:
    data1.append( linFall( tempDif, length, i, maxTemp ) );
    data2.append( linFall( tempDif, length, i, maxTemp ) );
    data3.append( linFall( tempDif, length, i, maxTemp ) );

elif pattern == 2:
  for i in x:
    data1.append( linRise( tempDif, length, i, minTemp ) );
    data2.append( linRise( tempDif, length, i, minTemp ) );
    data3.append( linRise( tempDif, length, i, minTemp ) );

elif pattern == 3:
  for i in x:
    data1.append( fall( tempDif, length, i, minTemp ) );
    data2.append( fall( tempDif, length, i, minTemp ) );
    data3.append( fall( tempDif, length, i, minTemp ) );

elif pattern == 4:
  for i in x:
    data1.append( rise( tempDif, length, i, minTemp ) );
    data2.append( rise( tempDif, length, i, minTemp ) );
    data3.append( rise( tempDif, length, i, minTemp ) );

elif pattern == 5:
  for i in x:
    data1.append( dip( tempDif, length, i, minTemp ) );
    data2.append( dip( tempDif, length, i, minTemp ) );
    data3.append( dip( tempDif, length, i, minTemp ) );

elif pattern == 6:
  for i in x:
    data1.append( hump( tempDif, length, i, minTemp ) );
    data2.append( hump( tempDif, length, i, minTemp ) );
    data3.append( hump( tempDif, length, i, minTemp ) );

else:
  print( "Apologies, but that pattern does not exist." );

# Adding Noise
if noise == 'Y':
  for i in x:
    data1[i] = data1[i] + random.uniform( -noiseMax, noiseMax );
    data2[i] = data2[i] + random.uniform( -noiseMax, noiseMax );
    data3[i] = data3[i] + random.uniform( -noiseMax, noiseMax );

# Adding Stuck-At Fault
if tempSAF1 == 'Y':
  for i in range( SAFStart1, SAFEnd1 ):
    data1[i] = SAFValue1;

# Adding Stuck-At Fault
if tempSAF2 == 'Y':
  for i in range( SAFStart2, SAFEnd2 ):
    data2[i] = SAFValue2;

# Adding Stuck-At Fault
if tempSAF3 == 'Y':
  for i in range( SAFStart3, SAFEnd3 ):
    data3[i] = SAFValue3;

# Print Calculations
for i in x:
    temp1 = data1[i]
    temp2 = data2[i]
    temp3 = data3[i]

    voltage1 = max([
                    min([
                        ((temp1 - (SENSOR_TMIN)) / (SENSOR_TMAX - SENSOR_TMIN)) * SENSOR_VMAX,
                        SENSOR_VMAX]),
                  0])

    voltage2 = max([
                  min([
                      ((temp2 - (SENSOR_TMIN)) / (SENSOR_TMAX - SENSOR_TMIN)) * SENSOR_VMAX,
                      SENSOR_VMAX]),
                0])

    voltage3 = max([
                    min([
                        ((temp3 - (SENSOR_TMIN)) / (SENSOR_TMAX - SENSOR_TMIN)) * SENSOR_VMAX,
                        SENSOR_VMAX]),
                  0])
    reportedTemp = (data1[i] + data2[i] + data3[i])
    divisor = 3
    # NOTE we take the average temperature reported by these voltages to
    # get a good idea of what the temp was supposed to be
    # this will throw off things that have stuck at errors,
    # so if we get those, don't bother reporting average

    if tempSAF1 == 'Y':
        reportedTemp -= data1[i]
        divisor -= 1
    if tempSAF2 == 'Y':
        reportedTemp -= data2[i]
        divisor -= 1
    if tempSAF3 == 'Y':
        reportedTemp -= data3[i]
        divisor -= 1

    if divisor == 0:
        print ("You dope, don't put everything as a stuck at fault")
        divisor = 0.0000000000001

    reportedTemp /= divisor

    dataFile.write( str( voltage1 ) + ", " +
                    str( voltage2 ) + ", " +
                    str( voltage3 ) + ", " +
                    str( reportedTemp ) + "\n" )

    print(  str( voltage1 ) + ", " +
            str( voltage2 ) + ", " +
            str( voltage3 ) + ", " +
            str(reportedTemp) + "\n" )

# Close File and Terminate
dataFile.close( );
print( "\n\n\n" );

# END TempDataGen.py - EWG SDG
