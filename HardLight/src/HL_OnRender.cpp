//==============================================================================
#include "HardLight.h"
#include <glm\gtx\rotate_vector.hpp>

float Scale;
vec3 oldPos = vec3(0.0f,1.0f,600.0f);
vector<TailWall*> playerTail;
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;

	PxTransform newPos = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	vec3 dis = vec3(newPos.p.x,newPos.p.y,newPos.p.z);
	vec3 major = oldPos -dis;
	Scale = sqrt(major.x*major.x+major.z*major.z);
	skybox->set_actor(gPhysics->createRigidStatic(newPos));
	if(Scale > 1){
		newPos.p.x = (newPos.p.x+oldPos.x)/2.0;
		newPos.p.y = (newPos.p.y+oldPos.y)/2.0;
		newPos.p.z = (newPos.p.z+oldPos.z)/2.0;
		oldPos = dis;
		
		TailWall* Wall = new TailWall(gPhysics->createRigidStatic(newPos),MeshMap::Instance()->getEntityMesh("Wall.obj"),"../data/Textures/LightTrail.tga");
		playerTail.push_back(Wall);
		Wall->setScale(Scale);
		world.add_entity(Wall);
		if(playerTail.size() > 10){
			world.remove(playerTail[0]);
			playerTail.erase(playerTail.begin());
		}
	}
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera controls
	cam_translate += vec3(0.0f, 0.0f, (forward-back)*speed);
	cam_rotate += (right-left)*speed / 30.0f;
	if (cam_rotate > PxTwoPi) cam_rotate -= PxTwoPi;
	if (cam_rotate < 0.0f) cam_rotate += PxTwoPi;

	vec3 camera_position(cam_translate);
	camera_position = rotateY(camera_position, cam_rotate);
	vec3 light(5.0f, 15.0f, -5.0f);
	// view_matrix for all entities
	PxTransform gPose = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	camera_position = rotate(camera_position, rads, vec3(axis.x, axis.y, axis.z));


	vec3 v_pos(gPose.p.x, gPose.p.y, gPose.p.z);
	vec3 up(0.0f, 1.0f, 0.0f);
	if (cam_translate.z > 0.0f) up *= -1.0f;
	camera_position += v_pos;
	mat4 view_matrix = lookAt(camera_position, v_pos + vec3(0,5,0), up);

	for(unsigned int i = 0; i < world.getEntities().size(); i++)
	{
		world.getEntities()[i]->render(projection_matrix, view_matrix, light);
	}

	SDL_GL_SwapWindow(window);

}

//==============================================================================
