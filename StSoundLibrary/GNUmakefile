.PHONY: all clean

library = libstsound.a
sources = Ym2149Ex.cpp digidrum.cpp Ymload.cpp LZH/LzhLib.cpp YmMusic.cpp YmUserInterface.cpp

CXXFLAGS=-DBITS32

all: $(library) 

clean:
	$(RM) $(library)
	$(RM) $(sources:.cpp=.dep)
	$(RM) $(sources:.cpp=.o)

%.dep: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(sources:.cpp=.dep)

$(library): $(sources:.cpp=.o)
	$(AR) -r $@ $?


