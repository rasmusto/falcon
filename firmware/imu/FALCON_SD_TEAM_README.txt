File: FALCON_SD_TEAM_README.txt

Code for the Piccolo (on IMU_CPU PCB) is being developed with Code Composer Studio 4.

The projects for the IMU_CPU board are located in imu_code/revx.y

The DSP2803x_headers folder contains headers defining registers for all peripherals on the 
device. The headers are in DSP2803x_headers->include, and the file 
"DSP2803x_GlobalVariableDefs.c" in DSP2803x_headers->source must be linked to the project as well
to use these headers.

The DPS2803x_common folder has a bunch of c files for using different peripherals. Mainly just
inits for all peripherals. This is a good starting point for using the device.

LINK TO ANY OF THE PROVIDED CODE IF YOU WANT TO USE IT AS IS IN A PROJECT. IF YOU PLAN TO CHANGE
THE PROVIDED CODE, MAKE A NEW FILE AND COPY OVER WHAT YOU WANT, DONT ALTER THE ORIGINAL 
(it is referenced by multiple projects).