#############################################################################
##                              Read Me                                    ##
##                        IQmath C++ Library V1.4c                         ##
#############################################################################

This Read Me file contains the following sections:

1.  File Structure
2.  Function Summary
3.  Building A Project
   
Note: The user should read the "C" Read Me file before reading this.
   
=============================================================================
1.  File Structure:
=============================================================================
The C++ IQmath library consist of the following files:

   IQmathLib.h       ; IQmath C header file.
   IQmathCPP.h       ; IQmath C++ header file.
   IQmath.lib        ; IQmath library object file containing all functions 
                     ; & tables.
   IQmath.cmd        ; IQmath example linker command file.

The C++ version of the IQmath librray requires the C header file and is
built on top of the C functions and definitions.

See "Building A Project" section of this Read Me file on how to include
the above files in a user C++ program/project.

=============================================================================
2.  Function Summary
=============================================================================
Below is a summary of all the functions that are supported in this version
of the library. It includes an approximate estimate of the cycles and
code size for each function or operation:

------------------------+------------------------+---------------------------
     C Operation        |      C++ Operation     |       Description
------------------------+------------------------+---------------------------
Conversion Operations:
------------------------+------------------------+---------------------------
_iq, _iqN               |iq, iqN                 | IQ data types
------------------------+------------------------+---------------------------
_IQ(A), _IQN(A)         |IQ(A), IQN(A)           | Converts float to IQ
------------------------+------------------------+---------------------------
_IQtoF(A),              |IQtoF(A),               | Converts IQ to float 
_IQNtoF(A)              |IQNtoF(A)               |
------------------------+------------------------+---------------------------
_IQtoIQN(A)             |IQtoIQN(A)              | Converts IQ to IQN 
------------------------+------------------------+---------------------------
_IQNtoIQ(A)             |IQNtoIQ(A)              | Converts IQN to IQ
------------------------+------------------------+---------------------------
_IQtoQN(A)              |IQtoQN(A)               | Converts IQ to 16-bit Q
------------------------+------------------------+---------------------------
_QNtoIQ(A)              |QNtoIQ(A)               | Converts 16-bit Q to IQ
------------------------+------------------------+---------------------------
_atoIQ(A)               |atoIQ(A),               | Converts ascii to IQ
_atoIQN(A)              |atoIQN(A)               |   
------------------------+------------------------+---------------------------
_IQint(A),              |IQint(A),               | long = integer(IQ)
_IQNint(A)              |IQNint(A)               |
------------------------+------------------------+---------------------------
_IQfrac(A),             |IQfrac(A),              | IQ = fraction(IQ)
_IQNfrac(A)             |IQNfrac(A)              |
------------------------+------------------------+---------------------------
Basic Math Operations:
------------------------+------------------------+---------------------------
_IQmpy(A,B),            |A * B                   | IQ Multiply
_IQNmpy(A)              |                        |
------------------------+------------------------+---------------------------
_IQdiv(A,B),            |A / B                   | IQ divide
_IQNdiv(A,B)            |                        |
------------------------+------------------------+---------------------------
"+ ", "+=",             |"+ ", "+=",             | IQ add and subtract
"- ", "-="              |"- ", "-=",             |
------------------------+------------------------+---------------------------
"> ", "< ",             |"> ", "< ",             | IQ boolean operations 
"<=", ">=",             |"<=", ">=",             | 
"==", "!=",             |"==", "!=",             | 
"&&", "||"              |"&&", "||",             | 
------------------------+------------------------+---------------------------
"& ", "&=",             |"& ", "&=",             | IQ bitwise operations
"| ", "|=",             |"| ", "|=",             |
"^ ", "^="              |"^ ", "^=",             | 
------------------------+------------------------+---------------------------
Trigonometric Operations:
------------------------+------------------------+---------------------------
_IQsin(A),              |IQsin(A),               | IQ sine
_IQNsin(A)              |IQNsin(A)               |
------------------------+------------------------+---------------------------
_IQsinPU(A),            |IQsinPU(A),             | IQ Per Unit sine
_IQNsinPU(A)            |IQNsinPU(A)             |
------------------------+------------------------+---------------------------
_IQcos(A),              |IQcos(A),               | IQ cosine
_IQNcos(A)              |IQNcos(A)               |
------------------------+------------------------+---------------------------
_IQcosPU(A),            |IQcosPU(A),             | IQ Per Unit cosine
_IQNcosPU(A)            |IQNcosPU(A)             |
------------------------+------------------------+---------------------------
_IQatan2(A,B),          |IQatan2(A,B),           | IQ arctangent (2 operand)
_IQNatan2(A,B)          |IQNatan2(A,B)           |
------------------------+------------------------+---------------------------
_IQatan2PU(A,B),        |IQatan2PU(A,B),         | IQ Per Unit arctangent
_IQNatan2PU(A,B)        |IQNatan2PU(A,B)         | (2 operand)
------------------------+------------------------+---------------------------
_IQatan(A),             |IQatan(A),              | IQ arctangent
_IQNatan(A)             |IQNatan(A)              |
------------------------+------------------------+---------------------------
_IQsqrt(A),             |IQsqrt(A),              | IQ square root
_IQNsqrt(A)             |IQNsqrt(A)              |
------------------------+------------------------+---------------------------
_IQisqrt(A),            |IQisqrt(A),             | IQ inverse square root
_IQNisqrt(A)            |IQNisqrt(A)             |
------------------------+------------------------+---------------------------
_IQmag(A,B),            |IQmag(A,B),             | IQ magnitude
_IQNmag(A,B)            |IQNmag(A,B)             |
------------------------+------------------------+---------------------------
Miscellaneous Operations:
------------------------+------------------------+---------------------------
_IQrmpy(A,B),           |IQrmpy(A,B),            | IQ multiply with rounding
_IQNrmpy(A,B)           |IQNrmpy(A,B)            |
------------------------+------------------------+---------------------------
_IQrsmpy(A,B),          |IQrsmpy(A,B)            | IQ multiply with rounding   
_IQNrsmpy(A,B)          |IQNrsmpy(A,B)           | and saturation
------------------------+------------------------+---------------------------
_IQsat(A,Pos,Neg)       |IQsat(A,Pos,Neg)        | IQ saturate between Pos
                        |                        | and Neg values
