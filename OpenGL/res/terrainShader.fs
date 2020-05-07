#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

// Texture information
uniform samples2D texture_1;
uniform samples2D texture_2;
uniform samples2D texture_3;

// Inputs from vertexshader
in float normalizedHeight;

void main()
{
	
	//gl_FragColor = texture2D(sampler, texCoord0) * 
	//	clamp(dot(-lightDirection, normal0), 0.0, 1.0);


	if (normalizedHeight < 0.1)
	{
		gl_FragColor = texture2D(texture_1, texCoord0) * 
			clamp(dot(-lightDirection, normal0), 0.0, 1.0);
	}
	else if (normalizedHeight < 0.2 & normalizedHeight >=0.1)
	{
		gl_FragColor = (texture2D(texture_1, texCoord0)*(normalizedHeight - 0.1) 
					+ texture2D(texture_2, texCoord0)*(0.2 - normalizedHeight)) *
					clamp(dot(-lightDirection,normal0),0.0,1.0));
	}
	else if (normalizedHeight < 0.5 & normalizedHeight >= 0.2)
	{
		gl_FragColor = (texture2D(texture_2,texCoord0) * 
					clamp(dot(-lightDirection, normal0), 0.0, 1.0));
	}
	else if (normalizedHeight < 0.65 & normalizedHeight >= 0.5)
	{
		gl_FragColor = (texture2D(texture_2, texCoord0)*(normalizedHeight - 0.5) 
				+ texture2D(texture_3, texCoord0)*(0.65 - normalizedHeight)) *
				clamp(dot(-lightDirection,normal0),0.0,1.0));
	}
	else if (normalizedHeight < 1.0)
	{
		gl_FragColor = (texture2D(texture_3,texCoord0) * 
				clamp(dot(-lightDirection, normal0), 0.0, 1.0));
	}
	else{
		gl_FragColor = (texture2D(texture_1,texCoord0) * 
				clamp(dot(-lightDirection, normal0), 0.0, 1.0));
	}

	//vec4 text1C = texture2D(texture_1, texCoord0);
	//vec4 text2C = texture2D(texture_2, texCoord0);
	//vec4 text3C = texture2D(texture_3, texCoord0);

	//vec4 texMult = text1C * text2C;
	//vec4 texHeightColor = text1C * (10.f - gl_Position.y);
	//texHeightColor += text2C * gl_Position;
	//color = clamp(texHeightColor, 0.f, 1.f);

	//out_Color = color;

}
