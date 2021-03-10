#include <iostream>
#include "airs/Initializer.h"
#include "airs/MessageBox.h"
#include "GameManager.h"
#include "ResourceManager.h"


#pragma comment(lib, "airsd.lib")



int main(int argc, char** argv)
{
	try
	{
		airs::Initializer Token;
		GameManager God("loader.txt");
		God.Run();
		
		/*airs::GraphicsWindow Window("shit", 500, 500);
		Window.SetCursor(airs::Cursor::Cross);
		Window.Show();

		airs::Font Font("consolas", 24);
		airs::DynamicCharset Charset(Font);
		airs::StaticText Text(Charset);

		Text.Resolution(Window.Width(), Window.Height());
		Text.Location(0, 0);

		Text.Color(0xffffffffu);
		Text << std::u16string((char16_t*)L"penis пидарас");
		Text.Color(0xff00ff80u);
		Text << "\n000 !)";
		

		//airs::Spriteset Spriteset;
		//Spriteset.Load(airs::Bitmap("logo.png"));
		//airs::SpritesRenderer Renderer(Spriteset);
		//Renderer.Resolution(Window.Width(), Window.Height());
		//Renderer.Push(0, 0);


		//Window.ClearColor(0, 0, 1, 1);
		while (true)
		{
			Window.ProcessMessages();
			Window.Clear();

			Text.Render();

			//Renderer.Render();

			Window.Render();
		}
		*/
		return 0;
	}
	catch (std::exception ex)
	{
		airs::MessageBox::Show(ex.what());
		return -1;
	}
}