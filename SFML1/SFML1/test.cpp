/// Team Dark Matter
/// CS 3505: Prof David Johnson: Fall 2015
/// Team Members: Anne Aoki, Daniel Clyde, Alice Griffin, Igor Ivanov, April McCarrick, Brandon Tobin, Alex Whitelock

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Audio\Music.hpp>
#include <SFML\Network.hpp>
#include <stdlib.h>
#include <list>
#pragma comment(lib, "sfml-network.lib")
#include <TGUI\TGUI.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>
#include <sstream>
using namespace std;


// Message that will be displayed on login screen depending on login status
std::string loginMessage;
std::string loginMess2;

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

sf::TcpSocket socket2;
const unsigned short PORT = 5000;

struct PackStruct
{
	std::string connType;
	std::string userName;
	std::string password;
	bool admin = false;
	bool authorized = false;
	bool alreadyExist = false;
	int level = -2;
};

PackStruct clearStruct(PackStruct p)
{
	p.connType = "";
	p.userName = "";
	p.password = "";
	p.admin = false;
	p.authorized = false;
	p.alreadyExist = false;
	int level = -2;

	return p;
}

sf::Packet& operator >>(sf::Packet& Packet, PackStruct& P)
{
	return Packet >> P.connType >> P.userName >> P.password >> P.admin >> P.authorized >> P.level >> P.alreadyExist;
}

sf::Packet& operator <<(sf::Packet& Packet, const PackStruct& P)
{
	return Packet << P.connType << P.userName << P.password << P.admin << P.authorized << P.level << P.alreadyExist;
}

