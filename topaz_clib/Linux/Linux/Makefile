BSrcDir = ../Src
BIncDir = ../Include
PIncDir = ../Include/polarssl
SrcDir  = Src
IncDir  = Include
LibDir  = Lib/RedHat64


ObjList = \
		AALines.o\
		AATables.o\
		BitmapCharacter.o\
		bmpwrite.o\
		CharacterMap.o\
		Des.o\
		DesCrypt.o\
		Dessp.o\
		HotSpotList.o\
		LCDGraphicBitmap.o\
		LCDInterface.o\
		md5.o\
		PointBuffer.o\
		Safer.o\
		SigLib.o\
		SigFile.o\
		Signature.o\
		SignatureCrypto.o\
		SignatureDraw.o\
		SignatureDrawAntiAlias.o\
		SignatureImpExp.o\
		SignatureKeyPad.o\
		SigPoint.o\
		SigStroke.o\
		SigWindowType.o\
		TabletCore.o\
		TabletInterface.o\
		TabletParameters.o\
		TabletSampleList.o\
		TabletSerial.o\
		TiffImage.o\
		Utilities.o\
		aes.o\
		bignum.o\
		dhm.o\
		havege.o\
		timing.o\
		sha2.o\
		TabletCrypto.o\
		CaptureSigLinux.o\
		CircularBufferLinux.o\
		descriptors.o\
		error.o\
		HidIoIFLinux.o\
		linux.o\
		ProcessSerialDataLinux.o\
		SerialIoIFLinux.o\
		SocketIoIFLinux.o\
		NewSocketIoIFLinux.o\
		usb.o\
		UsbIoIFLinux.o

H-Files = \
		$(BIncDir)/AALines.h\
		$(BIncDir)/BitmapCharacter.h\
		$(BIncDir)/bmp.h\
		$(BIncDir)/CaptureSig.h\
		$(BIncDir)/CharacterMap.h\
		$(BIncDir)/CircularBuffer.h\
		$(BIncDir)/Des.h\
		$(BIncDir)/HidIoIF.h\
		$(BIncDir)/HotSpot.h\
		$(BIncDir)/HotSpotList.h\
		$(BIncDir)/LCDGraphicBitmap.h\
		$(BIncDir)/LCDInterface.h\
		$(BIncDir)/md5.h\
		$(BIncDir)/TabletPoint.h\
		$(BIncDir)/PointBuffer.h\
		$(BIncDir)/ProcessSerialData.h\
		$(BIncDir)/Safer.h\
		$(BIncDir)/SerialIoIF.h\
		$(BIncDir)/SigClasses.h\
		$(BIncDir)/SigFile.h\
		$(BIncDir)/SigLib.h\
		$(BIncDir)/Signature.h\
		$(BIncDir)/SigPoint.h\
		$(BIncDir)/SigSock.h\
		$(BIncDir)/SigStroke.h\
		$(BIncDir)/SigWindowType.h\
		$(BIncDir)/SocketIoIF.h\
		$(BIncDir)/TabletInterface.h\
		$(BIncDir)/TabletParameters.h\
		$(BIncDir)/TabletSampleList.h\
		$(BIncDir)/TiffImage.h\
		$(BIncDir)/UsbIoIF.h\
		$(BIncDir)/Utilities.h
	  

LH-Files = \
		$(IncDir)/CaptureSigLinux.h\
		$(IncDir)/CircularBufferLinux.h\
		$(IncDir)/error.h\
		$(IncDir)/HidIoIFLinux.h\
		$(IncDir)/linux.h\
		$(IncDir)/ProcessSerialDataLinux.h\
		$(IncDir)/SerialIoIFLinux.h\
		$(IncDir)/SocketIoIFLinux.h\
		$(IncDir)/NewSocketIoIFLinux.h\
		$(IncDir)/usb.h\
		$(IncDir)/usbi.h\
		$(IncDir)/UsbIoIFLinux.h


#C-Flags = -Wall -c -D_POSIX_C_SOURCE -D__USE_POSIX199309 -I$(BIncDir) -I$(IncDir) -DLinux -DNoUsleep
C-Flags = -Wall -c -D_POSIX_C_SOURCE -fpic -I$(BIncDir) -I$(IncDir) -I$(PIncDir) -DLinux -DREDHAT40
#C-Flags = -Wall -c -D_POSIX_C_SOURCE -I$(BIncDir) -I$(IncDir) -DLinux

#L-Flags = -Wall -D_POSIX_C_SOURCE -D__USE_POSIX199309 -lpthread 
L-Flags = -Wall -D_POSIX_C_SOURCE -lpthread 


#SigTabltTest:	SigTabltTest.cpp $(H-Files) SigLib.a
#	g++ -o SigTabltTest $(L-Flags) SigTabltTest.cpp SigLib.a


