#pragma once
#include <Windows.h>
#include "Objet3D.h"
class UI
{
protected :
	vector<Objet3D> listeUI;
	vector<bool> isShowed;
	float frame;
public :
	void AddObject(Objet3D o);
	void changeState(bool b, int i);
	void affichage(std::vector<bool> keys);
};

