#ifndef _HR_RENDERPREDECLARE_H_
#define _HR_RENDERPREDECLARE_H_

#include <memory>

struct IDXGIFactory1;
struct IDXGIFactory2;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct IDXGISwapChain1;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;
struct ID3D11Resource;
struct ID3D11Texture1D;
struct ID3D11Texture2D;
struct ID3D11Texture3D;
struct ID3D11Buffer;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

struct ID3D11SamplerState;

namespace Hr
{
	typedef std::shared_ptr<IDXGIFactory1>				IDXGIFactory1Ptr;
	typedef std::shared_ptr<IDXGIFactory2>              IDXGIFactory2Ptr;
	typedef std::shared_ptr<ID3D11Device>               ID3D11DevicePtr;
	typedef std::shared_ptr<ID3D11DeviceContext>		ID3D11DeviceContextPtr;
	typedef std::shared_ptr<IDXGISwapChain>             IDXGISwapChainPtr;
	typedef std::shared_ptr<IDXGISwapChain1>            IDXGISwapChain1Ptr;
	typedef std::shared_ptr<ID3D11RenderTargetView>     ID3D11RenderTargetViewPtr;
	typedef std::shared_ptr<ID3D11DepthStencilView>     ID3D11DepthStencilViewPtr;
	typedef std::shared_ptr<ID3D11ShaderResourceView>   ID3D11ShaderResourceViewPtr;
	typedef std::shared_ptr<ID3D11Resource>             ID3D11ResourcePtr;
	typedef std::shared_ptr<ID3D11Texture1D>            ID3D11Texture1DPtr;
	typedef std::shared_ptr<ID3D11Texture2D>            ID3D11Texture2DPtr;
	typedef std::shared_ptr<ID3D11Texture3D>            ID3D11Texture3DPtr;
	typedef std::shared_ptr<ID3D11Buffer>				ID3D11BufferPtr;
	typedef std::shared_ptr<ID3D11VertexShader>         ID3D11VertexShaderPtr;
	typedef std::shared_ptr<ID3D11PixelShader>          ID3D11PixelShaderPtr;
	typedef std::shared_ptr<ID3D11InputLayout>          ID3D11InputLayoutPtr;

	typedef std::shared_ptr<ID3D11SamplerState>         ID3D11SamplerStatePtr;

	class HrD3D11Device;
	typedef std::unique_ptr<HrD3D11Device> HrD3D11DevicePtr;
	class HrD3D11Utility;
	typedef std::unique_ptr<HrD3D11Utility> HrD3D11UtilityPtr;

	class HrD3D11RenderFactory;
	typedef std::shared_ptr<HrD3D11RenderFactory> HrD3D11RenderFactoryPtr;

	class HrD3D11Render;
	typedef std::shared_ptr<HrD3D11Render> HrD3D11RenderPtr;
	class HrD3D11RenderLayout;
	typedef std::shared_ptr<HrD3D11RenderLayout> HrD3D11RenderLayoutPtr;
	class HrD3D11FrameBuffer;
	typedef std::shared_ptr<HrD3D11FrameBuffer> HrD3D11FrameBufferPtr;
	class HrD3D11RenderTarget;
	typedef std::shared_ptr<HrD3D11RenderTarget> HrD3D11RenderTargetPtr;
	class HrD3D11DepthStencil;
	typedef std::shared_ptr<HrD3D11DepthStencil> HrD3D11DepthStencilPtr;
	class HrD3D11Texture;
	typedef std::shared_ptr<HrD3D11Texture> HrD3D11TexturePtr;
	class HrD3D11Texture2D;
	typedef std::shared_ptr<HrD3D11Texture2D> HrD3D11Texture2DPtr;

	class HrD3D11Shader;
	typedef std::shared_ptr<HrD3D11Shader> HrD3D11ShaderPtr;
	class HrD3D11GraphicsBuffer;
	typedef std::shared_ptr<HrD3D11GraphicsBuffer> HrD3D11GraphicsBufferPtr;

	class HrD3D11ShaderCompiler;
	typedef std::shared_ptr<HrD3D11ShaderCompiler> HrD3D11ShaderCompilerPtr;

	class HrD3D11BlendState;
}

#endif