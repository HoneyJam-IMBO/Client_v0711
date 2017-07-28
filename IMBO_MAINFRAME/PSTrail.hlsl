
Texture2D    gtxtDefault : register(t0);
SamplerState gssWRAP_LINEAR : register(s0);
struct PS_OUT {
	float4 Color : SV_TARGET0;
	//float4 Normal : SV_TARGET1;
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
	return output;	
}