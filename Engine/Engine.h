#ifndef _ENGINE_H
#define _ENGINE_H

#include "Serialization/JSON.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Shader.h"
#include "Renderer/Program.h"
#include "Renderer/Material.h"
#include "Renderer/VertexBuffer.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Core/Memory.h"
#include "Core/Logger.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Audio/AudioSys.h"

#include "Physics/PhysicsSystem.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"
#include "Framework/EventManager.h"

#include "Components/ModelComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodPhysicsComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/TextComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/TilemapComponent.h"
#include "Components/CameraComponent.h"
#include "Components/CameraControllerComponent.h"

#include "Components/CharacterComponent.h"

#include "Resource/ResourceManager.h"

#include "glm/glm.hpp" // OpenGL Mathematics

#include <memory>
#include <vector>
#include <list>

namespace en
{
	extern InputSystem __inputsys;
	extern Time __time;
	extern Renderer __renderer;
	extern AudioSys __audiosys;
	extern ResourceManager __registry;
	extern PhysicsSystem __physics;
	extern EventManager __eventmanager;

	class Engine : public Singleton<Engine>
	{
	public:
		void Init();
		void Register();
		void Update();
		void Shutdown();
	};
}
#endif // _ENGINE_H