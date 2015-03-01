//==============================================================================
#include "HardLight.h"
#include <glm\gtx\rotate_vector.hpp>


float Scale;
int i = 0;
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;
	Bike* bike = bikes.get_player_bikes()[0];

	PxTransform newPos = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	vec3 dis = vec3(newPos.p.x,newPos.p.y,newPos.p.z);
	vec3 major = oldPos -dis;
	Scale = sqrt(major.x*major.x+major.z*major.z);
	skybox->set_actor(gPhysics->createRigidStatic(newPos));
	if(Scale > 0.5){ // size of slices
		newPos.p.x = (newPos.p.x+oldPos.x)/2.0;
		newPos.p.y = (newPos.p.y+oldPos.y)/2.0;
		newPos.p.z = (newPos.p.z+oldPos.z)/2.0;
		oldPos = dis;
		if(playerTail.size() < 30){
		TailSegment* Wall = new TailSegment(gPhysics->createRigidStatic(newPos),MeshMap::Instance()->getEntityMesh("Wall.obj"),"../data/Textures/LightTrail.tga");
		playerTail.push_back(Wall);
		Wall->setScale(Scale);
		world.add_entity(Wall);
		}else{
			
			playerTail[i]->get_actor()->setGlobalPose(newPos);
			playerTail[i]->setScale(Scale);
			i = (i+1)%30;
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
	vec3 light(newPos.p.x + 400.0f, newPos.p.y + 1000.0f, newPos.p.z + 200.0f);
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
