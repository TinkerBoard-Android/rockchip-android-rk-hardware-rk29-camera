#include <ebase/types.h>
#include <ebase/trace.h>
#include <ebase/builtins.h>

#include <common/return_codes.h>

#include "isi.h"
#include "isi_iss.h"
#include "isi_priv.h"
#include "GC2155_priv.h"

/*****************************************************************************
 * DEFINES
 *****************************************************************************/

/*****************************************************************************
 * GLOBALS
 *****************************************************************************/

// Image sensor register settings default values taken from data sheet OV8810_DS_1.1_SiliconImage.pdf.
// The settings may be altered by the code in IsiSetupSensor.
const IsiRegDescription_t GC2155_g_aRegDescription[] =
{
	
	{0xfe , 0xf0,"",eReadWrite,},
	{0xfe , 0xf0,"",eReadWrite,},
	{0xfe , 0xf0,"",eReadWrite,},
	{0xfc , 0x06,"",eReadWrite,},
	{0xf6 , 0x00,"",eReadWrite,},
	{0xf7 , 0x1d,"",eReadWrite,},
	{0xf8 , 0x84,"",eReadWrite,},
	{0xfa , 0x00,"",eReadWrite,},
	{0xf9 , 0xfe,"",eReadWrite,},
	{0xf2 , 0x00,"",eReadWrite,},
/////////////////////////////////////////////////
//////////////////ISP reg//////////////////////
////////////////////////////////////////////////////
	{0xfe , 0x00,"",eReadWrite,},
	{0x03 , 0x08,"",eReadWrite,},//04
	{0x04 , 0x48,"",eReadWrite,},//24
	{0x09 , 0x00,"",eReadWrite,},
	{0x0a , 0x00,"",eReadWrite,},
	{0x0b , 0x00,"",eReadWrite,},
	{0x0c , 0x00,"",eReadWrite,},
	{0x0d , 0x04,"",eReadWrite,},
	{0x0e , 0xc0,"",eReadWrite,},
	{0x0f , 0x06,"",eReadWrite,},
	{0x10 , 0x50,"",eReadWrite,},
	{0x12 , 0x2e,"",eReadWrite,},
	{0x17 , 0x14,"",eReadWrite,}, // mirror
	{0x18 , 0x02,"",eReadWrite,},
	{0x19 , 0x0e,"",eReadWrite,},
	{0x1a , 0x01,"",eReadWrite,},
	{0x1b , 0x4b,"",eReadWrite,},
	{0x1c , 0x07,"",eReadWrite,},
	{0x1d , 0x10,"",eReadWrite,},
	{0x1e , 0x98,"",eReadWrite,},
	{0x1f , 0x78,"",eReadWrite,},
	{0x20 , 0x05,"",eReadWrite,},
	{0x21 , 0x40,"",eReadWrite,},
	{0x22 , 0xf0,"",eReadWrite,},
	{0x24 , 0x16,"",eReadWrite,},
	{0x25 , 0x01,"",eReadWrite,},
	{0x26 , 0x10,"",eReadWrite,},
	{0x2d , 0x40,"",eReadWrite,},
	{0x30 , 0x01,"",eReadWrite,},
	{0x31 , 0x90,"",eReadWrite,},
	{0x33 , 0x04,"",eReadWrite,},
	{0x34 , 0x01,"",eReadWrite,},
		/////////////////////////////////////////////////
		//////////////////ISP reg////////////////////
		/////////////////////////////////////////////////
	{0xfe , 0x00,"",eReadWrite,},
	{0x80 , 0xff,"",eReadWrite,},
	{0x81 , 0x2c,"",eReadWrite,},
	{0x82 , 0xfa,"",eReadWrite,},
	{0x83 , 0x00,"",eReadWrite,},
	{0x84 , 0x00,"",eReadWrite,}, //yuv 01
	{0x85 , 0x08,"",eReadWrite,},
	{0x86 , 0x03,"",eReadWrite,},
	{0x89 , 0x03,"",eReadWrite,},
	{0x8a , 0x00,"",eReadWrite,},
	{0x8b , 0x00,"",eReadWrite,},
	{0xb0 , 0x55,"",eReadWrite,},
	{0xc3 , 0x11,"",eReadWrite,}, //00
	{0xc4 , 0x20,"",eReadWrite,},
	{0xc5 , 0x30,"",eReadWrite,},
	{0xc6 , 0x38,"",eReadWrite,},
	{0xc7 , 0x40,"",eReadWrite,},
	{0xec , 0x02,"",eReadWrite,},
	{0xed , 0x04,"",eReadWrite,},
	{0xee , 0x60,"",eReadWrite,},
	{0xef , 0x90,"",eReadWrite,},
	{0xb6 , 0x01,"",eReadWrite,},
	{0x90 , 0x01,"",eReadWrite,},
	{0x91 , 0x00,"",eReadWrite,},
	{0x92 , 0x00,"",eReadWrite,},
	{0x93 , 0x00,"",eReadWrite,},
	{0x94 , 0x00,"",eReadWrite,},
	{0x95 , 0x04,"",eReadWrite,},
	{0x96 , 0xb0,"",eReadWrite,},
	{0x97 , 0x06,"",eReadWrite,},
	{0x98 , 0x40,"",eReadWrite,},
		/////////////////////////////////////////
		/////////// BLK ////////////////////////
		/////////////////////////////////////////
	{0xfe , 0x00,"",eReadWrite,},
	{0x18 , 0x02,"",eReadWrite,},
	{0x40 , 0x42,"",eReadWrite,},
	{0x41 , 0x00,"",eReadWrite,},
	{0x43 , 0x54,"",eReadWrite,},
	{0x5e , 0x00,"",eReadWrite,},
	{0x5f , 0x00,"",eReadWrite,},
	{0x60 , 0x00,"",eReadWrite,},
	{0x61 , 0x00,"",eReadWrite,},
	{0x62 , 0x00,"",eReadWrite,},
	{0x63 , 0x00,"",eReadWrite,},
	{0x64 , 0x00,"",eReadWrite,},
	{0x65 , 0x00,"",eReadWrite,},
	{0x66 , 0x20,"",eReadWrite,},
	{0x67 , 0x20,"",eReadWrite,},
	{0x68 , 0x20,"",eReadWrite,},
	{0x69 , 0x20,"",eReadWrite,},
	{0x6a , 0x08,"",eReadWrite,},
	{0x6b , 0x08,"",eReadWrite,},
	{0x6c , 0x08,"",eReadWrite,},
	{0x6d , 0x08,"",eReadWrite,},
	{0x6e , 0x08,"",eReadWrite,},
	{0x6f , 0x08,"",eReadWrite,},
	{0x70 , 0x08,"",eReadWrite,},
	{0x71 , 0x08,"",eReadWrite,},
	{0x72 , 0xf0,"",eReadWrite,},
	{0x7e , 0x3c,"",eReadWrite,},
	{0x7f , 0x00,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},
	{0xad , 0x80,"",eReadWrite,},// r ratio
	{0xae , 0x7d,"",eReadWrite,},// g ratio
	{0xaf , 0x80,"",eReadWrite,},// b ratio
		////////////////////////////////////////
		/////////// AEC ////////////////////////
		////////////////////////////////////////
	{0xfe , 0x01,"",eReadWrite,},
	{0x01 , 0x08,"",eReadWrite,},
	{0x02 , 0xc0,"",eReadWrite,},
	{0x03 , 0x04,"",eReadWrite,},
	{0x04 , 0x90,"",eReadWrite,},
	{0x05 , 0x30,"",eReadWrite,},
	{0x06 , 0x98,"",eReadWrite,},
	{0x07 , 0x28,"",eReadWrite,},
	{0x08 , 0x6c,"",eReadWrite,},
	{0x09 , 0x00,"",eReadWrite,},
	{0x0a , 0xc2,"",eReadWrite,},
	{0x0b , 0x11,"",eReadWrite,},
	{0x0c , 0x36,"",eReadWrite,},//10 cyrille
	{0x13 , 0x2d,"",eReadWrite,},
	{0x17 , 0x00,"",eReadWrite,},
	{0x18 , 0x97,"",eReadWrite,},// cyrille
	{0x19 , 0x97,"",eReadWrite,},// cyrille
	{0x1c , 0x11,"",eReadWrite,},
	{0x1e , 0x61,"",eReadWrite,},
	{0x1f , 0x30,"",eReadWrite,},
	{0x20 , 0x40,"",eReadWrite,},
	{0x22 , 0x80,"",eReadWrite,},
	{0x23 , 0x20,"",eReadWrite,},
	
	{0x12 , 0x35,"",eReadWrite,},
	{0x15 , 0x50,"",eReadWrite,},
	{0x10 , 0x31,"",eReadWrite,},
	{0x3e , 0x28,"",eReadWrite,},
	{0x3f , 0xe0,"",eReadWrite,},
	{0x40 , 0xe0,"",eReadWrite,},
	{0x41 , 0x08,"",eReadWrite,},
	
	{0xfe , 0x02,"",eReadWrite,},
	{0x0f , 0x05,"",eReadWrite,},
		/////////////////////////////
		//////// INTPEE /////////////
		/////////////////////////////
	{0xfe , 0x02,"",eReadWrite,},
	{0x90 , 0x6c,"",eReadWrite,},
	{0x91 , 0x03,"",eReadWrite,},
	{0x92 , 0xc4,"",eReadWrite,},
	{0x97 , 0x64,"",eReadWrite,},
	{0x98 , 0x88,"",eReadWrite,},
	{0x9d , 0x0c,"",eReadWrite,},//08
	{0xa2 , 0x11,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},
		/////////////////////////////
		//////// DNDD///////////////
		/////////////////////////////
	{0xfe , 0x02,"",eReadWrite,},
	{0x80 , 0xc1,"",eReadWrite,},
	{0x81 , 0x08,"",eReadWrite,},
	{0x82 , 0x0c,"",eReadWrite,},//05
	{0x83 , 0x09,"",eReadWrite,},//04
	{0x84 , 0x0a,"",eReadWrite,},
	{0x86 , 0x80,"",eReadWrite,},
	{0x87 , 0x30,"",eReadWrite,},
	{0x88 , 0x15,"",eReadWrite,},
	{0x89 , 0x80,"",eReadWrite,},
	{0x8a , 0x60,"",eReadWrite,},
	{0x8b , 0x30,"",eReadWrite,},
		/////////////////////////////////////////
		/////////// ASDE ////////////////////////
		/////////////////////////////////////////
	{0xfe , 0x01,"",eReadWrite,},
	{0x21 , 0x14,"",eReadWrite,},
	{0xfe , 0x02,"",eReadWrite,},
	{0x3c , 0x06,"",eReadWrite,},
	{0x3d , 0x40,"",eReadWrite,},
	{0x48 , 0x30,"",eReadWrite,},
	{0x49 , 0x06,"",eReadWrite,},
	{0x4b , 0x08,"",eReadWrite,},
	{0x4c , 0x20,"",eReadWrite,},
	{0xa3 , 0x50,"",eReadWrite,},
	{0xa4 , 0x30,"",eReadWrite,},
	{0xa5 , 0x40,"",eReadWrite,},
	{0xa6 , 0x80,"",eReadWrite,},
	{0xab , 0x40,"",eReadWrite,},
	{0xae , 0x0c,"",eReadWrite,},
	{0xb3 , 0x42,"",eReadWrite,},
	{0xb4 , 0x24,"",eReadWrite,},
	{0xb6 , 0x50,"",eReadWrite,},
	{0xb7 , 0x01,"",eReadWrite,},
	{0xb9 , 0x28,"",eReadWrite,}, 
	{0xfe , 0x00,"",eReadWrite,},	 
		///////////////////gamma1////////////////////
	#if 0
	{0xfe , 0x02,"",eReadWrite,},
	{0x10 , 0x0d,"",eReadWrite,},
	{0x11 , 0x12,"",eReadWrite,},
	{0x12 , 0x17,"",eReadWrite,},
	{0x13 , 0x1c,"",eReadWrite,},
	{0x14 , 0x27,"",eReadWrite,},
	{0x15 , 0x34,"",eReadWrite,},
	{0x16 , 0x44,"",eReadWrite,},
	{0x17 , 0x55,"",eReadWrite,},
	{0x18 , 0x6e,"",eReadWrite,},
	{0x19 , 0x81,"",eReadWrite,},
	{0x1a , 0x91,"",eReadWrite,},
	{0x1b , 0x9c,"",eReadWrite,},
	{0x1c , 0xaa,"",eReadWrite,},
	{0x1d , 0xbb,"",eReadWrite,},
	{0x1e , 0xca,"",eReadWrite,},
	{0x1f , 0xd5,"",eReadWrite,},
	{0x20 , 0xe0,"",eReadWrite,},
	{0x21 , 0xe7,"",eReadWrite,},
	{0x22 , 0xed,"",eReadWrite,},
	{0x23 , 0xf6,"",eReadWrite,},
	{0x24 , 0xfb,"",eReadWrite,},
	{0x25 , 0xff,"",eReadWrite,},
	#else
	{0xfe , 0x02,"",eReadWrite,},
	{0x10 , 0x0a,"",eReadWrite,},
	{0x11 , 0x0e,"",eReadWrite,},
	{0x12 , 0x13,"",eReadWrite,},
	{0x13 , 0x18,"",eReadWrite,},
	{0x14 , 0x23,"",eReadWrite,},
	{0x15 , 0x2f,"",eReadWrite,},
	{0x16 , 0x3b,"",eReadWrite,},
	{0x17 , 0x47,"",eReadWrite,},
	{0x18 , 0x5f,"",eReadWrite,},
	{0x19 , 0x75,"",eReadWrite,},
	{0x1a , 0x87,"",eReadWrite,},
	{0x1b , 0x97,"",eReadWrite,},
	{0x1c , 0xa4,"",eReadWrite,},
	{0x1d , 0xb8,"",eReadWrite,},
	{0x1e , 0xc7,"",eReadWrite,},
	{0x1f , 0xd4,"",eReadWrite,},
	{0x20 , 0xde,"",eReadWrite,},
	{0x21 , 0xe5,"",eReadWrite,},
	{0x22 , 0xea,"",eReadWrite,},
	{0x23 , 0xf1,"",eReadWrite,},
	{0x24 , 0xf7,"",eReadWrite,},
	{0x25 , 0xfc,"",eReadWrite,},	
	#endif
		///////////////////gamma2////////////////////
	{0xfe , 0x02,"",eReadWrite,},
	{0x26 , 0x0d,"",eReadWrite,},
	{0x27 , 0x12,"",eReadWrite,},
	{0x28 , 0x17,"",eReadWrite,},
	{0x29 , 0x1c,"",eReadWrite,},
	{0x2a , 0x27,"",eReadWrite,},
	{0x2b , 0x34,"",eReadWrite,},
	{0x2c , 0x44,"",eReadWrite,},
	{0x2d , 0x55,"",eReadWrite,},
	{0x2e , 0x6e,"",eReadWrite,},
	{0x2f , 0x81,"",eReadWrite,},
	{0x30 , 0x91,"",eReadWrite,},
	{0x31 , 0x9c,"",eReadWrite,},
	{0x32 , 0xaa,"",eReadWrite,},
	{0x33 , 0xbb,"",eReadWrite,},
	{0x34 , 0xca,"",eReadWrite,},
	{0x35 , 0xd5,"",eReadWrite,},
	{0x36 , 0xe0,"",eReadWrite,},
	{0x37 , 0xe7,"",eReadWrite,},
	{0x38 , 0xed,"",eReadWrite,},
	{0x39 , 0xf6,"",eReadWrite,},
	{0x3a , 0xfb,"",eReadWrite,},
	{0x3b , 0xff,"",eReadWrite,},
		/////////////////////////////////////////////// 
		///////////YCP /////////////////////// 
		/////////////////////////////////////////////// 
	{0xfe , 0x02,"",eReadWrite,},
	{0xd1 , 0x28,"",eReadWrite,},//28
	{0xd2 , 0x28,"",eReadWrite,},//28
	{0xd3 , 0x40,"",eReadWrite,},//40
	{0xd5 , 0xfa,"",eReadWrite,},	//00	
	{0xdd , 0x14,"",eReadWrite,},//88
	{0xde , 0x84,"",eReadWrite,},
	{0xed , 0x80,"",eReadWrite,},
		////////////////////////////
		//////// LSC ///////////////
		////////////////////////////
	#if 0
	{0xfe , 0x01,"",eReadWrite,},
	{0xc2 , 0x1f,"",eReadWrite,},
	{0xc3 , 0x13,"",eReadWrite,},
	{0xc4 , 0x0e,"",eReadWrite,},
	{0xc8 , 0x16,"",eReadWrite,},
	{0xc9 , 0x0f,"",eReadWrite,},
	{0xca , 0x0c,"",eReadWrite,},
	{0xbc , 0x52,"",eReadWrite,},
	{0xbd , 0x2c,"",eReadWrite,},
	{0xbe , 0x27,"",eReadWrite,},
	{0xb6 , 0x47,"",eReadWrite,},
	{0xb7 , 0x32,"",eReadWrite,},
	{0xb8 , 0x30,"",eReadWrite,},
	{0xc5 , 0x00,"",eReadWrite,},
	{0xc6 , 0x00,"",eReadWrite,},
	{0xc7 , 0x00,"",eReadWrite,},
	{0xcb , 0x00,"",eReadWrite,},
	{0xcc , 0x00,"",eReadWrite,},
	{0xcd , 0x00,"",eReadWrite,},
	{0xbf , 0x0e,"",eReadWrite,},
	{0xc0 , 0x00,"",eReadWrite,},
	{0xc1 , 0x00,"",eReadWrite,},
	{0xb9 , 0x08,"",eReadWrite,},
	{0xba , 0x00,"",eReadWrite,},
	{0xbb , 0x00,"",eReadWrite,},
	{0xaa , 0x0a,"",eReadWrite,},
	{0xab , 0x0c,"",eReadWrite,},
	{0xac , 0x0d,"",eReadWrite,},
	{0xad , 0x02,"",eReadWrite,},
	{0xae , 0x06,"",eReadWrite,},
	{0xaf , 0x05,"",eReadWrite,},
	{0xb0 , 0x00,"",eReadWrite,},
	{0xb1 , 0x05,"",eReadWrite,},
	{0xb2 , 0x02,"",eReadWrite,},
	{0xb3 , 0x04,"",eReadWrite,},
	{0xb4 , 0x04,"",eReadWrite,},
	{0xb5 , 0x05,"",eReadWrite,},
	{0xd0 , 0x00,"",eReadWrite,},
	{0xd1 , 0x00,"",eReadWrite,},
	{0xd2 , 0x00,"",eReadWrite,},
	{0xd6 , 0x02,"",eReadWrite,},
	{0xd7 , 0x00,"",eReadWrite,},
	{0xd8 , 0x00,"",eReadWrite,},
	{0xd9 , 0x00,"",eReadWrite,},
	{0xda , 0x00,"",eReadWrite,},
	{0xdb , 0x00,"",eReadWrite,},
	{0xd3 , 0x00,"",eReadWrite,},
	{0xd4 , 0x00,"",eReadWrite,},
	{0xd5 , 0x00,"",eReadWrite,},
	{0xa4 , 0x04,"",eReadWrite,},
	{0xa5 , 0x00,"",eReadWrite,},
	{0xa6 , 0x77,"",eReadWrite,},
	{0xa7 , 0x77,"",eReadWrite,},
	{0xa8 , 0x77,"",eReadWrite,},
	{0xa9 , 0x77,"",eReadWrite,},
	{0xa1 , 0x80,"",eReadWrite,},
	{0xa2 , 0x80,"",eReadWrite,},
	#else 
	{0xfe , 0x01,"",eReadWrite,},
	{0xc2 , 0x09,"",eReadWrite,},
	{0xc3 , 0x12,"",eReadWrite,},
	{0xc4 , 0x0f,"",eReadWrite,},
	{0xc8 , 0x19,"",eReadWrite,},
	{0xc9 , 0x10,"",eReadWrite,},
	{0xca , 0x00,"",eReadWrite,},
	{0xbc , 0x2b,"",eReadWrite,},
	{0xbd , 0x19,"",eReadWrite,},
	{0xbe , 0x08,"",eReadWrite,},
	{0xb6 , 0x28,"",eReadWrite,},
	{0xb7 , 0x42,"",eReadWrite,},
	{0xb8 , 0x3a,"",eReadWrite,},
	{0xc5 , 0x31,"",eReadWrite,},
	{0xc6 , 0x09,"",eReadWrite,},
	{0xc7 , 0x00,"",eReadWrite,},
	{0xcb , 0x2a,"",eReadWrite,},
	{0xcc , 0x01,"",eReadWrite,},
	{0xcd , 0x15,"",eReadWrite,},
	{0xbf , 0x00,"",eReadWrite,},
	{0xc0 , 0x00,"",eReadWrite,},
	{0xc1 , 0x0e,"",eReadWrite,},
	{0xb9 , 0x24,"",eReadWrite,},
	{0xba , 0x13,"",eReadWrite,},
	{0xbb , 0x13,"",eReadWrite,},
	{0xaa , 0x02,"",eReadWrite,},
	{0xab , 0x07,"",eReadWrite,},
	{0xac , 0x00,"",eReadWrite,},
	{0xad , 0x12,"",eReadWrite,},
	{0xae , 0x0d,"",eReadWrite,},
	{0xaf , 0x1e,"",eReadWrite,},
	{0xb0 , 0x23,"",eReadWrite,},
	{0xb1 , 0x13,"",eReadWrite,},
	{0xb2 , 0x00,"",eReadWrite,},
	{0xb3 , 0x00,"",eReadWrite,},
	{0xb4 , 0x0a,"",eReadWrite,},
	{0xb5 , 0x00,"",eReadWrite,},
	{0xd0 , 0x31,"",eReadWrite,},
	{0xd1 , 0x07,"",eReadWrite,},
	{0xd2 , 0x00,"",eReadWrite,},
	{0xd6 , 0x0a,"",eReadWrite,},
	{0xd7 , 0x00,"",eReadWrite,},
	{0xd8 , 0x00,"",eReadWrite,},
	{0xd9 , 0x00,"",eReadWrite,},
	{0xda , 0x00,"",eReadWrite,},
	{0xdb , 0x46,"",eReadWrite,},
	{0xd3 , 0x22,"",eReadWrite,},
	{0xd4 , 0x2c,"",eReadWrite,},
	{0xd5 , 0x00,"",eReadWrite,},
	{0xa4 , 0x00,"",eReadWrite,},
	{0xa5 , 0x00,"",eReadWrite,},
	{0xa6 , 0x00,"",eReadWrite,},
	{0xa7 , 0x04,"",eReadWrite,},
	{0xa8 , 0x32,"",eReadWrite,},
	{0xa9 , 0x00,"",eReadWrite,},
	{0xa1 , 0x80,"",eReadWrite,},
	{0xa2 , 0x80,"",eReadWrite,},
	
	#endif
	{0xfe , 0x01,"",eReadWrite,},
	{0xdc , 0x35,"",eReadWrite,},
	{0xdd , 0x28,"",eReadWrite,},
	{0xdf , 0x0d,"",eReadWrite,},
	{0xe0 , 0x88,"",eReadWrite,},//70
	{0xe1 , 0x70,"",eReadWrite,},//78
	{0xe2 , 0x88,"",eReadWrite,},//70
	{0xe3 , 0x70,"",eReadWrite,},//78
	{0xe6 , 0x90,"",eReadWrite,},
	{0xe7 , 0x70,"",eReadWrite,},
	{0xe8 , 0x90,"",eReadWrite,},
	{0xe9 , 0x70,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},
		///////////////////////////////////////////////
		/////////// AWB////////////////////////
		///////////////////////////////////////////////
	{0xfe , 0x01,"",eReadWrite,},
	{0x4f , 0x00,"",eReadWrite,},
	{0x4f , 0x00,"",eReadWrite,},
	{0x4b , 0x01,"",eReadWrite,},
	{0x4f , 0x00,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x71,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x91,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x50,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x70,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x90,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xb0,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xd0,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x4f,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x6f,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8f,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xaf,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xcf,"",eReadWrite,},
	{0x4e , 0x02,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x6e,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8e,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xae,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xce,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x4d,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x6d,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8d,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xad,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xcd,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x4c,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x6c,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8c,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xac,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xcc,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xec,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x4b,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x6b,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8b,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xab,"",eReadWrite,},
	{0x4e , 0x03,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0x8a,"",eReadWrite,},
	{0x4e , 0x04,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xaa,"",eReadWrite,},
	{0x4e , 0x04,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xca,"",eReadWrite,},
	{0x4e , 0x04,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xa9,"",eReadWrite,},
	{0x4e , 0x04,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xc9,"",eReadWrite,},
	{0x4e , 0x04,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xcb,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xeb,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x0b,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x2b,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x4b,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x01,"",eReadWrite,},
	{0x4d , 0xea,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x0a,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x2a,"",eReadWrite,},
	{0x4e , 0x05,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x6a,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x29,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x49,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x69,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x89,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xa9,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xc9,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x48,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x68,"",eReadWrite,},
	{0x4e , 0x06,"",eReadWrite,},
	{0x4c , 0x03,"",eReadWrite,},
	{0x4d , 0x09,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xa8,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xc8,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xe8,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x03,"",eReadWrite,},
	{0x4d , 0x08,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x03,"",eReadWrite,},
	{0x4d , 0x28,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0x87,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xa7,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xc7,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x02,"",eReadWrite,},
	{0x4d , 0xe7,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4c , 0x03,"",eReadWrite,},
	{0x4d , 0x07,"",eReadWrite,},
	{0x4e , 0x07,"",eReadWrite,},
	{0x4f , 0x01,"",eReadWrite,},
	{0xfe , 0x01,"",eReadWrite,},
		
	{0x50 , 0x80,"",eReadWrite,},
	{0x51 , 0xa8,"",eReadWrite,},
	{0x52 , 0x57,"",eReadWrite,},
	{0x53 , 0x38,"",eReadWrite,},
	{0x54 , 0xc7,"",eReadWrite,},
	{0x56 , 0x0e,"",eReadWrite,},
	{0x58 , 0x08,"",eReadWrite,},
	{0x5b , 0x00,"",eReadWrite,},
	{0x5c , 0x74,"",eReadWrite,},
	{0x5d , 0x8b,"",eReadWrite,},
	{0x61 , 0xd3,"",eReadWrite,},
	{0x62 , 0x90,"",eReadWrite,},
	{0x63 , 0xaa,"",eReadWrite,},
	{0x65 , 0x04,"",eReadWrite,},
	{0x67 , 0xb2,"",eReadWrite,},
	{0x68 , 0xac,"",eReadWrite,},
	{0x69 , 0x00,"",eReadWrite,},
	{0x6a , 0xb2,"",eReadWrite,},
	{0x6b , 0xac,"",eReadWrite,},
	{0x6c , 0xdc,"",eReadWrite,},
	{0x6d , 0xb0,"",eReadWrite,},
	{0x6e , 0x30,"",eReadWrite,},
	{0x6f , 0x40,"",eReadWrite,},
	{0x70 , 0x05,"",eReadWrite,},
	{0x71 , 0x80,"",eReadWrite,},
	{0x72 , 0x80,"",eReadWrite,},
	{0x73 , 0x30,"",eReadWrite,},
	{0x74 , 0x01,"",eReadWrite,},
	{0x75 , 0x01,"",eReadWrite,},
	{0x7f , 0x08,"",eReadWrite,},
	{0x76 , 0x70,"",eReadWrite,},
	{0x77 , 0x48,"",eReadWrite,},
	{0x78 , 0xa0,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},
	
		//////////////////////////////////////////
		///////////CC////////////////////////
		//////////////////////////////////////////
	{0xfe , 0x02,"",eReadWrite,},
	{0xc0 , 0x01,"",eReadWrite,},
	{0xc1 , 0x4d,"",eReadWrite,},//4a cyrille
	{0xc2 , 0xf3,"",eReadWrite,},//f3 cyrille
	{0xc3 , 0xfd,"",eReadWrite,},// fc cyrille
	{0xc4 , 0xe4,"",eReadWrite,},
	{0xc5 , 0x43,"",eReadWrite,},//48 cyrille
	{0xc6 , 0xec,"",eReadWrite,},
	{0xc7 , 0x45,"",eReadWrite,},
	{0xc8 , 0xf8,"",eReadWrite,},
	{0xc9 , 0x02,"",eReadWrite,},
	{0xca , 0xfe,"",eReadWrite,},
	{0xcb , 0x42,"",eReadWrite,},
	{0xcc , 0x00,"",eReadWrite,},
	{0xcd , 0x45,"",eReadWrite,},
	{0xce , 0xf0,"",eReadWrite,},
	{0xcf , 0x00,"",eReadWrite,},
	{0xe3 , 0xf0,"",eReadWrite,},
	{0xe4 , 0x45,"",eReadWrite,},
	{0xe5 , 0xe8,"",eReadWrite,}, 
		//////////////////////////////////////////
		///////////ABS ////////////////////
		//////////////////////////////////////////
	{0xfe , 0x01,"",eReadWrite,},
	{0x9f , 0x42,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,}, 

		//////////////frame rate 50Hz/////////
#if 1
		{0xfe , 0x00,"",eReadWrite,},
		{0x05 , 0x01,"",eReadWrite,},
		{0x06 , 0x56,"",eReadWrite,},
		{0x07 , 0x00,"",eReadWrite,},
		{0x08 , 0x32,"",eReadWrite,},
		{0xfe , 0x01,"",eReadWrite,},
		{0x25 , 0x00,"",eReadWrite,},
		{0x26 , 0xfa,"",eReadWrite,}, 
		{0x27 , 0x04,"",eReadWrite,}, 
		{0x28 , 0xe2,"",eReadWrite,}, //20fps 
		{0x29 , 0x06,"",eReadWrite,}, 
		{0x2a , 0xd6,"",eReadWrite,}, //16fps 
		{0x2b , 0x07,"",eReadWrite,}, 
		{0x2c , 0xd0,"",eReadWrite,}, //12fps
		{0x2d , 0x0b,"",eReadWrite,}, 
		{0x2e , 0xb8,"",eReadWrite,}, //8fps
		{0xfe , 0x00,"",eReadWrite,},
#else
		//////////////frame rate   50Hz
		{0xfe, 0x00,"",eReadWrite,},
		{0x05, 0x02,"",eReadWrite,},
		{0x06, 0x2d,"",eReadWrite,},
		{0x07, 0x00,"",eReadWrite,},
		{0x08, 0xa0,"",eReadWrite,},
		{0xfe, 0x01,"",eReadWrite,},
		{0x25, 0x00,"",eReadWrite,},
		{0x26, 0xd4,"",eReadWrite,},
		{0x27, 0x04,"",eReadWrite,},
		{0x28, 0xf8,"",eReadWrite,},
		{0x29, 0x08,"",eReadWrite,},
		{0x2a, 0x48,"",eReadWrite,},
		{0x2b, 0x0a,"",eReadWrite,},
		{0x2c, 0xc4,"",eReadWrite,},
		{0x2d, 0x0f,"",eReadWrite,},
		{0x2e, 0xbc,"",eReadWrite,},
		{0xfe, 0x00,"",eReadWrite,},
#endif

	
	///////GC2155_Sensor_SVGA////
	{0xfe , 0x00,"",eReadWrite,},
	{0xfa , 0x00,"",eReadWrite,},
	{0xfd , 0x01,"",eReadWrite,}, 
	//{0xc2 , 0x10,"",eReadWrite,},	
		//// crop window			  
	{0xfe , 0x00,"",eReadWrite,},
	{0x90 , 0x01,"",eReadWrite,}, 
	{0x91 , 0x00,"",eReadWrite,},
	{0x92 , 0x00,"",eReadWrite,},
	{0x93 , 0x00,"",eReadWrite,},
	{0x94 , 0x00,"",eReadWrite,},
	{0x95 , 0x02,"",eReadWrite,},
	{0x96 , 0x58,"",eReadWrite,},
	{0x97 , 0x03,"",eReadWrite,},
	{0x98 , 0x20,"",eReadWrite,},
	{0x99 , 0x11,"",eReadWrite,},
	{0x9a , 0x06,"",eReadWrite,},
		//// AWB					  
	{0xfe , 0x00,"",eReadWrite,},
	{0xec , 0x01,"",eReadWrite,}, 
	{0xed , 0x02,"",eReadWrite,},
	{0xee , 0x30,"",eReadWrite,},
	{0xef , 0x48,"",eReadWrite,},
	{0xfe , 0x01,"",eReadWrite,},
	{0x74 , 0x00,"",eReadWrite,}, 
		//// AEC					  
	{0xfe , 0x01,"",eReadWrite,},
	{0x01 , 0x04,"",eReadWrite,},
	{0x02 , 0x60,"",eReadWrite,},
	{0x03 , 0x02,"",eReadWrite,},
	{0x04 , 0x48,"",eReadWrite,},
	{0x05 , 0x18,"",eReadWrite,},
	{0x06 , 0x4c,"",eReadWrite,},
	{0x07 , 0x14,"",eReadWrite,},
	{0x08 , 0x36,"",eReadWrite,},
	{0x0a , 0xc0,"",eReadWrite,}, 
	{0x21 , 0x14,"",eReadWrite,}, 
	{0xfe , 0x00,"",eReadWrite,},
		//// gamma
	{0xfe , 0x00,"",eReadWrite,},
	{0xc3 , 0x11,"",eReadWrite,},
	{0xc4 , 0x20,"",eReadWrite,},
	{0xc5 , 0x30,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},
////////svga setting end//////


//////////////////////////////////////////
///////////OUTPUT ////////////////////
//////////////////////////////////////////
	{0xfe , 0x00,"",eReadWrite,},
	{0xf2 , 0x0f,"",eReadWrite,},	

	{0x0000 ,0x00,"eTableEnd",eTableEnd}

};

