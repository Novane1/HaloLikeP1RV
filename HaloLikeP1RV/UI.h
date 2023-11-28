#pragma once
#include <Windows.h>
#include "Objet3D.h"
#include "Shader.h"
class UI
{
protected:
    vector<Objet3D> listeUI; // Liste des objets 3D considérés comme un UI
    vector<bool> isShowed; // Liste  des états des objets de la liste, true voulant dire que l'objet est donc activé, et donc à afficher.
    // un état à la case i de isShowed correspond naturellement à l'objet i de listeUI
    float frame; // frame de l'animation de course de l'arme
    float frameRunKnife; // frame de l'animation de course du couteau
    float frameRightClick;// frame de l'animation de coup du couteau
public:
    void AddObject(Objet3D o); // Ajoute un objet à la listeUI
    void changeState(bool b, int i); // Chanfe l'état de l'objet i de isShowed en b
    void affichage(std::vector<bool> keys, std::vector<bool> mouseClick,Shader healthShader,Shader alphaShader ,glm::vec3 pos, glm::vec3 target,int health, int frameHealth); // affichage de l'UI
    bool isKnife();
    bool isGun();
    vector<bool> isShowedFunc();
};