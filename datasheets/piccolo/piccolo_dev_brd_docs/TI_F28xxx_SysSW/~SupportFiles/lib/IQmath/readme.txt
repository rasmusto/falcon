#############################################################################
##                              Read Me First                              ##
##                       IQmath C & C++ Library V1.4d                      ##
##                               (30 March 2002)                           ##
#############################################################################
##                             ATTENTION                                   ##
##                             =========                                   ##
## V1.4a Of The IQmath library will only work with CCS release 2.01 and    ##
## codegen release 3.02 or above. This IQmath library version makes use of ##
## intrinsics that are only available from the specified tool versions.    ##
## Earlier versions of the tools cannot be used on this release.           ##
##                                                                         ##
## Additionally, V1.3 of the IQmath library cannot be used on the F2810/12 ##
## devices. Only V1.4 and later can. The IQmath tables found in the Boot   ##
## ROM of the F2810/12 devices only work with V1.4 library and later.      ##
##                                                                         ##
#############################################################################

This Read Me file summarizes the changes between different versions of the
IQmath library. The following additional documents also apply:

  ReadMeIQmathC.TXT   ; C Function Summary, Project Build Details, Examples
  ReadMeIQmathCPP.TXT ; C++ Function Summary, Project Build Details

#############################################################################
## Summary Of Changes From V1.4c to V1.4d                                  ##
## Date: 30 March 2003                                                     ##
#############################################################################
 
1. Updated the IQmathLib.h & IQmathCPP.h header file to conditionally include
   the header file. This fecilitates multiple inclution of header file in 
   same source file.

2. Added macro parameters inside the parentheses in number of places where 
   it matters

3. Bug fix in IQNfrac function

4. Improved the IQNmpyI32frac & IQNmpyI32int function

#############################################################################
## Summary Of Changes From V1.4b to V1.4c                                  ##
## Date: 20 Jun 2002                                                       ##
#############################################################################

1. Fixed bug with _IQint, _IQfrac, _IQmpyI32int, _IQmpyI32frac functions.
   They gave an incorrect result for negative values with zero fractional
   part (i.e. -5.0, -33.0, etc..).

2. Fixed problem with linker command files IQmath.cmd and linker command
   files in samples. There was an overlapping region and added the
   .econst section.

3. The above changes affected the following files:

           IQmath.lib
           IQmath.cmd
           All samples

#############################################################################
## Summary Of Changes From V1.4a to V1.4b                                  ##
## Date: 18 Jun 2002                                                       ##
#############################################################################

1. Fixed a bug with the "_IQNtoIQ(A)" and "_IQtoIQN(A)" operations. The shift
   values were incorrect. This change affected the following files:

		IQmathLib.h

#############################################################################
## Summary Of Changes From V1.4 to V1.4a                                   ##
## Date: 12 Jun 2002                                                       ##
#############################################################################

1. Renamed the "IQmathV14.lib" file to "IQmath.lib" file. This removes the
   version number and makes it easier for the user to upgrade.

2. Fixed a problem with the "_IQ(float)" operation which converts a floating
   point variable or constant to an IQ value. It was causing a compiler error
   when using variable references. This change affected the following
   file(s):

		IQmathLib.h

3. Modified the sample programs. One set is provided for the K1 (C & C++) 
   and one set is provided for the F2812 EzDSP (C & C++). ReadMe files are
   provided for each example.

#############################################################################
## Summary Of Changes From V1.3 to V1.4                                    ##
## Date: 17 May 2002                                                       ##
#############################################################################

1. The following new functions were added to V1.4 of the library (C & C++):

    _IQtoF(A)                      ; Convert IQ to float
    _IQint(A)                      ; long = integer(IQ)
    _IQfrac(B)                     ; IQ = fraction(IQ)
    _IQsat(A,Pos,Neg)              ; saturate IQ between Pos and Neg IQ
    _IQmpyIQX(A,IQA,B,IQB)         ; IQ = IQA * IQB
    _IQmpyI32(A,B)                 ; IQ = IQ * long
    _IQmpyI32int(A,B)              ; long = integer(IQ * long)
    _IQmpyI32frac(A,B)             ; IQ = fraction(IQ * long)
    _IQsinPU(A)                    ; Per Unit sine
    _IQcosPU(A)                    ; Per Unit cosine
    _IQatan2PU(A,B)                ; Per Unit arctangent (2 operand)
    _IQmag(A,B)                    ; Magnitude = sqrt(A^2 + B^2)
    _IQabs(A)                      ; IQ = absolute(IQ)
    
2. The following operators were added to C++ library:

    >, <, <=, >=, !=, ==, &&, ||   ; bollean operations
    &, &=, |, |=, ^, ^=            ; bitwise operations
    
3. The following functions were removed:

     _IQlong(A,B)                  ; Use IQmpyI32/int/frac operations instead
     _longIQ(A,B)                  ; Use IQmpyI32/int/frac operations instead
     
4. The IQMathTables was modified to remove the first word in the sin/cos
   table. V1.4 of the tables is included in the Boot ROM of the F2810/F2812 
   devices.
   
   Note: V1.3 of the library will not work on F2810/F2812 devices.
   
5. The accuracy of all functions was improved. The accuracy is approximately 
   28 to 30 bits (function dependant).  
   
6. Usefull predefined constants were added (they can be found at the top of 
   the "IQmathLib.h" file).
   
7. To assist with debug, the "IQmath.gel" file is supplied which enables
   the display and configuration of IQ variables in the watch windows.
   
   Note: Instructions are in the "IQmath.gel" file.

8. The C and C++ sample programs have been updated.

9. Improved documentation.
   
=============================================================================
No more.
=============================================================================
