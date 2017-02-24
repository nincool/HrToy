#ifndef _HR_PIXELFORMAT_H_
#define _HR_PIXELFORMAT_H_

namespace Hr
{
	enum EnumPixelFormat
	{
		/// Unknown pixel format.
		PF_UNKNOWN = 0,
		/// 8-bit pixel format, all bits luminance.
		PF_L8 = 1,
		PF_BYTE_L = PF_L8,
		/// 16-bit pixel format, all bits luminance.
		PF_L16 = 2,
		PF_SHORT_L = PF_L16,
		/// 8-bit pixel format, all bits alpha.
		PF_A8 = 3,
		PF_BYTE_A = PF_A8,
		/// 8-bit pixel format, 4 bits alpha, 4 bits luminance.
		PF_A4L4 = 4,
		/// 2 byte pixel format, 1 byte luminance, 1 byte alpha
		PF_BYTE_LA = 5,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_R5G6B5 = 6,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_B5G6R5 = 7,
		/// 8-bit pixel format, 2 bits blue, 3 bits green, 3 bits red.
		PF_R3G3B2 = 31,
		/// 16-bit pixel format, 4 bits for alpha, red, green and blue.
		PF_A4R4G4B4 = 8,
		/// 16-bit pixel format, 5 bits for blue, green, red and 1 for alpha.
		PF_A1R5G5B5 = 9,
		/// 24-bit pixel format, 8 bits for red, green and blue.
		PF_R8G8B8 = 10,
		/// 24-bit pixel format, 8 bits for blue, green and red.
		PF_B8G8R8 = 11,
		/// 32-bit pixel format, 8 bits for alpha, red, green and blue.
		PF_A8R8G8B8 = 12,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_A8B8G8R8 = 13,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_B8G8R8A8 = 14,
		/// 32-bit pixel format, 8 bits for red, green, blue and alpha.
		PF_R8G8B8A8 = 28,
		/// 32-bit pixel format, 8 bits for red, 8 bits for green, 8 bits for blue
		/// like PF_A8R8G8B8, but alpha will get discarded
		PF_X8R8G8B8 = 26,
		/// 32-bit pixel format, 8 bits for blue, 8 bits for green, 8 bits for red
		/// like PF_A8B8G8R8, but alpha will get discarded
		PF_X8B8G8R8 = 27,

		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		PF_BYTE_RGB = PF_B8G8R8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		PF_BYTE_BGR = PF_R8G8B8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		PF_BYTE_BGRA = PF_A8R8G8B8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		PF_BYTE_RGBA = PF_A8B8G8R8,
	 
