#version 330 core

in vec3 v_worldPosition;
in vec3 v_normal;
in vec2 v_texCoord;

uniform vec4 u_color;

uniform vec3 u_lightDirection;
uniform vec3 u_lightColor;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(-u_lightDirection);

    float diffuse = max(
        dot(normal, lightDirection),
        0.0
    );

    float ambient = 0.2;

    vec3 lighting =
        u_lightColor *
        (ambient + diffuse);

    FragColor = vec4(
        u_color.rgb * lighting,
        u_color.a
    );
}