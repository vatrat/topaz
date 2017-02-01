#TOOL_TGT=arm-stevens-linux-gnueabi
#CC =  $(ARM_PATH)/$(TOOL_TGT)-gcc
#CP =  $(ARM_PATH)/$(TOOL_TGT)-g++
#AR =  $(ARM_PATH)/$(TOOL_TGT)-ar
#RANLIB =  $(ARM_PATH)/$(TOOL_TGT)-ranlib
CC =  gcc
CP =  g++
AR =  ar
RANLIB =  ranlib

IncDir  = .../Include
BIncDir = ../../Include
LibDir  = ..




C-Flags = -Wall -c -D_POSIX_C_SOURCE -I$(BIncDir) -I$(IncDir) -DLinux -DREDHAT40
L-Flags = -Wall -D_POSIX_C_SOURCE -lpthread -lz



All:	SigTabltTest OpenCloseTest 



SigTabltTest:	SigTabltTest.o SimpleDemo.o TipDemo.o Test20.o $(LibDir)/SigLib.a $(H-Files) 
	$(CP) -o SigTabltTest $(L-Flags) SigTabltTest.o SimpleDemo.o TipDemo.o Test20.o $(LibDir)/SigLib.a



OpenCloseTest:	OpenCloseTest.o $(LibDir)/SigLib.a $(H-Files) 
	$(CP) -o OpenCloseTest $(L-Flags) OpenCloseTest.o  $(LibDir)/SigLib.a


SigTabltTest.o: SigTabltTest.cpp $(H-Files)
	$(CP) $(C-Flags) SigTabltTest.cpp


TipDemo.o: TipDemo.cpp $(H-Files)
	$(CP) $(C-Flags) TipDemo.cpp

SimpleDemo.o: SimpleDemo.cpp $(H-Files)
	$(CP) $(C-Flags) SimpleDemo.cpp

Test20.o: Test20.cpp $(H-Files)
	$(CP) $(C-Flags) Test20.cpp

OpenCloseTest.o: OpenCloseTest.cpp $(H-Files)
	$(CP) $(C-Flags) OpenCloseTest.cpp


