CPPFLAGS = -g -O0 \
	-I/usr/local/include
LDFLAGS = \
	-L/usr/local/lib \
	-lSDL2

SRCS = \
	src/Render.cpp

flowest: $(SRCS)
	$(LINK.cpp) -o $@ $^

clean:
	rm -f flowest

run: flowest
	./flowest