/// Team Dark Matter
/// CS 3505: Prof David Johnson: Fall 2015
/// Team Members: Anne Aoki, Daniel Clyde, Alice Griffin, Igor Ivanov, April McCarrick, Brandon Tobin, Alex Whitelock

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Audio\Music.hpp>
#include <TGUI\TGUI.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <string>
#include <mysql.h>

// Change this number to change which level you have completed up until 
int level = 1;

// Message that will be displayed on login screen depending on login status
std::string loginMessage;
std::string loginMess2;

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

void loginScreen(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	// picture->load("../TGUI/examples/xubuntu_bg_aluminium.jpg");
	picture->load("../images/bio.jpg");
	picture->setSize(800, 600);

	// Create the levelSelect label
	tgui::Label::Ptr nameLabel(gui);
	nameLabel->setTextColor(sf::Color::Green);
	nameLabel->setTextSize(160);
	nameLabel->setTextStyle(sf::Text::Bold);
	nameLabel->setText("BioFun");
	nameLabel->setPosition(140, 30);

	tgui::Label::Ptr nameLabel2(gui);
	nameLabel2->setTextColor(sf::Color::White);
	nameLabel2->setTextSize(22);
	nameLabel2->setTextStyle(sf::Text::Bold);
	nameLabel2->setText("Brought to you by DarkMatter");
	nameLabel2->setPosition(235, 160);

	// Create the username label
	tgui::Label::Ptr labelUsername(gui);
	labelUsername->setText("Username:");
	labelUsername->setPosition(200, 200);

	// Create the password label
	tgui::Label::Ptr labelPassword(gui);
	labelPassword->setText("Password:");
	labelPassword->setPosition(200, 290);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername(gui, "Username");
	editBoxUsername->load("../TGUI/widgets/Black.conf");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(200, 230);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
	editBoxPassword->setPosition(200, 320);
	editBoxPassword->setPasswordCharacter('*');

	// Create the login button
	tgui::Button::Ptr button(gui);
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(270, 380);
	button->setText("Login");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	// Create the new account button 
	tgui::Button::Ptr newAccountButton(gui);
	newAccountButton->load("../TGUI/widgets/Black.conf");
	newAccountButton->setSize(260, 60);
	newAccountButton->setPosition(270, 455);
	newAccountButton->setText("New Account");
	newAccountButton->bindCallback(tgui::Button::LeftMouseClicked);
	newAccountButton->setCallbackId(2);

	// Create the status update label
	tgui::Label::Ptr labelStatus(gui, "StatusUpdate");
	labelStatus->setTextColor(sf::Color::Yellow);
	labelStatus->setTextSize(30);
	float messLength = loginMessage.length();
	labelStatus->setPosition(400 - ((messLength * 15) / 2), 530);
	labelStatus->setText(loginMessage);

	// Create the status update label
	tgui::Label::Ptr labelStatus2(gui, "StatusUpdate2");
	labelStatus2->setTextColor(sf::Color::Yellow);
	labelStatus2->setTextSize(30);
	float messLength2 = loginMess2.length();
	labelStatus2->setPosition(400 - ((messLength2 * 15) / 2), 560);
	labelStatus2->setText(loginMess2);
}

