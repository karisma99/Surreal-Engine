#include "GraphicsObject_Sprite.h"
#include "Model.h"
#include "Texture.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/ModelManager.h"
#include "GPUController.h"
#include "Surreal Engine/SceneManager.h"
#include "Surreal Engine/Scene.h"
#include "Camera.h"
#include "Rect.h"

GraphicsObject_Sprite::GraphicsObject_Sprite(Texture* _tex)
	:pShader(static_cast<ShaderTexture*>(ShaderManager::Get("textureFlat"))),
	tex(_tex),
	world(Matrix(IDENTITY)),
	position(Vect(0, 0, 0))
{
	GraphicsObject_Base::SetModel(ModelManager::Get("UnitSquare"));
}

GraphicsObject_Sprite::~GraphicsObject_Sprite()
{
	
}

void GraphicsObject_Sprite::SetTexture(Texture* _tex)
{
	tex = _tex;
}

void GraphicsObject_Sprite::SetWorld(const Matrix& worldMat)
{
	world = worldMat;
}
void GraphicsObject_Sprite::SetPosition(const Vect& pos)
{
	position = pos;
}

void GraphicsObject_Sprite::SetViewport()
{

}

const Vect& GraphicsObject_Sprite::GetPosition()
{
	return position;
}

void GraphicsObject_Sprite::Render()
{
	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(pShader->GetContext());
}

void GraphicsObject_Sprite::RenderWireframe()
{
	GPUController::SetRasterizerWireframe();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(pShader->GetContext());
}

void GraphicsObject_Sprite::RenderPartialTexture(Rect* r)
{
	ID3D11RasterizerState* scissorState = nullptr; 
	CD3D11_RASTERIZER_DESC rsDesc(D3D11_FILL_SOLID, D3D11_CULL_BACK, FALSE, 0, 0.f, 0.f, TRUE, TRUE, TRUE, FALSE);
	assert(!FAILED(GPUController::GetDevice()->CreateRasterizerState(&rsDesc, &scissorState)));


	CD3D11_RECT rect((LONG)r->x, (LONG)r->y, (LONG)(r->x + r->width), (LONG)(r->y + r->height));
	GPUController::GetContext()->RSSetScissorRects(1, &rect);

	GPUController::SetRasterizerSolid();

	pShader->SetToContext(GPUController::GetContext());
	pShader->SendCamMatrices(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getViewMatrix(), SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera()->getProjMatrix());

	pShader->SendWorld(world);
	pModel->SetToContext(pShader->GetContext());

	pShader->SetTextureResourceAndSampler(tex);
	pModel->Render(pShader->GetContext());
}