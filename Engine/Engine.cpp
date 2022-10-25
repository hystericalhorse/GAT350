#include "Engine.h"

namespace en
{
	void Engine::Init()
	{
		en::Engine::Instance().Register();

		en::__eventmanager.Init();

		en::__renderer.Init();
		en::__inputsys.Init();
		en::__audiosys.Init();
		en::__physics.Init();
		en::__registry.Init();
	}

	void Engine::Update()
	{
		en::__eventmanager.Update();

		en::__audiosys.Update();
		en::__inputsys.Update();
		en::__time.Tick();
		en::__physics.Update();
	}

	void Engine::Shutdown()
	{
		en::Factory::Instance().Shutdown();

		en::__audiosys.Shutdown();
		en::__renderer.Shutdown();
		en::__inputsys.Shutdown();
		en::__physics.Shutdown();
		en::__registry.Shutdown();

		en::__eventmanager.Shutdown();
	}

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RigidBodPhysicsComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(CameraController);
	}

	InputSystem __inputsys;
	Time __time;
	Renderer __renderer;
	AudioSys __audiosys;
	ResourceManager __registry;
	PhysicsSystem __physics;
	EventManager __eventmanager;
}