const IsiRegDescription_t GC2155_g_svga[] =
{
	{0xfe , 0x00,"",eReadWrite,},
	{0xb6 , 0x01,"",eReadWrite,},
	{0xfa , 0x00,"",eReadWrite,},
	{0xfd , 0x01,"",eReadWrite,},

////window setting/////
	{0x09 , 0x00,"",eReadWrite,},
	{0x0a , 0x00,"",eReadWrite,},
	{0x0b , 0x00,"",eReadWrite,},
	{0x0c , 0x00,"",eReadWrite,},
	{0x0d , 0x04,"",eReadWrite,},
	{0x0e , 0xc0,"",eReadWrite,},
	{0x0f , 0x06,"",eReadWrite,},
	{0x10 , 0x50,"",eReadWrite,},

	//// crop window			  
	{0xfe , 0x00,"",eReadWrite,},
	{0x90 , 0x01,"",eReadWrite,}, 
	{0x91 , 0x00,"",eReadWrite,},
	{0x92 , 0x00,"",eReadWrite,},
	{0x93 , 0x00,"",eReadWrite,},
	{0x94 , 0x00,"",eReadWrite,},
	{0x95 , 0x02,"",eReadWrite,},
	{0x96 , 0x58,"",eReadWrite,},
	{0x97 , 0x03,"",eReadWrite,},
	{0x98 , 0x20,"",eReadWrite,},
	{0x99 , 0x11,"",eReadWrite,},
	{0x9a , 0x06,"",eReadWrite,},
	{0x9b , 0x00,"",eReadWrite,},
	{0x9c , 0x00,"",eReadWrite,},
	{0x9d , 0x00,"",eReadWrite,},
	{0x9e , 0x00,"",eReadWrite,},
	{0x9f , 0x00,"",eReadWrite,},
	{0xa0 , 0x00,"",eReadWrite,},	
	{0xa1 , 0x00,"",eReadWrite,},
	{0xa2  ,0x00,"",eReadWrite,},

	//// AWB					  
	{0xfe , 0x00,"",eReadWrite,},
	{0xec , 0x01,"",eReadWrite,}, 
	{0xed , 0x02,"",eReadWrite,},
	{0xee , 0x30,"",eReadWrite,},
	{0xef , 0x48,"",eReadWrite,},
	{0xfe , 0x01,"",eReadWrite,},
	{0x74 , 0x00,"",eReadWrite,}, 
	//// AEC					  
	{0xfe , 0x01,"",eReadWrite,},
	{0x01 , 0x04,"",eReadWrite,},
	{0x02 , 0x60,"",eReadWrite,},
	{0x03 , 0x02,"",eReadWrite,},
	{0x04 , 0x48,"",eReadWrite,},
	{0x05 , 0x18,"",eReadWrite,},
	{0x06 , 0x4c,"",eReadWrite,},
	{0x07 , 0x14,"",eReadWrite,},
	{0x08 , 0x36,"",eReadWrite,},
	{0x0a , 0xc0,"",eReadWrite,}, 
	{0x21 , 0x14,"",eReadWrite,}, 
	{0xfe , 0x00,"",eReadWrite,},
	//// gamma
	{0xfe , 0x00,"",eReadWrite,},
	{0xc3 , 0x11,"",eReadWrite,},
	{0xc4 , 0x20,"",eReadWrite,},
	{0xc5 , 0x30,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},

//////////////frame rate 50Hz/////////
#if 1
	{0xfe , 0x00,"",eReadWrite,},
	{0x05 , 0x01,"",eReadWrite,},
	{0x06 , 0x56,"",eReadWrite,},
	{0x07 , 0x00,"",eReadWrite,},
	{0x08 , 0x32,"",eReadWrite,},
	{0xfe , 0x01,"",eReadWrite,},
	{0x25 , 0x00,"",eReadWrite,},
	{0x26 , 0xfa,"",eReadWrite,}, 
	{0x27 , 0x04,"",eReadWrite,}, 
	{0x28 , 0xe2,"",eReadWrite,}, //20fps 
	{0x29 , 0x06,"",eReadWrite,}, 
	{0x2a , 0xd6,"",eReadWrite,}, //16fps 
	{0x2b , 0x07,"",eReadWrite,}, 
	{0x2c , 0xd0,"",eReadWrite,}, //12fps
	{0x2d , 0x0b,"",eReadWrite,}, 
	{0x2e , 0xb8,"",eReadWrite,}, //8fps
	{0xfe , 0x00,"",eReadWrite,},
#else
	//////////////frame rate   50Hz
	{0xfe, 0x00,"",eReadWrite,},
	{0x05, 0x02,"",eReadWrite,},
	{0x06, 0x2d,"",eReadWrite,},
	{0x07, 0x00,"",eReadWrite,},
	{0x08, 0xa0,"",eReadWrite,},
	{0xfe, 0x01,"",eReadWrite,},
	{0x25, 0x00,"",eReadWrite,},
	{0x26, 0xd4,"",eReadWrite,},
	{0x27, 0x04,"",eReadWrite,},
	{0x28, 0xf8,"",eReadWrite,},
	{0x29, 0x08,"",eReadWrite,},
	{0x2a, 0x48,"",eReadWrite,},
	{0x2b, 0x0a,"",eReadWrite,},
	{0x2c, 0xc4,"",eReadWrite,},
	{0x2d, 0x0f,"",eReadWrite,},
	{0x2e, 0xbc,"",eReadWrite,},
	{0xfe, 0x00,"",eReadWrite,},
#endif
	
    {0x0000 ,0x00,"eTableEnd",eTableEnd}
};

