#include "Config.h"

float Config::stageTotalTime = 5.0f * 60; // 5 min
float Config::timeToUpgrade = 1.0f; // 10 sec

int Config::numMaxEnemies = 250;

float Config::shotCountdown = 0.300f;
float Config::ReloadTime = 2.0f;
float Config::shotDamage = 40.0;
int Config::numMaxShots = 6;

float Config::minTimeToRecoverHp = stageTotalTime + 1; // impossível no início do jogo, libera-se com upgrade