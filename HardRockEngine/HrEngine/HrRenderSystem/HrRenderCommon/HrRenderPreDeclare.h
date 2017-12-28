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

	class HrD3D11RenderFactory;
	typedef std::shared_ptr<HrD3D11RenderFactory> HrD3D11RenderFactoryPtr;

	class HrD3D11Render;
	typedef std::shared_ptr<HrD3D11Render> HrD3D11RenderPtr;
	class HrD3D11FrameBuffer;
	typedef std::shared_ptr<HrD3D11FrameBuffer> HrD3D11FrameBufferPtr;
	class HrD3D11RenderTarget;
	typedef std::shared_ptr<HrD3D11RenderTarget> HrD3D11RenderTargetPtr;

	class HrD3D11Device;
	typedef std::unique_ptr<HrD3D11Device> HrD3D11DevicePtr;
	class HrD3D11Utility;
	typedef std::unique_ptr<HrD3D11Utility> HrD3D11UtilityPtr;

	class HrD3D11Shader;
	class HrD3D11GraphicsBuffer;

	class HrD3D11ShaderCompiler;
	typedef std::shared_ptr<HrD3D11ShaderCompiler> HrD3D11ShaderCompilerPtr;

	class HrD3D11BlendState;

}

#endif