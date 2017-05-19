

server:server.o event_demultiplexer.o reactor.o global.o
				g++  -o server server.o event_demultiplexer.o reactor.o global.o
server.o:server.cpp common.h
				g++  -c server.cpp
event_demultiplexer.o:event_demultiplexer.cpp event_demultiplexer.h
				g++ -c event_demultiplexer.cpp
reactor.o:reactor.cpp reactor.h  singleton.h timeheap.h
				g++ -c reactor.cpp
global.o:global.cpp global.h singleton.h timeheap.h
				g++ -c global.cpp

clean:
				rm server.o reactor.o event_demultiplexer.o global.o

