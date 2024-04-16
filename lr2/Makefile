# Определение компилятора
CC=gcc

# Определение имени исполняемого файла
TARGET=logger_test
PROCESS_TARGET=process_test

# Путь к директории с библиотеками
LIB_PATH=./liblogger

# Путь к директории с заголовочными файлами
INCLUDE_PATH=./liblogger

# Правило по умолчанию для создания исполняемых файлов
all: $(TARGET) $(PROCESS_TARGET)

# Правило для сборки исполняемого файла logger_test
$(TARGET): logger_test.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

# Правило для сборки объектного файла из исходного кода теста логгера
logger_test.o: logger_test.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

# Правило для сборки исполняемого файла process_test
$(PROCESS_TARGET): process_test.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

# Правило для сборки объектного файла из исходного кода теста процессов
process_test.o: process_test.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

# Правило для очистки проекта от объектных файлов и исполняемых файлов
clean:
	rm -f *.o $(TARGET) $(PROCESS_TARGET)