// diffusion.fs
#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;

void main()
{
    vec2 texel = 1.0 / resolution;
    vec4 sum = vec4(0.0);

	sum += texture(texture0, fragTexCoord + texel * vec2(-1, -1)) * 0.025;
    sum += texture(texture0, fragTexCoord + texel * vec2( 0, -1)) * 0.10;
    sum += texture(texture0, fragTexCoord + texel * vec2( 1, -1)) * 0.025;

    sum += texture(texture0, fragTexCoord + texel * vec2(-1,  0)) * 0.10;
    sum += texture(texture0, fragTexCoord + texel * vec2( 0,  0)) * 0.50;
    sum += texture(texture0, fragTexCoord + texel * vec2( 1,  0)) * 0.10;

    sum += texture(texture0, fragTexCoord + texel * vec2(-1,  1)) * 0.025;
    sum += texture(texture0, fragTexCoord + texel * vec2( 0,  1)) * 0.10;
    sum += texture(texture0, fragTexCoord + texel * vec2( 1,  1)) * 0.025;

	sum.rgb -= vec3(0.005);

	if (sum.g > 0.3) {
		sum.b += 0.01;
	}
    sum.rgb = max(sum.rgb, 0.0);
	finalColor = sum;
}

