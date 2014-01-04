CPPFLAGS = -g -O0

SRCS = \
	src/main_belt.cpp

flowest: $(SRCS)
	$(LINK.cpp) -o $@ $^

clean:
	rm -f flowest

run: flowest
	./flowest