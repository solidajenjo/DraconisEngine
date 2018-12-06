#ifndef _MODULE_SCENE_H
#define _MODULE_SCENE_H

#include "Module.h"
#include <map>
#include <string>

class GameObject;
class ComponentCamera;

class ModuleScene :
	public Module
{
public:
	
	bool Init() override;
	update_status Update() override;
	bool CleanUp() override; //clean when a new model is loaded & on exit

	void InsertGameObject(GameObject* newGO); //Insert instantiated Game Object
	void ImportGameObject(GameObject* newGO); //Insert imported game Object
	void DestroyGameObject(GameObject* destroyableGO);
	void ShowHierarchy(bool isWorld = true); //editor drawing moved here to mantain controled & private the gameobjects on the scene. This avoids wrong loads & destroys
	void DrawNode(GameObject* gObj, bool isWorld = true);

	bool IsRoot(const GameObject* go) const;

	bool MakeParent(char parentUUID[40], GameObject* son); //searchs for a gameobject by it's UUID and attaches son to it
	
	GameObject* FindInstanceOrigin(char instance[40]);	

	void SetSkyBox(); //sets skybox on framebuffer

	void Serialize();
	void LinkGameObjects();

	//members

	GameObject* selected = nullptr;
	ComponentCamera* sceneCamera = nullptr;

private:

	void FlattenHierarchy(GameObject* go);
	
	//members

	std::map<std::string, GameObject*> sceneGameObjects; //handles all scene game objects
	
	GameObject* root = nullptr; //scene root
	GameObject* directory = nullptr; //handles all imported files
};

#endif