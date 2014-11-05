#include "MyApp.h"
#include "HR_Camera/HrCamera.h"
#include "HR_Material/HrMaterial.h"
#include "HR_Light/HrLight.h"
#include "HR_FastTool/HrD3DFastTool.h"
#include "HR_Texture/HrTexture.h"
#include "HR_SkeletalAnimation/HrHierarchyCtrler.h"
#include "HR_Input/HrDirectInputTool.h"
#include "HR_Terrain/HrTerrain.h"
#include "HR_Physics/HrBoundingBox.h"
#include "HR_Particle/HrSnow.h"
#include "HR_Particle/HrFirework.h"
#include "HR_Particle/HrParticleGun.h"
#include <boost/format.hpp>
#include <string>


using namespace HR;
CMyApp::CMyApp(void)
{
	m_nUpdateCnt = 0;

	m_pMyCamera = NULL;
	m_pMyMaterial = NULL;
	m_pMyPlaneMaterial = NULL;

	m_pMyLight = NULL;
	m_pMyTexture = NULL;
	//m_pTexture = NULL;

	m_pAlphaTexture = NULL;
	m_pDetailTexture = NULL;
	m_pOnePieceTexture = NULL;
	m_pPlaneTexture = NULL;

	m_pHierarchyCtrler = NULL;

	m_pDirectInput = NULL;
	m_pSnow = NULL;
	m_pBoundingBox = NULL;

	//初始化Log
	CHrLog::HrLogConf stHrLog;
	stHrLog.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;
	stHrLog.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;
	stHrLog.nLevelFlag = _HDEBUG;
	char szModuleFilePath[255];
	::ZeroMemory(szModuleFilePath, sizeof(szModuleFilePath));
	GetModuleFileName(NULL, szModuleFilePath, sizeof(szModuleFilePath));
	char* pFilePath = strrchr(szModuleFilePath, '\\');
	if (pFilePath != NULL)
	{
		*pFilePath = '\0';
	}
	boost::format fmt("%1%\\%2%");
	fmt % szModuleFilePath % "HLog.log";
	std::string str = fmt.str();
	memcpy(stHrLog.szLogFileName, str.c_str(), sizeof(stHrLog.szLogFileName));
	HLog.LogInit(stHrLog);
}

CMyApp::~CMyApp(void)
{
}

void CMyApp::AppRelease()
{
	CHrApplication::AppRelease();

	SAFE_DELETE(m_pMyCamera);
	SAFE_DELETE(m_pMyMaterial);
	SAFE_DELETE(m_pMyLight);
	SAFE_DELETE(m_pMyTexture);

	SAFE_DELETE(m_pAlphaTexture);
	SAFE_DELETE(m_pDetailTexture);
	SAFE_DELETE(m_pTrueAlphaTexture);
	SAFE_DELETE(m_pMyPlaneMaterial);
	SAFE_DELETE(m_pPlaneTexture);

	SAFE_DELETE(m_pOnePieceTexture);

	SAFE_DELETE(m_pHierarchyCtrler);

	SAFE_DELETE(m_pDirectInput);
	SAFE_DELETE(m_pSnow);
	SAFE_DELETE(m_pBoundingBox);
	//SAFE_DELETE(m_pFirework);
}

