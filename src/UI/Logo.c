#include "AllWindows.h"

#include "../Graphics.h"
#include "../Widget.h"

#include "../Data/Screen.h"

#include "graphics/image.h"
#include "sound/music.h"

void UI_Logo_init()
{
	sound_music_play_intro();
}

void UI_Logo_drawBackground()
{
	Graphics_clearScreen();
	Graphics_drawImage(image_group(GROUP_LOGO), Data_Screen.offset640x480.x, Data_Screen.offset640x480.y);
	Widget_GameText_drawCenteredColored(13, 7,
		(Data_Screen.width - 320) / 2, Data_Screen.offset640x480.y + 462,
		320, FONT_NORMAL_PLAIN, COLOR_WHITE);
}

void UI_Logo_handleMouse(const mouse *m)
{
	if (m->left.went_up || m->right.went_up) {
		UI_Window_goTo(Window_MainMenu);
	}
}
