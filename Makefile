CFLAGS=$(shell pkg-config --cflags opencv)
LIBS=$(shell pkg-config --libs opencv)

% : %.cpp
	g++ $(CFLAGS) $(LIBS) -o $@ $<
