#include <zmq.hpp>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;
int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PUB);

	socket.bind("tcp://*:5556");

	while(true)
	{
		//zmq::message_t request;
		//socket.recv(&request);

		sleep(1);
		int a = rand() * 100000 %10;
		int b = rand() * 1000 % 10;
		int c = rand() * 343434 % 10;
		zmq::message_t reply(8);
		//memcpy((void*)reply.data(), str.data(), 20);
		printf("%d %d %d\n",a,b,c);
       // sprintf((char*)reply.data(), "helloworlf");
        sprintf((char*)reply.data(), "%d %d %d", a,b,c);
		socket.send(reply);
	}	
	return 0;
}
