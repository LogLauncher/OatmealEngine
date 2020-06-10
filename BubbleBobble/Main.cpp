#include "Minigin.h"

#if _DEBUG
#include <vld.h>
#endif

#include <memory>

#include "DemoScene.h"
#include "SceneManager.h"

void InitScenes()
{
	OatmealEngine::SceneManager::GetInstance().AddScene(std::make_shared<DemoScene>());
	OatmealEngine::SceneManager::GetInstance().SetStartScene("DemoScene");
}

int main()
{
	InitScenes();

	OatmealEngine::Minigin engine;
	engine.SetWindowDimentions(720, 720);
	engine.Run();

	return 0;
}