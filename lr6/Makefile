# Определение компилятора
CC=gcc

# Определение имени исполняемого файла
TARGET=lab6

# Путь к директории с библиотеками
LIB_PATH=./liblogger

# Путь к директории с заголовочными файлами
INCLUDE_PATH=./liblogger

# Правило по умолчанию для создания исполняемых файлов
all: $(TARGET)

# Правило для сборки исполняемого файла logger_test
$(TARGET): lab6.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

# Правило для сборки объектного файла из исходного кода теста логгера
lab6.o: lab6.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

clean:
	rm -f *.o $(TARGET)