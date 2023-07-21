all: main.o UTaxi.o Trip.o Driver.o Customer.o Person.o Location.o Error.o Coordination.o Handle_Command.o
	g++ -o utaxi.out main.o UTaxi.o Trip.o Driver.o Customer.o Person.o Location.o Error.o Coordination.o Handle_Command.o
main.o:main.cc UTaxi.hh
	g++ -c main.cc
Handle_Command.o:Handle_Command.cc Handle_Command.hh Define.hh
	g++ -c Handle_Command.cc
UTaxi.o:UTaxi.cc UTaxi.hh Trip.hh Driver.hh Customer.hh Person.hh Location.hh Error.hh Coordination.hh Define.hh Handle_Command.hh
	g++ -c UTaxi.cc
Trip.o:Trip.cc Trip.hh Driver.hh Customer.hh Location.hh Define.hh Error.hh
	g++ -c Trip.cc
Driver.o:Driver.cc Driver.hh Person.hh Define.hh
	g++ -c Driver.cc
Customer.o:Customer.cc Customer.hh Person.hh Define.hh
	g++ -c Customer.cc
Person.o:Person.cc Person.hh Define.hh
	g++ -c Person.cc
Location.o:Location.cc Location.hh Coordination.hh
	g++ -c Location.cc
Coordination.o:Coordination.cc Coordination.hh Define.hh
	g++ -c Coordination.cc
Error.o:Error.hh Error.cc
	g++ -c Error.cc
clean:
	rm utaxi.out *.o