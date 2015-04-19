server : server.o
	g++ -g -o server -g server.cpp ../lib/libdb.a ../lib/liblog.a -std=c++11 -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lm -lssl -lcrypto -lpthread -lrt 
server.o : server.cpp Connection.h mLanuch.h ../publicRoom/InRoom.h ../publicRoom/UpdateParty.h ../include/Rdwr.h ../include/BroadcastInterface.h
	g++ -c -g server.cpp Connection.h mLanuch.h ../publicRoom/InRoom.h ../publicRoom/UpdateParty.h ../include/Rdwr.h ../include/BroadcastInterface.h -std=c++11 -I/usr/include/mysql -rdynamic -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lm -lssl -lcrypto -lpthread -lrt 
clean :
	rm *.o server
