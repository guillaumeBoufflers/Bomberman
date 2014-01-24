#include						"SoundController.hh"

SoundController::SoundController() : _volumeMusic(100), _volumeFx(40), _inGame(false)
{

}

SoundController 				*SoundController::getInstance() {
	static SoundController 		*instance = NULL;

	if (!instance)
		instance = new SoundController();
	return (instance);
}

SoundController::~SoundController()
{
	if (this->_music) {
		this->_music->Stop();
		delete this->_music;
	}
	for (std::list<sf::Sound *>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it) {
		(*it)->Stop();
		const sf::SoundBuffer *buffer = (*it)->GetBuffer();
		if (buffer)
			delete buffer;
		delete *it;
		it = this->_sounds.erase(it);
	}
}

void 							SoundController::update() {
	this->updateMusic();
	this->updateFx();
}

void 							SoundController::updateMusic() {
	if (this->_music && this->_music->GetStatus() == sf::Sound::Stopped)
		this->changeTrackShuffle();
}

void 							SoundController::updateFx() {
	for (std::list<sf::Sound *>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it) {
		if (*it && (*it)->GetStatus() == sf::Sound::Stopped) {
			const sf::SoundBuffer *buffer = (*it)->GetBuffer();
			if (buffer)
				delete buffer;
			delete *it;
			it = this->_sounds.erase(it);
		}
	}
}

void 							SoundController::setInGame(bool value) {
	if (value != this->_inGame) {
		this->_inGame = value;
		this->changeTrackShuffle();
	}
}

void 							SoundController::initialize() {
	this->_music = new sf::Music();
	if (!this->_music)
		exit(0);

	std::string folder;

	folder = "medias/sounds/music/human-after-all/";
	this->_menuMusicList.push_back(folder + "human-after-all.ogg");
	this->_menuMusicList.push_back(folder + "robot-rock.ogg");
	this->_menuMusicList.push_back(folder + "technologic.ogg");
	this->_menuMusicList.push_back(folder + "television-rules-the-nation.ogg");
	this->_menuMusicList.push_back(folder + "the-prime-time-of-your-life.ogg");

	folder = "medias/sounds/music/random-access-memories/";
	this->_menuMusicList.push_back(folder + "01-give-life-back-to-music.ogg");
	this->_menuMusicList.push_back(folder + "02-the-game-of-love.ogg");
	this->_menuMusicList.push_back(folder + "03-georgio-by-moroder.ogg");
	this->_menuMusicList.push_back(folder + "04-within.ogg");
	this->_menuMusicList.push_back(folder + "05-instant-crush.ogg");
	this->_menuMusicList.push_back(folder + "06-lose-yourself-to-dance.ogg");
	this->_menuMusicList.push_back(folder + "07-touch.ogg");
	this->_menuMusicList.push_back(folder + "08-get-lucky.ogg");
	this->_menuMusicList.push_back(folder + "09-beyond.ogg");
	this->_menuMusicList.push_back(folder + "10-motherboard.ogg");
	this->_menuMusicList.push_back(folder + "11-fragments-of-time.ogg");
	this->_menuMusicList.push_back(folder + "12-doin-it-right.ogg");
	this->_menuMusicList.push_back(folder + "13-contact.ogg");

	folder = "medias/sounds/music/discovery/";
	this->_menuMusicList.push_back(folder + "aerodynamic.ogg");
	this->_menuMusicList.push_back(folder + "face-to-face.ogg");
	this->_menuMusicList.push_back(folder + "harder-better-faster-stronger.ogg");
	this->_menuMusicList.push_back(folder + "one-more-time.ogg");
	this->_menuMusicList.push_back(folder + "too-long.ogg");

	folder = "medias/sounds/music/8-bit/";
	this->_gameMusicList.push_back(folder + "bittersweet-symphony.ogg");
	this->_gameMusicList.push_back(folder + "blue.ogg");
	this->_gameMusicList.push_back(folder + "call-me-maybe.ogg");
	this->_gameMusicList.push_back(folder + "crazy.ogg");
	this->_gameMusicList.push_back(folder + "daddy-cool.ogg");
	this->_gameMusicList.push_back(folder + "daddy-dj.ogg");
	this->_gameMusicList.push_back(folder + "everybody.ogg");
	this->_gameMusicList.push_back(folder + "just-an-illusion.ogg");
	this->_gameMusicList.push_back(folder + "levels.ogg");
	this->_gameMusicList.push_back(folder + "mr-vain.ogg");
	this->_gameMusicList.push_back(folder + "nightcall.ogg");
	this->_gameMusicList.push_back(folder + "pjanoo.ogg");
	this->_gameMusicList.push_back(folder + "thrift-shop.ogg");

	std::string fx = "medias/sounds/fx/";
	this->_fxList.push_back(fx + "explosion.ogg");
	this->_fxList.push_back(fx + "die.ogg");
	this->_fxList.push_back(fx + "nuke.ogg");

	this->playTrack(this->_menuMusicList.front());	
}

