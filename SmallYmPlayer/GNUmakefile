.PHONY: all clean

executable = SmallYmPlayer
sources = SmallYmPlayer.cpp SoundServerOpenAL.cpp

CXXFLAGS=-std=c++11

uname=$(shell uname)

ifeq ($(uname), Darwin)
LDFLAGS+=-framework OpenAL -pthread -lm
else
LDFLAGS=-L/usrlocal/lib -lopenal -lpthread -lm
CXXFLAGS=-I/usr/local/include -DBITS32 -I.
endif

all: $(executable)

$(executable): $(sources:.cpp=.o) ../StSoundLibrary/libstsound.a
	$(CXX) $^ -o $@ $(LDFLAGS)

../StSoundLibrary/libstsound.a:
	$(MAKE) -C ../StSoundLibrary

clean:
	$(RM) $(executable)
	$(RM) $(sources:.cpp=.dep)
	$(RM) $(sources:.cpp=.o)

%.dep: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(sources:.cpp=.dep)

