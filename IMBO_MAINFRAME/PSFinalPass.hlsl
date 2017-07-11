
sampler gSampler : register(s0);

texture2D gAlbedoTexture : register(t1);
texture2D gAlphaTexture : register(t2);
texture2D gSkyBoxTexture : register(t3);
texture2D gDistTexture : register(t4);


struct VS_TEXTURED_OUTPUT {
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET
{
	float2		Trans = input.texCoord;
	float4		Noise = gDistTexture.Sample(gSampler, Trans);
	//float4		Noise = tex2D(DistortionSampler, Trans);
	float2		UV = input.texCoord + Noise.xy * 0.05f;		// 0.05 -> ø÷∞Ó¿« ¡§µµ


	float Alpha = gAlphaTexture.Sample(gSampler, UV).r;
	float4 AlbedoColor = gAlbedoTexture.Sample(gSampler, UV);
	float4 SkyboxColor = gSkyBoxTexture.Sample(gSampler, UV);

	if (Alpha == 0)return SkyboxColor;
	else if (Alpha == 1)return AlbedoColor;
	return 	SkyboxColor + AlbedoColor * (Alpha + 0.01);
}