void levelSelectionScreen(tgui::Gui& gui, int levelNum)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/bio.jpg");
	picture->setSize(800, 600);

	// Create the levelSelect label
	tgui::Label::Ptr levelSelectLabel(gui);
	levelSelectLabel->setTextColor(sf::Color::Green);
	levelSelectLabel->setTextSize(60);
	levelSelectLabel->setTextStyle(sf::Text::Bold);
	levelSelectLabel->setText("Select your Level...");
	levelSelectLabel->setPosition(130, 100);

	tgui::SpriteSheet::Ptr spritesheet1(gui);
	tgui::SpriteSheet::Ptr spritesheet2(gui);
	tgui::SpriteSheet::Ptr spritesheet3(gui);

	switch (levelNum)
	{
	case 1:
		spritesheet1->load("../images/body.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 180);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton_lock.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 180);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(666);

		spritesheet3->load("../images/cell_lock.jpg");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 180);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(666);
		break;
	case 2:
		spritesheet1->load("../images/body_done.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 180);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton_edit.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 180);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(4);

		spritesheet3->load("../images/cell_lock.jpg");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 180);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(666);
		break;
	case 3:
		spritesheet1->load("../images/body_done.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 180);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton_done.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 180);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(4);

		spritesheet3->load("../images/cell.gif");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 180);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(5);
		break;
	case 4:
		spritesheet1->load("../images/body.jpg");
		spritesheet1->setSize(200, 140);
		spritesheet1->setPosition(25, 180);
		spritesheet1->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet1->setCallbackId(3);

		spritesheet2->load("../images/skeleton_edit.jpg");
		spritesheet2->setSize(200, 140);
		spritesheet2->setPosition(300, 180);
		spritesheet2->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet2->setCallbackId(4);

		spritesheet3->load("../images/cell.gif");
		spritesheet3->setSize(200, 140);
		spritesheet3->setPosition(575, 180);
		spritesheet3->bindCallback(tgui::Button::LeftMouseClicked);
		spritesheet3->setCallbackId(5);
		break;
	default:
		break;
	}

	// Create Level Labels
	tgui::Label::Ptr level1Label(gui);
	level1Label->setText("Level 1");
	level1Label->setPosition(65, 340);

	tgui::Label::Ptr level2label(gui);
	level2label->setText("Level 2");
	level2label->setPosition(340, 340);

	tgui::Label::Ptr level3label(gui);
	level3label->setText("Level 3");
	level3label->setPosition(615, 340);

	// Create the Return to Login Screen button
	tgui::Button::Ptr toLoginButton(gui, "ToLogin");
	toLoginButton->load("../TGUI/widgets/Black.conf");
	toLoginButton->setSize(260, 60);
	toLoginButton->setPosition(270, 390);
	toLoginButton->setText("Return to Login");
	toLoginButton->bindCallback(tgui::Button::LeftMouseClicked);
	toLoginButton->setCallbackId(8);

	// Create the Close button 
	tgui::Button::Ptr closeButton(gui, "Close");
	closeButton->load("../TGUI/widgets/Black.conf");
	closeButton->setSize(260, 60);
	closeButton->setPosition(270, 470);
	closeButton->setText("End Game");
	closeButton->bindCallback(tgui::Button::LeftMouseClicked);
	closeButton->setCallbackId(9);
}

