dbm : DBConnections.o dbI.o
	g++ -o dbm DBConnections.o dbI.o -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto -lpthread -lrt -std=c++11
DBConnections.o : DBConnections.cpp *h
	g++ -c -g DBConnections.h DBConnections.cpp *h -I/usr/include/mysql $(mysql_config --cflags) -std=c++11 -lpthread -lrt
dbI.o : dbI.cpp
	g++ -c -g DBInterface.h dbI.cpp -I/usr/include/mysql $(mysql_config --cflags) -std=c++11  -lpthread -lrt
clean :
	rm dbI.o
