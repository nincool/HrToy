#include "HrRenderD3D11DemoXNA.h"


using namespace Hr;
using namespace std;
using namespace DirectX;

HrRenderD3D11DemoXNA::HrRenderD3D11DemoXNA()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_pSwapChain = nullptr;

	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
}

void HrRenderD3D11DemoXNA::SetD3DDevice(ID3D11Device* pDevice
	, ID3D11DeviceContext* pDeviceContex
	, ID3D11RenderTargetView* pRenderTargetView
	, ID3D11DepthStencilView* pDepthStencilView
	, IDXGISwapChain* pSwapChain)
{
	m_pD3D11Device = pDevice;
	m_pD3D11ImmediateContext = pDeviceContex;
	m_pRenderTargetView = pRenderTargetView;
	m_pDepthStencilView = pDepthStencilView;
	m_pSwapChain = pSwapChain;

}

bool HrRenderD3D11DemoXNA::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoXNA::Render()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);



	m_pSwapChain->Present(0, 0);

	return true;
}


void HrRenderD3D11DemoXNA::Release()
{
}

bool HrRenderD3D11DemoXNA::LoadContent()
{
	// Check support for SSE2 (Pentium4, AMD K8, and above).
	if (!XMVerifyCPUSupport())
	{
		HRERROR(_T("xna math not supported"));
		return false;
	}
	XMVECTOR p = XMVectorSet(2.0f, 2.0f, 1.0f, 0.0f);
	XMVECTOR q = XMVectorSet(2.0f, -0.5f, 0.5f, 0.1f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 4.0f, 8.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 2.5f);
	XMVECTOR w = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);

	PrintVector(p);
	PrintVector(XMVectorSwizzle(u, 2, 2, 1, 3));
	//XMVectorAbs(v)  ��������һ����������������ÿ��������v�Ķ�Ӧ�����ľ���ֵ
	PrintVector(XMVectorAbs(v));
	//XMVectorCos(v)   ��������һ����������������ÿ��������v�Ķ�Ӧ����������ֵ
	PrintVector(XMVectorCos(w));
	//XMVectorLog(v)   ��������һ����������������ÿ��������v�Ķ�Ӧ��������2Ϊ�׵Ķ���ֵ
	PrintVector(XMVectorLog(u));
	//XMVectorExp(v)   ��������һ������(e^v[0],e^v[1], e^v[2], e^v[3])������e^x��ʾe��x����
	PrintVector(XMVectorLog(u));
	//XMVectorPow(u, v)   ��������һ������(u[0]^v[0], u[1]^v[1],u[2]^v[2], u[3]^v[3])������x^y��ʾx��y����
	PrintVector(XMVectorPow(u, p));
	//XMVectorSqrt(v)   ��������һ����������������ÿ��������v�Ķ�Ӧ����������ƽ����
	PrintVector(XMVectorSqrt(u));
	//XMVectorSwizzle(v,a, b, c, d)   ��������һ������(v[a],v[b], v[c], v[d])
	PrintVector(XMVectorSwizzle(u, 1, 1, 2, 2));
	//XMVectorMultiply(u,v)   ��������һ����������������ÿ��������u�Ķ�Ӧ������v�Ķ�Ӧ�����ĳ˻�
	PrintVector(XMVectorMultiply(u, p));
	//XMVectorSaturate(v)     ����������v�ĸ�����������saturate������õ���ֵ��ɵ�������saturate(x)����0����x<0����x����0<=x<=1������1��x>1��
	PrintVector(XMVectorSaturate(q));

	//XMVECTOR XMVectorZero();        //[0,0,0,0]  
	XMVECTOR vZero = XMVectorZero();
	//XMVECTOR XMVectorSplatOne();    //[1.f, 1.f, 1.f, 1.f] 
	XMVECTOR vSplatOne = XMVectorSplatOne();
	//XVMECTOR XMVectorSet(FLOAT x, FLOAT y, FLOAT z, FLOAT w);   //[x,y,z,w]  
	XMVECTOR vSet = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	//XMVECTOR XMVectorReplicate(FLOAT s);    //[s, s, s, s] 
	XMVECTOR vReplicate = XMVectorReplicate(-2.0f);
	//XMVECTOR XMVectorSplatX(FXMVECTOR v);   //[v.x, v.x, v.x, v.x]  
	//XMVECTOR XMVectorSplatY(FXMVECTOR v);   //[v.y, v.y, v.y, v.y]  
	//XMVECTOR XMVectorSplatZ(FXMVECTOR v);   //[v.y, v.y, v.y, v.y]  

	//XMVECTOR XMVector3Length(FXMVECTOR v);     //����L�����Ϊ[L,L,L,L],Ч�������ȫ��ΪXMVECTOR���ͣ�����ֻȡһ��ά���ɡ�  
	//XMVECTOR XMVector3LengthSq(FXMVECTOR v);   //����Lƽ������������ͬ�ϡ������κη���scalar����ͬ��  
	//XMVECTOR XMVector3Dot(FXMVECTOR v1, FXMVECTOR v2);  //���dot��[dot, dot, dot, dot]  
	//XMVECTOR XMVector3Cross(FXMVECTOR v1, FXMVECTOR v2);    //���  
	//XMVECTOR XMVector3Normalize(FXMVECTOR v);       //��һ��  
	//XMVECTOR XMVector3Orthogonal(FXMVECTOR v);      //����һ����ֱ������  
	//XMVECTOR XMVector3AngleBetweenVectors(FXMVECTOR v1, FXMVECTOR v2);  //������������Ƕ�angle��[angle, angle, angle, angle] 

	//XMMATRIX XMMatrixIdentity();                //���ص�λ���󣬼��Խ���ȫ1������ȫ0  
	//BOOL     XMMatrixIsIdentity(CXMMATRIX M);       //�ж�һ�������Ƿ�Ϊ��λ����  
	//XMMATRIX XMMatrixMultiply(CXMMATRIX A, CXMMATRIX B);    //���������  
	//XMMATRIX XMMatrixTranspose(CXMMATRIX M);        //����ת��  
	//XMVECTOR XMMatrixDeterminant(CXMMATRIX M);      //������Ӧ����ʽ��ֵdet  
	//XMMATRIX XMMatrixInverse(XMVECTOR *pDet, CXMMATRIX M);  //�����M���棬*pDetΪ�þ����det  
	XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixIdentity();
	XMMATRIX C = A * B;
	XMMATRIX D = XMMatrixTranspose(A);
	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX E = XMMatrixInverse(&det, A);
	
	//XMMATRIX XMMatrixScaling(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ); //�����仯��ָ�����������ϵ�������  
	//XMMATRIX XMMatrixScalingFromVector(FXMVECTOR scale);            //ͨ������ָ���������������ȣ��������任  
	//XMMATRIX XMMatrixRotationX(FLOAT angle);                //Χ��x�����ת�任  
	//XMMATRIX XMMatrixRotationY(FLOAT angle);                //Χ��y�����ת�任  
	//XMMATRIX XMMatrixRotationZ(FLOAT angle);                //Χ��z�����ת�任  
	//XMMATRIX XMMatrixRotationAxis(FXMVECTOR axis, FLOAT angle);     //Χ��������axis����ת�任  
	//XMMATRIX XMMatrixTranslation(FLOAT x, FLOAT y, FLOAT z);        //ƽ�Ʊ任��ָ�����������ƽ����  
	//XMMATRIX XMMatrixTranslationFromVector(FXMVECTOR offset);       //ͨ������ָ�����������ƽ��������ƽ�Ʊ任  
	//XMVECTOR XMVector3Transform(FXMVECTOR v, CXMMATRIX m);          //�������������  
	//XMVECTOR XMVector3TransformCoord(FXMVECTOR v, CXMMATRIX m);         //������������ˣ�������w=1,���Ϊ��ı任  
	//XMVECTOR XMVector3TransformNormal(FXMVECTOR v, CXMMATRIX m);        //������������ˣ�������w=0,���Ϊ�����ı任 
	
	return true;
}

void Hr::HrRenderD3D11DemoXNA::PrintVector(FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	HRLOG(_T("VectorInfo: x[%f] y[%f] z[%f] w[%f]"), dest.x, dest.y, dest.z, dest.w);
}

