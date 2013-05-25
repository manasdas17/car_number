EXE=DetectNumbers

$(EXE) : $(EXE).cpp main.cpp $(EXE).h
	g++ -o $@ $^ `pkg-config opencv --cflags --libs tesseract` -ggdb

.PHONY : clean
clean:
	rm -rf $(EXE) $(EXE).o *.swf
