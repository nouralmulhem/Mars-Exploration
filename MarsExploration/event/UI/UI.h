#pragma once
#ifndef _UI_H
#define _UI_H

#include<iostream>
#include<sstream>
#include<string>
#include <conio.h>
#include <stdio.h>
#include<stdlib.h>

#include <Windows.h>
#include"..\ADT\LinkedQueue.h"
using namespace std;
class MarsStation; // forward decleration of class MarsStation
class UI
{

private:
	MarsStation* M;
public:
	UI(MarsStation* ptr);
	void PrintMsg (string );
	string ReadInput();
	int Readint();
	void print_day();
	void InterMode();
	void select_mode();
	void StepMode();
	void SilentMode();
	void print1(LinkedQueue<int>& dummy);
	void print2(LinkedQueue<int>& dummy);

	// the functionality of all functions written with its definition in CPP 
};

#endif



