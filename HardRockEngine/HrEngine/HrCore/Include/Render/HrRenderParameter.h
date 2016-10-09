#ifndef _HR_RENDERPARAMETER_H_
#define _HR_RENDERPARAMETER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderParameter
	{
	public:
		enum EnumRenderParamType
		{
			RPT_WORLD_MATRIX,
			/// The current world matrix, inverted
			RPT_INVERSE_WORLD_MATRIX,
			/** Provides transpose of world matrix.
			Equivalent to RenderMonkey's "WorldTranspose".
			*/
			RPT_TRANSPOSE_WORLD_MATRIX,
			/// The current world matrix, inverted & transposed
			RPT_INVERSE_TRANSPOSE_WORLD_MATRIX,

			/// The current array of world matrices, as a 3x4 matrix, used for blending
			RPT_WORLD_MATRIX_ARRAY_3x4,
			/// The current array of world matrices, used for blending
			RPT_WORLD_MATRIX_ARRAY,
			/// The current array of world matrices transformed to an array of dual quaternions, represented as a 2x4 matrix
			RPT_WORLD_DUALQUATERNION_ARRAY_2x4,
			/// The scale and shear components of the current array of world matrices
			RPT_WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4,

			/// The current view matrix
			RPT_VIEW_MATRIX,
			/// The current view matrix, inverted
			RPT_INVERSE_VIEW_MATRIX,
			/** Provides transpose of view matrix.
			Equivalent to RenderMonkey's "ViewTranspose".
			*/
			RPT_TRANSPOSE_VIEW_MATRIX,
			/** Provides inverse transpose of view matrix.
			Equivalent to RenderMonkey's "ViewInverseTranspose".
			*/
			RPT_INVERSE_TRANSPOSE_VIEW_MATRIX,


			/// The current projection matrix
			RPT_PROJECTION_MATRIX,
			/** Provides inverse of projection matrix.
			Equivalent to RenderMonkey's "ProjectionInverse".
			*/
			RPT_INVERSE_PROJECTION_MATRIX,
			/** Provides transpose of projection matrix.
			Equivalent to RenderMonkey's "ProjectionTranspose".
			*/
			RPT_TRANSPOSE_PROJECTION_MATRIX,
			/** Provides inverse transpose of projection matrix.
			Equivalent to RenderMonkey's "ProjectionInverseTranspose".
			*/
			RPT_INVERSE_TRANSPOSE_PROJECTION_MATRIX,


			/// The current view & projection matrices concatenated
			RPT_VIEWPROJ_MATRIX,
			/** Provides inverse of concatenated view and projection matrices.
			Equivalent to RenderMonkey's "ViewProjectionInverse".
			*/
			RPT_INVERSE_VIEWPROJ_MATRIX,
			/** Provides transpose of concatenated view and projection matrices.
			Equivalent to RenderMonkey's "ViewProjectionTranspose".
			*/
			RPT_TRANSPOSE_VIEWPROJ_MATRIX,
			/** Provides inverse transpose of concatenated view and projection matrices.
			Equivalent to RenderMonkey's "ViewProjectionInverseTranspose".
			*/
			RPT_INVERSE_TRANSPOSE_VIEWPROJ_MATRIX,


			/// The current world & view matrices concatenated
			RPT_WORLDVIEW_MATRIX,
			/// The current world & view matrices concatenated, then inverted
			RPT_INVERSE_WORLDVIEW_MATRIX,
			/** Provides transpose of concatenated world and view matrices.
			Equivalent to RenderMonkey's "WorldViewTranspose".
			*/
			RPT_TRANSPOSE_WORLDVIEW_MATRIX,
			/// The current world & view matrices concatenated, then inverted & transposed
			RPT_INVERSE_TRANSPOSE_WORLDVIEW_MATRIX,
			/// view matrices.


			/// The current world, view & projection matrices concatenated
			RPT_WORLDVIEWPROJ_MATRIX,
			/** Provides inverse of concatenated world, view and projection matrices.
			Equivalent to RenderMonkey's "WorldViewProjectionInverse".
			*/
			RPT_INVERSE_WORLDVIEWPROJ_MATRIX,
			/** Provides transpose of concatenated world, view and projection matrices.
			Equivalent to RenderMonkey's "WorldViewProjectionTranspose".
			*/
			RPT_TRANSPOSE_WORLDVIEWPROJ_MATRIX,
			/** Provides inverse transpose of concatenated world, view and projection
			matrices. Equivalent to RenderMonkey's "WorldViewProjectionInverseTranspose".
			*/
			RPT_INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX,


			/// render target related values
			/** -1 if requires texture flipping, +1 otherwise. It's useful when you bypassed
			projection matrix transform, still able use this value to adjust transformed y position.
			*/
			RPT_RENDER_TARGET_FLIPPING,

			/** -1 if the winding has been inverted (e.g. for reflections), +1 otherwise.
			*/
			RPT_VERTEX_WINDING,

			/// Fog colour
			RPT_FOG_COLOUR,
			/// Fog params: density, linear start, linear end, 1/(end-start)
			RPT_FOG_PARAMS,


			/// Surface ambient colour, as set in Pass::setAmbient
			RPT_SURFACE_AMBIENT_COLOUR,
			/// Surface diffuse colour, as set in Pass::setDiffuse
			RPT_SURFACE_DIFFUSE_COLOUR,
			/// Surface specular colour, as set in Pass::setSpecular
			RPT_SURFACE_SPECULAR_COLOUR,
			/// Surface emissive colour, as set in Pass::setSelfIllumination
			RPT_SURFACE_EMISSIVE_COLOUR,
			/// Surface shininess, as set in Pass::setShininess
			RPT_SURFACE_SHININESS,
			/// Surface alpha rejection value, not as set in Pass::setAlphaRejectionValue, but a floating number between 0.0f and 1.0f instead (255.0f / Pass::getAlphaRejectionValue())
			RPT_SURFACE_ALPHA_REJECTION_VALUE,


			/// The number of active light sources (better than gl_MaxLights)
			RPT_LIGHT_COUNT,


			/// The ambient light colour set in the scene
			RPT_AMBIENT_LIGHT_COLOUR,

			/// Light diffuse colour (index determined by setAutoConstant call)
			RPT_LIGHT_DIFFUSE_COLOUR,
			/// Light specular colour (index determined by setAutoConstant call)
			RPT_LIGHT_SPECULAR_COLOUR,
			/// Light attenuation parameters, Vector4(range, constant, linear, quadric)
			RPT_LIGHT_ATTENUATION,
			/** Spotlight parameters, Vector4(innerFactor, outerFactor, falloff, isSpot)
			innerFactor and outerFactor are cos(angle/2)
			The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
			Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively
			*/
			RPT_SPOTLIGHT_PARAMS,
			/// A light position in world space (index determined by setAutoConstant call)
			RPT_LIGHT_POSITION,
			/// A light position in object space (index determined by setAutoConstant call)
			RPT_LIGHT_POSITION_OBJECT_SPACE,
			/// A light position in view space (index determined by setAutoConstant call)
			RPT_LIGHT_POSITION_VIEW_SPACE,
			/// A light direction in world space (index determined by setAutoConstant call)
			RPT_LIGHT_DIRECTION,
			/// A light direction in object space (index determined by setAutoConstant call)
			RPT_LIGHT_DIRECTION_OBJECT_SPACE,
			/// A light direction in view space (index determined by setAutoConstant call)
			RPT_LIGHT_DIRECTION_VIEW_SPACE,
			/** The distance of the light from the center of the object
			a useful approximation as an alternative to per-vertex distance
			calculations.
			*/
			RPT_LIGHT_DISTANCE_OBJECT_SPACE,
			/** Light power level, a single scalar as set in Light::setPowerScale  (index determined by setAutoConstant call) */
			RPT_LIGHT_POWER_SCALE,
			/// Light diffuse colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
			RPT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED,
			/// Light specular colour pre-scaled by Light::setPowerScale (index determined by setAutoConstant call)
			RPT_LIGHT_SPECULAR_COLOUR_POWER_SCALED,
			/// Array of light diffuse colours (count set by extra param)
			RPT_LIGHT_DIFFUSE_COLOUR_ARRAY,
			/// Array of light specular colours (count set by extra param)
			RPT_LIGHT_SPECULAR_COLOUR_ARRAY,
			/// Array of light diffuse colours scaled by light power (count set by extra param)
			RPT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY,
			/// Array of light specular colours scaled by light power (count set by extra param)
			RPT_LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY,
			/// Array of light attenuation parameters, Vector4(range, constant, linear, quadric) (count set by extra param)
			RPT_LIGHT_ATTENUATION_ARRAY,
			/// Array of light positions in world space (count set by extra param)
			RPT_LIGHT_POSITION_ARRAY,
			/// Array of light positions in object space (count set by extra param)
			RPT_LIGHT_POSITION_OBJECT_SPACE_ARRAY,
			/// Array of light positions in view space (count set by extra param)
			RPT_LIGHT_POSITION_VIEW_SPACE_ARRAY,
			/// Array of light directions in world space (count set by extra param)
			RPT_LIGHT_DIRECTION_ARRAY,
			/// Array of light directions in object space (count set by extra param)
			RPT_LIGHT_DIRECTION_OBJECT_SPACE_ARRAY,
			/// Array of light directions in view space (count set by extra param)
			RPT_LIGHT_DIRECTION_VIEW_SPACE_ARRAY,
			/** Array of distances of the lights from the center of the object
			a useful approximation as an alternative to per-vertex distance
			calculations. (count set by extra param)
			*/
			RPT_LIGHT_DISTANCE_OBJECT_SPACE_ARRAY,
			/** Array of light power levels, a single scalar as set in Light::setPowerScale
			(count set by extra param)
			*/
			RPT_LIGHT_POWER_SCALE_ARRAY,
			/** Spotlight parameters array of Vector4(innerFactor, outerFactor, falloff, isSpot)
			innerFactor and outerFactor are cos(angle/2)
			The isSpot parameter is 0.0f for non-spotlights, 1.0f for spotlights.
			Also for non-spotlights the inner and outer factors are 1 and nearly 1 respectively.
			(count set by extra param)
			*/
			RPT_SPOTLIGHT_PARAMS_ARRAY,

			/** The derived ambient light colour, with 'r', 'g', 'b' components filled with
			product of surface ambient colour and ambient light colour, respectively,
			and 'a' component filled with surface ambient alpha component.
			*/
			RPT_DERIVED_AMBIENT_LIGHT_COLOUR,
			/** The derived scene colour, with 'r', 'g' and 'b' components filled with sum
			of derived ambient light colour and surface emissive colour, respectively,
			and 'a' component filled with surface diffuse alpha component.
			*/
			RPT_DERIVED_SCENE_COLOUR,

			/** The derived light diffuse colour (index determined by setAutoConstant call),
			with 'r', 'g' and 'b' components filled with product of surface diffuse colour,
			light power scale and light diffuse colour, respectively, and 'a' component filled with surface
			diffuse alpha component.
			*/
			RPT_DERIVED_LIGHT_DIFFUSE_COLOUR,
			/** The derived light specular colour (index determined by setAutoConstant call),
			with 'r', 'g' and 'b' components filled with product of surface specular colour
			and light specular colour, respectively, and 'a' component filled with surface
			specular alpha component.
			*/
			RPT_DERIVED_LIGHT_SPECULAR_COLOUR,

			/// Array of derived light diffuse colours (count set by extra param)
			RPT_DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY,
			/// Array of derived light specular colours (count set by extra param)
			RPT_DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY,
			/** The absolute light number of a local light index. Each pass may have
			a number of lights passed to it, and each of these lights will have
			an index in the overall light list, which will differ from the local
			light index due to factors like setStartLight and setIteratePerLight.
			This binding provides the global light index for a local index.
			*/
			RPT_LIGHT_NUMBER,
			/// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
			RPT_LIGHT_CASTS_SHADOWS,
			/// Returns (int) 1 if the  given light casts shadows, 0 otherwise (index set in extra param)
			RPT_LIGHT_CASTS_SHADOWS_ARRAY,


			/** The distance a shadow volume should be extruded when using
			finite extrusion programs.
			*/
			RPT_SHADOW_EXTRUSION_DISTANCE,
			/// The current camera's position in world space
			RPT_CAMERA_POSITION,
			/// The current camera's position in object space
			RPT_CAMERA_POSITION_OBJECT_SPACE,
			/// The view/projection matrix of the assigned texture projection frustum
			RPT_TEXTURE_VIEWPROJ_MATRIX,
			/// Array of view/projection matrices of the first n texture projection frustums
			RPT_TEXTURE_VIEWPROJ_MATRIX_ARRAY,
			/** The view/projection matrix of the assigned texture projection frustum,
			combined with the current world matrix
			*/
			RPT_TEXTURE_WORLDVIEWPROJ_MATRIX,
			/// Array of world/view/projection matrices of the first n texture projection frustums
			RPT_TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY,
			/// The view/projection matrix of a given spotlight
			RPT_SPOTLIGHT_VIEWPROJ_MATRIX,
			/// Array of view/projection matrix of a given spotlight
			RPT_SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY,
			/** The view/projection matrix of a given spotlight projection frustum,
			combined with the current world matrix
			*/
			RPT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX,
			/** An array of the view/projection matrix of a given spotlight projection frustum,
			combined with the current world matrix
			*/
			RPT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX_ARRAY,
			/// A custom parameter which will come from the renderable, using 'data' as the identifier
			RPT_CUSTOM,
			/** provides current elapsed time
			*/
			RPT_TIME,
			/** Single float value, which repeats itself based on given as
			parameter "cycle time". Equivalent to RenderMonkey's "Time0_X".
			*/
			RPT_TIME_0_X,
			/// Cosine of "Time0_X". Equivalent to RenderMonkey's "CosTime0_X".
			RPT_COSTIME_0_X,
			/// Sine of "Time0_X". Equivalent to RenderMonkey's "SinTime0_X".
			RPT_SINTIME_0_X,
			/// Tangent of "Time0_X". Equivalent to RenderMonkey's "TanTime0_X".
			RPT_TANTIME_0_X,
			/** Vector of "Time0_X", "SinTime0_X", "CosTime0_X",
			"TanTime0_X". Equivalent to RenderMonkey's "Time0_X_Packed".
			*/
			RPT_TIME_0_X_PACKED,
			/** Single float value, which represents scaled time value [0..1],
			which repeats itself based on given as parameter "cycle time".
			Equivalent to RenderMonkey's "Time0_1".
			*/
			RPT_TIME_0_1,
			/// Cosine of "Time0_1". Equivalent to RenderMonkey's "CosTime0_1".
			RPT_COSTIME_0_1,
			/// Sine of "Time0_1". Equivalent to RenderMonkey's "SinTime0_1".
			RPT_SINTIME_0_1,
			/// Tangent of "Time0_1". Equivalent to RenderMonkey's "TanTime0_1".
			RPT_TANTIME_0_1,
			/** Vector of "Time0_1", "SinTime0_1", "CosTime0_1",
			"TanTime0_1". Equivalent to RenderMonkey's "Time0_1_Packed".
			*/
			RPT_TIME_0_1_PACKED,
			/** Single float value, which represents scaled time value [0..2*Pi],
			which repeats itself based on given as parameter "cycle time".
			Equivalent to RenderMonkey's "Time0_2PI".
			*/
			RPT_TIME_0_2PI,
			/// Cosine of "Time0_2PI". Equivalent to RenderMonkey's "CosTime0_2PI".
			RPT_COSTIME_0_2PI,
			/// Sine of "Time0_2PI". Equivalent to RenderMonkey's "SinTime0_2PI".
			RPT_SINTIME_0_2PI,
			/// Tangent of "Time0_2PI". Equivalent to RenderMonkey's "TanTime0_2PI".
			RPT_TANTIME_0_2PI,
			/** Vector of "Time0_2PI", "SinTime0_2PI", "CosTime0_2PI",
			"TanTime0_2PI". Equivalent to RenderMonkey's "Time0_2PI_Packed".
			*/
			RPT_TIME_0_2PI_PACKED,
			/// provides the scaled frame time, returned as a floating point value.
			RPT_FRAME_TIME,
			/// provides the calculated frames per second, returned as a floating point value.
			RPT_FPS,
			/// viewport-related values
			/** Current viewport width (in pixels) as floating point value.
			Equivalent to RenderMonkey's "ViewportWidth".
			*/
			RPT_VIEWPORT_WIDTH,
			/** Current viewport height (in pixels) as floating point value.
			Equivalent to RenderMonkey's "ViewportHeight".
			*/
			RPT_VIEWPORT_HEIGHT,
			/** This variable represents 1.0/ViewportWidth.
			Equivalent to RenderMonkey's "ViewportWidthInverse".
			*/
			RPT_INVERSE_VIEWPORT_WIDTH,
			/** This variable represents 1.0/ViewportHeight.
			Equivalent to RenderMonkey's "ViewportHeightInverse".
			*/
			RPT_INVERSE_VIEWPORT_HEIGHT,
			/** Packed of "ViewportWidth", "ViewportHeight", "ViewportWidthInverse",
			"ViewportHeightInverse".
			*/
			RPT_VIEWPORT_SIZE,

			/// view parameters
			/** This variable provides the view direction vector (world space).
			Equivalent to RenderMonkey's "ViewDirection".
			*/
			RPT_VIEW_DIRECTION,
			/** This variable provides the view side vector (world space).
			Equivalent to RenderMonkey's "ViewSideVector".
			*/
			RPT_VIEW_SIDE_VECTOR,
			/** This variable provides the view up vector (world space).
			Equivalent to RenderMonkey's "ViewUpVector".
			*/
			RPT_VIEW_UP_VECTOR,
			/** This variable provides the field of view as a floating point value.
			Equivalent to RenderMonkey's "FOV".
			*/
			RPT_FOV,
			/** This variable provides the near clip distance as a floating point value.
			Equivalent to RenderMonkey's "NearClipPlane".
			*/
			RPT_NEAR_CLIP_DISTANCE,
			/** This variable provides the far clip distance as a floating point value.
			Equivalent to RenderMonkey's "FarClipPlane".
			*/
			RPT_FAR_CLIP_DISTANCE,

			/** provides the pass index number within the technique
			of the active materil.
			*/
			RPT_PASS_NUMBER,

			/** provides the current iteration number of the pass. The iteration
			number is the number of times the current render operation has
			been drawn for the active pass.
			*/
			RPT_PASS_ITERATION_NUMBER,


			/** Provides a parametric animation value [0..1], only available
			where the renderable specifically implements it.
			*/
			RPT_ANIMATION_PARAMETRIC,

			/** Provides the texel offsets required by this rendersystem to map
			texels to pixels. Packed as
			float4(absoluteHorizontalOffset, absoluteVerticalOffset,
			horizontalOffset / viewportWidth, verticalOffset / viewportHeight)
			*/
			RPT_TEXEL_OFFSETS,

			/** Provides information about the depth range of the scene as viewed
			from the current camera.
			Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
			*/
			RPT_SCENE_DEPTH_RANGE,

			/** Provides information about the depth range of the scene as viewed
			from a given shadow camera. Requires an index parameter which maps
			to a light index relative to the current light list.
			Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
			*/
			RPT_SHADOW_SCENE_DEPTH_RANGE,

			/** Provides an array of information about the depth range of the scene as viewed
			from a given shadow camera. Requires an index parameter which maps
			to a light index relative to the current light list.
			Passed as float4(minDepth, maxDepth, depthRange, 1 / depthRange)
			*/
			RPT_SHADOW_SCENE_DEPTH_RANGE_ARRAY,

			/** Provides the fixed shadow colour as configured via SceneManager::setShadowColour;
			useful for integrated modulative shadows.
			*/
			RPT_SHADOW_COLOUR,
			/** Provides texture size of the texture unit (index determined by setAutoConstant
			call). Packed as float4(width, height, depth, 1)
			*/
			RPT_TEXTURE_SIZE,
			/** Provides inverse texture size of the texture unit (index determined by setAutoConstant
			call). Packed as float4(1 / width, 1 / height, 1 / depth, 1)
			*/
			RPT_INVERSE_TEXTURE_SIZE,
			/** Provides packed texture size of the texture unit (index determined by setAutoConstant
			call). Packed as float4(width, height, 1 / width, 1 / height)
			*/
			RPT_PACKED_TEXTURE_SIZE,

			/** Provides the current transform matrix of the texture unit (index determined by setAutoConstant
			call), as seen by the fixed-function pipeline.
			*/
			RPT_TEXTURE_MATRIX,

			/** Provides the position of the LOD camera in world space, allowing you
			to perform separate LOD calculations in shaders independent of the rendering
			camera. If there is no separate LOD camera then this is the real camera
			position. See Camera::setLodCamera.
			*/
			RPT_LOD_CAMERA_POSITION,
			/** Provides the position of the LOD camera in object space, allowing you
			to perform separate LOD calculations in shaders independent of the rendering
			camera. If there is no separate LOD camera then this is the real camera
			position. See Camera::setLodCamera.
			*/
			RPT_LOD_CAMERA_POSITION_OBJECT_SPACE,
			/** Binds custom per-light constants to the shaders. */
			RPT_LIGHT_CUSTOM,

			RPT_UNKNOWN = 999
		};

		enum EnumRenderParamDataType
		{
			RPDT_FLOAT,
		};

		HrRenderParameter();
		~HrRenderParameter();

	public:
		HR_SYNTHESIZE_PASS_BY_REF(std::string, m_strName, Name);
		HR_SYNTHESIZE(EnumRenderParamType, m_paramType, ParamType);
		HR_SYNTHESIZE(EnumRenderParamDataType, m_dataType, RenderParamDataType);
		HR_SYNTHESIZE(uint32, m_nStartOffset, StartOffset);
	};
}

#endif


