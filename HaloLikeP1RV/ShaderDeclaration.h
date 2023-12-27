#pragma once
const char* vertexShaderSourceBase = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;

    }
)";



const char* fragmentShaderSourceBase = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {


    vec4 texColor = texture(texture1, TexCoord); 
    

    FragColor = texColor;
    }
)";





const char* vertexShaderSourceBaseP = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform float closeRange;
    out float outCloseRange;
    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        outCloseRange = closeRange;
    }
)";



const char* fragmentShaderSourceBaseP = R"(
    #version 330 core
    in vec2 TexCoord;
    in float outCloseRange;
    out vec4 FragColor;
    

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    
    texColor.a = outCloseRange;
    FragColor = texColor;
    }
)";


const char* vertexShaderSourceAlpha = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    void main() {
        gl_Position =   model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";
const char* fragmentShaderSourceAlpha = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    texColor.a = 0.7f;

    FragColor = texColor;
    }
)";










const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D texture1; // Texture unit

    void main() {

    vec4 texColor = texture(texture1, TexCoord); 
    vec4 redColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color

    float blendFactor = 0.5; // You can change this value

    FragColor = mix(texColor, redColor, blendFactor);
    }
)";












const char* vertexShaderSourceSkyBox = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    pos = aPos;
    }
)";


const char* fragmentShaderSourceSkyBox = R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 pos;
    const vec4 skytop =vec4(0.0f, 0.0f, 0.2f, 1.0f); 
    const vec4 skyhorizon = vec4(1.0f, 0.5f, 0.0f, 1.0f);
   
    void main() {
        vec3 pointOnSphere = normalize(pos);
        float a = min(pointOnSphere.y+0.8,1.0);

        FragColor =mix(skyhorizon, skytop, a);
       
    }
)";

const char* vertexShaderSourceHealth = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    layout(location = 2) in vec3 normal;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    out vec3 norm;
    void main() {
        gl_Position =   model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0));
        norm = normal;
    }
)";


const char* fragmentShaderSourceHealth = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    in vec3 pos;
    in vec3 norm;
    uniform sampler2D texture1; // Texture unit

    void main() {
        vec3 redColor = vec3(1.0, 0.0, 0.0);

    
        vec3 norma = normalize(norm);
        vec3 lPos = vec3(5,5,0);
        vec3 lightDir = normalize(pos - vec3(0,5,0));
        float diff = max(max(dot(norma, lightDir),0),0.4);
        vec3 diffuse = diff * redColor;

        FragColor =vec4(diffuse, 1.0);
        
    }
)";


const char* vertexShaderSourceSmog = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    layout(location = 2) in vec3 normal;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    out vec2 TexCoord;
    out vec3 pos;
    out vec3 norm;



    void main() {
        gl_Position =   projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0));
        norm = normal;
    }
)";


const char* fragmentShaderSourceSmog = R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 pos;


float rand(vec2 co) {
        return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }
    void main() {
         vec3 pointOnSphere = normalize(pos);

        // Adjust the frequency and amplitude for the noise pattern
        float frequency = 5.0;
        float amplitude = 1.0;

        // Generate noise for the electricity pattern
        float noise = rand(pos.xy * frequency);

        // Create a sine function for periodic variation
        float sineFactor = sin(pos.y * 10.0);

        // Combine noise and sine function for variation
        float electricityPattern = noise + sineFactor;

        // Adjust the color based on the position along the electricity
        vec3 electricityColor = vec3(0.0, 1.0, 1.0); // Adjust color as needed
        electricityColor *= mix(0.2, 1.0, abs(pos.y));

        // Calculate the final color using the combined pattern and base color
        vec3 finalColor = electricityColor * electricityPattern * amplitude;

        // Add some brightness to enhance the effect
        finalColor += vec3(0.2);

        FragColor = vec4(finalColor, 1.0);
        
    }
)";


const char* vertexShaderSourceGround = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform vec3 meteorPos;
    uniform vec3 bossPos;
    uniform float longRadius;
    uniform float t;
    uniform float closeRadius;
    out float outCloseRadius;
    out vec2 TexCoord;
    out vec3 pos;
    out float outLongRadius;
    out float outT;
    out vec3 metPos;
    out vec3 bPos;
    void main() {
        gl_Position =   projection *view *model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        pos = vec3(model * vec4(aPos, 1.0)); 
        outT = t;
        metPos = meteorPos;
        bPos = bossPos;
        outLongRadius = longRadius;
        outCloseRadius = closeRadius;
    }
)";


const char* fragmentShaderSourceGround = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    in float outT;
    in vec3 metPos;
    in vec3 pos;
    in vec3 bPos;
    in float outLongRadius;
    in float outCloseRadius;
    uniform sampler2D texture1; // Texture unit

    void main() {
    float x = outT;
    float distanceToCenter = length(pos.xz - metPos.xz);
    float distanceToBoss = length(pos.xz - bPos.xz);
    vec4 texColor = texture(texture1, TexCoord); 
    vec4 darkEarthBrown = vec4(0.4, 0.2, 0.1,1.0); 
 vec4 orangeColor = vec4(0.7f, 0.35f, 0.0f,1.0f); // Red color
vec4 redColor = vec4(1.0f, 0.0f, 0.0f,1.0f); // Red color

    float blendFactor = 0.5; // You can change this value

    

     if (distanceToCenter <= x) {
        FragColor = mix(texColor, orangeColor, 0.7);

        } 
    else if (distanceToBoss<=outCloseRadius) {

            FragColor = mix(texColor, redColor, blendFactor);
        }
    else if (distanceToBoss>=outLongRadius && distanceToBoss<=(outLongRadius+1.0f) ) {

            FragColor = mix(texColor, redColor, blendFactor);
        }
    else{FragColor = mix(texColor, darkEarthBrown, blendFactor);}
    }
)";
