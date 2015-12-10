#include "main.h"
#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML\Network.hpp>
#include <mysql.h>


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
};

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
			received >> packed;
			std::cout << "Received packet that contains " << packed.connType << " " << packed.userName << " " << packed.password << " "<< std::endl;
			if (packed.connType == "LOGIN")
			{
				packed = loginCheck(packed);
				received.clear();
				received << packed;
				client.send(received);
				std::cout << "Test";
			}
		}
	}

	return 0;
}