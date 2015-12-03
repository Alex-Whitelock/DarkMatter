#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>
#include <Box2D\Box2D.h>
#include <iostream>


void loginScreen(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
    // picture->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
	picture->load("../images/bio.jpg");
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
	picture->load("../images/bio.jpg");
	picture->setSize(800, 600);

	// Create the levelSelect label
	tgui::Label::Ptr levelSelectLabel(gui);
	levelSelectLabel->setText("Please select your level...");
	levelSelectLabel->setPosition(200, 100);

	tgui::SpriteSheet::Ptr spritesheet1(gui);
	tgui::SpriteSheet::Ptr spritesheet2(gui);
	tgui::SpriteSheet::Ptr spritesheet3(gui);

	switch (levelNum)
	{
	case 1:
		spritesheet1->load("../images/body.jpg");
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
		spritesheet1->load("../images/body.jpg");
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
		spritesheet1->load("../images/body.jpg");
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

	// Create Level Labels
	tgui::Label::Ptr level1Label(gui);
	level1Label->setText("Level 1");
	level1Label->setPosition(65, 390);

	tgui::Label::Ptr level2label(gui);
	level2label->setText("Level 2");
	level2label->setPosition(340, 390);

	tgui::Label::Ptr level3label(gui);
	level3label->setText("Level 3");
	level3label->setPosition(615, 390);

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

void level2(tgui::Gui& gui){

	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/skeleton_arrow.jpg");
	picture->setSize(800, 600);

	// Drop down comboxes
	tgui::ComboBox::Ptr comboBox1(gui, "Femur");
	comboBox1->load("../TGUI/widgets/Black.conf");
	comboBox1->setSize(120, 21);
	comboBox1->setPosition(150, 350);
	comboBox1->addItem("Femur");
	comboBox1->addItem("Cranium");
	comboBox1->addItem("Pelvis");
	comboBox1->addItem("Humerus");	
	comboBox1->addItem("Carpals");
	comboBox1->addItem("Patella");
	comboBox1->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox2(gui, "Cranium");
	comboBox2->load("../TGUI/widgets/Black.conf");
	comboBox2->setSize(120, 21);
	comboBox2->setPosition(130, 27);
	comboBox2->addItem("Femur");
	comboBox2->addItem("Cranium");
	comboBox2->addItem("Pelvis");
	comboBox2->addItem("Humerus");
	comboBox2->addItem("Carpals");
	comboBox2->addItem("Patella");
	comboBox2->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox3(gui, "Pelvis");
	comboBox3->load("../TGUI/widgets/Black.conf");
	comboBox3->setSize(120, 21);
	comboBox3->setPosition(559, 273);
	comboBox3->addItem("Femur");
	comboBox3->addItem("Cranium");
	comboBox3->addItem("Pelvis");
	comboBox3->addItem("Humerus");
	comboBox3->addItem("Carpals");
	comboBox3->addItem("Patella");
	comboBox3->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox4(gui, "Humerus");
	comboBox4->load("../TGUI/widgets/Black.conf");
	comboBox4->setSize(120, 21);
	comboBox4->setPosition(52, 128);
	comboBox4->addItem("Femur");
	comboBox4->addItem("Cranium");
	comboBox4->addItem("Pelvis");
	comboBox4->addItem("Humerus");
	comboBox4->addItem("Carpals");
	comboBox4->addItem("Patella");
	comboBox4->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox5(gui, "Carpals");
	comboBox5->load("../TGUI/widgets/Black.conf");
	comboBox5->setSize(120, 21);
	comboBox5->setPosition(65, 250);
	comboBox5->addItem("Femur");
	comboBox5->addItem("Cranium");
	comboBox5->addItem("Pelvis");
	comboBox5->addItem("Humerus");
	comboBox5->addItem("Carpals");
	comboBox5->addItem("Patella");
	comboBox5->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox6(gui, "Patella");
	comboBox6->load("../TGUI/widgets/Black.conf");
	comboBox6->setSize(120, 21);
	comboBox6->setPosition(595, 400);
	comboBox6->addItem("Femur");
	comboBox6->addItem("Cranium");
	comboBox6->addItem("Pelvis");
	comboBox6->addItem("Humerus");
	comboBox6->addItem("Carpals");
	comboBox6->addItem("Patella");
	comboBox6->addItem("Vertebrae");

	tgui::ComboBox::Ptr comboBox7(gui, "Vertebrae");
	comboBox7->load("../TGUI/widgets/Black.conf");
	comboBox7->setSize(120, 21);
	comboBox7->setPosition(538, 178);
	comboBox7->addItem("Femur");
	comboBox7->addItem("Cranium");
	comboBox7->addItem("Pelvis");
	comboBox7->addItem("Humerus");
	comboBox7->addItem("Carpals");
	comboBox7->addItem("Patella");
	comboBox7->addItem("Vertebrae");

	// Create Done button
	tgui::Button::Ptr button(gui);
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(55, 520);
	button->setText("Done");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(21);

	// Create the progressBar label
	tgui::Label::Ptr progressBarLabel(gui);
	progressBarLabel->setText("Progress");
	progressBarLabel->setTextColor(sf::Color::Black);
	progressBarLabel->setPosition(585, 510);

	tgui::LoadingBar::Ptr progressBar(gui, "boneProgress");
	progressBar->load("../TGUI/widgets/Black.conf");
	progressBar->setPosition(540, 550);
	progressBar->setSize(250, 30);
	progressBar->setValue(0);
}

void level2check(tgui::Gui& gui)
{
	tgui::LoadingBar::Ptr progress = gui.get("boneProgress");
	progress->setValue(0);

	tgui::ComboBox::Ptr temp = gui.get("Femur");
	int test = temp->getSelectedItemIndex();
	std::cout << test << std::endl;
	if (test == 0)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("Cranium");
	test = temp->getSelectedItemIndex();
	if (test == 1)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("Pelvis");
	test = temp->getSelectedItemIndex();
	if (test == 2)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("Humerus");
	test = temp->getSelectedItemIndex();
	if (test == 3)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("Carpals");
	test = temp->getSelectedItemIndex();
	if (test == 4)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("Patella");
	test = temp->getSelectedItemIndex();
	if (test == 5)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);
	
	temp = gui.get("Vertebrae");
	test = temp->getSelectedItemIndex();
	if (test == 6)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);
}

