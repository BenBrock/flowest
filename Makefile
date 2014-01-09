CPPFLAGS = -g -O3 -std=c++11 \
	-Iolb/src

LDFLAGS = \
	-lSDL2

SRCS = \
	src/flowest.cpp \
	src/maths.cpp \
	src/graphics.cpp \
	src/physics.cpp

flowest: $(SRCS)
	$(LINK.cpp) -o $@ $^

clean:
	rm -f flowest

run: flowest
	./flowest