/*
*	Helper method for Celebration that creates the ground for the Box2D physics engine
*/
void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((600.f / 2) / SCALE, (2.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

/*
*	Helper method for Celebration that creates the Box2D fixtures that the SFML textures are applied to
*	in the Box2D physics engine.
*/
void CreateBox(b2World& World, float X, float Y)
{
	// Random Confetti
	int _X = (rand() % 600) + 1;
	int _Y = (rand() % 160) + 1;

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(_X / SCALE, _Y / SCALE);
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

void celebration()
{
	// Number of confetti stars to make
	float stars = 100;

	/** Prepare the window */
	sf::RenderWindow childWindow(sf::VideoMode(600, 400, 32), "Celebrate!");
	childWindow.setFramerateLimit(60);
	tgui::Gui childGui(childWindow);

	/** Prepare the world */
	//b2Vec2 Gravity(0.f, 9.8f); // Earth gravity
	b2Vec2 Gravity(0.f, 4.8f);
	b2World World(Gravity);
	CreateGround(World, 300.f, 400.f);

	/** Prepare audio */
	sf::Music music;
	//if (!music.openFromFile("../audio/WooHoo.wav")) {
	//if (!music.openFromFile("../audio/Applause.wav")) {
	if (!music.openFromFile("../audio/Music_Box.wav")) {
		std::cout << "Music NOT Loaded" << std::endl;
	}
	else {
		std::cout << "Music Loaded" << std::endl;
	}
	music.play();

	/** Prepare textures */
	sf::Texture GroundTexture;
	GroundTexture.loadFromFile("ground.png");
	sf::Texture BoxTexture1;
	BoxTexture1.loadFromFile("../images/Confetti_goldStar.png");
	sf::Texture BoxTexture2;
	BoxTexture2.loadFromFile("../images/Confetti_blueStar.png");
	sf::Texture BoxTexture3;
	BoxTexture3.loadFromFile("../images/Confetti_greenStar.png");

	while (childWindow.isOpen())
	{
		CreateBox(World, 300.f, 100.f);
		World.Step(1 / 60.f, 8, 3);
		childWindow.clear(sf::Color::White);

		int BoxCount = 1;
		int BodyCount = 0;
		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				sf::Sprite Sprite;
				if (BoxCount == 1) {
					Sprite.setTexture(BoxTexture1); //gold
				}
				if (BoxCount == 2) {
					Sprite.setTexture(BoxTexture2); //blue
				}
				if (BoxCount == 3) {
					Sprite.setTexture(BoxTexture3); //green
					BoxCount = 0;
				}
				BoxCount++;

				Sprite.setOrigin(16.f, 16.f); // For 32x32 box
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				childWindow.draw(Sprite);

				BodyCount++;
				if (BodyCount == 120)
				{
					music.stop();
					childWindow.close();
				}
			}
			else
			{
				sf::Sprite GroundSprite;
				GroundSprite.setTexture(GroundTexture);
				GroundSprite.setOrigin(300.f, 1.f);
				GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				childWindow.draw(GroundSprite);
			}
		}
		// Congratulations text
		sf::Font font;
		font.loadFromFile("../images/Yikes!.ttf");

		sf::Text text1;
		text1.setFont(font);
		text1.setString("Congratulations!!!");
		text1.setColor(sf::Color::Black);
		text1.setStyle(sf::Text::Bold);
		text1.setCharacterSize(80);
		text1.setPosition(30, 100);
		text1.setStyle(sf::Text::Regular);
		childWindow.draw(text1);

		sf::Text text2;
		text2.setFont(font);
		text2.setString("Level Completed");
		text2.setColor(sf::Color::Black);
		text2.setStyle(sf::Text::Bold);
		text2.setCharacterSize(60);
		text2.setPosition(130, 200);
		text2.setStyle(sf::Text::Regular);
		childWindow.draw(text2);

		childWindow.display();
	}
}

void lockedScreen()
{
	/** Prepare audio */
	sf::Music music;
	//if (!music.openFromFile("../audio/Sad_Trombone.wav")) {
	//if (!music.openFromFile("../audio/Croud Boo 3.wav")) {
	if (!music.openFromFile("../audio/Cartoon Hop.wav")) {
		std::cout << "Sad Music NOT Loaded" << std::endl;
	}
	else {
		std::cout << "Sad Music Loaded" << std::endl;
	}
	music.play();
}

/*
*  Helper Method for making the "Combos" AKA "pull-down" menu selectors.  This method will create the combo and
*    populate it with the options for the player.
*
*  @param gui - GUI object, needed in this method for the purpose of creating the new combo within the game GUI
*  @param bodyPart - string containing the name of the body part to have its pull-down made
*  @param xPos - x position of the combo.  The combo should appear at the tail of the arrow on the background picture
*  @param yPos - y position of the combo on the screen.
*/
void makeComboHelper(tgui::Gui& gui, std::string bodyPart, float xPos, float yPos)
{
	tgui::ComboBox::Ptr Combo(gui, bodyPart);
	Combo->load("../TGUI/widgets/Black.conf");
	Combo->setSize(120, 21);
	Combo->setPosition(xPos, yPos);
	Combo->addItem("Toes");
	Combo->addItem("Knee");
	Combo->addItem("Shoulder");
	Combo->addItem("Head");
	Combo->addItem("Arm");
	Combo->addItem("Neck");
	Combo->addItem("Hand");
}

/*
*  Level 1 is a skin level level.  The body parts to label are skin deep (head, shoulders, knees, toes, etc).  This
*    method handles the creation and positioning of all objects on the screen.  This includes the background picture,
*    each pull-down menu, the "Submit" button and the progress bar.
*
*  @param gui - GUI object passed through representing the Game GUI
*/
void level1(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/body_arrow.jpg");
	picture->setSize(800, 600);

	//Make the pull-down selectors for each body part
	makeComboHelper(gui, "Head", 135, 78);
	makeComboHelper(gui, "Shoulder", 105, 215);
	makeComboHelper(gui, "Knee", 120, 445);
	makeComboHelper(gui, "Toes", 95, 530);
	makeComboHelper(gui, "Neck", 540, 190);
	makeComboHelper(gui, "Arm", 570, 290);
	makeComboHelper(gui, "Hand", 585, 365);

	// Create SubmitButton button
	tgui::Button::Ptr SubmitButton(gui, "SubmitButton");
	SubmitButton->load("../TGUI/widgets/Black.conf");
	SubmitButton->setSize(260, 60);
	SubmitButton->setPosition(530, 520);
	SubmitButton->setText("Submit");
	SubmitButton->bindCallback(tgui::Button::LeftMouseClicked);
	SubmitButton->setCallbackId(11);

	// Create Secret button
	tgui::Button::Ptr SecretPhase(gui);
	SecretPhase->load("../TGUI/widgets/Black.conf");
	SecretPhase->setSize(400, 150);
	SecretPhase->setPosition(200, 80);
	SecretPhase->hide();
	SecretPhase->setText("Proceed to Secret Phase!");
	SecretPhase->bindCallback(tgui::Button::LeftMouseClicked);
	SecretPhase->setCallbackId(12);

	// Create the progressBar label
	tgui::Label::Ptr progressBarLabel(gui);
	progressBarLabel->setText("Progress");
	progressBarLabel->setTextColor(sf::Color::Black);
	progressBarLabel->setPosition(580, 10);

	tgui::LoadingBar::Ptr progressBar(gui, "skinProgress");
	progressBar->load("../TGUI/widgets/Black.conf");
	progressBar->setPosition(530, 50);
	progressBar->setSize(250, 30);
	progressBar->setValue(0);
}

/*
*  Helper method for checking a level.  Checks the user's input(s) in pull-down menus for correctness.
*  Changes the color of the text based on correctness as well and updates the progress bar accordingly.
*
*  @param gui - GUI object passed along
*  @param bodyPart - string identifying which body part is being checked (which pull-down)
*  @param correctAnswer - int containing the correct answer for the pulldown.  To be compared with input(s)
*  @param progress - Keeps track of the progress bar and updates according to correctness and score
*/
void helpCheckLevel(tgui::Gui& gui, std::string bodyPart, int correctAnswer, tgui::LoadingBar::Ptr progress)
{
	//tgui::LoadingBar::Ptr progress = gui.get("skinProgress");
	tgui::ComboBox::Ptr temp = gui.get(bodyPart);
	int checkAnswer = temp->getSelectedItemIndex();

	if (checkAnswer == correctAnswer)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
	}
	else
		temp->setTextColor(sf::Color::Red);

	if (progress->getValue() == 98)
	{
		progress->setValue(100);
		gui.remove(gui.get("SubmitButton"));

		// Create the done button
		tgui::Button::Ptr nextButton(gui, "NextButton");
		nextButton->load("../TGUI/widgets/Black.conf");
		nextButton->setSize(260, 60);
		nextButton->setPosition(530, 520);
		nextButton->setText("Next");
		nextButton->bindCallback(tgui::Button::LeftMouseClicked);
		nextButton->setCallbackId(12);

		celebration();

		//Send stuff to database
	}
}
/*
*  This method will check for correctness of the user's input for level 1.  This method is a callback handler
*    for the "Submit" button in the skin level.  This method will change the color of the letters depending on correctness
*    as well as update the progress bar for the skin level
*/
void checkLevel1(tgui::Gui& gui)
{
	tgui::LoadingBar::Ptr progress = gui.get("skinProgress"); //get progress info from skin level
	progress->setValue(0); //Reinitialize to 0 in order to prevent double-points

	//Use Helper to check each pull-down option for correctness
	helpCheckLevel(gui, "Head", 3, progress);
	helpCheckLevel(gui, "Shoulder", 2, progress);
	helpCheckLevel(gui, "Knee", 1, progress);
	helpCheckLevel(gui, "Toes", 0, progress);
	helpCheckLevel(gui, "Neck", 5, progress);
	helpCheckLevel(gui, "Arm", 4, progress);
	helpCheckLevel(gui, "Hand", 6, progress);
}

