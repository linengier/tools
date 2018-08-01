CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++

TARGET 	= test
PATH_DIR= $(shell pwd)
DIRS 	= $(PATH_DIR)
FILES 	= $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJ_O 	= $(FILES):%.o:%.c_
$(TARGET):$(FILES)
	echo "files:$(FILES), $(OBJ_O)"
	#$(CC) -O $@ $^
	gcc -o $@ $^

clean:
	rm -fr $(TARGET)
