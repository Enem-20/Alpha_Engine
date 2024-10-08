#pragma once 

#ifndef CANVAS_H
#define CANVAS_H

#include <list>
#include<memory>

class GameObject;

namespace reactphysics3d {
	class CollisionBody;
}

class Canvas
{
public:
	Canvas();

	reactphysics3d::CollisionBody* getCollisionBody();
private:
	reactphysics3d::CollisionBody* body;
};

#endif