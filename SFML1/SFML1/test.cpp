#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>
#include <Box2D\Box2D.h>
//#include "mysql\mysql_connection.h"
//#include <mysql\cppconn\driver.h>
//#include <mysql\cppconn\exception.h>
//#include <mysql\cppconn\resultset.h>
//#include <mysql\cppconn\statement.h>
//#include <mysql\cppconn\prepared_statement.h>
#include <iostream>
//#include "mysql_connection.h"
//
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//
//
//// Link to the Connector/C++ library
//#pragma comment(lib, "mysqlcppconn.lib")

void loginScreen(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
   // picture->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
	picture->load("../images/satan.jpg");
	picture->setSize(800, 600);

	// Create the username label
	tgui::Label::Ptr labelUsername(gui);
	labelUsername->setText("Username:");
	labelUsername->setPosition(200, 100);

	// Create the password label
	tgui::Label::Ptr labelPassword(gui);
	labelPassword->setText("Password:");
	labelPassword->setPosition(200, 250);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername(gui, "Username");
	editBoxUsername->load("../TGUI/widgets/Black.conf");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(200, 140);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
	editBoxPassword->setPosition(200, 290);
	editBoxPassword->setPasswordCharacter('*');

	// Create the login button
	tgui::Button::Ptr button(gui);
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(270, 400);
	button->setText("Login");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	// Create the new account button 
	tgui::Button::Ptr newAccountButton(gui);
	newAccountButton->load("../TGUI/widgets/Black.conf");
	newAccountButton->setSize(260, 60);
	newAccountButton->setPosition(270, 500);
	newAccountButton->setText("New Account");
	newAccountButton->bindCallback(tgui::Button::LeftMouseClicked);
	newAccountButton->setCallbackId(2);

}

void levelSelectionScreen(tgui::Gui& gui, int levelNum)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
	picture->setSize(800, 600);

	// Create the levelSelect label
	tgui::Label::Ptr levelSelectLable(gui);
	levelSelectLable->setText("Please select your level...");
	levelSelectLable->setPosition(200, 100);

	tgui::SpriteSheet::Ptr spritesheet1(gui);
	tgui::SpriteSheet::Ptr spritesheet2(gui);
	tgui::SpriteSheet::Ptr spritesheet3(gui);

	switch (levelNum)
	{
	case 1:
		spritesheet1->load("../TGUI/examples/ThinkLinux.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 200);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/satan.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 200);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(666);

		spritesheet3->load("../images/satan.jpg");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 200);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(666);
		break;

	case 2:
		spritesheet1->load("../TGUI/examples/ThinkLinux.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 200);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 200);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(4);

		spritesheet3->load("../images/satan.jpg");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 200);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(666);
		break;
	case 3:
		spritesheet1->load("../TGUI/examples/ThinkLinux.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 200);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 200);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(4);

		spritesheet3->load("../images/cell.gif");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 200);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(5);
		break;
	default:
		break;
	}

	/*tgui::SpriteSheet::Ptr spritesheet1(gui);
	spritesheet1->load("../TGUI/examples/ThinkLinux.jpg");
	spritesheet1->setSize(200, 140);
	spritesheet1->setPosition(25, 200);
	spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
	spritesheet1->setCallbackId(3);

	tgui::SpriteSheet::Ptr spritesheet2(gui);
	spritesheet2->load("../TGUI/examples/Linux.jpg");
	spritesheet2->setSize(200, 140);
	spritesheet2->setPosition(300, 200);
	spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
	spritesheet2->setCallbackId(4);

	tgui::SpriteSheet::Ptr spritesheet3(gui);
	spritesheet3->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
	spritesheet3->setSize(200, 140);
	spritesheet3->setPosition(575, 200);
	spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
	spritesheet3->setCallbackId(5);
	*/

	// Create Level Lables
	tgui::Label::Ptr level1Lable(gui);
	level1Lable->setText("Level 1");
	level1Lable->setPosition(65, 390);

	tgui::Label::Ptr level2lable(gui);
	level2lable->setText("Level 2");
	level2lable->setPosition(340, 390);

	tgui::Label::Ptr level3lable(gui);
	level3lable->setText("Level 3");
	level3lable->setPosition(615, 390);

	//sf::Drawable canvas(gui);

	/*tgui::Canvas::Ptr canvas(gui);
	canvas->setSize(200, 140);
	canvas->setPosition(200, 150);
	canvas->*/

	//tgui::Panel::Ptr panel(gui, "Level 1");
	//panel->setSize(200, 140);
	//panel->setPosition(200, 150);
	//panel->setBackgroundTexture(&texture);
	////panel->setBackgroundColor(sf::Color::Green);
	//panel->bindCallback(tgui::Button::LeftMouseClicked);
	//panel->setCallbackId(3);
	//
	
	
	//tgui::Button::Ptr level1(gui);
	//level1->("../TGUI/examples/ThinkLinux.jpg");
	//level1->setPosition(200, 250);
	//tgui::ChildWindow::Ptr level1(gui);
	//level1->load("../TGUI/examples/ThinkLinux.jpg");
	//level1->setIcon("../TGUI/examples/ThinkLinux.jpg");
	//level1->setSize(200, 200);
	//level1->setPosition(200, 250);
	//// Create the password label
	//tgui::Label::Ptr labelPassword(gui);
	//labelPassword->setText("Password:");
	//labelPassword->setPosition(200, 250);

	//// Create the username edit box
	//tgui::EditBox::Ptr editBoxUsername(gui, "Username");
	//editBoxUsername->load("../TGUI/widgets/Black.conf");
	//editBoxUsername->setSize(400, 40);
	//editBoxUsername->setPosition(200, 140);

	//// Create the password edit box (we will copy the previously created edit box)
	//tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
	//editBoxPassword->setPosition(200, 290);
	//editBoxPassword->setPasswordCharacter('*');

	//// Create the login button
	//tgui::Button::Ptr button(gui);
	//button->load("../TGUI/widgets/Black.conf");
	//button->setSize(260, 60);
	//button->setPosition(270, 400);
	//button->setText("Login");
	//button->bindCallback(tgui::Button::LeftMouseClicked);
	//button->setCallbackId(1);

	//// Create the new account button 
	//tgui::Button::Ptr newAccountButton(gui);
	//newAccountButton->load("../TGUI/widgets/Black.conf");
	//newAccountButton->setSize(260, 60);
	//newAccountButton->setPosition(270, 500);
	//newAccountButton->setText("New Account");
	//newAccountButton->bindCallback(tgui::Button::LeftMouseClicked);
	//newAccountButton->setCallbackId(2);
}

