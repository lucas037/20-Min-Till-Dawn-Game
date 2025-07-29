#ifndef CONFIG_H
#define CONFIG_H

class Config {
private:
public:
	static float stageTotalTime;
	static float timeToUpgrade;

	static int numMaxEnemies;

	static float shotCountdown;
	static float ReloadTime;
	static float shotDamage;
	static int numMaxShots;

	static float minTimeToRecoverHp;
};

#endif