void level2(tgui::Gui& gui){

	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/skeleton.jpg");
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
	tgui::Button::Ptr button(gui, "SubmitButton");
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(55, 520);
	button->setText("Submit");
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

	if (progress->getValue() == 98)
	{
		progress->setValue(100);
		gui.remove(gui.get("SubmitButton"));

		// Create the done button
		tgui::Button::Ptr nextButton(gui);
		nextButton->load("../TGUI/widgets/Black.conf");
		nextButton->setSize(260, 60);
		nextButton->setPosition(55, 520);
		nextButton->setText("Next");
		nextButton->bindCallback(tgui::Button::LeftMouseClicked);
		nextButton->setCallbackId(22);

		celebration();
	}
}

void level3(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/cell.gif");
	picture->setSize(800, 600);

	// Create the submit button
	tgui::Button::Ptr submitButton(gui, "level3Done");
	submitButton->load("../TGUI/widgets/Black.conf");
	submitButton->setSize(260, 60);
	submitButton->setPosition(270, 500);
	submitButton->setText("Submit");
	submitButton->bindCallback(tgui::Button::LeftMouseClicked);
	submitButton->setCallbackId(31);

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

		celebration();
	}
}

//void levelComplete(int levelNumber)
//{

// MySQL calls to update user progress 

