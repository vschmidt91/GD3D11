#include "pch.h"
#include "D3D11FullscreenQuad.h"

using namespace DirectX;

D3D11FullscreenQuad::D3D11FullscreenQuad() {
	QuadVB = nullptr;
}


D3D11FullscreenQuad::~D3D11FullscreenQuad() {
	if ( QuadVB )QuadVB->Release();
}

HRESULT D3D11FullscreenQuad::CreateQuad( ID3D11Device* device ) {
	SimpleVertexStruct* vx = new SimpleVertexStruct[6];
	UINT CurVertex = 0;

	/*FarCornersA4[0]		= DirectX::XMFLOAT3(-farX,  farY, farZ);
	FarCornersA4[1]		= DirectX::XMFLOAT3(farX,  farY, farZ);
	FarCornersA4[2]		= DirectX::XMFLOAT3(farX, -farY, farZ);
	FarCornersA4[3]		= DirectX::XMFLOAT3(-farX, -farY, farZ);*/

	vx[0].Position = XMFLOAT3( -1, -1, 0 );
	vx[0].TexCoord = XMFLOAT2( 0, 1 );

	vx[1].Position = XMFLOAT3( -1, 1, 0 );
	vx[1].TexCoord = XMFLOAT2( 0, 0 );

	vx[2].Position = XMFLOAT3( 1, -1, 0 );
	vx[2].TexCoord = XMFLOAT2( 1, 1 );


	vx[3].Position = XMFLOAT3( 1, 1, 0 );
	vx[3].TexCoord = XMFLOAT2( 1, 0 );

	vx[4].Position = XMFLOAT3( 1, -1, 0 );
	vx[4].TexCoord = XMFLOAT2( 1, 1 );

	vx[5].Position = XMFLOAT3( -1, 1, 0 );
	vx[5].TexCoord = XMFLOAT2( 0, 0 );


	//Create the vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = 6 * sizeof( SimpleVertexStruct );
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = &vx[0];
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	device->CreateBuffer( &bufferDesc, &InitData, &QuadVB );

	delete [] vx;

	return S_OK;
}