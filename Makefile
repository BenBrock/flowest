CPPFLAGS = -g -O0 -std=c++11 \
	-Iolb/src \
	-Iolb/src/external \
	-Iolb/src/external/cvmlcpp \
	-Iolb/src/external/boost

LDFLAGS = \
	-lSDL2

ARCHIVES = \
	olb/build/generic/lib/libolb.a

SRCS = \
	src/flowest.cpp \
	src/graphics.cpp \
	src/physics.cpp

flowest: $(SRCS)
	$(LINK.cpp) -o $@ $^ $(ARCHIVES)

clean:
	rm -f flowest

run: flowest
	./flowest
