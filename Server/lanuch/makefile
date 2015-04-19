server : server.o
	g++ -g -o server -g server.cpp ../lib/libdb.a ../lib/liblog.a -std=c++11 -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lm -lssl -lcrypto -lpthread -lrt 
server.o : server.cpp Connection.h mLanuch.h
	g++ -c -g server.cpp Connection.h -std=c++11 $(mysql_config --cflags) -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lm -lssl -lcrypto -lpthread -lrt 

