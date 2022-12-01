/*! \page spritedemo Adding 2D Elements

\section spritesetup Sprite Setup
Sprite are derived from Drawable. To make a 2D element, derive from RallySprite. \n
A Sprite should set its position, scale, and rotation in the constructor, \n
and define the Draw2D method and call Render with the 2D Orthographic camera.
\n
\code
#include "../src/RallySprite.h"
class SpriteTest : public RallySprite, public Align16
{
public:
	SpriteTest();
	SpriteTest(float angle, float x, float y, float scale);
	~SpriteTest();
	virtual void Draw2D();

	void Remove();
};
\endcode
\n
\code
void SpriteTest::Draw2D()
{
	Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
}
\endcode
\n
In the constructor, as with a game object, you also need to register it to draw, \n
as well as set an image to use, one that was loaded in LoadResources.
\n
\code
SpriteTest::SpriteTest(float angle, float x, float y, float scale)
{
	SetImage("heart");

	SetAngle(angle);
	SetCenter(50, 0);
	SetScalePixel(scale, scale);
	SetPosition(x, y);

	SubmitDrawRegistration();
}
\endcode
\n
Lastly, when you would like a sprite to stop appearing on screen, \n
either if it is recycled or in a custom method, you must deregister it.
\n
\code
	SubmitDrawDeregistration();
\endcode
\n
\n
\n
*/