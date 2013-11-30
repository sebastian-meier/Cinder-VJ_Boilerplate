uniform sampler2D tex0;
uniform vec2 redOffset;
uniform vec2 greenOffset;
uniform float alpha;

void main(){
    vec3 sum = texture2D( tex0, gl_TexCoord[0].st).rgb;
    sum[0] += texture2D( tex0, gl_TexCoord[0].st + redOffset).r * alpha;
    sum[1] += texture2D( tex0, gl_TexCoord[0].st + greenOffset).g * alpha;
    gl_FragColor.rgb = sum;
    gl_FragColor.a = 1.0;
}