CC=gcc
OPT=-Wall
EXEC=sudoku
OBJ=./obj
BIN=./bin
SRC=./src
All:before $(EXEC) message

before:
	@clear
	@echo
	@echo "  ########################################"
	@echo "  ####### +-------------------+ ##########"
	@echo "  ####### | ***************** | ##########"
	@echo "  ####### | * SUDOKU SOLVER * | ##########"
	@echo "  ####### | ***************** | ##########"
	@echo "  ####### +-------------------+ ##########"
	@echo "  ########################################"


#compile basic Fucntions
basicFunctions.o: $(SRC)/basicFunctions.c
	@echo
	@echo "--->  Compiling the basic_Function.c file..."
	@$(CC) -o $(OBJ)/basicFunctions.o -c $(SRC)/basicFunctions.c $(OPT)

#compile rules
rules.o: $(SRC)/rules.c
	@echo
	@echo "--->  Compiling the rules.c file..."
	@$(CC) -o $(OBJ)/rules.o -c $(SRC)/rules.c $(OPT)

#compile candidates Functions file
candidates.o: $(SRC)/candidates.c
	@echo
	@echo "--->  Compiling the candidatesFunction.c file..."
	@$(CC) -o $(OBJ)/candidates.o -c $(SRC)/candidates.c $(OPT)

#compile mainFunctions
mainFunctions.o: $(SRC)/mainFunctions.c
	@echo
	@echo "--->  Compiling the mainFunctions.c file..."
	@$(CC) -o $(OBJ)/mainFunctions.o -c $(SRC)/mainFunctions.c $(OPT)

#compile main
main.o: $(SRC)/main.c
	@echo
	@echo "--->  Compiling the main.c file..."
	@$(CC) -o $(OBJ)/main.o -c $(SRC)/main.c $(OPT)

$(EXEC): main.o basicFunctions.o candidates.o mainFunctions.o rules.o
	@echo
	@echo "--->  Linking the main with the other files..."
	@$(CC) $(OBJ)/main.o $(OBJ)/basicFunctions.o $(OBJ)/candidates.o $(OBJ)/mainFunctions.o $(OBJ)/rules.o -o $(BIN)/$(EXEC)
clean:
	@echo
	@echo "--->  Cleaning the objects files..."
	@rm -rf $(OBJ)/* $(BIN)/*

message:
	@echo 
	@echo "+----------------------------------+"
	@echo "|            All done!             |"
	@echo "+----------------------------------+"
	@echo 
	@echo "Now run ./bin/sudoku"
	@echo 
