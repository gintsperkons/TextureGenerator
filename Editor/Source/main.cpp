#include <Engine.h>
#include <Core/Logger/Logger.h>

int main()
{
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();

	engine->AddWindow("TextureGenEngine2", 800, 600);

	

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}