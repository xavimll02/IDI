#version 330 core

in vec3 matambF;
in vec3 matdiffF;
in vec3 matspecF;
in float matshinF;

in vec3 nSCO;
in vec3 vertexSCO;
out vec4 FragColor;
uniform vec3 posFocusC;
uniform vec3 colorFocusC;
uniform vec3 posFocusE;
uniform vec3 colorFocusE;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * matambF;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffF * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinF == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinF);
    return (matspecF * colFocus * shine); 
}

void main()
{	
    vec3 focusCSCO = posFocusC;
    vec3 focusESCO = posFocusE;
    vec3 LC = normalize(focusCSCO - vertexSCO);
    vec3 LE = normalize(focusESCO - vertexSCO);
    vec3 NM = normalize(nSCO);
	FragColor = vec4((Ambient()+Difus(NM,LC,colorFocusC)+Especular(NM, LC, vec4(vertexSCO,1.0), colorFocusC)+Difus(NM,LE,colorFocusE)+Especular(NM,LE,vec4(vertexSCO,1.0),colorFocusE)),1.0);
}
