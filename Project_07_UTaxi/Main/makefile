utaxi.out:build/template_parser.o build/response.o build/request.o build/utilities.o build/server.o build/route.o build/main.o build/UTaxi.o build/Trip.o build/Driver.o build/Customer.o build/Person.o build/Location.o build/Coordination.o build/Error.o build/Interface.o build/handler.o
	g++ -o utaxi.out build/template_parser.o build/response.o build/request.o build/utilities.o build/server.o build/route.o build/main.o build/UTaxi.o build/Trip.o build/Driver.o build/Customer.o build/Person.o build/Location.o build/Coordination.o build/Error.o build/Interface.o build/handler.o

build/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	g++ -c utils/template_parser.cpp -o build/template_parser.o

build/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	g++ -c utils/response.cpp -o build/response.o

build/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	g++ -c utils/request.cpp -o build/request.o

build/utilities.o: utils/utilities.cpp utils/utilities.hpp
	g++ -c utils/utilities.cpp -o build/utilities.o

build/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	g++ -c server/server.cpp -o build/server.o

build/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	g++ -c server/route.cpp -o build/route.o

build/main.o:main.cc Interface.hh logicPart/UTaxi.hh
	g++ -c main.cc -o build/main.o

build/UTaxi.o:logicPart/UTaxi.cc logicPart/UTaxi.hh logicPart/Trip.hh logicPart/Driver.hh logicPart/Customer.hh logicPart/Person.hh logicPart/Location.hh logicPart/Error.hh logicPart/Coordination.hh logicPart/Define.hh
	g++ -c logicPart/UTaxi.cc -o build/UTaxi.o

build/Trip.o:logicPart/Trip.cc logicPart/Trip.hh logicPart/Driver.hh logicPart/Customer.hh logicPart/Location.hh logicPart/Define.hh logicPart/Error.hh
	g++ -c logicPart/Trip.cc -o build/Trip.o

build/Driver.o:logicPart/Driver.cc logicPart/Driver.hh logicPart/Person.hh logicPart/Define.hh
	g++ -c logicPart/Driver.cc -o build/Driver.o

build/Customer.o:logicPart/Customer.cc logicPart/Customer.hh logicPart/Person.hh logicPart/Define.hh
	g++ -c logicPart/Customer.cc -o build/Customer.o

build/Person.o:logicPart/Person.cc logicPart/Person.hh logicPart/Define.hh
	g++ -c logicPart/Person.cc -o build/Person.o

build/Location.o:logicPart/Location.cc logicPart/Location.hh logicPart/Coordination.hh
	g++ -c logicPart/Location.cc -o build/Location.o

build/Coordination.o:logicPart/Coordination.cc logicPart/Coordination.hh logicPart/Define.hh
	g++ -c logicPart/Coordination.cc -o build/Coordination.o

build/Error.o:logicPart/Error.hh logicPart/Error.cc
	g++ -c logicPart/Error.cc -o build/Error.o

build/Interface.o:Interface.cc Interface.hh logicPart/UTaxi.hh logicPart/handler.hh server/server.hpp
	g++ -c Interface.cc -o build/Interface.o

build/handler.o:logicPart/handler.cc logicPart/handler.hh server/server.hpp logicPart/UTaxi.hh
	g++ -c logicPart/handler.cc -o build/handler.o

clean:
	rm utaxi.out build/*.o