void level3(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/cell.gif");
	picture->setSize(800, 600);

	// Create the done button
	tgui::Button::Ptr doneButton(gui, "level3Done");
	doneButton->load("../TGUI/widgets/Black.conf");
	doneButton->setSize(260, 60);
	doneButton->setPosition(270, 500);
	doneButton->setText("Done");
	doneButton->bindCallback(tgui::Button::LeftMouseClicked);
	doneButton->setCallbackId(31);

	tgui::Tab::Ptr nucleusTab(gui, "nucleus");
	nucleusTab->load("../TGUI/widgets/Black.conf");
	nucleusTab->setPosition(5, 240);
	nucleusTab->setTabHeight(20);
	nucleusTab->add("nucleus");
	nucleusTab->add("mitochondria");
	nucleusTab->add("ribosome");

	tgui::Tab::Ptr erTab(gui, "er");
	erTab->load("../TGUI/widgets/Black.conf");
	erTab->setPosition(5, 175);
	erTab->setTabHeight(20);
	erTab->add("golgi");
	erTab->add("lysosome");
	erTab->add("endoplasmic reticulum");

	tgui::Tab::Ptr cmTab(gui, "cm");
	cmTab->load("../TGUI/widgets/Black.conf");
	cmTab->setPosition(5, 110);
	cmTab->setTabHeight(20);
	cmTab->add("lysosome");
	cmTab->add("cell membrane");
	cmTab->add("mitochondria");

	tgui::Tab::Ptr ribosomeTab(gui, "ribosome");
	ribosomeTab->load("../TGUI/widgets/Black.conf");
	ribosomeTab->setPosition(5, 420);
	ribosomeTab->setTabHeight(20);
	ribosomeTab->add("ribsome");
	ribosomeTab->add("endoplasmic reticulum");
	ribosomeTab->add("lysosome");

	tgui::Tab::Ptr golgiTab(gui, "golgi");
	golgiTab->load("../TGUI/widgets/Black.conf");
	golgiTab->setPosition(530, 350);
	golgiTab->setTabHeight(20);
	golgiTab->add("nucleus");
	golgiTab->add("cell membrane");
	golgiTab->add("golgi");

	tgui::Tab::Ptr mitochondriaTab(gui, "mitochondria");
	mitochondriaTab->load("../TGUI/widgets/Black.conf");
	mitochondriaTab->setPosition(500, 390);
	mitochondriaTab->setTabHeight(20);
	mitochondriaTab->add("mitochondria");
	mitochondriaTab->add("ribosome");
	mitochondriaTab->add("nucleus");


	tgui::Tab::Ptr lysosomeTab(gui, "lysosome");
	lysosomeTab->load("../TGUI/widgets/Black.conf");
	lysosomeTab->setPosition(470, 420);
	lysosomeTab->setTabHeight(20);
	lysosomeTab->add("golgi");
	lysosomeTab->add("lysosome");
	lysosomeTab->add("endoplasmic reticulum");

	// Create the progressBar label
	tgui::Label::Ptr progressBarLabel(gui);
	progressBarLabel->setText("Progress");
	progressBarLabel->setTextColor(sf::Color::Black);
	progressBarLabel->setPosition(580, 10);

	tgui::LoadingBar::Ptr progressBar(gui, "cellProgress");
	progressBar->load("../TGUI/widgets/Black.conf");
	progressBar->setPosition(530, 50);
	progressBar->setSize(250, 30);
	progressBar->setValue(0);
}