void CMyApp::AppSetup()
{
	//创建纹理
	m_pMyTexture = new CHrTexture();
	m_pMyTexture->Initialize(CHrD3DUtil::GetD3DDevice());
	bool bSuccess = m_pMyTexture->LoadTexture("Res/Texture1.jpg", true);
	m_pAlphaTexture = new CHrTexture();
	m_pAlphaTexture->LoadTexture("Res/alphachannel.bmp", false);
	m_pDetailTexture = new CHrTexture();
	m_pDetailTexture->LoadTexture("Res/detail.bmp", false);
	m_pTrueAlphaTexture = new CHrTexture();
	m_pTrueAlphaTexture->LoadTexture("Res/alphaflower.dds", false);
	m_pOnePieceTexture = new CHrTexture();
	m_pOnePieceTexture->LoadTexture("Res/one-piece-anime50.png", false);
	m_pPlaneTexture = new CHrTexture();
	m_pPlaneTexture->LoadTexture("Res/plane.jpg", false);
	
	//摄像机
	m_pMyCamera = new CHrCamera();
	m_pMyCamera->Initialize(CHrD3DUtil::GetD3DDevice());
	m_pMyCamera->SetViewMatrix();
	m_pMyCamera->SetProjMatrix();

	m_pMyMaterial = CHrD3DFastTool::Instance()->CreateMaterial(CHrD3DFastTool::MATERIAL_WHITE);
	

	m_pMyPlaneMaterial = new CHrMaterial();
	m_pMyPlaneMaterial->ResetMaterial();
	m_pMyPlaneMaterial->SetAmbientColor(D3DCOLOR_XRGB(150, 150, 150));
	m_pMyPlaneMaterial->SetDiffuseColor(D3DCOLOR_XRGB(255, 255, 255));
	m_pMyPlaneMaterial->SetSpecularColor(D3DCOLOR_XRGB(0, 0, 0));
	m_pMyPlaneMaterial->SetPower(5.0f);
	
	
	//设置环境光
	//CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
	////开启灯光
	CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, true);
	CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	////设置使用灯光
	m_pMyLight = CHrD3DFastTool::Instance()->CreateLight(CHrD3DFastTool::_HR_DIRECTLIGHT_::LIGHT_WHITE);
	m_pMyLight->SetLightDirection(D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	m_pMyLight->SetAmbientColor(D3DCOLOR_XRGB(200, 200, 200));
	CHrD3DUtil::GetD3DDevice()->SetLight(0, m_pMyLight->GetLight());
	CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);
	CHrD3DUtil::GetD3DDevice()->LightEnable(0, true);
	CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);

	//设置纹理过滤方式
	CHrD3DUtil::SetSamplerLiner();

	//加载x文件动画控制
	m_pHierarchyCtrler = new CHrHierarchyCtrler();
	m_pHierarchyCtrler->Initialize(CHrD3DUtil::GetD3DDevice());
	m_pHierarchyCtrler->CreateHierarchy("Res/lxq.X");
	D3DXMATRIX matPosition;
	D3DXMatrixTranslation(&matPosition, 0.0f, 0.0f, 100.0f);
	m_pHierarchyCtrler->SetPosition(matPosition);
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	m_pHierarchyCtrler->SetScale(matScale);

	m_pTerrain = new CHrTerrain();
	m_pTerrain->Initialize(CHrD3DUtil::GetD3DDevice());
	m_pTerrain->LoadTerrainFromFile("Res/coastMountain64.raw", "Res/green.jpg");
	m_pTerrain->InitTerrain(64, 64, 1.0f, 0.05f);

	m_pBoundingBox = new CHrBoundingBox();
	m_pBoundingBox->m_vMin = D3DXVECTOR3(-10.0f, -10.0f, -10.0f);
	m_pBoundingBox->m_vMax = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	m_pSnow = new CHrSnow(m_pBoundingBox, 10);
	m_pSnow->Initialize(CHrD3DUtil::GetD3DDevice(), "Res/snowflake.dds");

	//D3DXVECTOR3 vOrigin(0.0f, 10.0f, 50.0f);
	//m_pFirework = new CHrFirework(&vOrigin, 6000);
	//m_pFirework->Initialize(CHrD3DUtil::GetD3DDevice(), "Res/flare.bmp");

	m_pParticleGun = new CHrParticleGun(m_pMyCamera);
	m_pParticleGun->Initialize(CHrD3DUtil::GetD3DDevice(), "Res/flare_alpha.dds");

	//输入
	m_pDirectInput = new CHrDirectInputTool();
	m_pDirectInput->Initialize(m_hWnd, m_hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void CMyApp::UpdateScene()
{
	++m_nUpdateCnt;

	float fCameraMoveSpeed = 0.01f;
	float fCameraRotateSpeed = 0.01f;

	m_pDirectInput->GetInput();
	//使用输入控制
	if (m_pDirectInput->IsKeyDown(DIK_A))
	{
		m_pMyCamera->MoveAlongRightVec(-fCameraMoveSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	if (m_pDirectInput->IsKeyDown(DIK_D))
	{
		m_pMyCamera->MoveAlongRightVec(fCameraMoveSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	if (m_pDirectInput->IsKeyDown(DIK_W))
	{
		m_pMyCamera->MoveAlongLookVec(fCameraMoveSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	if (m_pDirectInput->IsKeyDown(DIK_S))
	{
		m_pMyCamera->MoveAlongLookVec(-fCameraMoveSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	if (m_pDirectInput->IsKeyDown(DIK_I))
	{
		m_pMyCamera->RotationLookAxis(fCameraRotateSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	if (m_pDirectInput->IsKeyDown(DIK_J))
	{
		m_pMyCamera->RotationRightAxis(fCameraRotateSpeed);
		m_pMyCamera->SetViewMatrix();
	}
	
	//鼠标控制右向量和上向量的旋转
	m_pMyCamera->RotationUpAxis(m_pDirectInput->MouseDX() * 0.001f);
	m_pMyCamera->RotationRightAxis(m_pDirectInput->MouseDY() * 0.001f);
	m_pMyCamera->SetViewMatrix();


	if (m_pDirectInput->IsKeyDown(DIK_T))
	{
		CHrD3DUtil::SetSamplerLiner();
	}
	if (m_pDirectInput->IsKeyDown(DIK_R))
	{
		CHrD3DUtil::SetSamplerPoint();
	}
	if (m_pDirectInput->IsKeyDown(DIK_Y))
	{
		CHrD3DUtil::SetSamplerAnisotropy();
	}
	if (m_pDirectInput->IsKeyDown(DIK_Z))
	{
		CHrD3DUtil::GetD3DDevice()->SetRenderState(D3DRS_ZENABLE, false);
	}
	if (m_pDirectInput->IsKeyDown(DIK_SPACE))
	{
		HLog.Log(_HDEBUG, "HR", "Key Space Down");
		m_pParticleGun->AddParticle();
	}

	D3DXMATRIX matRotateY;
	D3DXMatrixRotationY(&matRotateY, m_nUpdateCnt * 0.0001f);
	
	m_pHierarchyCtrler->UpdateAnim();

	//m_pSnow->Update(0.01f);

	//m_pFirework->Update(0.01f);
	//if (m_pFirework->IsDead())
	//{
	//	m_pFirework->Reset();
	//}
	m_pParticleGun->Update(0.001f);
}

void CMyApp::PreRender()
{

}

void CMyApp::RenderScene()
{
	CHrD3DUtil::GetD3DDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, 0x00, 1.0f, 0);
	CHrD3DUtil::GetD3DDevice()->BeginScene();

	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld, 0.0f, 0.0f, 0.0f);
	//绘制地形
	m_pTerrain->RenderTerrain(&matWorld, false);

	//m_pSnow->Render();

	//m_pFirework->Render();

	m_pParticleGun->Render();
	CHrD3DUtil::GetD3DDevice()->EndScene();
	CHrD3DUtil::GetD3DDevice()->Present(0, 0, 0, 0);
}

void CMyApp::PostRender()
{

}



