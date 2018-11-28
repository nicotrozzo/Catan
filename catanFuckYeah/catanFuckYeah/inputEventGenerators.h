#pragma once

#include "bossFSMEvents.h"

enum implInputEvent : inputEventTypes {MOUSE_EVENT, KEYBOARD_EVENT};

class mouseEvent : public inputEv 
{
	//guarda coordenadas del click
	//guarda coordenadas del mouse en caso opcional
public:
	inputEventTypes getInputEvType() { return MOUSE_EVENT; }
};

class keyboardEvent : public inputEv
{
	//guarda tecla apretada
public:
	inputEventTypes getInputEvType() { return KEYBOARD_EVENT; }
};

class timerEvent : public inputEv
{
public:
	//capaz no tenga nada, a lo sumo un identificador
	inputEventTypes getInputEvType() { return TIMER_EVENT; }
};

class networkingEvent : public inputEv
{
	//valor hexa del paquete
	//string con info extra
public:
	inputEventTypes getInputEvType() { return NETWORKING_EVENT; }
};

class mouseEventGenerator : public eventGenerator
{

public:
	mouseEventGenerator();
	genericEvent * getEvent(void);

private:

};

class timerEventGenerator : public eventGenerator
{

public:
	timerEventGenerator(double speed);
	genericEvent * getEvent(void);

private:

};

class keyboardEventGenerator : public eventGenerator
{

public:
	keyboardEventGenerator();
	genericEvent * getEvent(void);

private:

};

/*class networkingEventGenerator : public eventGenerator
{

public:
	networkingEventGenerator();
	genericEvent * getEvent(void);

private:

};*/