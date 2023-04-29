#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform vec3 posFocusE1;
uniform vec3 colorFocusE1;
uniform vec3 posFocusE2;
uniform vec3 colorFocusE2;
uniform vec3 posFocusE3;
uniform vec3 colorFocusE3;
uniform vec3 posFocusE4;
uniform vec3 colorFocusE4;
uniform vec3 posFocusM;
uniform vec3 colorFocusM;

uniform mat4 TG;
uniform mat4 TGM;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec3 LE1 = normalize(vec4(View * vec4(posFocusE1,1.0)).xyz - fvertex);
    vec3 LE2 = normalize(vec4(View * vec4(posFocusE2,1.0)).xyz - fvertex);
    vec3 LE3 = normalize(vec4(View * vec4(posFocusE3,1.0)).xyz - fvertex);
    vec3 LE4 = normalize(vec4(View * vec4(posFocusE4,1.0)).xyz - fvertex);
    vec3 LM = normalize(vec4(View * TGM * vec4(posFocusM,1.0)).xyz - fvertex);
    vec3 NM = normalize(fnormal);
    
    vec3 PhongE1 = Difus(NM, LE1, colorFocusE1) + Especular(NM, LE1, fvertex, colorFocusE1);
    vec3 PhongE2 = Difus(NM, LE2, colorFocusE2) + Especular(NM, LE2, fvertex, colorFocusE2);
    vec3 PhongE3 = Difus(NM, LE3, colorFocusE3) + Especular(NM, LE3, fvertex, colorFocusE3);
    vec3 PhongE4 = Difus(NM, LE4, colorFocusE4) + Especular(NM, LE4, fvertex, colorFocusE4);
    vec3 PhongM = Difus(NM, LM, colorFocusM) + Especular(NM, LM, fvertex, colorFocusM);
    FragColor = vec4(Ambient() + PhongE1 + PhongE2 + PhongE3 + PhongE4 + PhongM, 1.0);
}
