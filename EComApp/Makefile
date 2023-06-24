CPP = g++
FLAGS = -O5 -Wall -W
RM = rm -f
EXEC = MyEComApp
OBJECTS = main.o myflipkart.o item.o user.o

all : $(OBJECTS) compile

main.o : main.cpp
	$(CPP) $(FLAGS) -c main.cpp

myflipkart.o : myflipkart.cpp
	$(CPP) $(FLAGS) -c myflipkart.cpp

user.o : user.cpp
	$(CPP) $(FLAGS) -c user.cpp

item.o : item.cpp
	$(CPP) $(FLAGS) -c item.cpp

compile :
	$(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC)

clean :
	$(RM) $(OBJECTS) $(EXEC)
