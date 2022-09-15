#ifndef _ShaderTextureLight
#define _ShaderTextureLight

#include "ShaderBase.h"

struct ID3D11Buffer;
struct ID3D11Device;

// forward declaration
class Texture;

class ShaderTextureLight : public ShaderBase
{
public:
	ShaderTextureLight();
	ShaderTextureLight(const ShaderTextureLight&) = delete;				 // Copy constructor
	ShaderTextureLight(ShaderTextureLight&&) = default;                  // Move constructor
	ShaderTextureLight& operator=(const ShaderTextureLight&) = default;  // Copy assignment operator
	ShaderTextureLight& operator=(ShaderTextureLight&&) = default;       // Move assignment operator
	~ShaderTextureLight();		  							             // Destructor

	void SetToContext(ID3D11DeviceContext* devcon) override;
	void ShaderTextureLight::SetTextureResourceAndSampler(Texture* tex);

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp);
	void SetPointLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp);
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFogValues(const float& fogStart, const float& fogRange, const Vect& fogColor);

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData[3];

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData[3];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWorldAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight[3];
		SpotLight SptLight[3];
		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;

	struct FogValues
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	ID3D11Buffer* mpBufferFogValues;
};

#endif _ShaderTextureLight