		/// 32-bit pixel format, 2 bits for alpha, 10 bits for red, green and blue.
		PF_A2R10G10B10 = 15,
		/// 32-bit pixel format, 10 bits for blue, green and red, 2 bits for alpha.
		PF_A2B10G10R10 = 16,
		/// DDS (DirectDraw Surface) DXT1 format
		PF_DXT1 = 17,
		/// DDS (DirectDraw Surface) DXT2 format
		PF_DXT2 = 18,
		/// DDS (DirectDraw Surface) DXT3 format
		PF_DXT3 = 19,
		/// DDS (DirectDraw Surface) DXT4 format
		PF_DXT4 = 20,
		/// DDS (DirectDraw Surface) DXT5 format
		PF_DXT5 = 21,
		/// 16-bit pixel format, 16 bits (float) for red
		PF_FLOAT16_R = 32,
		/// 48-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue
		PF_FLOAT16_RGB = 22,
		/// 64-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue, 16 bits (float) for alpha
		PF_FLOAT16_RGBA = 23,
		// 32-bit pixel format, 32 bits (float) for red
		PF_FLOAT32_R = 33,
		/// 96-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue
		PF_FLOAT32_RGB = 24,
		/// 128-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue, 32 bits (float) for alpha
		PF_FLOAT32_RGBA = 25,
		/// 32-bit, 2-channel s10e5 floating point pixel format, 16-bit green, 16-bit red
		PF_FLOAT16_GR = 35,
		/// 64-bit, 2-channel floating point pixel format, 32-bit green, 32-bit red
		PF_FLOAT32_GR = 36,
		/// Depth texture format
		PF_DEPTH = 29,
		/// 64-bit pixel format, 16 bits for red, green, blue and alpha
		PF_SHORT_RGBA = 30,
		/// 32-bit pixel format, 16-bit green, 16-bit red
		PF_SHORT_GR = 34,
		/// 48-bit pixel format, 16 bits for red, green and blue
		PF_SHORT_RGB = 37,
		/// PVRTC (PowerVR) RGB 2 bpp
		PF_PVRTC_RGB2 = 38,
		/// PVRTC (PowerVR) RGBA 2 bpp
		PF_PVRTC_RGBA2 = 39,
		/// PVRTC (PowerVR) RGB 4 bpp
		PF_PVRTC_RGB4 = 40,
		/// PVRTC (PowerVR) RGBA 4 bpp
		PF_PVRTC_RGBA4 = 41,
		/// PVRTC (PowerVR) Version 2, 2 bpp
		PF_PVRTC2_2BPP = 42,
		/// PVRTC (PowerVR) Version 2, 4 bpp
		PF_PVRTC2_4BPP = 43,
		/// 32-bit pixel format, 11 bits (float) for red, 11 bits (float) for green, 10 bits (float) for blue
		PF_R11G11B10_FLOAT = 44,
		/// 8-bit pixel format, 8 bits red (unsigned int).
		PF_R8_UINT = 45,
		/// 16-bit pixel format, 8 bits red (unsigned int), 8 bits blue (unsigned int).
		PF_R8G8_UINT = 46,
		/// 24-bit pixel format, 8 bits red (unsigned int), 8 bits blue (unsigned int), 8 bits green (unsigned int).
		PF_R8G8B8_UINT = 47,
		/// 32-bit pixel format, 8 bits red (unsigned int), 8 bits blue (unsigned int), 8 bits green (unsigned int), 8 bits alpha (unsigned int).
		PF_R8G8B8A8_UINT = 48,
		/// 16-bit pixel format, 16 bits red (unsigned int).
		PF_R16_UINT = 49,
		/// 32-bit pixel format, 16 bits red (unsigned int), 16 bits blue (unsigned int).
		PF_R16G16_UINT = 50,
		/// 48-bit pixel format, 16 bits red (unsigned int), 16 bits blue (unsigned int), 16 bits green (unsigned int).
		PF_R16G16B16_UINT = 51,
		/// 64-bit pixel format, 16 bits red (unsigned int), 16 bits blue (unsigned int), 16 bits green (unsigned int), 16 bits alpha (unsigned int).
		PF_R16G16B16A16_UINT = 52,
		/// 32-bit pixel format, 32 bits red (unsigned int).
		PF_R32_UINT = 53,
		/// 64-bit pixel format, 32 bits red (unsigned int), 32 bits blue (unsigned int).
		PF_R32G32_UINT = 54,
		/// 96-bit pixel format, 32 bits red (unsigned int), 32 bits blue (unsigned int), 32 bits green (unsigned int).
		PF_R32G32B32_UINT = 55,
		/// 128-bit pixel format, 32 bits red (unsigned int), 32 bits blue (unsigned int), 32 bits green (unsigned int), 32 bits alpha (unsigned int).
		PF_R32G32B32A32_UINT = 56,
		/// 8-bit pixel format, 8 bits red (signed int).
		PF_R8_SINT = 57,
		/// 16-bit pixel format, 8 bits red (signed int), 8 bits blue (signed int).
		PF_R8G8_SINT = 58,
		/// 24-bit pixel format, 8 bits red (signed int), 8 bits blue (signed int), 8 bits green (signed int).
		PF_R8G8B8_SINT = 59,
		/// 32-bit pixel format, 8 bits red (signed int), 8 bits blue (signed int), 8 bits green (signed int), 8 bits alpha (signed int).
		PF_R8G8B8A8_SINT = 60,
		/// 16-bit pixel format, 16 bits red (signed int).
		PF_R16_SINT = 61,
		/// 32-bit pixel format, 16 bits red (signed int), 16 bits blue (signed int).
		PF_R16G16_SINT = 62,
		/// 48-bit pixel format, 16 bits red (signed int), 16 bits blue (signed int), 16 bits green (signed int).
		PF_R16G16B16_SINT = 63,
		/// 64-bit pixel format, 16 bits red (signed int), 16 bits blue (signed int), 16 bits green (signed int), 16 bits alpha (signed int).
		PF_R16G16B16A16_SINT = 64,
		/// 32-bit pixel format, 32 bits red (signed int).
		PF_R32_SINT = 65,
		/// 64-bit pixel format, 32 bits red (signed int), 32 bits blue (signed int).
		PF_R32G32_SINT = 66,
		/// 96-bit pixel format, 32 bits red (signed int), 32 bits blue (signed int), 32 bits green (signed int).
		PF_R32G32B32_SINT = 67,
		/// 128-bit pixel format, 32 bits red (signed int), 32 bits blue (signed int), 32 bits green (signed int), 32 bits alpha (signed int).
		PF_R32G32B32A32_SINT = 68,
		/// 32-bit pixel format, 9 bits for blue, green, red plus a 5 bit exponent.
		PF_R9G9B9E5_SHAREDEXP = 69,
		/// DDS (DirectDraw Surface) BC4 format (unsigned normalised)
		PF_BC4_UNORM = 70,
		/// DDS (DirectDraw Surface) BC4 format (signed normalised)
		PF_BC4_SNORM = 71,
		/// DDS (DirectDraw Surface) BC5 format (unsigned normalised)
		PF_BC5_UNORM = 72,
		/// DDS (DirectDraw Surface) BC5 format (signed normalised)
		PF_BC5_SNORM = 73,
		/// DDS (DirectDraw Surface) BC6H format (unsigned 16 bit float)
		PF_BC6H_UF16 = 74,
		/// DDS (DirectDraw Surface) BC6H format (signed 16 bit float)
		PF_BC6H_SF16 = 75,
		/// DDS (DirectDraw Surface) BC7 format (unsigned normalised)
		PF_BC7_UNORM = 76,
		/// DDS (DirectDraw Surface) BC7 format (unsigned normalised sRGB)
		PF_BC7_UNORM_SRGB = 77,
		/// 8-bit pixel format, all bits red.
		PF_R8 = 78,
		/// 16-bit pixel format, 8 bits red, 8 bits green.
		PF_RG8 = 79,
		/// 8-bit pixel format, 8 bits red (signed normalised int).
		PF_R8_SNORM = 80,
		/// 16-bit pixel format, 8 bits red (signed normalised int), 8 bits blue (signed normalised int).
		PF_R8G8_SNORM = 81,
		/// 24-bit pixel format, 8 bits red (signed normalised int), 8 bits blue (signed normalised int), 8 bits green (signed normalised int).
		PF_R8G8B8_SNORM = 82,
		/// 32-bit pixel format, 8 bits red (signed normalised int), 8 bits blue (signed normalised int), 8 bits green (signed normalised int), 8 bits alpha (signed normalised int).
		PF_R8G8B8A8_SNORM = 83,
		/// 16-bit pixel format, 16 bits red (signed normalised int).
		PF_R16_SNORM = 84,
		/// 32-bit pixel format, 16 bits red (signed normalised int), 16 bits blue (signed normalised int).
		PF_R16G16_SNORM = 85,
		/// 48-bit pixel format, 16 bits red (signed normalised int), 16 bits blue (signed normalised int), 16 bits green (signed normalised int).
		PF_R16G16B16_SNORM = 86,
		/// 64-bit pixel format, 16 bits red (signed normalised int), 16 bits blue (signed normalised int), 16 bits green (signed normalised int), 16 bits alpha (signed normalised int).
		PF_R16G16B16A16_SNORM = 87,
		/// ETC1 (Ericsson Texture Compression)
		PF_ETC1_RGB8 = 88,
		/// ETC2 (Ericsson Texture Compression)
		PF_ETC2_RGB8 = 89,
		/// ETC2 (Ericsson Texture Compression)
		PF_ETC2_RGBA8 = 90,
		/// ETC2 (Ericsson Texture Compression)
		PF_ETC2_RGB8A1 = 91,
		/// ATC (AMD_compressed_ATC_texture)
		PF_ATC_RGB = 92,
		/// ATC (AMD_compressed_ATC_texture)
		PF_ATC_RGBA_EXPLICIT_ALPHA = 93,
		/// ATC (AMD_compressed_ATC_texture)
		PF_ATC_RGBA_INTERPOLATED_ALPHA = 94,
		// Number of pixel formats currently defined
		PF_COUNT = 95
	};

