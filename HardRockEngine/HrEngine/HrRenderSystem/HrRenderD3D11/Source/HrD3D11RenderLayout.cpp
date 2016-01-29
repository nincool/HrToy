#include "HrD3D11RenderLayout.h"

using namespace Hr;

HrD3D11RenderLayout::HrD3D11RenderLayout()
{
	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;
}

ID3D11InputLayout* HrD3D11RenderLayout::GetInputLayout()
{
	return m_pInputLayout;
}

ID3D11Buffer* HrD3D11RenderLayout::GetVertexBuffer()
{
	return m_pVertexBuffer;
}
