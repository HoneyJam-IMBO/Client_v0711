
Texture2D    gtxtDefault : register(t5);
SamplerState gssWRAP_LINEAR : register(s0);

struct PS_OUT {
	float4 Color : SV_TARGET0;
	float4 Alpha : SV_TARGET1;
};
struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};
PS_OUT main(VSOutput input) : SV_TARGET
{
	PS_OUT output = (PS_OUT)0;

	output.Color = gtxtDefault.Sample(gssWRAP_LINEAR, input.texCoord);
	output.Alpha = float4(output.Color.a, 0.f, 0.f, 1.f);
	return output;	
}