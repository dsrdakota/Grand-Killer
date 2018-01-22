#include "movementSound.hpp"

#include "../../../../Manager/Sound.hpp"

movementSound::movementSound(Car *car)
{
	this->car = car;

	std::string pathToSounds = "data/Models/Cars/";
	std::string nameSound;

	switch (*car->getType())
	{
	case carType::Type::Ambulance:
		break;
	case carType::Type::Audi:
		break;
	case carType::Type::Black_viper:
		break;
	case carType::Type::Car:
		break;
	case carType::Type::Mini_truck:
		break;
	case carType::Type::Mini_van:
		break;
	case carType::Type::Police:
		break;
	case carType::Type::Taxi:

		pathToSounds += "Taxi/sound/";
		nameSound = "Taxi";

		break;
	case carType::Type::Truck:
		break;
	}

	isSetW = false;
	isSetS = false;

	accelerationSound = new sf::Sound(*soundManager::load(nameSound + "acceleration", pathToSounds + "Acceleration.wav"));
	brakingSound = new sf::Sound(*soundManager::load(nameSound + "braking", pathToSounds + "Braking.wav"));
	stopSound = new sf::Sound(*soundManager::load(nameSound + "stop", pathToSounds + "Stop.wav"));
}

movementSound::~movementSound()
{
	delete accelerationSound;
	delete brakingSound;
	delete stopSound;
}

void movementSound::play()
{
	if (car->getSpeed() > 0)
	{
		stopSound->stop();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isSetW)
		{
			if (accelerationSound->getStatus() == sf::Sound::Stopped ||
				accelerationSound->getStatus() == sf::Sound::Paused)
				accelerationSound->play();
			accelerationSound->setPlayingOffset(sf::seconds(car->getSpeed() * 9.f / car->getMaxSpeed()));

			isSetW = true;
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isSetW || accelerationSound->getStatus() == sf::Sound::Stopped)
		{
			accelerationSound->pause();
			isSetW = false;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isSetS)
		{
			if (brakingSound->getStatus() == sf::Sound::Stopped ||
				brakingSound->getStatus() == sf::Sound::Paused)
				brakingSound->play();
			brakingSound->setPlayingOffset(sf::seconds((18.f - car->getSpeed()) * 9.f / 18.f));
			isSetS = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isSetS || brakingSound->getStatus() == sf::Sound::Stopped)
		{
			brakingSound->pause();
			isSetS = false;
		}
	}
	else
	{
		accelerationSound->stop();
		brakingSound->stop();
		if (stopSound->getStatus() != sf::Sound::Playing)
			stopSound->play();
	}

	if (time.time->asSeconds() >= 0.5)
	{
		if (accelerationSound->getStatus() == sf::Sound::Playing)
			accelerationSound->setPlayingOffset(sf::seconds(car->getSpeed() * 9.f / car->getMaxSpeed()));
		else if (brakingSound->getStatus() == sf::Sound::Playing)
			brakingSound->setPlayingOffset(sf::seconds((18.f - car->getSpeed()) * 9.f / 18.f));

		*time.time = sf::Time::Zero;
		time.clock->restart();
	}
}
