#ifndef		__ENUM_HH__
#define		__ENUM_HH__

enum		ObjectType
  {
    OBJSPEC,
    EXPLOSION,
    TOXICCLOUD,
    OBJ,
    DESTRUCTIBLEWALL,
    UNDESTRUCTIBLEWALL,
    EMPTY,
    BONUS,
    BONUSSPEED, //bonus vitesse    ==>done
    BONUSSTOCK, //bonus stock bombe	==>done
    BONUSRANGE, //bonus portée		==>done
    BONUSCLAYMORE, //bonus mine		==>done
    BONUSROCKET, //bonus missile	==>done
    BONUSNUKE, //bonus bombe nucléaire	==>done
    BONUSTOXIC, //bonus bombe toxique	==>done
    BONUSSPIKE,//bonus bombe penetrante	==>done
    BONUSREMOTE, // bonus remote	==>done
    BONUSLIFE, //bonus vie		==>done
    BONUSSHIELD, //bonus invincible	==>done
    BONUSGHOST, //bonus ghost		==>donem
    BONUSHEALTH, //bonus santé		==>done
    BONUSRANDOM, // bonus random
    PLAYER, // player
    HUMANPLAYER, // player
    IAPLAYER, // player
    BOMB,
    BASICBOMB,
    TOXICBOMB,
    CLAYMORE,
    ROCKET,
    NUKEBOMB,
    SPIKEBOMB,
    REMOTEBOMB,
    END
  };

enum	difficulty
  {
    EASY = 2,
    MEDIUM = 3,
    HARD = 4
  };
//pour l'enum difficulté rajouter avec le chiffre + 1 , ne surtout pas mettre 0 ou 1
#endif
