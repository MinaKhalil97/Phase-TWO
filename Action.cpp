#include"Actions\Action.h"
#include"GUI\UI_Info.h"
void Action::correct(int& x, int &y)
{
	y -= UI.ToolBarHeight;
	int Cx1 = (x) / 15;
	int Cx2 = (x + 14) / 15;
	Cx1 *= 15;
	Cx2 *= 15;
	if (abs(Cx1 - x) <= abs(Cx2 - x)) x /= 15;
	else x = (x + 14) / 15;

	int Cy1 = (y) / 15;
	int Cy2 = (y + 14) / 15;
	Cy1 *= 15;
	Cy2 *= 15;
	if (abs(Cy1 - y) <= abs(Cy2 - y)) y /= 15;
	else y = (y + 14) / 15;
}