const IsiRegDescription_t GC2155_g_1600x1200[] =
{
//////////////////////////////////////////////
	{0xfe , 0x00,"",eReadWrite,},
	{0xb6 , 0x00,"",eReadWrite,},
	{0xfa , 0x11,"",eReadWrite,},
	{0xfd , 0x00,"",eReadWrite,},
	//{0xc2 , 0x00,"",eReadWrite,},
		//// crop window
	{0xfe , 0x00,"",eReadWrite,},
	{0x90 , 0x01,"",eReadWrite,},
	{0x91 , 0x00,"",eReadWrite,},
	{0x92 , 0x00,"",eReadWrite,},
	{0x93 , 0x00,"",eReadWrite,},
	{0x94 , 0x00,"",eReadWrite,},
	{0x95 , 0x04,"",eReadWrite,},
	{0x96 , 0xb0,"",eReadWrite,},
	{0x97 , 0x06,"",eReadWrite,},
	{0x98 , 0x40,"",eReadWrite,},
	{0x99 , 0x11,"",eReadWrite,}, 
	{0x9a , 0x06,"",eReadWrite,},

	{0x9b , 0x00,"",eReadWrite,},
	{0x9c , 0x00,"",eReadWrite,},
	{0x9d , 0x00,"",eReadWrite,},
	{0x9e , 0x00,"",eReadWrite,},
	{0x9f , 0x00,"",eReadWrite,},
	{0xa0 , 0x00,"",eReadWrite,},  
	{0xa1 , 0x00,"",eReadWrite,},
	{0xa2  ,0x00,"",eReadWrite,},

		//// AWB   
	{0xfe , 0x00,"",eReadWrite,},
	{0xec , 0x02,"",eReadWrite,},
	{0xed , 0x04,"",eReadWrite,},
	{0xee , 0x60,"",eReadWrite,},
	{0xef , 0x90,"",eReadWrite,},
	{0xfe , 0x01,"",eReadWrite,},
	{0x74 , 0x01,"",eReadWrite,},
		//// AEC	  
	{0xfe , 0x01,"",eReadWrite,},
	{0x01 , 0x08,"",eReadWrite,},
	{0x02 , 0xc0,"",eReadWrite,},
	{0x03 , 0x04,"",eReadWrite,},
	{0x04 , 0x90,"",eReadWrite,},
	{0x05 , 0x30,"",eReadWrite,},
	{0x06 , 0x98,"",eReadWrite,},
	{0x07 , 0x28,"",eReadWrite,},
	{0x08 , 0x6c,"",eReadWrite,},
	{0x0a , 0xc2,"",eReadWrite,}, 
	{0x21 , 0x15,"",eReadWrite,}, //if 0xfa=11,then 0x21=15;else if 0xfa=00,then 0x21=14
	{0xfe , 0x00,"",eReadWrite,},
		//// gamma
	{0xfe , 0x00,"",eReadWrite,},
	{0xc3 , 0x00,"",eReadWrite,}, //if shutter/2 when capture,then exp_gamma_th/2
	{0xc4 , 0x90,"",eReadWrite,},
	{0xc5 , 0x98,"",eReadWrite,},
	{0xfe , 0x00,"",eReadWrite,},

	{0x0000 ,0x00,"eTableEnd",eTableEnd}

};


