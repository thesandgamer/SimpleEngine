#include "Sphere.h"
#include "MeshComponent.h"
#include "Assets.h"

Sphere::Sphere()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
}
