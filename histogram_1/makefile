
CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

% : %.cpp
	#rm $@
	g++ -o $@ $< $(CFLAGS) $(LIBS) 
	