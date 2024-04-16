# Определение компилятора
CC=gcc

# Определение имени исполняемого файла
CLIENT_TARGET=client
SERVER_TARGET=server

# Путь к директории с библиотеками
LIB_PATH=./liblogger

# Путь к директории с заголовочными файлами
INCLUDE_PATH=./liblogger

# Правило по умолчанию для создания исполняемых файлов
all: $(CLIENT_TARGET) $(SERVER_TARGET)

# Правило для сборки исполняемого файла 
$(CLIENT_TARGET): client.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

client.o: client.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

$(SERVER_TARGET): server.o
	$(CC) $(CFLAGS) -L$(LIB_PATH) -llogger -o $@ $^

server.o: server.c $(INCLUDE_PATH)/logger.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $<

clean:
	rm -f *.o $(CLIENT_TARGET) $(SERVER_TARGET)