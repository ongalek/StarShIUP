#include "GameManager.h"
#include "airs/Timer.h"
#include "airs/Text.h"
#include "ResourceManager.h"





void GameManager::SizeChanged(int w, int h)
{
	FPSText.Resolution(w, h);
	Renderer.Resolution(w, h);
}

bool GameManager::OnClose()
{
	IsRunning = false;
	return true;
}



GameManager::GameManager(std::string path) : Charset(airs::Font("consolas", 100),true), 
	Window(Charset,"StarShIUP", 512, 512),FPSText(Charset), Resources(path, Window),Ship(Resources),
	Renderer(Resources.getSpriteset()), Menu(Resources), CurScene(&Menu), 
	Ivan(Resources), About(Resources), YouWin(Resources), GameOver(Resources)
{ 
	Window.SetCursor(airs::Cursor::Cross);
	Menu.Setup();
	FPSText.Color(0xff00ff80u);
	Window.Closing.bind<GameManager, &GameManager::OnClose>(this);
	Window.Resize.bind<GameManager, &GameManager::SizeChanged>(this);
	Window.LoadBitmap(airs::Bitmap("Resources/Button.png"));

}

void GameManager::Run()
{
	
	Window.Show(airs::Window::Appear::Maximize);
	
	IsRunning = true;
	airs::Timer timer;
	timer.Start();
	int frame = 0;
	double time = 0;
	int FpS = 0;
	double overall_time = 0;
	while (IsRunning)
	{   

		double dt = timer.Elapsed();
		timer.Reset();

		time += dt;
		overall_time += dt;
		frame++;
		if (time >= 1)
		{
			time = time - 1;
			
			FpS = frame;
			frame = 0;
		}

		if (CurScene != nullptr)
		{
			std::string Request = CurScene->Update(dt);
			if (Request == "quit")
			{
				IsRunning = false;
			}
			if (Request == "ShipScene")
			{
				CurScene = &Ship;
				Ship.Setup();
			}
			if (Request == "VanyaGame")
			{
				CurScene = &Ivan;
				Ivan.Setup();
			}
			if (Request == "About")
			{
				CurScene = &About;
				About.Setup();
			}
			if (Request == "YouWin")
			{
				CurScene = &YouWin;
				YouWin.Setup();
			}
			if (Request == "GameOver")
			{
				CurScene = &GameOver;
				GameOver.Setup();
			}
			if (Request == "Menu")
			{
				CurScene = &Menu;
				Menu.Setup();
			}
		}


		
		Window.Clear();
		Renderer.Clear();
		FPSText.Clear();
		if (CurScene != nullptr)
		{
			CurScene->Render(Renderer, FPSText);
		}
		
		FPSText.Origin(0, Window.Height() - Charset.Height());
		FPSText << FpS;
		Renderer.Time(overall_time * 1000);
		Renderer.Render();
		FPSText.Render();
		Window.Render();
		
		
		Window.ProcessMessages();
	}

}
