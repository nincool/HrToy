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
	//XMVectorAbs(v)  ——返回一个向量，该向量的每个分量是v的对应分量的绝对值
	PrintVector(XMVectorAbs(v));
	//XMVectorCos(v)   ——返回一个向量，该向量的每个分量是v的对应分量的余弦值
	PrintVector(XMVectorCos(w));
	//XMVectorLog(v)   ——返回一个向量，该向量的每个分量是v的对应分量的以2为底的对数值
	PrintVector(XMVectorLog(u));
	//XMVectorExp(v)   ——返回一个向量(e^v[0],e^v[1], e^v[2], e^v[3])，其中e^x表示e的x次幂
	PrintVector(XMVectorLog(u));
	//XMVectorPow(u, v)   ——返回一个向量(u[0]^v[0], u[1]^v[1],u[2]^v[2], u[3]^v[3])，其中x^y表示x的y次幂
	PrintVector(XMVectorPow(u, p));
	//XMVectorSqrt(v)   ——返回一个向量，该向量的每个分量是v的对应分量的算术平方根
	PrintVector(XMVectorSqrt(u));
	//XMVectorSwizzle(v,a, b, c, d)   ——返回一个向量(v[a],v[b], v[c], v[d])
	PrintVector(XMVectorSwizzle(u, 1, 1, 2, 2));
	//XMVectorMultiply(u,v)   ——返回一个向量，该向量的每个分量是u的对应分量与v的对应分量的乘积
	PrintVector(XMVectorMultiply(u, p));
	//XMVectorSaturate(v)     ——返回由v的各个分量进行saturate操作后得到的值组成的向量；saturate(x)返回0（若x<0），x（若0<=x<=1）或者1（x>1）
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

	//XMVECTOR XMVector3Length(FXMVECTOR v);     //长度L，结果为[L,L,L,L],效率起见，全部为XMVECTOR类型，我们只取一个维即可。  
	//XMVECTOR XMVector3LengthSq(FXMVECTOR v);   //长度L平方根，结果存放同上。其他任何返回scalar数的同理  
	//XMVECTOR XMVector3Dot(FXMVECTOR v1, FXMVECTOR v2);  //点积dot，[dot, dot, dot, dot]  
	//XMVECTOR XMVector3Cross(FXMVECTOR v1, FXMVECTOR v2);    //叉乘  
	//XMVECTOR XMVector3Normalize(FXMVECTOR v);       //归一化  
	//XMVECTOR XMVector3Orthogonal(FXMVECTOR v);      //返回一个垂直的向量  
	//XMVECTOR XMVector3AngleBetweenVectors(FXMVECTOR v1, FXMVECTOR v2);  //返回两向量间角度angle，[angle, angle, angle, angle] 

	//XMMATRIX XMMatrixIdentity();                //返回单位矩阵，即对角线全1，其他全0  
	//BOOL     XMMatrixIsIdentity(CXMMATRIX M);       //判断一个矩阵是否为单位矩阵  
	//XMMATRIX XMMatrixMultiply(CXMMATRIX A, CXMMATRIX B);    //两矩阵相乘  
	//XMMATRIX XMMatrixTranspose(CXMMATRIX M);        //矩阵转置  
	//XMVECTOR XMMatrixDeterminant(CXMMATRIX M);      //求矩阵对应行列式的值det  
	//XMMATRIX XMMatrixInverse(XMVECTOR *pDet, CXMMATRIX M);  //求矩阵M的逆，*pDet为该矩阵的det  
	XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixIdentity();
	XMMATRIX C = A * B;
	XMMATRIX D = XMMatrixTranspose(A);
	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX E = XMMatrixInverse(&det, A);
	
	//XMMATRIX XMMatrixScaling(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ); //伸缩变化，指定三个方向上的伸缩比  
	//XMMATRIX XMMatrixScalingFromVector(FXMVECTOR scale);            //通过向量指定三个方向伸缩比，求伸缩变换  
	//XMMATRIX XMMatrixRotationX(FLOAT angle);                //围绕x轴的旋转变换  
	//XMMATRIX XMMatrixRotationY(FLOAT angle);                //围绕y轴的旋转变换  
	//XMMATRIX XMMatrixRotationZ(FLOAT angle);                //围绕z轴的旋转变换  
	//XMMATRIX XMMatrixRotationAxis(FXMVECTOR axis, FLOAT angle);     //围绕任意轴axis的旋转变换  
	//XMMATRIX XMMatrixTranslation(FLOAT x, FLOAT y, FLOAT z);        //平移变换，指定三个方向的平移量  
	//XMMATRIX XMMatrixTranslationFromVector(FXMVECTOR offset);       //通过向量指定三个方向的平移量，求平移变换  
	//XMVECTOR XMVector3Transform(FXMVECTOR v, CXMMATRIX m);          //向量、矩阵相乘  
	//XMVECTOR XMVector3TransformCoord(FXMVECTOR v, CXMMATRIX m);         //向量、矩阵相乘，但向量w=1,因此为点的变换  
	//XMVECTOR XMVector3TransformNormal(FXMVECTOR v, CXMMATRIX m);        //向量、矩阵相乘，但向量w=0,因此为向量的变换 
	
	return true;
}

void Hr::HrRenderD3D11DemoXNA::PrintVector(FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	HRLOG(_T("VectorInfo: x[%f] y[%f] z[%f] w[%f]"), dest.x, dest.y, dest.z, dest.w);
}