SigLib.a:	$(ObjList) libtiff/*.o zlib-1.2.3/*.o
#	rm tSigLib.a
	ar -r tSigLib.a $(ObjList) libtiff/*.o zlib-1.2.3/*.o
	cp tSigLib.a SigLib.a
	ranlib SigLib.a
	objdump -l -a SigLib.a
	rm -f $(LibDir)/SigLib.a
	cp SigLib.a $(LibDir)



AALines.o:	$(BSrcDir)/AALines.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/AALines.c


AATables.o:	$(BSrcDir)/AATables.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/AATables.c


BitmapCharacter.o:	$(BSrcDir)/BitmapCharacter.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/BitmapCharacter.cpp


bmpwrite.o:	$(BSrcDir)/bmpwrite.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/bmpwrite.cpp


CharacterMap.o:	$(BSrcDir)/CharacterMap.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/CharacterMap.cpp


Des.o:		$(BSrcDir)/Des.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/Des.c


DesCrypt.o:	$(BSrcDir)/DesCrypt.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/DesCrypt.cpp


Dessp.o:	$(BSrcDir)/Dessp.c $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/Dessp.c


HotSpotList.o: $(BSrcDir)/HotSpotList.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/HotSpotList.cpp


LCDGraphicBitmap.o:	$(BSrcDir)/LCDGraphicBitmap.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/LCDGraphicBitmap.cpp


LCDInterface.o:	$(BSrcDir)/LCDInterface.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/LCDInterface.cpp


md5.o:		$(BSrcDir)/md5.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/md5.c


PointBuffer.o:	$(BSrcDir)/PointBuffer.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/PointBuffer.cpp


Safer.o:	$(BSrcDir)/Safer.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/Safer.c


SigFile.o:	$(BSrcDir)/SigFile.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SigFile.cpp


SigLib.o:	$(BSrcDir)/SigLib.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SigLib.cpp


Signature.o:	$(BSrcDir)/Signature.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/Signature.cpp


SignatureCrypto.o:	$(BSrcDir)/SignatureCrypto.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SignatureCrypto.cpp


SignatureDraw.o:	$(BSrcDir)/SignatureDraw.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SignatureDraw.cpp


SignatureDrawAntiAlias.o:	$(BSrcDir)/SignatureDrawAntiAlias.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SignatureDrawAntiAlias.cpp


SignatureImpExp.o:	$(BSrcDir)/SignatureImpExp.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SignatureImpExp.cpp


SignatureKeyPad.o:	$(BSrcDir)/SignatureKeyPad.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SignatureKeyPad.cpp


SigPoint.o:	$(BSrcDir)/SigPoint.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SigPoint.cpp


SigStroke.o:	$(BSrcDir)/SigStroke.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SigStroke.cpp


SigWindowType.o:	$(BSrcDir)/SigWindowType.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/SigWindowType.cpp


TabletCore.o:	$(BSrcDir)/TabletCore.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletCore.cpp


TabletInterface.o:	$(BSrcDir)/TabletInterface.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletInterface.cpp


TabletParameters.o:	$(BSrcDir)/TabletParameters.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletParameters.cpp


TabletSampleList.o:	$(BSrcDir)/TabletSampleList.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletSampleList.cpp


TabletSerial.o:		$(BSrcDir)/TabletSerial.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletSerial.cpp


TiffImage.o:	$(BSrcDir)/TiffImage.cpp $(H-Files)
	g++ $(C-Flags) -DLinux $(BSrcDir)/TiffImage.cpp


Utilities.o:	$(BSrcDir)/Utilities.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/Utilities.cpp


aes.o:	$(BSrcDir)/aes.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/aes.c


bignum.o:	$(BSrcDir)/bignum.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/bignum.c


dhm.o:	$(BSrcDir)/dhm.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/dhm.c


havege.o:	$(BSrcDir)/havege.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/havege.c


timing.o:	$(BSrcDir)/timing.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/timing.c


sha2.o:	$(BSrcDir)/sha2.c $(H-Files)
	gcc $(C-Flags) $(BSrcDir)/sha2.c


TabletCrypto.o:	$(BSrcDir)/TabletCrypto.cpp $(H-Files)
	g++ $(C-Flags) $(BSrcDir)/TabletCrypto.cpp


CaptureSigLinux.o:	$(SrcDir)/CaptureSigLinux.cpp $(H-Files)
	g++ $(C-Flags) $(SrcDir)/CaptureSigLinux.cpp


CircularBufferLinux.o:	$(SrcDir)/CircularBufferLinux.cpp $(H-Files)
	g++ $(C-Flags) $(SrcDir)/CircularBufferLinux.cpp


HidIoIFLinux.o:	$(SrcDir)/HidIoIFLinux.cpp $(H-Files)
	g++ $(C-Flags) $(SrcDir)/HidIoIFLinux.cpp


ProcessSerialDataLinux.o:	$(SrcDir)/ProcessSerialDataLinux.cpp $(H-Files) $(LH-Files)
	g++ $(C-Flags) $(SrcDir)/ProcessSerialDataLinux.cpp


SerialIoIFLinux.o:	$(SrcDir)/SerialIoIFLinux.cpp $(H-Files) $(LH-Files)
	g++ $(C-Flags) $(SrcDir)//SerialIoIFLinux.cpp


SocketIoIFLinux.o:	$(SrcDir)/SocketIoIFLinux.cpp $(H-Files) $(LH-Files)
	g++ $(C-Flags) $(SrcDir)/SocketIoIFLinux.cpp


NewSocketIoIFLinux.o:	$(SrcDir)/NewSocketIoIFLinux.cpp $(H-Files) $(LH-Files)
	g++ $(C-Flags) $(SrcDir)/NewSocketIoIFLinux.cpp


UsbIoIFLinux.o:	$(SrcDir)/UsbIoIFLinux.cpp $(H-Files) $(LH-Files)
	g++ $(C-Flags) $(SrcDir)/UsbIoIFLinux.cpp


descriptors.o:	$(SrcDir)/descriptors.c $(H-Files) $(LH-Files)
	gcc $(C-Flags) $(SrcDir)/descriptors.c


error.o:	$(SrcDir)/error.c $(H-Files) $(LH-Files)
	gcc $(C-Flags) $(SrcDir)/error.c


linux.o:	$(SrcDir)/linux.c $(H-Files) $(LH-Files)
	gcc $(C-Flags) $(SrcDir)/linux.c


usb.o:		$(SrcDir)/usb.c $(H-Files) $(LH-Files)
	gcc $(C-Flags) $(SrcDir)/usb.c

 
