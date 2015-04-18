
APPNAME=temp-max-shutdown
SOURCEFILE=temp-max-shutdown.cpp

all: $(APPNAME)
$(APPNAME): $(SOURCEFILE)
	g++ -std=c++11 -o $(APPNAME) $(SOURCEFILE)

clean:
	rm $(APPNAME)
