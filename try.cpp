#include <zmq.hpp>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;
int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	zmq::socket_t publisher(context, ZMQ_PUB);

	socket.bind("tcp://*5556");

	while(true)
	{
		zmq::message_t request;
		socket.recv(&request);
		printf("hello");

		sleep(1);

		zmq::message_t reply(5);
		memcpy((void*)reply.data(), "world", 5);

		socket.send(reply);
	}	
	return 0;
}