// Level Complete Animation 
//}

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
	tgui::Gui gui(window);

	// Load the font (you should check the return value to make sure that it is loaded)
	gui.setGlobalFont("../TGUI/fonts/DejaVuSans.ttf");

	// Load the widgets
	loginScreen(gui);

	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;

	int state;

	//initialize mysql connection
	mysql_init(&mysql);

	//connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

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

				std::string username = editBoxUsername->getText();
				std::string password = editBoxPassword->getText();
				std::string command = "SELECT * FROM Users WHERE UserName = '" + username + "' AND Password = '" + password + "'";

				mysql_query(connection, command.c_str());
				result = mysql_store_result(connection);

				if ((row = mysql_fetch_row(result)))
				{
					int i = 0;
					bool admin = false;

					//Grabs all fields from Users table and traverses them
					while ((field = mysql_fetch_field(result)))
					{
						std::cout << field->name << ": " << row[i] << std::endl;						
						std::string temp = field->name;
						if (temp.compare("Admin") == 0){
							std::string admVal = row[i];
							admin = admVal.compare("1") == 0;
						}

						i++;
					}

					if (admin){
						std::cout << "User " << username << " is admin" << std::endl;
					}
					else{
						std::cout << "User " << username << " is not admin" << std::endl;
					}
					loginMessage = "Logged in successfully!";
					std::cout << loginMessage << std::endl;
					// This levelNum int will come from the database 
					levelSelectionScreen(gui, level);
				}
				else
				{
					//loginMessage = "Incorrect username and/or password. Please try again...";
					loginMessage = "Incorrect username and/or password.";
					loginMess2 = "Please try again...";
					std::cout << loginMessage << std::endl;
					loginScreen(gui);
				}
				mysql_free_result(result);
			}

			if (callback.id == 2)
			{
				// Get the username and password
				tgui::EditBox::Ptr editBoxUsername = gui.get("Username");
				tgui::EditBox::Ptr editBoxPassword = gui.get("Password");

				sf::String username = editBoxUsername->getText();
				sf::String password = editBoxPassword->getText();

				//Check if user exists
				std::string command = "SELECT * FROM Users WHERE UserName = '" + username + "'";

				mysql_query(connection, command.c_str());
				result = mysql_store_result(connection);

				if (!(row = mysql_fetch_row(result)))
				{
					std::string command = "INSERT INTO Users (Username, Password) VALUES ('" + username + "', '" + password + "')";
					mysql_query(connection, command.c_str());
					loginMessage = "Creating account...";
					std::cout << loginMessage << std::endl;
					//loginScreen(gui);
				}
				else
				{
					//loginMessage = "This username already exists. Please try again...";
					loginMessage = "This username already exists.";
					loginMess2 = "Please try again...";
					std::cout << loginMessage << std::endl;
					//loginScreen(gui);
				}

				mysql_free_result(result);
			}

			if (callback.id == 3)
			{
				std::cout << "Loading Level 1" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level1(gui);
			}

			if (callback.id == 4)
			{
				// Load the bone level
				std::cout << "Loading Level 2" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level2(gui);
			}

			if (callback.id == 5)
			{
				std::cout << "Loading Level 3" << std::endl;
				window.clear();
				gui.removeAllWidgets();
				level3(gui);
			}

			// Generated from "Return to Login" button on level selection screen
			if (callback.id == 8)
			{
				loginScreen(gui);
			}

			// Generated from "Exit" button on level selection screen
			if (callback.id == 9)
			{
				mysql_close(connection);
				window.close();
			}

			if (callback.id == 11)
			{
				checkLevel1(gui);
			}

			if (callback.id == 12)
			{
				levelSelectionScreen(gui, 2);
			}

			if (callback.id == 21)
			{
				// Check bone level's answers
				level2check(gui);
			}

			if (callback.id == 22)
			{
				levelSelectionScreen(gui, 3);
			}			

			if (callback.id == 31)
			{
				level3check(gui);
			}

			if (callback.id == 32)
			{
				levelSelectionScreen(gui, 4);
			}

			if (callback.id == 666)
			{
				lockedScreen();
			}
		}

		window.clear();

		// Draw all created widgets
		gui.draw();

		window.display();
	}


	mysql_close(connection);

	return EXIT_SUCCESS;
}
