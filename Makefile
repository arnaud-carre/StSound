RM = rm -f
CFLAGS = -Wall

SAMPLES=YmSampleFiles
LIB_SRC=StSoundLibrary
OBJS = $(LIB_SRC)/digidrum.o $(LIB_SRC)/Ymload.o $(LIB_SRC)/Ym2149Ex.o $(LIB_SRC)/YmMusic.o $(LIB_SRC)/YmUserInterface.o

all: libym.a Ym2Wav

libym.a: $(OBJS)
	$(AR) cr libym.a $(OBJS)

$(LIB_SRC)/digidrum.o: $(LIB_SRC)/digidrum.cpp $(LIB_SRC)/YmTypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_SRC)/Ym2149Ex.o: $(LIB_SRC)/Ym2149Ex.cpp $(LIB_SRC)/Ym2149Ex.h $(LIB_SRC)/YmTypes.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_SRC)/Ymload.o: $(LIB_SRC)/Ymload.cpp $(LIB_SRC)/YmMusic.h $(LIB_SRC)/LZH/LZH.H
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_SRC)/YmMusic.o: $(LIB_SRC)/YmMusic.cpp $(LIB_SRC)/YmMusic.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_SRC)/YmUserInterface.o: $(LIB_SRC)/YmUserInterface.cpp $(LIB_SRC)/StSoundLibrary.h $(LIB_SRC)/YmMusic.h
	$(CC) $(CFLAGS) -c -o $@ $<

LzhLib.o: $(LIB_SRC)/LZH/LzhLib.cpp $(LIB_SRC)/LZH/LZH.H $(LIB_SRC)/YmTypes.h
	$(CC) -c $(LIB_SRC)/LZH/LzhLib.cpp

liblzh.a: LzhLib.o
	$(AR) cr $@ $<

Ym2Wav: Ym2Wav/Ym2Wav.cpp StSoundLibrary/StSoundLibrary.h liblzh.a libym.a
	$(CXX) -o Ym2Wav/Ym2Wav.o -c Ym2Wav/Ym2Wav.cpp
	$(CXX) -o Ym2Wav/Ym2Wav Ym2Wav/Ym2Wav.o -L. -lym -llzh

clean:
	$(RM) $(LIB_SRC)/*~ $(LIB_SRC)/*.o $(LIB_SRC)/*.a
	$(RM) Ym2Wav/*.o Ym2Wav/Ym2Wav

cleantest:
	$(RM) $(SAMPLES)/*.wav

%.wav: %.ym
	Ym2Wav/Ym2Wav "$<" "$@"

SAMPLE_FILES:=$(wildcard $(SAMPLES)/*.ym)
TESTS:=$(patsubst %.ym,%.wav,$(SAMPLE_FILES))

test: cleantest $(TESTS)