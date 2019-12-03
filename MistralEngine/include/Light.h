#ifndef LIGHT_H
#define LIGHT_H
#pragma once
#include <string>
#include "MistralEngine.h"
#include "GameObjects.h"


class Light
{
public:
	Light(MistralEngine* game)
	{
		m_game = game;
		R = 0; G = 0; B = 0;
		X = 0; Y = 0; Z = 0;
		Strenght = 0;
		SpecularStrenght = 0;
	}

	void SetR(GLfloat r)
	{
		R = r;
	}
	void SetG(GLfloat g)
	{
		G = g;
	}
	void SetB(GLfloat b)
	{
		B = b;
	}
	void SetX(GLfloat x)
	{
		X = x;
	}
	void SetY(GLfloat y)
	{
		Y = y;
	}
	void SetZ(GLfloat z)
	{
		Z = z;
	}
	void SetStrenght(GLfloat s)
	{
		Strenght = s;
	}
	void SetSpecularStrenght(int ss)
	{
		SpecularStrenght =ss;
	}

	GLfloat getR()
	{
		return R;
	}
	GLfloat getG()
	{
		return G;
	}
	GLfloat getB()
	{
		return B;
	}
	GLfloat getX()
	{
		return X;
	}
	GLfloat getY()
	{
		return Y;
	}
	GLfloat getZ()
	{
		return Z;
	}
	GLfloat getStrenght()
	{
		return Strenght;
	}
	int getSpecularStrenght()
	{
		return SpecularStrenght;
	}



private:
	MistralEngine* m_game;
	GLfloat R, G , B;
	GLfloat X, Y, Z ;
	GLfloat Strenght;
	int SpecularStrenght;

	

};
#endif
