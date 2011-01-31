      IQ math Sample C++ Program (V1.4c) for F2812 EzDSP
      ==================================================

Note:	To make this work on the F2812 EzDSP, the following 
	steps must be carried out:

	1) Use the attached f2812.gel file to configure the
	device.

	2) Make sure your boot mode is set to "boot to H0" 
	by selecting the correct jumper settings.  
	Refer to the attached schematics, page 4.

Description:
--------------------------------------------------------------
This sample program generates two sine waves called X and Y.
It will then calculate the normalized magnitude and phase of 
the two waveforms using the following formulas:

        Mag   = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2)
        Phase = (long) (atan2PU(X,Y) * 360)

The program will prompt the user to change the gain and 
frequency of the X and Y waveforms.

The default Q value used is 24. This gives a numerical range
of:

        IQ24 range = -128.0 to 127.999 999 94

To avoid saturation of the Mag value and other calculations,
the following max values are recommended for the user input:

        GainX max = 127.999 999 94/2 = 63.999 999 97
        FreqX max = 127.999 999 94
        GainY max = 127.999 999 94/2 = 63.999 999 97
        FreqY max = 127.999 999 94

Instructions:
--------------------------------------------------------------
1. Invoke CCS

2. Load workspace file "IQsampleCPP.wks"

   Note: In CCS V2.0 and earlier, the workspace file cannot
         resolve relative locations and hence will only work
         with the saved directory structure. For this sample,
         the directory structure is:

         C:\work\IQmath\IQmathLib\IQmathLib\Samples\F2812EzDSP_SampleCPP

         Alternatively, the user can load the project file:

             "IQsampleCPP.pjt"

         Loading the project file will require the user
         to manually configure the graph displays for the 
         following plots:

         Name                  Address          Size  Q value
         --------------------  ---------------  ----  -------
         X waveform            &Dlog.Xwaveform  256   24
         Y waveform            &Dlog.Xwaveform  256   24
         Normalized Magnitude  &Dlog.Mag        256   24
         Normalized Phase      &Dlog.Phase      256   24

         Note: You can also use the GlobalQ variable name
               for the Q value setting.

3. Load program file "IQsampleCPP.out"

4. Run. 

5. The program will prompt the user to select the X and Y
   waveform Gain and Freq ratios (default set at 1.0). The
   equations used are:

       X = GainX * sin(X + FreqX*Step)
       Y = GainY * sin(Y + FreqY*Step)

       Step = 0.314159265 = PI/10
   
6. The GLOBAL_Q value used by default is 24. You can change this 
   value and see the effects. The waveform shapes should remain 
   the same until effects like overflow conditions start to 
   impact the calculations. You will need to recompile the
   program when changing this value.

   Note: The Q value in the X, Y and Mag graph windows needs
         to be changed to match. The Phase display is in 
         integer format so it doesn't need changing. 
--------------------------------------------------------------
Have fun, no more.
