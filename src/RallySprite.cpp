#include "RallySprite.h"

RallySprite::RallySprite()
{

}
RallySprite::RallySprite(std::string imgKey)
{
	Model* pModelSprite = ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSquareXY);
	ShaderObject* pShaderObject_sprite = ShaderManager::Get("spriteRender");
	Image* pImage = ImageManager::Get(imgKey);
	pGOSprite = new GraphicsObject_Sprite(pModelSprite, pShaderObject_sprite, pImage, pImage->pImageRect);
	scaleX = 1.0f;
	scaleY = 1.0f;
	centerX = 0;
	centerY = 0;
}

RallySprite::RallySprite(Image* i)
{
	Model* pModelSprite = ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSquareXY);
	ShaderObject* pShaderObject_sprite = ShaderManager::Get("spriteRender");
	pGOSprite = new GraphicsObject_Sprite(pModelSprite, pShaderObject_sprite, i, i->pImageRect);
	scaleX = 1.0f;
	scaleY = 1.0f;
	centerX = 0;
	centerY = 0;
}

void RallySprite::SetImage(Image* i)
{
	Model* pModelSprite = ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSquareXY);
	ShaderObject* pShaderObject_sprite = ShaderManager::Get("spriteRender");
	pGOSprite = new GraphicsObject_Sprite(pModelSprite, pShaderObject_sprite, i, i->pImageRect);
}

void RallySprite::SetImage(std::string imgKey)
{
	Model* pModelSprite = ModelManager::GetPremadeModel(Model::PreMadeModels::UnitSquareXY);
	ShaderObject* pShaderObject_sprite = ShaderManager::Get("spriteRender");
	Image* pImage = ImageManager::Get(imgKey);
	pGOSprite = new GraphicsObject_Sprite(pModelSprite, pShaderObject_sprite, pImage, pImage->pImageRect);
}

RallySprite::~RallySprite()
{
	if (pGOSprite != nullptr)
	{
		delete pGOSprite;
	}
}

void RallySprite::Render(Camera* pcam)
{

	Matrix Scale;
	Matrix RotZ;
	Matrix Trans;
	Scale.set(SCALE, scaleX, scaleY, 1.0f);
	RotZ.set(ROT_Z, angle);
	Trans.set(TRANS, pGOSprite->origPosX + centerX, pGOSprite->origPosY + centerY, 0.0f);
	Matrix world = Scale * RotZ * Trans;

	pGOSprite->SetWorld(world);
	pGOSprite->Render(pcam);
}
float RallySprite::GetAngle()
{
	return angle;
}
void RallySprite::SetAngle(float a)
{
	angle = a;
}
void RallySprite::SetCenter(float offsetx, float offsety)
{
	centerX = offsetx;
	centerY = offsety;
}
void RallySprite::SetPosition(float x, float y)
{
	pGOSprite->origPosX = x;
	pGOSprite->origPosY = y;
}
void RallySprite::SetScaleFactor(float scalex, float scaley)
{
	scaleX = scalex;
	scaleY = scaley;
}
void RallySprite::SetScalePixel(float width, float height)
{
	//pGOSprite->origWidth = width;
	//pGOSprite->origHeight = height;
	scaleX = width / pGOSprite->origWidth;
	scaleY = height / pGOSprite->origHeight;
}
