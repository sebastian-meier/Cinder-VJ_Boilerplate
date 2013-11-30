#pragma once
#include "cinder/CinderResources.h"

#define SHADER_FRAG_LineDistortion	CINDER_RESOURCE( ./, LineDistortion_frag.glsl, 128, GLSL )
#define SHADER_VERT_LineDistortion	CINDER_RESOURCE( ./, LineDistortion_vert.glsl, 129, GLSL )
#define SHADER_FRAG_ColorOffset		CINDER_RESOURCE( ./, ColorOffset_frag.glsl, 130, IMAGE )
#define SHADER_VERT_ColorOffset		CINDER_RESOURCE( ./, ColorOffset_vert.glsl, 131, IMAGE )
#define SHADER_FRAG_Blur            CINDER_RESOURCE( ./, Blur_frag.glsl, 132, IMAGE )
#define SHADER_VERT_Blur            CINDER_RESOURCE( ./, Blur_vert.glsl, 133, IMAGE )
#define RES_SAMPLE                  CINDER_RESOURCE( ../resources/, Mix_TinyTrouble.mp3, 134, MP3 )
#define IMG_TNYTRP_BW               CINDER_RESOURCE( ../resources/, tnytrp_bw.png, 128, IMAGE )
#define IMG_TNYTRP_WB               CINDER_RESOURCE( ../resources/, tnytrp_wb.png, 128, IMAGE )
