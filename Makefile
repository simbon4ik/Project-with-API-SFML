all: *.cpp
	g++ *.cpp -o rectangle -lsfml-graphics -lsfml-window -lsfml-system 

clean:  
	rm -f *.o
