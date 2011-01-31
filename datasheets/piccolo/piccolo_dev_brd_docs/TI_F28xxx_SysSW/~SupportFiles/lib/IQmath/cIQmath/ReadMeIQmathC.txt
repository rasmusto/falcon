#############################################################################
##                              Read Me                                    ##
##                        IQmath C Library V1.4c                           ##
#############################################################################

This Read Me file contains the following sections:

1.  File Structure
2.  Function Summary
3.  Building A Project
4.  User GLOBAL_Q Configuration
5.  Numerical Range, Resolution & Function Accuracy
6.  Function Usage Examples:
    6.1  _IQ(A)
    6.2  _IQtoF(A)
    6.3  _IQtoIQN(A), _IQNtoIQ(A)
    6.4  _IQtoQN(A), _QNtoIQ(A)
    6.5  _atoIQ(A)
    6.6  _IQint(A), _IQfrac(B)
    6.7  _IQmpy(A,B), _IQrmpy(A,B), _IQrsmpy(A,B)
    6.8  _IQsat(A,Pos,Neg)
    6.9  _IQmpyIQX(A,IQA,B,IQB)
    6.10  _IQmpyI32(A,B), _IQmpyI32int(A,B), _IQmpyI32frac(A,B)
    6.11 _IQdiv(A,B)
    6.12 _IQsin(A), _IQsinPU(A), _IQcos(A), _IQcosPU(A)
    6.13 _IQatan2(A,B), _IQatan2PU(A,B), _IQatan(A)
    6.14 _IQsqrt(A), _IQisqrt(A)
    6.15 _IQmag(A,B)
    6.16 _IQabs(A)
7.  Floating-Point Operating Mode 
8.  Predefined Constants
   
=============================================================================
1.  File Structure:
=============================================================================
The C IQmath library consist of the following files:

   IQmathLib.h       ; IQmath header file.
   IQmath.lib        ; IQmath library object file containing all functions 
                     ; & tables.
   IQmath.cmd        ; IQmath example linker command file.

See "Building A Project" section of this Read Me file on how to include
the above files in a user program.

=============================================================================
2.  Function Summary
=============================================================================
Below is a summary of all the functions that are supported in this version
of the library. It includes an approximate estimate of the cycles and
code size for each function or operation:

------------------------+-----+-----+----------------------------------------
Syntax                  |Cycls|Bytes| Description 
[1]                     | [2] | [3] |
------------------------+-----+-----+----------------------------------------
Conversion operations:
------------------------+-----+-----+----------------------------------------
_iq                     |   - |   - | IQ data type using GLOBAL_Q setting
                        |     |     | Note: typecast as 32-bit "long".
------------------------+-----|-----|----------------------------------------
_iq30                   |   - |   - | IQ data type using Q = 30 setting
  to                    |     |     | 
_iq1                    |   - |   - | IQ data type using Q = 1  setting
                        |     |     | Note: All typecast as 32-bit "long".
------------------------|-----|-----|----------------------------------------
_IQ(A),                 |   2 |   4 | Converts the floating point value "A"
_IQN(A)                 |     |     | to the equivalent "IQ" value.
------------------------|-----|-----|----------------------------------------
_IQtoF(A),              |  23 |  6+ | Converts the "IQ" value "A" to the 
_IQNtoF(A)              |     | (40)| equivalent floating-point value.
------------------------|-----|-----|----------------------------------------
_IQtoIQN(A)             |   3 |   6 | Converts the "GLOBAL_Q" value "A" to 
                        |     |     | the specified "IQN" value.
------------------------|-----|-----|----------------------------------------
_IQNtoIQ(A)             |   3 |   6 | Converts the specfied "IQN" value "A"     
                        |     |     | to the "GLOBAL_Q" value. 
------------------------|-----|-----|----------------------------------------
_IQtoQN(A)              |   2 |   6 | Converts the "CLOBAL_Q" value "A" to 
                        |     |     | specified 16-bit "QN" value.
------------------------|-----|-----|----------------------------------------
_QNtoIQ(A)              |   2 |   6 | Converts the specified 16-bit "QN"  
                        |     |     | value "A" to the "GLOBAL_Q" "IQ" value.