void level3check(tgui::Gui& gui)
{
	tgui::LoadingBar::Ptr progress = gui.get("cellProgress");
	progress->setValue(0);

	tgui::Tab::Ptr temp = gui.get("nucleus");
	int test = temp->getSelectedIndex();
	if (test == 0)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("er");
	test = temp->getSelectedIndex();
	if (test == 2)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}

	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("cm");
	test = temp->getSelectedIndex();
	if (test == 1)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("ribosome");
	test = temp->getSelectedIndex();
	if (test == 0)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("golgi");
	test = temp->getSelectedIndex();
	if (test == 2)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("mitochondria");
	test = temp->getSelectedIndex();
	if (test == 0)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	temp = gui.get("lysosome");
	test = temp->getSelectedIndex();
	if (test == 1)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	std::cout << "Level 3 Progress Is: " << progress->getValue() << std::endl;

	if (progress->getValue() == 98)
	{
		progress->setValue(100);
		gui.remove(gui.get("level3Done"));
		
		// Create the done button
		tgui::Button::Ptr nextButton(gui);
		nextButton->load("../TGUI/widgets/Black.conf");
		nextButton->setSize(260, 60);
		nextButton->setPosition(270, 500);
		nextButton->setText("Next");
		nextButton->bindCallback(tgui::Button::LeftMouseClicked);
		nextButton->setCallbackId(32);

		//tgui::Button::Ptr doneButton = gui.get("level3Done");
		//doneButton->setText("Next");
		//levelSelectionScreen(gui, 3);
		//doneButton->
		//doneButton->bindCallback(tgui::Button::LeftMouseClicked);
		//doneButton->setCallbackId(1);
		//levelComplete(3);
	}
}

//void levelComplete(int levelNumber)
//{

	// MySQL calls to update user progress 

	// Level Complete Animation 
//}

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
				// Load the bone level
				std::cout << "Loading Level 2" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level2(gui);
			}

			if (callback.id == 21)
			{
				// Check bone level's answers
				level2check(gui);
			}

			if (callback.id == 5)
			{
				std::cout << "Loading Level 3" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level3(gui);
			}

			if (callback.id == 31)
			{
				level3check(gui);
			}

			if (callback.id == 32)
			{
				levelSelectionScreen(gui, 3);
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