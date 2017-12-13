# ECE2195_DCA_Project
An organized collection of all ECE2195 DCA Project Files for Team 2.

# Contains

EditedCases                 - all temperature sensor data.
  
Graphs                      - all graphs produced in analysis of the neural networks.

InjectionLogic              - shutdown logic utilized in fault injection.
*threshold.txt             - final device temperature thresholds.
*Shutdown.c                - revisions to the original shutdown decision logic for fault injection.

InjectionLogicTMR           - TMR shutdown logic.
*ShutdownTMR.c             - adaptations to the fault-injectable shutdown logic program for TMR.
*threshold.txt             - final device temperature thresholds.

NeuralNet                   - neural network programming, scripts, training data, and associated documentation.
*TempDataGen v2.0.0.py     - updated temperature sensor data generator. 
*TempDataGen_triplex.py    - revised temperature sensor data for triple redundant neural network.
*line.py                   - single sensor neural network.
*tripleNeuralRedundancy.py - multiple sensor neural network.
*Various training text files and test output CSVs.

ShutdownLogic              - device shutdown decision logic.
*README                    - Evan Kain's original Shutdown.c logic readme.
*Shutdown.c                - shutdown logic program.
*Shutdown.h                - shutdown logic header file.
*threshold.txt             - original device temperature thresholds.
*Assorted text files for testing.

David Langerman - Evan Gretok - Evan Kain
