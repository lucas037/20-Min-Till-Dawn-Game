#include "Config.h"

float Config::stageTotalTime = 5.0f * 60 + 1.0f; // 5 min
float Config::timeToUpgrade = 5.0f;

int Config::numMaxEnemies = 250;

float Config::shotCountdown = 0.300f;
float Config::ReloadTime = 2.0f;
float Config::shotDamage = 40.0;
int Config::numMaxShots = 6;

float Config::minTimeToRecoverHp = stageTotalTime + 1; // impossível no início do jogo, libera-se com upgrade
float Config::dodgeChance = 0.0f;