------------------------|-----|-----|----------------------------------------
_atoIQ(A)               |>200 |  8+ | Converts the floating point ascii "A"      
_atoIQN(A)              |     |(286)| string to the equivalent "IQ" value.
------------------------|-----|-----|----------------------------------------
_IQint(A),              |  16 |  6+ | Return integer portion of IQ value:
_IQNint(A)              |     | (18)|    long = int(A)
------------------------|-----|-----|----------------------------------------
_IQfrac(A),             |  19 |  6+ | Return fractional portion of IQ value:
_IQNfrac(A)             |     | (24)|    IQ   = frac(A)
------------------------+-----+-----+----------------------------------------
Basic math operations:
------------------------+-----+-----+----------------------------------------
_IQmpy(A,B),            |   5 |  12 | IQ multiply: (A * B)   
_IQNmpy(A)              |     |     |    (A * B)
------------------------|-----|-----|----------------------------------------
_IQdiv(A,B),            |  73 | 10+ | IQ divide:
_IQNdiv(A,B)            |     |(142)|    (A / B)
------------------------|-----|-----|----------------------------------------
"+ ", "+=",             |   - |   - | IQ add and subtract
"- ", "-="              |     |     | 
------------------------|-----|-----|----------------------------------------
"> ", "< ",             |   - |   - | IQ boolean operations
"<=", ">=",             |     |     | 
"==", "!=",             |     |     | 
"&&", "||"              |     |     | 
------------------------|-----|-----|----------------------------------------
"& ", "&=",             |   - |   - | IQ bitwise operations
"| ", "|=",             |     |     | 
"^ ", "^="              |     |     | 
------------------------+-----+-----+----------------------------------------
Trigonometric Operations:
------------------------+-----+-----+----------------------------------------
_IQsin(A),              |  49 |  6+ | IQ sine:
_IQNsin(A)              |     |(100)|    IQ = sin(A)
------------------------|-----|-----|----------------------------------------
_IQsinPU(A),            |  43 |  6+ | IQ sine with per unit value "A":
_IQNsinPU(A)            |     | (82)|    IQ = sinPU(A), 0=0Deg, 1=360Deg
------------------------|-----|-----|----------------------------------------
_IQcos(A),              |  47 |  6+ | IQ cosine:
_IQNcos(A)              |     | (96)|    IQ = cos(A)
------------------------|-----|-----|----------------------------------------
_IQcosPU(A),            |  41 |  6+ | IQ cosine with per unit value "A":
_IQNcosPU(A)            |     | (78)|    IQ = cosPU(A),  0=0Deg, 1=360Deg
------------------------|-----|-----|----------------------------------------
_IQatan2(A,B),          | 118 | 10+ | IQ atan2:
_IQNatan2(A,B)          |     |(146)|    IQ = atan2(A,B)
------------------------|-----|-----|----------------------------------------
_IQatan2PU(A,B),        | 130 | 10+ | IQ atan2 with per unit return value:
_IQNatan2PU(A,B)        |     |(272)|    IQ = atan2PU(A,B), 0=0Deg, 1=360Deg
------------------------|-----|-----|----------------------------------------
_IQatan(A),             | 118 | 10+ | IQ atan:
_IQNatan(A)             |     |(146)|    IQ = atan(A)
------------------------|-----|-----|----------------------------------------
_IQsqrt(A),             |  70 |  6+ | IQ square root:
_IQNsqrt(A)             |     |(132)|    IQ = sqrt(A)
------------------------|-----|-----|----------------------------------------
_IQisqrt(A),            |  74 |  6+ | IQ inverse square root:
_IQNisqrt(A)            |     |(138)|    IQ = 1.0/sqrt(A)
------------------------|-----|-----|----------------------------------------
_IQmag(A,B),            |  96 | 10+ | IQ magnitude:
_IQNmag(A,B)            |     |(192)|    IQ = sqrt(A^2 + B^2)
------------------------+-----+-----+----------------------------------------
Miscellaneous Operations:
------------------------+-----+-----+----------------------------------------
_IQrmpy(A,B),           |  22 | 10+ | IQ multiply with rounding:
_IQNrmpy(A,B)           |     | (22)|    Round(A * B)
------------------------|-----|-----|----------------------------------------
_IQrsmpy(A,B),          |  30 | 10+ | IQ multiply with rounding & saturation:  
_IQNrsmpy(A,B)          |     | (38)|    Sat(Round(A * B) 
------------------------|-----|-----|----------------------------------------
_IQsat(A,Pos,Neg)       |   7 |  24 | IQ saturate value A between Pos and 
                        |     |     | Neg IQ values.   
------------------------|-----|-----|----------------------------------------
_IQmpyIQX(A,IQA,B,IQB), |   5 |  12 | Variable IQ multiply: 
_IQNmpyIQX(A,IQA,B,IQB) |     |     |    IQ = Aiq? * Biq?
------------------------|-----|-----|----------------------------------------
_IQmpyI32(A,B),         |   3 |   6 | IQ multiply Long, return IQ:
_IQNmpyI32(A,B)         |     |     |    IQ = Aiq * Blong
------------------------|-----|-----|----------------------------------------
_IQmpyI32int(A,B),      |  31 | 10+ | IQ multiply Long, return integer:
_IQNmpyI32int(A,B)      |     | (38)|    long = int(Aiq * Blong)
------------------------|-----|-----|----------------------------------------
_IQmpyI32frac(A,B),     |  37 | 10+ | IQ multiply Long, return fraction:
_IQNmpyI32frac(A,B)     |     | (52)|    IQ   = frac(Aiq * Blong)
------------------------|-----|-----|----------------------------------------
_IQabs(A),              |   2 |   4 | IQ absolute:
_IQNabs(A)              |     |     |    IQ = labs(IQ)
------------------------+-----+-----+----------------------------------------

Notes: [1] All instances of "_IQN..." in the above names refers to the user
           specifying the "IQ" value to use for the specific opeeration.
           For example:
           
             Y = _IQ(2.345)          ; Convert 2.345 to GLOBAL_Q value
             Y = _IQ26(2.345)        ; Convert 2.345 to IQ26 value
             Y = _IQmpy(X0,C0)       ; Y = X0*C0, all values use GLOBAL_Q
             Y = _IQ25mpy(X0,C0)     ; Y = X0*C0, all values use IQ25
             
       [2] The cycle times is approximate. It may vary based on the 
           location of the IQmathTables, the "Q" value used and the calling 
           overhead (which is compiler optimizer dependant). The following 
           assumptions are made for the data given:
             > Code executes from 0-wait SARAM
             > Stack is located in 0-wait SARAM
             > IQmathTables located in 1-wait ROM (as on F2810/F2812 devices)
             > Code, Stack & Tables are located in seperate memory blocks.
           The numbers given include the parameter passing and the call
           plus return overhead.  
       [3] The code size is approximate. It may vary based on the "Q" value
           used and the calling overhead (which is compiler optimizer
           dependant). If a value is given in brackets "+(..)", it is the 
           code size of the function itself and hence is only counted once
           if multiple instances of the same function are called.
           
=============================================================================
3.  Building A Project:
=============================================================================
To build a project the user needs to perform the following tasks:

3.1 Include the "IQmathLib.h" header in each source file:

     #include  "IQmathLib.h"
     
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
4.  User GLOBAL_Q Configuration:
=============================================================================
The user needs to configure the GLOBAL_Q value to use for the particular
application. This value can be set in one of two ways:

4.1 Modify the default value in the "IQmathLib.h" header file. Modifying 
    this value in the header file means that all files will use this value.
    
4.2 The header file setting can be overriden by setting the GLOBAL_Q value
    before the inclusion of the header file as shown below:

       #define   GLOBAL_Q    18     // Set GLOBAL_Q value for this file

       #include  <IQmathLib.h>
       
    This override only applies to the selected file.
    
It is recommended that the user select a GLOBAL_Q value for the complete
application and then if there are cases where a different value is required
(because of numerical range issues) then it is better to specify the
IQ value as part of the function or operation. For example;

_iq X, Y, Z;        // GLOBAL_Q range variables
_iq20 A, B, C;      // Variables requiring IQ = 20 range

       X = _IQmpy(Y,Z);         // uses GLOBAL_Q for all variables
       A = _IQ20mpy(B,C)        // uses IQ = 20 for all variables

=============================================================================
5.  Numerical Range, Resolution & Function Accuracy
=============================================================================
The numerical range and resolution for any given IQ value is as follows:
-----------------------------------------------------------------------------
Q value         Decimal Range            Numerical Resolution
------- -------------------------------- --------------------
IQ30        -2.0 to       1.999 999 999     0.000 000 001 
IQ29        -4.0 to       3.999 999 998     0.000 000 002 
IQ28        -8.0 to       7.999 999 996     0.000 000 004
IQ27       -16.0 to      15.999 999 993     0.000 000 007
IQ26       -32.0 to      31.999 999 985     0.000 000 015
IQ25       -64.0 to      63.999 999 970     0.000 000 030
IQ24      -128.0 to     127.999 999 940     0.000 000 060
IQ23      -256.0 to     255.999 999 881     0.000 000 119
IQ22      -512.0 to     511.999 999 762     0.000 000 238
IQ21     -1024.0 to    1023.999 999 523     0.000 000 477
IQ20     -2048.0 to    2047.999 999 046     0.000 000 954
IQ19     -4096.0 to    4095.999 998 093     0.000 001 907
IQ18     -8192.0 to    8191.999 996 185     0.000 003 815
IQ17    -16384.0 to   16383.999 992 371     0.000 007 629 
IQ16    -32768.0 to   32767.999 984 741     0.000 015 259
IQ15    -65536.0 to   65535.999 969 482     0.000 030 518
-----------------------------------------------------------------------------
Note: The IQmath library supports Q value range from 30 to 1. However,
      most users are likely to use Q values between 15 and 24.

The approximate numerical accuracy of various trigonometric functions is 
given below:

     Function       Accuracy
    -------------  ----------
    _IQsin          ~30bits
    _IQsinPU        ~30bits
    _IQcos          ~30bits
    _IQcosPU        ~30bits
    _IQatan2        ~28bits
    _IQatan2PU      ~28bits
    _IQatn          ~28bits
    _IQsqrt         ~28bits
    _IQisqrt        ~28bits
    _IQdiv          ~28bits
    _IQmag          ~28bits
    
All other functions or operations are accurate to approximately 31-bits.    

=============================================================================
6.  Function Usage Examples: 
=============================================================================
6.1  _IQ(A), _IQN(A)
-----------------------------------------------------------------------------
This operation is typically used to convert a floating-point constant or
variable to the equivalent IQ value. 

For example: We wish to implement the following equation:

     Y = M*1.26 - 2.345;
     
Using IQmath it would be written as follows:

     Y = _IQmpy(M, _IQ(1.26)) - _IQ(2.345);
     
If, we wish to specify what "Q" value to use, we can explicitly do that.
For example: Assume we wish to calculate the above equation using Q = 23:

     Y = _IQ23mpy(M, _IQ23(1.26)) - _IQ23(2.345);     

The _IQ(A) operation is also used to initialize global variables and tables.
For example:

_iq Array[4] = {_IQ(1.0), _IQ(2.5) _IQ(-0.2345), _IQ(0.0) }

Values of "0" can be entered as is.

For example: The above array could be initialized as follows also:

_iq Array[4] = {_IQ(1.0), _IQ(2.5) _IQ(-0.2345), 0 }

-----------------------------------------------------------------------------
6.2  _IQtoF(A), _IQNtoF(A)
-----------------------------------------------------------------------------
This operation is typically used in cases where the user may wish to
perform some operations in floating-point format or convert data back
to floating-point for display purposes.

For example: We wish to convert an array of IQ values to the equivalent
floating-point values:

_iq   DataIQ[N];
float DataF[N];

    for(i = 0; i < N, i++)
        DataF[i] = _IQtoF(DataIQ[i]);

-----------------------------------------------------------------------------
6.3  _IQtoIQN(A), _IQNtoIQ(A)
-----------------------------------------------------------------------------
These operations convert an IQ value, which has a resolution given by
GLOBAL_Q, to the specified IQ value and vice versa. Such operations may be
used in cases where a calculation may temporarely overflow the IQ value
resolution and hence require a different IQ value to be used for the
intermediate operations.

For example: We wish to calculate the following euqation:

     Z = sqrt(X^2 + Y^2)
     
The values Z, X, Y are given as GLOBAL_Q = 26, but the euqation itself
may generate an overflow. To guard against this, the intermediate
calculations will be performed using Q = 23 and the value converted
back at the end as shown below:

_iq Z, Y, X;       // GLOBAL_Q = 26 
_iq23 temp; 

    temp = _IQ23sqrt(   _IQ23mpy(_IQtoIQ23(X), _IQtoIQ23(X))
                      + _IQ23mpy(_IQtoIQ23(Y), _IQtoIQ23(Y)) );
    Y = _IQ23toIQ(temp);

-----------------------------------------------------------------------------
6.4  _IQtoQN(A), _QNtoIQ(A)
-----------------------------------------------------------------------------
These operations convert and IQ value, which has a resolution given by
GLOBAL_Q, to the specified 16-bit Q value and vice versa. Such operations
may be used in cases where the input and output data is 16-bits, but the
intermediate operations are operated using IQ data types.

For example: We wish to calculate the following sum of product:

      Y = X0*C0 + X1*C1 + X2*C2     // All values are 16-bit Q15
      
We can convert the Q15 values to IQ, perform the intermediate sums using
IQ and then store the result back as Q15:

short X0, X1, X2;  // Q15
short C0, C1, C2;  // Q15
short Y;           // Q15
_iq sum            // IQ (GLOBAL_Q)

      sum  = _IQmpy(_Q15toIQ(X0), _Q15toIQ(C0));
      sum += _IQmpy(_Q15toIQ(X1), _Q15toIQ(C1));
      sum += _IQmpy(_Q15toIQ(X2), _Q15toIQ(C2));
      Y    = _IQtoQ15(sum);

-----------------------------------------------------------------------------
6.5  _atoIQ(A), _atoIQN(A)
-----------------------------------------------------------------------------
These operations convert a floating-point ascii string to the equivalent
IQ value. This is usefull for programs that need to process user input
or ascii strings.

For example: The following code prompts the user to enter the value X:

char buffer[N];
_iq X;

      printf("Enter value X = ");
      gets(buffer);
      X = _atoIQ(buffer);            // IQ value (GLOBAL_Q)
     
-----------------------------------------------------------------------------
6.6  _IQint(A), _IQNint(A), _IQfrac(A), _IQNfrac(A)
-----------------------------------------------------------------------------
These operations convert an IQ value to the integer and fractional 
components. The integer portion gets converted to a "long" and the 
fractional component remains as an IQ value. 

For example:

_iq  Y0      =  2.3456;
_iq  Y1      = -2.3456
long Y0int,  Y1int;
_iq  Y0frac, Y1frac;

      Y0int  = _IQint(Y0);       // Y0int  =  2
      Y1int  = _IQint(Y1);       // Y1int  = -2
      Y0frac = _IQfrac(Y0);      // Y0frac =  0.3456
      Y1frac = _IQfrac(Y1);      // Y1frac = -0.3456
     
To rebuild the IQ value from the integer and fractional portions, the
following code example shows how to do this:

_iq  Y;
long Yint;
_iq  Yfrac;

      Y = _IQmpyI32(_IQ(1.0), Yint) + Yfrac;     

-----------------------------------------------------------------------------
6.7  _IQmpy(A,B),   _IQNmpy(A,B), 
     _IQrmpy(A,B),  _IQNrmpy(A,B), 
     _IQrsmpy(A,B), _IQNrsmpy(A,B)
-----------------------------------------------------------------------------
These operations multiply an IQ number with another IQ number and return
an IQ value. Ther are three variants and are explained below:

_IQmpy(A,B)     Multiplies A*B but performs no saturation and rounding.
                In most cases, the multiplication of two IQ variables
                will not exceed the range of the IQ variable. This operation
                takes the least amount of cycles and code size and should 
                be used most often. For example: Calculate "Y = M*X + B" with
                no rounding or saturation:
                               
                _iq Y, M, X, B;
                
                      Y = _IQmpy(M,X) + B;
                                                
_IQrmpy(A,B)    In cases where absolute accuracy is necessary, this operation
                performs the IQ multiply and rounds the result before storing
                back as an IQ number. This gives an additional 1/2 LSBit of
                accuracy. In the majority of cases, this is probably not
                necessary. For example: Calculate "Y = M*X + B" with 
                rounding but no saturation:

                _iq Y, M, X, B;
                
                      Y = _IQrmpy(M,X) + B;
                
_IQrsmpy(A,B)   In cases where the calculation may possibly exceed the range
                of the IQ variable, then this operation will round and then
                saturate the result to the maximum IQ value range before
                storing. For example: assume we have GLOBAL_Q = 26. This
                means that the range of the numbers is approx +/-32.0. If
                two IQ variables are multiplied together, then the maximum
                range of the result is 32*32 = +/- 1024. This operation would
                make sure that the result is saturated to +/- 32 in cases
                where the result exceeds this. For example: Calculate 
                "Y = M*X + B" with rounding and saturation:

                _iq Y, M, X, B;
                
                      Y = _IQrsmpy(M,X) + B;

-----------------------------------------------------------------------------
6.8  _IQsat(A,Pos,Neg)
-----------------------------------------------------------------------------
This operation saturates an IQ value to the given Positive and Negative
limits. This operation is usefull in areas where there is potential
for overflow in a calculation.

For example: We wish to calculate the linear equation "Y = M*X + B". All
variablesz are GLOBAL_Q = 26. However, there is a possibility that the
variable ranges may cause overflow, so we must perform the calculation
and saturate the result. To do this, we perform the intermediate operations
using IQ = 20 and then saturate before converting the result back to
the appropriate GLOBAL_Q value:
                
_iq Y, M, X, B;   // GLOBAL_Q = 26 (+/- 32 range)
_iq20 temp;       // IQ = 20       (+/- 2048 range)
         
     temp = _IQ20mpy(_IQtoIQ20(M), _IQtoIQ20(X)) + _IQtoIQ20(B);
     temp = _IQsat(temp, _IQtoIQ20(MAX_IQ_POS), _IQtoIQ20(MAX_IQ_NEG));
     Y    = _IQ20toIQ(temp);
                                
-----------------------------------------------------------------------------
6.9  _IQmpyIQX(A,IQA,B,IQB), _IQNmpyIQX(A,IQA,B,IQB)
-----------------------------------------------------------------------------
This operation is usefull when we wish to multiply values of different
IQ. For example: We wish to calculate the following equation:

    Y = X0*C0 + X1*C1 + X2*C2
    
Where X0, X1, X2 values are IQ = 20 and C0, C1, C2 values are 16-bit Q = 15,
and the result is to be stored as a GLOBAL_Q value:

_iq20  X0, X1, X2;     // All values IQ = 20
short  C0, C1, C2;     // All values 16-bit Q15
_iq    Y;              // Result GLOBAL_Q = 26

     Y  = _IQmpyIQX(X0, IQ20, C0, Q15)
     Y += _IQmpyIQX(X1, IQ20, C1, Q15)
     Y += _IQmpyIQX(X2, IQ20, C2, Q15)

-----------------------------------------------------------------------------
6.10 _IQmpyI32(A,B), _IQmpyI32int(A,B), _IQmpyI32frac(A,B)
-----------------------------------------------------------------------------
These operations multiply an IQ value with a 32-bit integer (long). We can
also keep the integer or fractional portion of the result. Such operations
are usefull when trying to scale IQ values, specifically when the value
needs to be converted to an integer quantity that must be exported to
a physical device, like a DAC.

For example: Convert an IQ value in the range +/- 1.0 to a DAC value
with the range 0 (-1) to 1023 (+1):

_iq Output;
short OutputDAC;

     temp = _IQmpyI32int(Output, 512);   // value converted to +/- 512
     temp += 512;                        // value scaled to 0 to 1023
     if( temp > 1023 )                   // saturate within range of DAC
         temp = 1023;
     if( temp < 0    )
         temp = 0;
     OutputDAC = temp;                   // output to DAC value

Note: The integer operation performs the multiply and calculates the integer
      portion from the resulting 64-bit calculation. Hence it avoids any
      overflow conditions.

-----------------------------------------------------------------------------
6.11 _IQdiv(A,B), _IQNdiv(A,B)
-----------------------------------------------------------------------------
This operation performs a divide on two IQ values. This is not modulus
division, but normal division. For example:

         2.3456/-1.2345 = -1.9
         
The division operation will saturate in cases where overflow occurs
because the denominator is much smaller then the numerator that the range
of the IQ number is exceeded.

For example: We wish to calculate the length of the Hypotenuse of a
right angle triangle given the adjacent length and the angle:

_iq Hyp;       // IQ hypotenuse length
_iq Angle;     // IQ angle in radians 
_iq Adj;       // IQ adjacent length

      Hyp = _IQdiv(Adj, _IQsin(Angle));  // calculate: Hyp = Adj/sin(Angle)

-----------------------------------------------------------------------------
6.12 _IQsin(A), _IQsinPU(A), _IQcos(A), _IQcosPU(A)
-----------------------------------------------------------------------------
These operations calculate the sin or cosine of the specified IQ angle.
The angle is specified in radians or Per Unit (PU) value. The per unit
calculation is common in motor control where the unit value refers to
a full 360 degree rotation:

                (0 = 0Deg) <= Angle < (1.0 = 360Deg)

        _IQsinPU(A) ===> is equivalent to ==> _IQsin(A*2*PI)
        _IQcosPU(A) ===> is equivalent to ==> _IQcos(A*2*PI)

For example: Generate a sine waveform X of selectable frequency:

_iq  StepAngle;     // this value is used to control the frequency
_iq  Angle;         // this is the current angle
_iq  WaveformX;     // this is the output waveform value

      Angle = Angle + StepAngle;
      if( Angle >= _IQ(2*PI) )
          Angle = 0;
      WaveformX = _IQsin(Angle);
      
Using the Per Unit function, the code would be written as follows:

_iq  StepAnglePU;   // this value is used to control the frequency
_iq  AnglePU;       // this is the current angle
_iq  WaveformX;     // this is the output waveform value

      AnglePU = AnglePU + StepAnglePU;
      if( AnglePU >= _IQ(1.0) )
          AnglePU = 0;
      WaveformX = _IQsinPU(AnglePU);

-----------------------------------------------------------------------------
6.13 _IQatan2(A,B), _IQatan2PU(A,B), _IQatan(A)
-----------------------------------------------------------------------------
The "_IQatan2" and "_IQatan2PU" operations return the angle in radians or 
Per Unit value for two orthogonal input vectors A and B as follows:

                    PU=0.25
                     PI/2                   if( A >= 0 )
                      +A                       0 <= Angle Radians <= PI 
                     /|\                       0 <= Angle PU      <= 0.5
                      |                     if( A <  0 )
                      |                      -PI <  Angle Radians <  0
                      |           PU = 0.0   0.5 <  Angle PU      <  1.0
        PI -B<--------+--------->B 0
       PU=0.5         |           PU = 1.0
                      |
                      |
                     \|/
                      -A
                    -PI/2  
                    PU=0.75
                    
The "_IQatan" function only calculates the angle between PI/2 and -PI/2
and is a less usefull version of the atan operation:

      _IQatan(A) ==> is equivalent to ==> _IQatan2(A, _IQ(1.0))
      
These operations are usefull for calculating the phase of two vectors.

For example: Calculate the phase of two vectors X and Y:

_iq X, Y;
_iq Phase;

    Phase = _IQatan2(Y,X);
    
Or, in per unit angle:

_iq X, Y;
_iq PhasePU;

    PhasePU = _IQatan2PU(Y,X);

-----------------------------------------------------------------------------
6.14 _IQsqrt(A), _IQisqrt(A)
-----------------------------------------------------------------------------
These operations calculate the square root or inverse square root of the
given IQ value. Such operations are usefull for calculating the magnitude
of two orthogonal vectors:

For example: Calculate the magnitude of orthogonal vectors X and Y:

                  Mag = sqrt(X^2 + Y^2)
                  
The code would be written as follows:

_iq X, Y;
_iq Mag;

    Mag = _IQsqrt(_IQmpy(X,X) + _IQmpy(Y,Y));
    
The "_IQisqrt" function simply computes the inverse of the square root
"1.0/sqrt(A)" and is a more accurate operation then the following:

     _IQisqrt(A) ==> is better then ==> _IQdiv(_IQ(1.0), _IQsqrt(A))

-----------------------------------------------------------------------------
6.15 _IQmag(A,B)
-----------------------------------------------------------------------------
This operation calculates the magnitude of two orthogonal vectors as follows:

                  Mag = sqrt(A^2 + B^2)
                  
This operation achieves better accuracy and avoids overflow problems that
may be encountered by using the "_IQsqrt" operation as shown above.

-----------------------------------------------------------------------------
6.16 _IQabs(A)
-----------------------------------------------------------------------------
This operation calculates the absolute value of an IQ number:

For example: Calculate the abs sum X0, X1, X2

_iq X0, X1, X2;
_iq Sum; 

    Sum = _IQabs(X0) + _IQabs(X1) + _IQabs(X2);

=============================================================================
7.  Floating-Point Operating Mode: 
=============================================================================
IQmath enables code written using the library functions to be compiled using 
equivalent floating-point operations. To enable this mode, the user needs
to select the "MATH_TYPE" as either "IQ_MATH" or "FLOAT_MATH" in the 
"IQmathLib.h" header file:

#define   FLOAT_MATH     1
#define   IQ_MATH        0

#ifndef   MATH_TYPE
#define   MATH_TYPE      IQ_MATH
#endif

For "IQmath", the "_iq" data type is cast as follows:

typedef   long    _iq;      // IQ number is a 32-bit integer

For "IQmath" in floating point mode, the "_iq" data type is cast as follows:

typedef   float   _iq;      // IQ number is 32-bit IEEE 754 floating-point

The user should not need to change any of the source code as each "IQmath"
operation is replaced with the equivalent floating-point operation as
shown in the table below:

-----------------------+-----------------------------------------------------
IQ Operation           | Equivalent Floating-Point Operation
-----------------------|-----------------------------------------------------
_IQ(A)                 | A
-----------------------|-----------------------------------------------------
_IQtoF(A)              | A
-----------------------|-----------------------------------------------------
_IQtoIQN(A)            | A
_IQNtoIQ(A)            | A
-----------------------|-----------------------------------------------------
_IQtoQ15(A)            | (short) (A##L * 32768.0L)
_IQtoQ14(A)            | (short) (A##L * 16384.0L)
_IQtoQ13(A)            | (short) (A##L * 8192.0L)
_IQtoQ12(A)            | (short) (A##L * 4096.0L)
_IQtoQ11(A)            | (short) (A##L * 2048.0L)
_IQtoQ10(A)            | (short) (A##L * 1024.0L)
_IQtoQ9(A)             | (short) (A##L * 512.0L)
_IQtoQ8(A)             | (short) (A##L * 256.0L)
_IQtoQ7(A)             | (short) (A##L * 128.0L)
_IQtoQ6(A)             | (short) (A##L * 64.0L)
_IQtoQ5(A)             | (short) (A##L * 32.0L)
_IQtoQ4(A)             | (short) (A##L * 16.0L)
_IQtoQ3(A)             | (short) (A##L * 8.0L)
_IQtoQ2(A)             | (short) (A##L * 4.0L)
_IQtoQ1(A)             | (short) (A##L * 2.0L)
-----------------------|-----------------------------------------------------
_Q15toIQ(A)            | (((float) A) * 0.000030518)
_Q14toIQ(A)            | (((float) A) * 0.000061035)
_Q13toIQ(A)            | (((float) A) * 0.000122070)
_Q12toIQ(A)            | (((float) A) * 0.000244141)
_Q11toIQ(A)            | (((float) A) * 0.000488281)
_Q10toIQ(A)            | (((float) A) * 0.000976563)
_Q9toIQ(A)             | (((float) A) * 0.001953125)
_Q8toIQ(A)             | (((float) A) * 0.003906250)
_Q7toIQ(A)             | (((float) A) * 0.007812500)
_Q6toIQ(A)             | (((float) A) * 0.015625000)
_Q5toIQ(A)             | (((float) A) * 0.031250000)
_Q4toIQ(A)             | (((float) A) * 0.062500000)
_Q3toIQ(A)             | (((float) A) * 0.125000000)
_Q2toIQ(A)             | (((float) A) * 0.250000000)
_Q1toIQ(A)             | (((float) A) * 0.500000000)
-----------------------|-----------------------------------------------------
_IQint(A)              | ((long) A)
_IQfrac(A)             | (A - (float)((long) A))
-----------------------|-----------------------------------------------------
_atoIQ(A)              | atof(A)
-----------------------|-----------------------------------------------------
_IQmpy(A,B)            | (A * B)
_IQrmpy(A,B)           | (A * B)
_IQrsmpy(A,B)          | (A * B)
-----------------------|-----------------------------------------------------
_IQsat(A, Pos, Neg)    | _satf(A, Pos, Neg)
-----------------------|-----------------------------------------------------
_IQmpyIQX(A,IQA,B,IQB) | (A*B)    
-----------------------|-----------------------------------------------------
_IQmpyI32(A,B)         | (A * (float) B)    
_IQmpyI32int(A,B)      | ((long) (A * (float) B))
_IQmpyI32frac(A,B)     | (A - (float)((long) (A * (float) B)))
-----------------------|-----------------------------------------------------
_IQdiv(A,B)            | (A / B)
-----------------------|-----------------------------------------------------
_IQsin(A)              | sin(A)
_IQsinPU(A)            | sin(A*2*PI)
-----------------------|-----------------------------------------------------
_IQcos(A)              | cos(A)
_IQcosPU(A)            | cos(A*2*PI)
-----------------------|-----------------------------------------------------
_IQatan(A)             | atan(A)
_IQatan2(A,B)          | atan2(A,B)
_IQatan2PU(A,B)        | ((atan2(A,B)/2*PI) >= 0.0 ? 
                       | (atan2(A,B)/2*PI):1.0 + (atan2(A,B)/2*PI))
-----------------------|-----------------------------------------------------
_IQsqrt(A)             | sqrt(A)
_IQisqrt(A)            | (1.0/sqrt(A))
-----------------------|-----------------------------------------------------
_IQmag(A,B)            | sqrt(A*A + B*B)
-----------------------|-----------------------------------------------------
_IQabs(A)              | abs(A)
-----------------------+-----------------------------------------------------

=============================================================================
8.  Predefined Constants:
=============================================================================
The following are usefull constants available to the user:

#define   QG          GLOBAL_Q
#define   Q30         30
#define   Q29         29
#define   Q28         28
#define   Q27         27
#define   Q26         26
#define   Q25         25
#define   Q24         24
#define   Q23         23
#define   Q22         22
#define   Q21         21
#define   Q20         20
#define   Q19         19
#define   Q18         18
#define   Q17         17
#define   Q16         16
#define   Q15         15
#define   Q14         14
#define   Q13         13
#define   Q12         12
#define   Q11         11
#define   Q10         10
#define   Q9          9
#define   Q8          8
#define   Q7          7
#define   Q6          6
#define   Q5          5
#define   Q4          4
#define   Q3          3
#define   Q2          2
#define   Q1          1

#define   MAX_IQ_POS  2147483647
#define   MAX_IQ_NEG  -2147483648
#define   MIN_IQ_POS  1
#define   MIN_IQ_NEG  -1

=============================================================================
No more.
=============================================================================
