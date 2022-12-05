#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;
 
uniform vec3 viewPos; 
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightEnd;

uniform sampler2D texture1;

float spotCutoff = 30.0;
float e = 2.7183;
float densidad = 0.5;

void main() {
    
    // ambient
    float ambientI = 0.4 ;
    vec3 ambient = ambientI * lightColor;
  	
    vec3 ld = normalize(lightEnd-lightPos);
    vec3 fd = normalize(vec3(FragPos - lightPos));
    float d = sqrt(pow(FragPos.x - lightPos.x,2) + pow(FragPos.y - lightPos.y, 2) + pow(FragPos.z - lightPos.z, 2));

    float f = pow(e, -(densidad*d));
    

    if(acos(dot(fd, ld)) < radians(spotCutoff)){
         
        //diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        //Specular
        float specularStrength = 2.0;
   	    vec3 viewDir = normalize(viewPos - FragPos);
	    vec3 reflectDir = reflect(-lightDir, norm);
	    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	    vec3 specular = specularStrength * spec * lightColor;

        vec3 result = (ambient+ diffuse + specular) * objectColor * f;
        FragColor = vec4(result, 1.0)*texture(texture1, TexCoord);
        
       
    }else{

        vec3 result = ambient * objectColor*f;
        FragColor = vec4(result, 1.0)*texture(texture1, TexCoord);

    }


} 
