#ifndef							__SOUNDCONTROLLER_HH__
#define							__SOUNDCONTROLLER_HH__

#include 						"common.hh"
#include 						"SFML/Audio.hpp"

class 							SoundController
{
public:
	static SoundController 		*getInstance();
	static void 				playFxSound(const char *str);
	~SoundController();

	void 						initialize();
	void 						update();

	void 						playMusic();
	void						pauseMusic();
	void	 					stopMusic();

	void 						setInGame(bool);

	void 						changeTrackShuffle();

	void						playFx(const std::string &);
	
	void 						setVolumeMusic(float);
	float 						getVolumeMusic();

	void 						setVolumeFx(float);
	float 						getVolumeFx();

	void						playTrack(const std::string &);

private:
	SoundController();
	float 						_volumeMusic;
	float 						_volumeFx;

	bool 						_inGame;

	std::list<std::string> 		_menuMusicList;
	std::list<std::string>		_gameMusicList;

	std::list<std::string> 		_musicPlayed;
	
	std::list<std::string> 		_fxList;

	std::list<sf::Sound *>		_sounds;
	sf::Music 					*_music;

	std::string 				getTrackNameShuffle();
	bool 						checkValidFx(const std::string &);

	void						updateMusic();
	void	 					updateFx();
};

#endif
