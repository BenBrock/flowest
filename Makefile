# Sorry
CXX = mpicxx

LDFLAGS = \
	-L/usr/local/lib \
	-lSDL2

CPPFLAGS = -g -O0 \
	-I/usr/local/include \
	-Ipalabos/src \
	-Ipalabos/externalLibraries

ARCHIVES = \
	palabos/lib/libplb_mpi.a

SRCS = \
	src/main_bechtel.cpp \
	src/Render.cpp \
	src/Surface.cpp

flowest: $(SRCS)
	$(LINK.cpp) -o $@ $^ $(ARCHIVES)

clean:
	rm -f flowest

run: flowest
	./flowestCXX = mpicxx