void 							SoundController::playMusic() {
	this->_music->Play();
}

void 							SoundController::pauseMusic() {
	this->_music->Pause();
}

void 							SoundController::stopMusic() {
	this->_music->Stop();
}

void 							SoundController::changeTrackShuffle() {
	std::string 				track = this->getTrackNameShuffle();
	this->playTrack(track);
}

void							SoundController::playTrack(const std::string &track) {
	this->_music->SetVolume(this->_volumeMusic);
	if (this->_music->GetStatus() == sf::Sound::Playing)
		this->stopMusic();
	if (this->_music->OpenFromFile(track))
		this->playMusic();
	else
		std::cout << "[SoundController] - Cannot load sound \"" << track << "\"" << std::endl;
}

void 							SoundController::playFxSound(const char *str) {
	SoundController 			*sound = SoundController::getInstance();

	std::string folder = "medias/sounds/fx/";
	std::string fx = str;
	sound->playFx(folder + fx);
}

void 							SoundController::playFx(const std::string &fx) {
	if (this->checkValidFx(fx)) {
		sf::SoundBuffer			*buffer;
		sf::Sound 				*sound;
		buffer = new sf::SoundBuffer();
		if (buffer->LoadFromFile(fx)) {
			sound = new sf::Sound(*buffer);
			sound->SetVolume(this->_volumeFx);
			sound->Play();
			this->_sounds.push_back(sound);
		} else {
			std::cout << "[SoundController] - Cannot load sound \"" << fx << "\"" << std::endl;
		}
	} else {
		std::cout << "[SoundController] - Cannot load sound \"" << fx << "\"" << std::endl;
	}
}

void 							SoundController::setVolumeMusic(float volume) {
	this->_volumeMusic = volume;
	this->_music->SetVolume(volume);
}

float 							SoundController::getVolumeMusic() {
	return (this->_volumeMusic);
}

void 							SoundController::setVolumeFx(float volume) {
	this->_volumeFx = volume;
	for (std::list<sf::Sound *>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it)
		if (*it && (*it)->GetStatus() == sf::Sound::Playing)
			(*it)->SetVolume(volume);
}

float 							SoundController::getVolumeFx() {
	return (this->_volumeFx);
}

std::string 					SoundController::getTrackNameShuffle() {
	if (!this->_inGame && this->_menuMusicList.size()) {
		std::list<std::string>::iterator randIt = this->_menuMusicList.begin();
		std::advance(randIt, std::rand() % this->_menuMusicList.size());
		return (*randIt);
	} else if (this->_gameMusicList.size()) {
		std::list<std::string>::iterator randIt = this->_gameMusicList.begin();
		std::advance(randIt, std::rand() % this->_gameMusicList.size());
		return (*randIt);
	}
	return ("");
}

bool							SoundController::checkValidFx(const std::string &fx) {
	for (std::list<std::string>::iterator it = this->_fxList.begin(); it != this->_fxList.end(); ++it)
		if ((*it) == fx)
			return (true);
	return (false);
}