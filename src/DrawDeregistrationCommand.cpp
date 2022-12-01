#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"
DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* up)
	:ptrUp(up)
{

}
void DrawDeregistrationCommand::execute()
{
	DrawableAttorney::Registration::SceneDeregistration(ptrUp);
}