#include "main.h"
#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML\Network.hpp>
#include <mysql.h>


//const unsigned short PORT = 5123;
//nst std::string IPADDRESS("192.168.63.1");

//sf::TcpSocket socket;
sf::Mutex globalMutex;
std::string msgSend;
bool quit = false;


struct PackStruct
{
	std::string connType;
	std::string userName;
	std::string password;
	bool admin;
	bool authorized;
	int level;
	//sf::Uint8   Age;
	//std::string Name;
	//float       Height;
};

/*void DoStuff(void)
{
	static std::string oldMsg;
	while (!quit)
	{
		sf::Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		globalMutex.unlock();

		socket.send(packetSend);

		std::string msg;
		sf::Packet packetReceive;

		socket.receive(packetReceive);
		if (packetReceive >> msg)
		{
			if (oldMsg != msg)
				if (!msg.empty())
				{
					std::cout << msg << std::endl;
					oldMsg = msg;
				}
		}
	}
}*/


/*void serverStartUp(void)
{
	sf::TcpSocket sock;
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(sock);
	
	if (listener.accept(sock) != sf::Socket::Done)
	{
		std::cout << "Made it here" << std::endl;
	}

	//std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}
*/
/*ol Client(void)
{
	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}*/

void GetInput(void)
{
	std::string s;
	std::cout << "\nEnter \"exit\" to quit or message to send: ";
	std::cin >> s;
	if (s == "exit")
		quit = true;
	globalMutex.lock();
	msgSend = s;
	globalMutex.unlock();
}


sf::Packet& operator >>(sf::Packet& Packet, PackStruct& P)
{
	return Packet >> P.connType >> P.userName >> P.password >> P.admin >> P.authorized >> P.level;
}

sf::Packet& operator <<(sf::Packet& Packet, const PackStruct& P)
{
	return Packet << P.connType << P.userName << P.password << P.admin << P.authorized << P.level;
}

PackStruct loginCheck(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	//initialize mysql connection
	mysql_init(&mysql);

	//connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM Users WHERE UserName = '" + p.userName + "' AND Password = '" + p.password + "'";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		bool admin = false;
		p.admin = false;
		user = p.userName;

		//Grabs all fields from Users table and traverses them
		while ((field = mysql_fetch_field(result)))
		{
			std::cout << field->name << ": " << row[i] << std::endl;
			std::string temp = field->name;
			if (temp.compare("Admin") == 0){
				std::string admVal = row[i];
				admin = admVal.compare("1") == 0;
			}
			if (temp.compare("GameLevel") == 0){
				std::string levelVal = row[i];
				level = atoi(levelVal.c_str());
				p.level = level;
				p.authorized = true;
			}
			i++;
		}

		if (admin){
			std::cout << "User " << p.userName << " is admin" << std::endl;
			p.admin = true;
		}
		else{
			std::cout << "User " << p.userName << " is not admin" << std::endl;
		}

		mysql_free_result(result);
	}
	else
	{
		p.authorized = false;
	}

	return p;
}

int main()
{
	sf::Thread* thread = 0;

	sf::TcpSocket client;

	sf::TcpListener listener;

	//listener.listen(5123);

	if (listener.listen(5000) != sf::TcpListener::Status::Done)
		return 1;

	std::cout << "Server is listening to port 5000, waiting for connections..." << std::endl;

	listener.accept(client);
	std::cout << "Client connected" << std::endl;

	PackStruct packed;
	sf::Packet received;

	while (!quit)
	{
		if (client.receive(received) == sf::Socket::Done)
		{
			//std::string test;
			//received >> test;
			received >> packed;
			std::cout << "Received packet that contains " << packed.connType << " " << packed.userName << " " << packed.password << " "<< std::endl;
			if (packed.connType == "LOGIN")
			{
				packed = loginCheck(packed);
				//sf::Packet temp;
				//temp << packed;
				received.clear();
				received << packed;
				client.send(received);
				std::cout << "Test";
			}
		}
	}

	//ar who;
	//d::cout << "Do you want to be a server (s) or a client (c) ? ";
	//d::cin >> who;

	// (who == 's')
		//serverStartUp();
	//se
	//lient();

	//thread = new sf::Thread(&DoStuff);
	//thread->launch();

	/*while (!quit)
	{
		GetInput();
	}
	if (thread)
	{
		thread->wait();
		delete thread;
	}*/
	return 0;
}