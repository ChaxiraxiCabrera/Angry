#include "Q.h"
# 1 "<stdin>"
# 1 "<interno>"
# 1 "<línea-de-orden>"
# 1 "<stdin>"
# 1 "Qlib.h" 1
# 2 "<stdin>" 2

BEGIN
STAT(0)
 STR(0x11ffa,"%s \n");
 STR(0x11ff4,"%i \n");
 STR(0x11fee,"%c \n");
 STR(0x11fe8,"%f \n");
 STR(0x11fe2,"%c \n");
 STR(0x11fdc,"   \n");
CODE(0)
L 0:
 GT(1);
L 1:

 R7 = R7 - 4;

 R0 = 1;

 R1 = 2;
 R0 = R0 + R1;

 I(0x11fd8) = R0;

 R7 = R7 - 4;

 R0 = 1;

 R1 = 2;

 R2 = 2;
 R1 = R1 * R2;

 R0 = R0 + R1;

 I(0x11fd4) = R0;

 R7 = R7 - 4;

 R0 = 1;

 R1 = 2;

 R2 = 2;
 R1 = R1 * R2;


 R2 = 2;
 R1 = R1 / R2;

 R0 = R0 + R1;

 I(0x11fd0) = R0;

 R7 = R7 - 4;

 R0 = 1;

 R1 = 2;
 R0 = R0 + R1;


 R1 = 2;
 R0 = R0 * R1;

 I(0x11fcc) = R0;

 R7 = R7 - 4;
 I(R7) = R0;
 R7 = R7 - 4;
 I(R7) = R1;
 R7 = R7 - 4;
 I(R7) = R2;

 R0 = 2;
 R1 = 0x11ff4;
 R2 = I(0x11fd8);
 GT(-12);
L 2:

 R2 = I(R7);
 R7 = R7 + 4;
 R1 = I(R7);
 R7 = R7 + 4;
 R0 = I(R7);
 R7 = R7 + 4;
 R7 = R7 - 4;
 I(R7) = R0;
 R7 = R7 - 4;
 I(R7) = R1;
 R7 = R7 - 4;
 I(R7) = R2;

 R0 = 3;
 R1 = 0x11ff4;
 R2 = I(0x11fd4);
 GT(-12);
L 3:

 R2 = I(R7);
 R7 = R7 + 4;
 R1 = I(R7);
 R7 = R7 + 4;
 R0 = I(R7);
 R7 = R7 + 4;
 R7 = R7 - 4;
 I(R7) = R0;
 R7 = R7 - 4;
 I(R7) = R1;
 R7 = R7 - 4;
 I(R7) = R2;

 R0 = 4;
 R1 = 0x11ff4;
 R2 = I(0x11fd0);
 GT(-12);
L 4:

 R2 = I(R7);
 R7 = R7 + 4;
 R1 = I(R7);
 R7 = R7 + 4;
 R0 = I(R7);
 R7 = R7 + 4;
 R7 = R7 - 4;
 I(R7) = R0;
 R7 = R7 - 4;
 I(R7) = R1;
 R7 = R7 - 4;
 I(R7) = R2;

 R0 = 5;
 R1 = 0x11ff4;
 R2 = I(0x11fcc);
 GT(-12);
L 5:

 R2 = I(R7);
 R7 = R7 + 4;
 R1 = I(R7);
 R7 = R7 + 4;
 R0 = I(R7);
 R7 = R7 + 4;
 R0=0;
 GT(-2);
END