------------------------+------------------------+---------------------------
_IQmpyIQX(A,IQA,B,IQB), |IQmpyIQX(A,IQA,B,IQB),  | Variable IQ multiply
_IQNmpyIQX(A,IQA,B,IQB) |IQNmpyIQX(A,IQA,B,IQB)  |
------------------------+------------------------+---------------------------
_IQmpyI32(A,B),         |IQmpyI32(A,B),          | IQ = IQ * long
_IQNmpyI32(A,B)         |IQNmpyI32(A,B)          |
------------------------+------------------------+---------------------------
_IQmpyI32int(A,B),      |IQmpyI32int(A,B),       | long = integer(IQ * long)
_IQNmpyI32int(A,B)      |IQNmpyI32int(A,B)       |
------------------------+------------------------+---------------------------
_IQmpyI32frac(A,B),     |IQmpyI32frac(A,B),      | IQ = fraction(IQ * long)
_IQNmpyI32frac(A,B)     |IQNmpyI32frac(A,B)      | 
------------------------+------------------------+---------------------------
_IQabs(A),              |IQabs(A),               | IQ = absolute(IQ)
_IQNabs(A)              |IQNabs(A)               | 
------------------------+------------------------+---------------------------

Note: For C,   N can be between 1 and 30.
      For C++, N can be between 15 and 30.
                        
=============================================================================
3.  Building A Project:
=============================================================================
To build a project the user needs to perform the following tasks:

3.1 Include the "IQmathCPP.h" and "IQmathLib.h" header in each source file
    as follows:

     extern "C" {
     #include  "IQmathLib.h"
     }
     #include  "IQmathCPP.h"
     
3.2 Include the "IQmath.lib" as part of the project. This file contains
    all of the "IQmath" functions in object format. The library is 
    constructed such that ONLY the functions that are used are included as 
    part of the project. This minimizes code size.
    
3.3 The example linker command file "IQmath.cmd" contains the section names
    for the IQmath object code. You can use this example file to configure
    the applications project command file. If the target is the F2810/12 
    devices, then the "IQmathTables" are located in Boot ROM and hence do not 
    need to be loaded. For the K1 device, they need to be loaded. Comment out 
    the appropriate section for the applicable device in the example linker 
    command file.
    
=============================================================================
No more.
=============================================================================
