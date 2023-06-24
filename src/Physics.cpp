#include "Physics.h"

Physics::Physics() {
	world = physicsCommon.createPhysicsWorld();
}

void Physics::Step() {
	world->update(timeStep);
	// Get the updated position of the body 
	reactphysics3d::Transform transform = hfbodies[hfbodies.size() - 1]->getTransform();
	reactphysics3d::Vector3 position = transform.getPosition();

	// Display the position of the body 
	std::cout << "Body 1 Position: (" << position.x << ", " <<position.y << ", " << position.z << ", " << hfbodies[hfbodies.size() - 1]->getCollider(0)->getCollisionShape()->to_string() << ")" << std::endl;


	// Display the position of the body 
	//std::cout << "Body 2 Position: (" << position.x << ", " <<position.y << ", " << position.z << ")" << std::endl;
}

void Physics::MakeCube(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd) {
	bodies.push_back(world->createRigidBody(reactphysics3d::Transform(pos, reactphysics3d::Quaternion::identity())));
	boxes.push_back(physicsCommon.createBoxShape(halfd));
	bodies[bodies.size()-1]->addCollider(boxes[boxes.size()-1], reactphysics3d::Transform(reactphysics3d::Vector3(0,0,0), reactphysics3d::Quaternion::identity()));
}

void Physics::MakeFloor(reactphysics3d::Vector3 pos, reactphysics3d::Vector3 halfd) {
	bodies.push_back(world->createRigidBody(reactphysics3d::Transform(pos, reactphysics3d::Quaternion::identity())));
	boxes.push_back(physicsCommon.createBoxShape(halfd));
	bodies[bodies.size() - 1]->addCollider(boxes[boxes.size() - 1], reactphysics3d::Transform(reactphysics3d::Vector3(0, 0, 0), reactphysics3d::Quaternion::identity()));
	bodies[bodies.size() - 1]->setType(reactphysics3d::BodyType::STATIC);
	bodies[bodies.size() - 1]->enableGravity(false);
}

void Physics::MakeHeightField(std::vector<float> h, int nbRows)
{
	float* heights = &h[0];
	float min= 340282346638528859811704183484516925440.0000000000000000, max= -340282346638528859811704183484516925440.0000000000000000;
	for (float f : h) {
		if (f < min)
			min = f;
		if (f > max)
			max = f;
	}
	hfbodies.push_back(world->createRigidBody(reactphysics3d::Transform(reactphysics3d::Vector3(4,max/2,4), reactphysics3d::Quaternion::identity())));
	heightfields.push_back(physicsCommon.createHeightFieldShape( h.size()/nbRows , nbRows, min, max, heights, reactphysics3d::HeightFieldShape::HeightDataType()));
	hfbodies[hfbodies.size() - 1]->addCollider(heightfields[heightfields.size() - 1], reactphysics3d::Transform(reactphysics3d::Vector3(0, 0, 0), reactphysics3d::Quaternion::identity()));
	hfbodies[hfbodies.size() - 1]->setType(reactphysics3d::BodyType::STATIC);
	hfbodies[hfbodies.size() - 1]->enableGravity(false);
}

void Physics::GetNewMeshes(std::vector<Mesh> &m) {
	m.clear();
	int j = 0;
	for (reactphysics3d::BoxShape* b : boxes) {
		std::vector<Vertex> v;
		std::vector<GLuint> i;
		for (int i = 0; i < b->getNbVertices();i++) {
			/*reactphysics3d::Transform t = bodies[j]->getTransform();
			reactphysics3d::Vector3 mod = t.getPosition();*/
			reactphysics3d::Vector3 vect = b->getVertexPosition(i);
			v.push_back({ glm::vec3(vect.x,vect.y,vect.z),glm::vec2(0),glm::vec3(j*0.05f) });
		}
		i = {
			//Top
			//3 , 7, 6,
			6, 7, 3,
			3 , 2, 6,
			

			//Bottom
			0, 4, 5,
			//0, 1, 5,
			5, 1, 0,

			//Left
			0, 3 , 7,
			//0, 4, 7,
			7, 4, 0,

			//Right
			//1, 2, 6,
			6, 2, 1,
			1, 5, 6,
			

			//Front
			//0, 3 , 2,
			2, 3, 0,
			0, 1, 2,
			

			//Back
			4, 7,  6,
			//4, 5,  6
			6, 5, 4

		};
		m.push_back(Mesh(v,i));
		j++;
	}
}

void Physics::GetTransfrom(std::vector<glm::vec3>& t) {
	t.clear();
	if (bodies.size() > t.size()) {
		for (reactphysics3d::RigidBody* b : bodies) {
			reactphysics3d::Vector3 mod = b->getTransform().getPosition();
			t.push_back(glm::vec3(mod.x, mod.y, mod.z));
		}
		return;
	}
	int i = 0;
	for (reactphysics3d::RigidBody* b : bodies) {
		reactphysics3d::Vector3 mod = b->getTransform().getPosition();
		t[i]=(glm::vec3(mod.x, mod.y, mod.z));
		i++;
	}
}

void Physics::GetRotation(std::vector<glm::vec4>& r) {
	r.clear();
	if (bodies.size() > r.size()) {
		for (reactphysics3d::RigidBody* b : bodies) {
			reactphysics3d::Quaternion q = b->getTransform().getOrientation();
			q.getUnit();
			r.push_back(glm::vec4(q.x, q.y, q.z,q.w));
		}
		return;
	}
	int i = 0;
	for (reactphysics3d::RigidBody* b : bodies) {
		reactphysics3d::Quaternion q = b->getTransform().getOrientation();
		q.getUnit();
		r[i]=(glm::vec4(q.x, q.y, q.z,q.w));
		i++;
	}
	
}
