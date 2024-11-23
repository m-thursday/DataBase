#!/bin/bash
set -e -v

g++ -Wall -o hello.exe hello.cpp
g++ -c addGame.cpp
g++ -c addPlayer.cpp
g++ -c findPlayer.cpp
g++ -c findPosition.cpp
g++ -c viewRanking.cpp
g++ -c viewGame.cpp
g++ -c viewDate.cpp
g++ -c odbc_db.cpp
g++ -Wall -I/usr/include/cppconn -o addGame.exe addGame.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o addPlayer.exe addPlayer.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o findPlayer.exe findPlayer.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o findPosition.exe findPosition.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o viewRanking.exe viewRanking.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o viewGame.exe viewGame.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o viewDate.exe viewDate.o odbc_db.o -L/usr/lib -lmysqlcppconn