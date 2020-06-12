#include "Minigin.h"

#if _DEBUG
#include <vld.h>
#endif

#include <memory>

#include "Scenes/TestScene.h"
#include "SceneManager.h"

void InitScenes()
{
	OatmealEngine::SceneManager::GetInstance().AddScene(std::make_shared<TestScene>());
	OatmealEngine::SceneManager::GetInstance().SetStartScene("TestScene");
}

int main()
{
	InitScenes();

	OatmealEngine::Minigin engine;
	engine.SetWindowDimentions(1920, 1080);
	engine.Run();

	return 0;
}