#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>
#include <Box2D\Box2D.h>
#include <iostream>


void loadWidgets(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
    picture->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
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
	button->setPosition(270, 440);
	button->setText("Login");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);
}

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

/** Create the base for the boxes to land */
void CreateGround(b2World& World, float X, float Y);

/** Create the boxes */
void CreateBox(b2World& World, int MouseX, int MouseY);

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
	tgui::Gui gui(window);

	// Load the font (you should check the return value to make sure that it is loaded)
	gui.setGlobalFont("../TGUI/fonts/DejaVuSans.ttf");

	// Load the widgets
	loadWidgets(gui);

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

				

					/** Prepare the window */
					sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
					Window.setFramerateLimit(60);
				
					/** Prepare the world */
					b2Vec2 Gravity(0.f, 9.8f);
					b2World World(Gravity);
					CreateGround(World, 400.f, 500.f);
				
					/** Prepare textures */
					sf::Texture GroundTexture;
					sf::Texture BoxTexture;
					GroundTexture.loadFromFile("ground.png");
					BoxTexture.loadFromFile("box.png");
				
					std::cout << "Hello world" << std::endl;
				
					while (Window.isOpen())
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							int MouseX = sf::Mouse::getPosition(Window).x;
							int MouseY = sf::Mouse::getPosition(Window).y;
							CreateBox(World, MouseX, MouseY);
						}
						World.Step(1 / 60.f, 8, 3);
				
						Window.clear(sf::Color::White);
						int BodyCount = 0;
						for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
						{
							if (BodyIterator->GetType() == b2_dynamicBody)
							{
								sf::Sprite Sprite;
								Sprite.setTexture(BoxTexture);
								Sprite.setOrigin(16.f, 16.f);
								Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
								Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
								Window.draw(Sprite);
								++BodyCount;
							}
							else
							{
								sf::Sprite GroundSprite;
								GroundSprite.setTexture(GroundTexture);
								GroundSprite.setOrigin(400.f, 8.f);
								GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
								GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
								Window.draw(GroundSprite);
							}
						}
						Window.display();
					}
				
					return 0;





			}

			//if (callback.id == 2)
		//	{

//			}
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
void CreateBox(b2World& World, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}