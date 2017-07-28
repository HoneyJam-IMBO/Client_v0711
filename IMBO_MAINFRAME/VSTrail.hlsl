

cbuffer ViewProjectionConstantBuffer : register(b11)
{
	matrix gmtxViewProjection;
};

cbuffer DefaultCB : register(b1) {
	matrix mtxWorld[1000];
};
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};
VS_OUTPUT main(float3 position : POSITION,
				float3 normal : NORMAL,
				float2 tex : TEXCOORD,
				uint instanceID : SV_InstanceID)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = mul(float4(position, 1.f), mtxWorld[instanceID]);
	output.position = mul(output.position, gmtxViewProjection);
	output.texCoord = tex;

	return output;
}