void loginScreen(tgui::Gui& gui)
{
	gui.removeAllWidgets();
	// Create the background image
	tgui::Picture::Ptr picture(gui);
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
	//editBoxUsername->setText("");
	editBoxUsername->setSize(400, 40);
	editBoxUsername->setPosition(200, 230);

	// Create the password edit box (we will copy the previously created edit box)
	tgui::EditBox::Ptr editBoxPassword = gui.copy(editBoxUsername, "Password");
	//editBoxPassword->setText("");
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
	int messLength = loginMessage.length();
	labelStatus->setPosition(400 - ((messLength * 15) / 2), 530);
	labelStatus->setText(loginMessage);

	// Create the status update label
	tgui::Label::Ptr labelStatus2(gui, "StatusUpdate2");
	labelStatus2->setTextColor(sf::Color::Yellow);
	labelStatus2->setTextSize(30);
	int messLength2 = loginMess2.length();
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

		spritesheet3->load("../images/cell_done.jpg");
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
	level1Label->setTextColor(sf::Color::Green);
	level1Label->setText("Body Level");
	level1Label->setPosition(50, 335);

	tgui::Label::Ptr level2label(gui);
	level2label->setTextColor(sf::Color::Green);
	level2label->setText("Bones Level");
	level2label->setPosition(310, 335);

	tgui::Label::Ptr level3label(gui);
	level3label->setTextColor(sf::Color::Green);
	level3label->setText("Cell Level");
	level3label->setPosition(610, 335);


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
	float stars = 200;

	/** Prepare the window */
	sf::RenderWindow childWindow(sf::VideoMode(600, 600, 32), "Celebrate!");
	childWindow.setFramerateLimit(60);
	tgui::Gui childGui(childWindow);

	/** Prepare the world */
	b2Vec2 Gravity(0.f, 4.8f);
	b2World World(Gravity);
	CreateGround(World, 300.f, 600.f);

	/** Prepare audio */
	sf::Music music;
	music.openFromFile("../audio/Applause.wav");

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
				if (BodyCount == stars)
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

void lockedScreen(tgui::Gui& gui)
{	
	// Prepare audio
	sf::Music music;
	if (!music.openFromFile("../audio/Cartoon Hop.wav")) {
		std::cout << "Sad Music NOT Loaded" << std::endl;
	}
	else {
		std::cout << "Sad Music Loaded" << std::endl;
	}
	music.play();
}

void teacherScreen(tgui::Gui& gui, sf::Packet p)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/bio.jpg");
	picture->setSize(800, 600);


	tgui::ListBox::Ptr listBox(gui, "userbox");
	listBox->load("../TGUI/widgets/Black.conf");
	listBox->setSize(260, 400);
	listBox->setPosition(270, 40);

	// Create the login button
	tgui::Button::Ptr deleteButton(gui);
	deleteButton->load("../TGUI/widgets/Black.conf");
	deleteButton->setSize(260, 60);
	deleteButton->setPosition(270, 455);
	deleteButton->setText("Delete");
	deleteButton->bindCallback(tgui::Button::LeftMouseClicked);
	deleteButton->setCallbackId(100);

	// Create the HTML button
	tgui::Button::Ptr htmlButton(gui);
	htmlButton->load("../TGUI/widgets/Black.conf");
	htmlButton->setSize(260, 60);
	htmlButton->setPosition(270, 530);
	htmlButton->setText("Generate HTML");
	htmlButton->bindCallback(tgui::Button::LeftMouseClicked);
	htmlButton->setCallbackId(101);

	sf::Uint32 size;
	p >> size;
	for (sf::Uint32 i = 0; i < size; i++)
	{
		std::string user;
		p >> user;
		listBox->addItem(user);
	}
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
void makeComboHelper(tgui::Gui& gui, int level, std::string bodyPart, float xPos, float yPos)
{
	tgui::ComboBox::Ptr Combo(gui, bodyPart);
	Combo->load("../TGUI/widgets/Black.conf");
	Combo->setSize(120, 21);
	Combo->setPosition(xPos, yPos);
	if (level == 1){
		Combo->addItem("Toes");
		Combo->addItem("Knee");
		Combo->addItem("Shoulder");
		Combo->addItem("Head");
		Combo->addItem("Arm");
		Combo->addItem("Neck");
		Combo->addItem("Hand");
	}
	else if (level == 2){
		Combo->addItem("Femur");
		Combo->addItem("Cranium");
		Combo->addItem("Pelvis");
		Combo->addItem("Humerus");
		Combo->addItem("Carpals");
		Combo->addItem("Patella");
		Combo->addItem("Vertebrae");
	}
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

	// Create the Return to LevelSelectScreen button
	tgui::Button::Ptr toLevelsButton(gui, "BackButton1");
	toLevelsButton->load("../TGUI/widgets/Black.conf");
	toLevelsButton->setSize(100, 50);
	toLevelsButton->setPosition(20, 60);
	toLevelsButton->setText("Back");
	toLevelsButton->bindCallback(tgui::Button::LeftMouseClicked);
	toLevelsButton->setCallbackId(10);

	// Create the Level description label
	tgui::Label::Ptr descriptionLabel(gui);
	descriptionLabel->setTextColor(sf::Color::Blue);
	descriptionLabel->setTextSize(22);
	descriptionLabel->setText("Use the drop-down menus to label the body parts the arrows point to.");
	descriptionLabel->setPosition(10, 10);


	// Make the pull-down selectors for each body part
	int level = 1; // first level is skin level
	makeComboHelper(gui, level, "Head", 135, 78);
	makeComboHelper(gui, level, "Shoulder", 105, 215);
	makeComboHelper(gui, level, "Knee", 120, 445);
	makeComboHelper(gui, level, "Toes", 95, 530);
	makeComboHelper(gui, level, "Neck", 540, 190);
	makeComboHelper(gui, level, "Arm", 570, 290);
	makeComboHelper(gui, level, "Hand", 585, 365);

	// Create SubmitButton button
	tgui::Button::Ptr SubmitButton(gui, "SubmitButton");
	SubmitButton->load("../TGUI/widgets/Black.conf");
	SubmitButton->setSize(260, 60);
	SubmitButton->setPosition(530, 520);
	SubmitButton->setText("Submit");
	SubmitButton->bindCallback(tgui::Button::LeftMouseClicked);
	SubmitButton->setCallbackId(11);

	// Create Secret button
	/* Secret Phase coming in version 2.0, pre-purchase DLC at your local Circuit City!! */
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
	progressBarLabel->setPosition(585, 55);
	tgui::LoadingBar::Ptr progressBar(gui, "skinProgress");
	progressBar->load("../TGUI/widgets/Black.conf");
	progressBar->setPosition(530, 85);
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

bool helpCheckLevel(tgui::Gui& gui, std::string bodyPart, int correctAnswer, tgui::LoadingBar::Ptr progress, int callbackID)
{
	// Copy the level type into a temp and get the correct answer (for levels 1 and 2)
	tgui::ComboBox::Ptr temp = gui.get(bodyPart);
	// Get player's answer
	int checkAnswer = temp->getSelectedItemIndex();
	// Boolean return value
	bool correct = false;

	// Check the correctness of the player's selection
	if (checkAnswer == -1){ // If no selection has been made, don't change word color
		return false;
	}
	else if (checkAnswer == correctAnswer)
	{
		temp->setTextColor(sf::Color::Green);
		int val = progress->getValue();
		val = val + 100 / 7;
		progress->setValue(val);
		correct = true;
	}
	else
	{
		temp->setTextColor(sf::Color::Red);
		correct = false;
	}

	// Update Progress Bar, Complete level if necessary
	if (progress->getValue() == 98)
	{
		progress->setValue(100);
		celebration();

		gui.remove(gui.get("SubmitButton"));

		// Create the done button
		tgui::Button::Ptr nextButton(gui, "NextButton");
		nextButton->load("../TGUI/widgets/Black.conf");
		nextButton->setSize(260, 60);
		nextButton->setPosition(530, 520);
		nextButton->setText("Next");
		nextButton->bindCallback(tgui::Button::LeftMouseClicked);
		nextButton->setCallbackId(callbackID);
	}
	// Set Return Value
	if (correct == true)
		return true;
	else
		return false;
}
/*
*  This method will check for correctness of the user's input for level 1.  This method is a callback handler
*    for the "Submit" button in the skin level.  This method will change the color of the letters depending on correctness
*    as well as update the progress bar for the skin level
*/
//void level1check(tgui::Gui& gui)
bool level1check(tgui::Gui& gui)
{
	tgui::LoadingBar::Ptr progress = gui.get("skinProgress"); //get progress info from skin level
	progress->setValue(0); //Reinitialize to 0 in order to prevent double-points

	int count = 0;
	int callbackID = 12;
	if (helpCheckLevel(gui, "Head", 3, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Shoulder", 2, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Knee", 1, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Toes", 0, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Neck", 5, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Arm", 4, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Hand", 6, progress, callbackID))
		count++;

	// If all combo boxes have the correct answer (player succeeded in beating level), return true otherwise return false.
	if (count == 7)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
*	
*/
void level2(tgui::Gui& gui){

	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/skeleton.jpg");
	picture->setSize(800, 600);

	// Create the Return to LevelSelectScreen button
	tgui::Button::Ptr toLevelsButton(gui, "BackToLevelSelect");
	toLevelsButton->load("../TGUI/widgets/Black.conf");
	toLevelsButton->setSize(100, 50);
	toLevelsButton->setPosition(680, 20);
	toLevelsButton->setText("Back");
	toLevelsButton->bindCallback(tgui::Button::LeftMouseClicked);
	toLevelsButton->setCallbackId(10);


	int level = 2; // Second level
	makeComboHelper(gui, level, "Femur", 150, 350);
	makeComboHelper(gui, level, "Cranium", 130, 27);
	makeComboHelper(gui, level, "Pelvis", 559, 273);
	makeComboHelper(gui, level, "Humerus", 52, 128);
	makeComboHelper(gui, level, "Carpals", 65, 250);
	makeComboHelper(gui, level, "Patella", 595, 400);
	makeComboHelper(gui, level, "Vertebrae", 538, 178);


	// Create Submit button
	tgui::Button::Ptr button(gui, "SubmitButton");
	button->load("../TGUI/widgets/Black.conf");
	button->setSize(260, 60);
	button->setPosition(20, 520);
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

bool level2check(tgui::Gui& gui)
{
	tgui::LoadingBar::Ptr progress = gui.get("boneProgress");
	progress->setValue(0);

	int count = 0;
	int callbackID = 22;
	if (helpCheckLevel(gui, "Femur", 3, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Cranium", 2, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Pelvis", 1, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Humerus", 0, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Carpals", 5, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Patella", 4, progress, callbackID))
		count++;
	if (helpCheckLevel(gui, "Vertebrae", 6, progress, callbackID))
		count++;

	// If all combo boxes have the correct answer (player succeeded in beating level), return true otherwise return false.
	if (count == 7)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void level3(tgui::Gui& gui)
{
	// Create the background image
	tgui::Picture::Ptr picture(gui);
	picture->load("../images/cell.gif");
	picture->setSize(800, 600);

	// Create the Return to LevelSelectScreen button
	tgui::Button::Ptr toLevelsButton(gui, "BackButton3");
	toLevelsButton->load("../TGUI/widgets/Black.conf");
	toLevelsButton->setSize(100, 50);
	toLevelsButton->setPosition(610, 140);
	toLevelsButton->setText("Back");
	toLevelsButton->bindCallback(tgui::Button::LeftMouseClicked);
	toLevelsButton->setCallbackId(10);

	// Create the Level description label
	tgui::Label::Ptr descriptionLabel(gui);
	descriptionLabel->setTextColor(sf::Color::Blue);
	descriptionLabel->setTextSize(27);
	descriptionLabel->setText("Select the best answer from choices for each cell part.");
	descriptionLabel->setPosition(30, 10);

	// Create the progressBar label
	tgui::Label::Ptr progressBarLabel(gui);
	progressBarLabel->setText("Progress");
	progressBarLabel->setTextColor(sf::Color::Black);
	progressBarLabel->setPosition(590, 60);

	tgui::LoadingBar::Ptr progressBar(gui, "cellProgress");
	progressBar->load("../TGUI/widgets/Black.conf");
	progressBar->setPosition(530, 100);
	progressBar->setSize(250, 30);
	progressBar->setValue(0);

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
	nucleusTab->setTabHeight(20);
	nucleusTab->setPosition(5, 240);
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
}

bool level3check(tgui::Gui& gui)
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
		celebration();

		gui.remove(gui.get("level3Done"));

		// Create the done button
		tgui::Button::Ptr nextButton(gui);
		nextButton->load("../TGUI/widgets/Black.conf");
		nextButton->setSize(260, 60);
		nextButton->setPosition(270, 500);
		nextButton->setText("Next");
		nextButton->bindCallback(tgui::Button::LeftMouseClicked);
		nextButton->setCallbackId(32);
		return true;
	}
	else
		return false;
}

string header(){
	return "<!DOCTYPE html><html><head>";
}
string style(){
	return "<style>h1{color: blue;font-family: verdana;font-size: 300%;}table, th, td{border: 1px solid black;	border - collapse: collapse;}th, td{padding: 5px;}th{text - align: left;}</style></head>";
}
string title(string s){
	return "<h1><center>" + s + "</center></h1>";
}
string bodyTabel(){
	return "<center><table style=\"width:100 % \"><center><tr><th>Firstname</th><th>Password</th><th>Current Level</th></tr>";

}
string tableEntry(string name, string password, string level){
	return "<tr><td>" + name + "</td><td>" + password + "</td><td>" + level + "</td>";
}

string footer(){
	return"</body></html>";
}
/* This method will turn any integer to a string for printing to the HTML file */
string intToString(int numToString){
	std::stringstream sstm;
	sstm << numToString;
	return sstm.str();
}
/**
*Helper method to get users from database and put them in tabel for html report
*/
std::list<std::string> getUsers(){
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT `Username` FROM `Users`";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	std::list<std::string> users;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		users.push_back(row[0]);
	}
	mysql_free_result(result);
	mysql_close(connection);

	return users;
}


/**
*Helper method to get Passwords from database and put them in tabel for html report
*/
std::list<std::string> getPassword(){
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT `Password` FROM `Users`";

	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	std::list<std::string> password;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		password.push_back(row[0]); //Add the elements to a list that can be returned and itterated over.
	}
	mysql_free_result(result);
	mysql_close(connection);

	return password;
}




/**
*Helper method to get level from database and put them in tabel for html report
*/
std::list<std::string> getLevel(){
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	MYSQL *connection, mysql;

	// Initialize mysql connection
	mysql_init(&mysql);

	// Connect params: connection, domain, username, password, dbName, port, socket, clientFlag
	connection = mysql_real_connect(&mysql, "db4free.net", "darkmatter", "darkmatter", "biofun", 3306, 0, 0);

	std::string command = "SELECT `GameLevel` FROM `Users`";


	mysql_query(connection, command.c_str());
	result = mysql_store_result(connection);

	std::list<std::string> level;
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		level.push_back(row[0]);
	}
	mysql_free_result(result);
	mysql_close(connection);

	return level;
}


/**
*  This method is a helper for formatting the HTML file in the correct fashion.  3 colmums, Username::Password::Level Progress for
*  each user in the database.  Takes in a packet from the server containing all of the user information from the server and uses
*  that packet to populate the table.
*/
void makeHtml(sf::Packet pack)
{
	std::list<std::string> users = getUsers();
	std::list<std::string> password = getPassword();
	std::list<std::string> level = getLevel();
	ofstream myfile;
	myfile.open("..\\TeacherReport.html");//Create a .thml file to write to.
	myfile << header();//Html code made by calling methods to break up the parts to allow easy modifications
	myfile << style();
	myfile << "<body>";
	myfile << title("Class Report");
	myfile << bodyTabel();//Open te tabel
	int i = 0;
	
	std::list<std::string>::const_iterator userIt = users.begin();
	std::list<std::string>::const_iterator passIt = password.begin();
	std::list<std::string>::const_iterator levelIt = level.begin();
	for (; userIt != users.end() && passIt != password.end() && levelIt != level.end(); userIt++, passIt++, levelIt++)
	{
		/* THIS IS THE LINE TO CHANGE (intToString(i) should be the level information of the user) */
		myfile << tableEntry(*userIt, *passIt, *levelIt);//TODO Change "Name", "Password", and the input to "intToString()" to the appropriate information for each person in the database
		/* THIS IS THE LINE TO CHANGE Change the loop limit also to be just however many people are in the databse */
		i++;
	}
	myfile << "</center></table></center>"; //Close the table
	myfile << footer();
}

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
	tgui::Gui gui(window);

	// Load the font (you should check the return value to make sure that it is loaded)
	gui.setGlobalFont("../TGUI/fonts/DejaVuSans.ttf");

	// Establish connection to the SFML server

	sf::IpAddress Address1 = sf::IpAddress::getLocalAddress();

	if (socket2.connect(Address1, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected to the SFML server \n" << std::endl;
	}
	else
	{
		std::cout << "Could not establish connection \n" << std::endl;
		std::cout << "Program will terminate \n" << std::endl;
		exit(0);
	}

	// Load the widgets
	loginScreen(gui);

	// Struct for keeping track of user data
	PackStruct tobeSent;
	
	int level = 0;
	std::string user;

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
			// Login button
			if (callback.id == 1)
			{
				// Get the username and password
				tgui::EditBox::Ptr editBoxUsername = gui.get("Username");
				tgui::EditBox::Ptr editBoxPassword = gui.get("Password");

				std::string username = editBoxUsername->getText();
				std::string password = editBoxPassword->getText();

				tobeSent.connType = "LOGIN";
				tobeSent.userName = username;
				tobeSent.password = password;

				sf::Packet pack;
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;

					if (tobeSent.authorized == true)
					{
						user = tobeSent.userName;
						loginMessage.clear();
						loginMess2.clear();
						loginMessage = "Logged in successfully!";

						if (tobeSent.admin == true)
						{
							pack.clear();

							tobeSent.connType = "USERS";
			
							sf::Packet pack;
							pack << tobeSent;

							socket2.send(pack);

							pack.clear();
							if (socket2.receive(pack) == sf::Socket::Done)
							{
								teacherScreen(gui, pack);
							}
						}
						else
						{
							levelSelectionScreen(gui, tobeSent.level);
						}
						
					}
					else
					{
						loginMessage.clear();
						loginMess2.clear();
						loginMessage = "Incorrect username and/or password.";
						loginMess2 = "Please try again...";
						tobeSent = clearStruct(tobeSent);
						std::cout << loginMessage << std::endl;
						loginScreen(gui);
					}
				}
			}

			// New Account Button
			if (callback.id == 2)
			{
				// Get the username and password
				tgui::EditBox::Ptr editBoxUsername = gui.get("Username");
				tgui::EditBox::Ptr editBoxPassword = gui.get("Password");

				sf::String username = editBoxUsername->getText();
				sf::String password = editBoxPassword->getText();

				// Do not allow user to be created with BLANK username or password
				if (username != "" || password != "")
				{

					//PackStruct tobeSent;
					tobeSent.connType = "NEWACCT";
					tobeSent.userName = username;
					tobeSent.password = password;

					sf::Packet pack;
					pack << tobeSent;

					socket2.send(pack);

					pack.clear();

					if (socket2.receive(pack) == sf::Socket::Done)
					{
						pack >> tobeSent;

						if (tobeSent.alreadyExist == false)
						{
							loginMessage.clear();
							loginMess2.clear();
							loginMessage = "Creating account...";
							std::cout << loginMessage << std::endl;
							levelSelectionScreen(gui, 1); // Start at Level=1 when creating new user
						}
						else
						{
							loginMessage.clear();
							loginMess2.clear();
							loginMessage = "This username already exists.";
							loginMess2 = "Please try again...";
							std::cout << loginMessage << std::endl;
							loginScreen(gui);
						}
					}
				}
				else
				{
					loginMessage.clear();
					loginMess2.clear();
					loginMessage = "Please enter Valid Login and Password";
					std::cout << loginMessage << std::endl;
					loginScreen(gui);
				}				
			}

			if (callback.id == 3)
			{
				window.clear();
				gui.removeAllWidgets();
				level1(gui);
			}

			if (callback.id == 4)
			{
				// Load the bone level
				window.clear();
				gui.removeAllWidgets();
				level2(gui);
			}

			if (callback.id == 5)
			{
				window.clear();
				gui.removeAllWidgets();
				level3(gui);
			}

			// Generated from "Return to Login" button on level selection screen
			if (callback.id == 8)
			{
				loginMessage.clear();
				loginMess2.clear();
				gui.removeAllWidgets();
				tobeSent = clearStruct(tobeSent);
				loginScreen(gui);
			}

			// Generated from "Exit" button on level selection screen
			if (callback.id == 9)
			{
				window.close();
			}

			// Back to LevelSelectionScreen from Level 1
			if (callback.id == 10)
			{
				sf::Packet pack;
				tobeSent.connType = "GAMELEVEL";
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;
					level = tobeSent.level;
					levelSelectionScreen(gui, level);
				}
			}

			if (callback.id == 11)
			{
				if (level1check(gui))
				{
					sf::Packet pack;
					tobeSent.connType = "ADVANCELEVEL1";
					pack << tobeSent;

					socket2.send(pack);

					pack.clear();

					if (socket2.receive(pack) == sf::Socket::Done)
					{
						pack >> tobeSent;
						level = tobeSent.level;
						levelSelectionScreen(gui, level);
					}
				}
			}

			if (callback.id == 12)
			{
				sf::Packet pack;
				tobeSent.connType = "GAMELEVEL";
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;
					level = tobeSent.level;
					levelSelectionScreen(gui, level);
				}
			}

			if (callback.id == 21)
			{

				if (level2check(gui))
				{
					sf::Packet pack;
					tobeSent.connType = "ADVANCELEVEL2";
					pack << tobeSent;

					socket2.send(pack);

					pack.clear();

					if (socket2.receive(pack) == sf::Socket::Done)
					{
						pack >> tobeSent;
						level = tobeSent.level;
						levelSelectionScreen(gui, level);
					}
				}
			}

			if (callback.id == 22)
			{
				sf::Packet pack;
				tobeSent.connType = "GAMELEVEL";
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;
					level = tobeSent.level;
					levelSelectionScreen(gui, level);
				}
			}

			if (callback.id == 31)
			{
				if (level3check(gui))
				{
					sf::Packet pack;
					tobeSent.connType = "ADVANCELEVEL3";
					pack << tobeSent;

					socket2.send(pack);

					pack.clear();

					if (socket2.receive(pack) == sf::Socket::Done)
					{
						pack >> tobeSent;
						level = tobeSent.level;
						levelSelectionScreen(gui, level);
					}
				}
			}

			if (callback.id == 32)
			{
				sf::Packet pack;
				tobeSent.connType = "GAMELEVEL";
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;
					level = tobeSent.level;
					levelSelectionScreen(gui, level);
				}
			}

			if (callback.id == 100)
			{
				
				tgui::ListBox::Ptr temp = gui.get("userbox");
				std::string name = temp->getSelectedItem();

				PackStruct deleteStruct;
				deleteStruct.connType = "DELETE";
				deleteStruct.userName = name;

				sf::Packet pack;
				
				pack << deleteStruct;

				socket2.send(pack);

				pack.clear();

				temp->removeItem(name);

			}
			if (callback.id == 101)
			{
				//**********TODO input what you need from the server class to get the name, password, and levelInfo to print the HTML file*************
				sf::Packet pack;
				tobeSent.connType = "HTMLREPORT";
				pack << tobeSent;

				socket2.send(pack);

				pack.clear();

				if (socket2.receive(pack) == sf::Socket::Done)
				{
					pack >> tobeSent;
					//level = tobeSent.level;
					//levelSelectionScreen(gui, level);
				}
				// PackStruct to keep track of each player.  Get each player's Name, Password, and Level progress to print to HTML file
//				sf::Packet pack; // Packet should contain all of the users to print to the HTML file
				makeHtml(pack); // makeHtml is a method that formats an HTML file.  It prints a table containing usernames, passwords, and level info
			}

			if (callback.id == 666)
			{
				lockedScreen(gui);
			}
		}
		window.clear();

		// Draw all created widgets
		gui.draw();
		window.display();
	}

	return EXIT_SUCCESS;
}