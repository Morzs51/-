# Определение компилятора
CC=gcc

# Определение имени исполняемого файла
TARGET=lab1

# Путь к директории с библиотеками
LIB_PATH=./liblogger

# Путь к директории с заголовочными файлами
INCLUDE_PATH=./liblogger

# Правило по умолчанию для создания исполняемых файлов
all: $(TARGET)

# Правило для сборки исполняемого файла logger_test
$(TARGET): lab1.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

# Правило для сборки объектного файла из исходного кода теста логгера
lab1.o: lab1.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

# Правило для запуска приложения с установленной переменной окружения
run: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB_PATH):$$LD_LIBRARY_PATH; \
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)