void loadWidgets01(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../TGUI/examples/cell.gif");
	picture->setSize(800, 600);

	// Create the username label
	tgui::Label::Ptr labelUsername(gui);
	labelUsername->setText("Username:");
	labelUsername->setPosition(200, 100);

	// Create the password label
	tgui::Label::Ptr labelPassword(gui);
	labelPassword->setText("Password:");
	labelPassword->setPosition(200, 250);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername(gui, "Username");
	editBoxUsername->load("../TGUI/widgets/Black.conf");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(200, 140);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
	editBoxPassword->setPosition(200, 290);
	editBoxPassword->setPasswordCharacter('*');

	// Create the login button
	tgui::Button::Ptr button(gui);
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(270, 400);
	button->setText("Login");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	// Create the new account button 
	tgui::Button::Ptr newAccountButton(gui);
	newAccountButton->load("../TGUI/widgets/Black.conf");
	newAccountButton->setSize(260, 60);
	newAccountButton->setPosition(270, 500);
	newAccountButton->setText("New Account");
	newAccountButton->bindCallback(tgui::Button::LeftMouseClicked);
	newAccountButton->setCallbackId(2);
}

void level3(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/cell.gif");
	picture->setSize(700, 500);

	// Create the done button
	tgui::Button::Ptr doneButton(gui);
	doneButton->load("../TGUI/widgets/Black.conf");
	doneButton->setSize(260, 60);
	doneButton->setPosition(270, 500);
	doneButton->setText("Done");
	doneButton->bindCallback(tgui::Button::LeftMouseClicked);
	doneButton->setCallbackId(32);

	tgui::Tab::Ptr tab(gui);
	tab->load("../TGUI/widgets/Black.conf");
	tab->setPosition(40, 300);
	tab->setSize(20, 40);
	tab->add("nucleus");
	tab->add("mitochondria");
	tab->add("ribosome");

}

/** We need this to easily convert between pixel and real-world coordinates*/
//static const float SCALE = 30.f;

/** Create the base for the boxes to land */
//void CreateGround(b2World& World, float X, float Y);

