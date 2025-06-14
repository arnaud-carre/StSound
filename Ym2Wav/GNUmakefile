.PHONY: all clean

executable = Ym2Wav
sources = Ym2Wav.cpp

CXXFLAGS=-DBITS32 -I.

all: $(executable) 

clean:
	$(RM) $(executable)
	$(RM) $(sources:.cpp=.dep)
	$(RM) $(sources:.cpp=.o)

$(executable): $(sources:.cpp=.o) ../StSoundLibrary/libstsound.a
	$(CXX) $^ -o $@

../StSoundLibrary/libstsound.a: 
	$(MAKE) -C ../StSoundLibrary

%.dep: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(sources:.cpp=.dep)

