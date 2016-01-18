#ifndef _HR_RENDERD3D11DEMOGEMOTRY_H_
#define _HR_RENDERD3D11DEMOGEMOTRY_H_

#include "IRenderDemo.h"

using namespace DirectX;

class ID3DX11Effect;
class ID3DX11EffectMatrixVariable;
namespace Hr
{
	class HR_RENDERDEMO_API HrRenderD3D11DemoGeometry : public IRenderDemo
	{
	public:
		HrRenderD3D11DemoGeometry();

		virtual void SetD3DDevice(ID3D11Device* pDevice
			, ID3D11DeviceContext* pDeviceContex
			, ID3D11RenderTargetView* pRenderTargetView
			, ID3D11DepthStencilView* pDepthStencilView
			, IDXGISwapChain* pSwapChain) override;

		virtual bool Init() override;
		virtual bool Render() override;
		virtual void Release() override;


		struct VertexPos
		{
			XMFLOAT3 pos;
			XMFLOAT4 color;
		};

		//定义一个通用的顶点结构：位置、法线、切线、纹理坐标
		struct Vertex
		{
			Vertex(){}
			Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT3 _tangent, XMFLOAT2 _tex) :
				pos(_pos), normal(_normal), tangent(_tangent), tex(_tex){}

			XMFLOAT3	pos;
			XMFLOAT3	normal;
			XMFLOAT3	tangent;
			XMFLOAT2	tex;
		};

		struct MeshData
		{
			std::vector<Vertex> vertices;
			std::vector<UINT> indices;
		};

		//该程序中绘制的几种几何图形：网格、立方体、球、圆柱
		MeshData	m_grid;
		MeshData	m_box;
		MeshData	m_sphere;
		MeshData	m_cylinder;

		//每个几何体在顶点、索引缓冲区中的起始位置
		UINT	m_gridVStart, m_gridIStart;
		UINT	m_boxVStart, m_boxIStart;
		UINT	m_sphereVStart, m_sphereIStart;
		UINT	m_cylinderVStart, m_cylinderIStart;
	private:
		bool LoadContent();
		bool BuildHLSL();
		bool BuildInputLayout();
		bool BuildBuffers();

		//创建一个立方体：指定宽(X方向)、高(Y方向)、深(Z方向)
		void CreateBox(float width, float height, float depth, MeshData &mesh);
		//创建一个网络格子：指定总宽度(X方向)、总高度(Z方向); m、n为宽、高方向上的格子数量
		void CreateGrid(float fWidth, float fHeight, UINT m, UINT n, MeshData &mesh);
		//创建一个球体：指定半径(radius)、slice和stack
		void CreateSphere(float radius, int slice, int stack, MeshData &mesh);
	protected:
		HR_SYNTHESIZE_READONLY(ID3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE_READONLY(ID3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);
		HR_SYNTHESIZE(IDXGISwapChain*, m_pSwapChain, SwapChain);

		HR_SYNTHESIZE(ID3D11RenderTargetView*, m_pRenderTargetView, RenderTargetView);
		HR_SYNTHESIZE(ID3D11DepthStencilView*, m_pDepthStencilView, DepthStencilView);


		ID3DX11Effect* m_pEffect;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;

		ID3DX11EffectMatrixVariable* m_pFxWorldViewProj;
	};
}

#endif




