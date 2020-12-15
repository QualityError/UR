#pragma once


//ai
const int human = 0;
const int randomAI = 1;
const int basicAI = 2;
const int safetyAI = 3;

int humanChoice(int roll, int side);
int randomAi(int roll, int side);
int basicAi(int roll, int side);
int basicSafetyAi(int roll, int side);