/** Create the boxes */
//void CreateBox(b2World& World, int MouseX, int MouseY);

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
	tgui::Gui gui(window);

	// Load the font (you should check the return value to make sure that it is loaded)
	gui.setGlobalFont("../TGUI/fonts/DejaVuSans.ttf");

	// Load the widgets
	loginScreen(gui);

	// Main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pass the event to all the widgets
			gui.handleEvent(event);
		}

		// The callback loop
		tgui::Callback callback;
		while (gui.pollCallback(callback))
		{
			// Make sure tha callback comes from the button
			if (callback.id == 1)
			{
				// Get the username and password
				tgui::EditBox::Ptr editBoxUsername = gui.get("Username");
				tgui::EditBox::Ptr editBoxPassword = gui.get("Password");

				sf::String username = editBoxUsername->getText();
				sf::String password = editBoxPassword->getText();

				// Continue here by checking if the username and password are correct ...
				std::cout << "Made it here" << std::endl;

				// This levelNum int will come from the database 
				int level = 3;

				levelSelectionScreen(gui, level);

				///** Prepare the window */
				//sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
				//Window.setFramerateLimit(60);
				//
				///** Prepare the world */
				//b2Vec2 Gravity(0.f, 9.8f);
				//b2World World(Gravity);
				//CreateGround(World, 400.f, 500.f);
				//
				///** Prepare textures */
				//sf::Texture GroundTexture;
				//sf::Texture BoxTexture;
				//GroundTexture.loadFromFile("ground.png");
				//BoxTexture.loadFromFile("box.png");
				//
				//std::cout << "Hello world" << std::endl;
				//
				//while (Window.isOpen())
				//{
				//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				//	{
				//		int MouseX = sf::Mouse::getPosition(Window).x;
				//		int MouseY = sf::Mouse::getPosition(Window).y;
				//		CreateBox(World, MouseX, MouseY);
				//	}
				//	World.Step(1 / 60.f, 8, 3);
				//
				//	Window.clear(sf::Color::White);
				//	int BodyCount = 0;
				//	for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
				//	{
				//		if (BodyIterator->GetType() == b2_dynamicBody)
				//		{
				//			sf::Sprite Sprite;
				//			Sprite.setTexture(BoxTexture);
				//			Sprite.setOrigin(16.f, 16.f);
				//			Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				//			Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				//			Window.draw(Sprite);
				//			++BodyCount;
				//		}
				//		else
				//		{
				//			sf::Sprite GroundSprite;
				//			GroundSprite.setTexture(GroundTexture);
				//			GroundSprite.setOrigin(400.f, 8.f);
				//			GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				//			GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				//			Window.draw(GroundSprite);
				//		}
				//	}
				//	Window.display();
				//}					
			}

			if (callback.id == 2)
			{
				std::cout << "Creating account..." << std::endl;
			}

			if (callback.id == 3)
			{
				std::cout << "Loading Level 1" << std::endl;
			}

			if (callback.id == 4)
			{
				std::cout << "Loading Level 2" << std::endl;
			}

			if (callback.id == 5)
			{
				std::cout << "Loading Level 3" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level3(gui);
			}
		}

		window.clear();

		// Draw all created widgets
		gui.draw();

		window.display();
	}

	return EXIT_SUCCESS;
}


///** We need this to easily convert between pixel and real-world coordinates*/
//static const float SCALE = 30.f;
//
///** Create the base for the boxes to land */
//void CreateGround(b2World& World, float X, float Y);
//
///** Create the boxes */
//void CreateBox(b2World& World, int MouseX, int MouseY);
//
//int main()
//{
//	/** Prepare the window */
//	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
//	Window.setFramerateLimit(60);
//
//	/** Prepare the world */
//	b2Vec2 Gravity(0.f, 9.8f);
//	b2World World(Gravity);
//	CreateGround(World, 400.f, 500.f);
//
//	/** Prepare textures */
//	sf::Texture GroundTexture;
//	sf::Texture BoxTexture;
//	GroundTexture.loadFromFile("ground.png");
//	BoxTexture.loadFromFile("box.png");
//
//	std::cout << "Hello world" << std::endl;
//
//	while (Window.isOpen())
//	{
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			int MouseX = sf::Mouse::getPosition(Window).x;
//			int MouseY = sf::Mouse::getPosition(Window).y;
//			CreateBox(World, MouseX, MouseY);
//		}
//		World.Step(1 / 60.f, 8, 3);
//
//		Window.clear(sf::Color::White);
//		int BodyCount = 0;
//		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//		{
//			if (BodyIterator->GetType() == b2_dynamicBody)
//			{
//				sf::Sprite Sprite;
//				Sprite.setTexture(BoxTexture);
//				Sprite.setOrigin(16.f, 16.f);
//				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
//				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
//				Window.draw(Sprite);
//				++BodyCount;
//			}
//			else
//			{
//				sf::Sprite GroundSprite;
//				GroundSprite.setTexture(GroundTexture);
//				GroundSprite.setOrigin(400.f, 8.f);
//				GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
//				GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
//				Window.draw(GroundSprite);
//			}
//		}
//		Window.display();
//	}
//
//	return 0;
//}
//
//void CreateBox(b2World& World, int MouseX, int MouseY)
//{
//	b2BodyDef BodyDef;
//	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
//	BodyDef.type = b2_dynamicBody;
//	b2Body* Body = World.CreateBody(&BodyDef);
//
//	b2PolygonShape Shape;
//	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
//	b2FixtureDef FixtureDef;
//	FixtureDef.density = 1.f;
//	FixtureDef.friction = 0.7f;
//	FixtureDef.shape = &Shape;
//	Body->CreateFixture(&FixtureDef);
//}
//
//void CreateGround(b2World& World, float X, float Y)
//{
//	b2BodyDef BodyDef;
//	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
//	BodyDef.type = b2_staticBody;
//	b2Body* Body = World.CreateBody(&BodyDef);
//
//	b2PolygonShape Shape;
//	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
//	b2FixtureDef FixtureDef;
//	FixtureDef.density = 0.f;
//	FixtureDef.shape = &Shape;
//	Body->CreateFixture(&FixtureDef);
//}