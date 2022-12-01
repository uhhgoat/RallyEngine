#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"
DrawRegistrationCommand::DrawRegistrationCommand(Drawable* up)
	:ptrUp(up)
{

}
void DrawRegistrationCommand::execute()
{
	DrawableAttorney::Registration::SceneRegistration(ptrUp);
}