	enum EnumVertexElementUsage
	{
		// vertex positions
		VEU_POSITION = 1,
		// vertex normals included (for lighting)
		VEU_NORMAL = 1 << 1,
		// Vertex -color
		VEU_COLOR = 1 << 9,
		// Vertex blend weights
		VEU_BLENDWEIGHT = 1 << 4,
		// Vertex blend indices
		VEU_BLENDINDEX = 1 << 5,
		// at least one set of texture coords (exact number specified in class)
		VEU_TEXTURECOORD = 1 << 6,
		// Vertex tangent
		VEU_TANGENT = 1 << 7,
		// Vertex binormal
		VEU_BINORMAL = 1 << 8,
	};

	/// Vertex element type, used to identify the base types of the vertex contents
	enum EnumVertexElementType
	{
		VET_FLOAT1 = 0,
		VET_FLOAT2 = 1,
		VET_FLOAT3 = 2,
		VET_FLOAT4 = 3,
		/// alias to more specific colour type - use the current rendersystem's colour packing
		VET_COLOUR = 4,
		VET_SHORT1 = 5,
		VET_SHORT2 = 6,
		VET_SHORT3 = 7,
		VET_SHORT4 = 8,
		VET_UBYTE4 = 9,
		/// D3D style compact colour
		VET_COLOUR_ARGB = 10,
		/// GL style compact colour
		VET_COLOUR_ABGR = 11,
		VET_DOUBLE1 = 12,
		VET_DOUBLE2 = 13,
		VET_DOUBLE3 = 14,
		VET_DOUBLE4 = 15,
		VET_USHORT1 = 16,
		VET_USHORT2 = 17,
		VET_USHORT3 = 18,
		VET_USHORT4 = 19,
		VET_INT1 = 20,
		VET_INT2 = 21,
		VET_INT3 = 22,
		VET_INT4 = 23,
		VET_UINT1 = 24,
		VET_UINT2 = 25,
		VET_UINT3 = 26,
		VET_UINT4 = 27
	};

	//��������
	enum EnumTopologyType
	{
		TT_POINTLIST,
		TT_LINELIST,
		TT_LINETRIP,
		TT_TRIANGLELIST,
		TT_TRIANGLETRIP,
	};

	//indice������������
	enum EnumIndexType
	{
		IT_16BIT,
		IT_32BIT,
	};

	//RasterizerFillMode
	enum EnumRasterizerFillModel
	{
		RFM_WIREFRAME,
		RFM_SOLD,
	};

	//RasterizerCullMode
	enum EnumRasterizerCullModel
	{
		RCM_CULL_NONE,
		RCM_CULL_FRONT,
		RCM_CULL_BACK
	};


}

#endif
