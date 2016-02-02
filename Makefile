CFLAGS=$(shell pkg-config --cflags opencv libcurl)

LIBS=$(shell pkg-config --libs opencv libcurl)

% : %.cpp
	g++ $(CFLAGS) $(LIBS) -o $@ $<
