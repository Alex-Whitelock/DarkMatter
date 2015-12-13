#include "main.h"
#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML\Network.hpp>
#include <mysql.h>
#include <stdlib.h>
#include <list>


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
	bool alreadyExist;
	int level;
};

//void GetInput(void)
//{
//	std::string s;
//	std::cout << "\nEnter \"exit\" to quit or message to send: ";
//	std::cin >> s;
//	if (s == "exit")
//		quit = true;
//	globalMutex.lock();
//	msgSend = s;
//	globalMutex.unlock();
//}


sf::Packet& operator >>(sf::Packet& Packet, PackStruct& P)
{
	return Packet >> P.connType >> P.userName >> P.password >> P.admin >> P.authorized >> P.level >> P.alreadyExist;
}

sf::Packet& operator <<(sf::Packet& Packet, const PackStruct& P)
{
	return Packet << P.connType << P.userName << P.password << P.admin << P.authorized << P.level << P.alreadyExist;
}

PackStruct loginCheck(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
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

		// Grabs all fields from Users table and traverses them
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

	mysql_close(connection);

	return p;
}

PackStruct newAccount(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	// Check if user exists
	std::string command = "SELECT * FROM Users WHERE Username = '" + p.userName + "'";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	if (!(row = mysql_fetch_row(result)))
	{
		std::string command = "INSERT INTO Users (Username, Password) VALUES ('" + p.userName + "', '" + p.password + "')";
		mysql_query(connection, command.c_str());

		p.alreadyExist = false;
	}
	else
	{
		p.alreadyExist = true;
	}

	mysql_free_result(result);
	mysql_close(connection);

	return p;
}

PackStruct getGameLevel(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);


	std::string command = "SELECT * FROM Users WHERE UserName = '" + p.userName + "'";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		// Grabs all fields from Users table and traverses them
		while ((field = mysql_fetch_field(result)))
		{
			std::string temp = field->name;
			if (temp.compare("GameLevel") == 0){
				std::string levelVal = row[i];
				level = atoi(levelVal.c_str());
				p.level = level;
			}
			i++;
		}
	}

	mysql_free_result(result);
	mysql_close(connection);

	return p;
}

PackStruct advanceLevel1(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM Users WHERE Username = '" + p.userName + "'";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		// Grabs all fields from Users table and traverses them
		while ((field = mysql_fetch_field(result)))
		{
			std::string temp = field->name;
			if (temp.compare("GameLevel") == 0){
				std::string gameVal = row[i];

				if (gameVal.compare(std::to_string(2)) < 0)
				{
					p.level = 2;
					std::string str_newlevel = std::to_string(p.level);
					std::string command = "UPDATE Users SET GameLevel = '" + str_newlevel + "' WHERE Username = '" + p.userName + "'";
					mysql_query(connection, command.c_str());

					std::cout << "Game level advances to " << p.level << std::endl;
				}
			}
			i++;
		}
	}

	mysql_free_result(result);
	mysql_close(connection);

	return p;
}

PackStruct advanceLevel2(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM Users WHERE Username = '" + p.userName + "'";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		// Grabs all fields from Users table and traverses them
		while ((field = mysql_fetch_field(result)))
		{
			std::string temp = field->name;
			if (temp.compare("GameLevel") == 0){
				std::string gameVal = row[i];

				if (gameVal.compare(std::to_string(3)) < 0)
				{
					p.level = 3;
					std::string str_newlevel = std::to_string(p.level);
					std::string command = "UPDATE Users SET GameLevel = '" + str_newlevel + "' WHERE Username = '" + p.userName + "'";
					mysql_query(connection, command.c_str());

					std::cout << "Game level advances to " << p.level << std::endl;
				}
			}
			i++;
		}
	}
	
	mysql_free_result(result);
	mysql_close(connection);

	return p;
}



PackStruct advanceLevel3(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM Users WHERE Username = '" + p.userName + "'";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		// Grabs all fields from Users table and traverses them
		while ((field = mysql_fetch_field(result)))
		{
			std::string temp = field->name;
			if (temp.compare("GameLevel") == 0){
				std::string gameVal = row[i];

				if (gameVal.compare(std::to_string(4)) < 0)
				{
					p.level = 4;
					std::string str_newlevel = std::to_string(p.level);
					std::string command = "UPDATE Users SET GameLevel = '" + str_newlevel + "' WHERE Username = '" + p.userName + "'";
					mysql_query(connection, command.c_str());

					std::cout << "Game level advances to " << p.level << std::endl;
				}
			}
			i++;
		}
	}

	mysql_free_result(result);
	mysql_close(connection);

	return p;
}

void deleteUser(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "DELETE FROM Users WHERE Username=\"" + p.userName + "\"";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	mysql_free_result(result);
	mysql_close(connection);
}

sf::Packet users()
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	
	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM `Users`";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	std::list<std::string> users;

	while ((row = mysql_fetch_row(result)) != NULL)
	{
		users.push_back(row[0]);
	}

	sf::Packet returnPack;
	returnPack << static_cast<sf::Uint32>(users.size());
	for (std::list<std::string>::const_iterator it = users.begin(); it != users.end(); it++)
		returnPack << *it;

	mysql_free_result(result);
	mysql_close(connection);

	return returnPack;
}

PackStruct html(PackStruct p)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;
	std::string user;
	int level = 0;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT * FROM Users";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);
	if ((row = mysql_fetch_row(result)))
	{
		int i = 0;
		bool admin = false;
		p.admin = false;
		user = p.userName;

		// Grabs all fields from Users table and traverses them
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

	mysql_close(connection);

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
			}
			
			if (packed.connType == "NEWACCT")
			{
				packed = newAccount(packed);
				received.clear();
				received << packed;
				client.send(received);
			}

			if (packed.connType == "GAMELEVEL")
			{
				packed = getGameLevel(packed);
				received.clear();
				received << packed;
				client.send(received);
			}

			if (packed.connType == "ADVANCELEVEL1")
			{
				packed = advanceLevel1(packed);
				received.clear();
				received << packed;
				client.send(received);
			}

			if (packed.connType == "ADVANCELEVEL2")
			{
				packed = advanceLevel2(packed);
				received.clear();
				received << packed;
				client.send(received);
			}

			if (packed.connType == "ADVANCELEVEL3")
			{
				packed = advanceLevel3(packed);
				received.clear();
				received << packed;
				client.send(received);
			}

			if (packed.connType == "DELETE")
			{
				deleteUser(packed);
			}

			if (packed.connType == "USERS")
			{
				received.clear();
				received = users();
				client.send(received);
			}

			if (packed.connType == "HTMLREPORT")
			{
				packed = html(packed);
				received.clear();
				received << packed;
				client.send(received);
			}
		}
	}

	return 0;
}