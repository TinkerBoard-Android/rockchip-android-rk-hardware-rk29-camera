/******************************************************************************
 *
 * Copyright 2010, Dream Chip Technologies GmbH. All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Dream Chip Technologies GmbH, Steinriede 10, 30827 Garbsen / Berenbostel,
 * Germany
 *
 *****************************************************************************/
/**
 * @file isi_iss.h
 *
 * @brief Interface description for image sensor specific implementation (iss).
 *
 *****************************************************************************/
/**
 * @page module_name_page Module Name
 * Describe here what this module does.
 *
 * For a detailed list of functions and implementation detail refer to:
 * - @ref module_name
 *
 * @defgroup ov5630_F2   Illumination Profile F2
 * @{
 *
 */
#ifndef __OV2715_F2_H__
#define __OV2715_F2_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define AWB_COLORMATRIX_ARRAY_SIZE_CIE_F2   2
#define AWB_LSCMATRIX_ARRAY_SIZE_CIE_F2     1

#define AWB_SATURATION_ARRAY_SIZE_CIE_F2    4
#define AWB_VIGNETTING_ARRAY_SIZE_CIE_F2    2

#define CC_OFFSET_SCALING_F2                10.0f

/*****************************************************************************/
/*!
 * CIE F2:
 *  cool white flourescent CWF
 */
/*****************************************************************************/

// crosstalk matrix
const Isi3x3FloatMatrix_t  OV2715_XTalkCoeff_F2 =
{
    {
        2.11813f,  -1.11962f,   0.00150f, 
       -0.29129f,   1.47821f,  -0.18692f, 
       -0.24547f,  -1.46329f,   2.70875f  
    }
};

// crosstalk offset matrix
const IsiXTalkFloatOffset_t OV2715_XTalkOffset_F2 =
{
    .fCtOffsetRed   = (-195.8125f / CC_OFFSET_SCALING_F2),
    .fCtOffsetGreen = (-191.125f  / CC_OFFSET_SCALING_F2),
    .fCtOffsetBlue  = (-188.5625f / CC_OFFSET_SCALING_F2)
};

// gain matrix
const IsiComponentGain_t OV2715_CompGain_F2 =
{
    .fRed      = 1.18794f,
    .fGreenR   = 1.00000f,
    .fGreenB   = 1.00000f,
    .fBlue     = 2.21726f 
};

// mean value of gaussian mixture model
const Isi2x1FloatMatrix_t OV2715_GaussMeanValue_F2 =
{
    {
        -0.08906f,  0.05864f
    }
};

// inverse covariance matrix
const Isi2x2FloatMatrix_t OV2715_CovarianceMatrix_F2 =
{
    {
        1276.73671f,  -726.99511f, 
        -726.99511f,  2570.47722f 
    }
};

// factor in gaussian mixture model
const IsiGaussFactor_t OV2715_GaussFactor_F2 =
{
    .fGaussFactor =  264.08696f 
};

// thresholds for switching between MAP classification and interpolation
const Isi2x1FloatMatrix_t OV2715_Threshold_F2 =
{
    {
        1.00000f,  1.00000f
    }
};

// saturation curve
float afSaturationSensorGain_F2[AWB_SATURATION_ARRAY_SIZE_CIE_F2] =
{
    1.0f, 2.0f, 4.0f, 8.0f
};

float afSaturation_F2[AWB_SATURATION_ARRAY_SIZE_CIE_F2] =
{
    100.0f, 100.0f, 90.0f, 74.0f
};

const IsiSaturationCurve_t OV2715_SaturationCurve_F2 =
{
    .ArraySize      = AWB_SATURATION_ARRAY_SIZE_CIE_F2,
    .pSensorGain    = &afSaturationSensorGain_F2[0],
    .pSaturation    = &afSaturation_F2[0]
};

// saturation depended color conversion matrices
IsiSatCcMatrix_t OV2715_SatCcMatrix_F2[AWB_COLORMATRIX_ARRAY_SIZE_CIE_F2] =
{
    {
        .fSaturation    = 74.0f,
        .XTalkCoeff     =
        {
            {
                1.99019f,  -1.08722f,   0.09703f, 
                0.26508f,   0.74812f,  -0.01320f, 
                0.32081f,  -1.37585f,   2.05504f  
            }
        }
    },
    {
        .fSaturation    = 100.0f,
        .XTalkCoeff     =
        {
            {
                2.11813f,  -1.11962f,   0.00150f, 
               -0.29129f,   1.47821f,  -0.18692f, 
               -0.24547f,  -1.46329f,   2.70875f              
            }
        }
    }
 };

const IsiCcMatrixTable_t OV2715_CcMatrixTable_F2 =
{
    .ArraySize          = AWB_COLORMATRIX_ARRAY_SIZE_CIE_F2,
    .pIsiSatCcMatrix    = &OV2715_SatCcMatrix_F2[0]
};

// saturation depended color conversion offset vectors
IsiSatCcOffset_t OV2715_SatCcOffset_F2[AWB_COLORMATRIX_ARRAY_SIZE_CIE_F2] =
{
    {
        .fSaturation    = 74.0f,
        .CcOffset       =
        {
            .fCtOffsetRed   = 0.0f,
            .fCtOffsetGreen = 0.0f,
            .fCtOffsetBlue  = 0.0f
        }
    },
    {
        .fSaturation    = 100.0f,
        .CcOffset       =
        {
            .fCtOffsetRed   = (-195.8125f / CC_OFFSET_SCALING_F2),
            .fCtOffsetGreen = (-191.125f  / CC_OFFSET_SCALING_F2),
            .fCtOffsetBlue  = (-188.5625f / CC_OFFSET_SCALING_F2)
        }
    }
};

const IsiCcOffsetTable_t OV2715_CcOffsetTable_F2=
{
    .ArraySize          = AWB_COLORMATRIX_ARRAY_SIZE_CIE_F2,
    .pIsiSatCcOffset    = &OV2715_SatCcOffset_F2[0]
};

// vignetting curve
float afVignettingSensorGain_F2[AWB_VIGNETTING_ARRAY_SIZE_CIE_F2] =
{
    1.0f, 8.0f
};

float afVignetting_F2[AWB_VIGNETTING_ARRAY_SIZE_CIE_F2] =
{
    100.0f, 100.0f
};

const IsiVignettingCurve_t OV2715_VignettingCurve_F2 =
{
    .ArraySize      = AWB_VIGNETTING_ARRAY_SIZE_CIE_F2,
    .pSensorGain    = &afVignettingSensorGain_F2[0],
    .pVignetting    = &afVignetting_F2[0]
};

// vignetting dependend lsc matrices
IsiVignLscMatrix_t OV2715_VignLscMatrix_CIE_F2_1920x1080[AWB_LSCMATRIX_ARRAY_SIZE_CIE_F2] = 
{
    // array item 0
    {
       .fVignetting    = 100.0f,
       .LscMatrix      =
       {
           // ISI_COLOR_COMPONENT_RED
           {
               {
                    1124U, 1103U, 1091U, 1073U, 1054U, 1051U, 1045U, 1035U, 1031U, 1028U, 1025U, 1024U, 1028U, 1033U, 1041U, 1048U, 1059U,
                    1126U, 1110U, 1093U, 1076U, 1063U, 1054U, 1049U, 1043U, 1037U, 1032U, 1030U, 1028U, 1028U, 1034U, 1038U, 1049U, 1056U,
                    1128U, 1109U, 1094U, 1078U, 1065U, 1062U, 1053U, 1048U, 1041U, 1034U, 1035U, 1034U, 1028U, 1032U, 1038U, 1049U, 1052U,
                    1127U, 1109U, 1095U, 1079U, 1069U, 1063U, 1052U, 1051U, 1042U, 1040U, 1034U, 1030U, 1032U, 1032U, 1037U, 1048U, 1045U,
                    1129U, 1113U, 1098U, 1083U, 1073U, 1065U, 1063U, 1049U, 1043U, 1042U, 1039U, 1035U, 1031U, 1032U, 1034U, 1042U, 1048U,
                    1137U, 1117U, 1100U, 1087U, 1076U, 1068U, 1060U, 1054U, 1048U, 1040U, 1040U, 1037U, 1033U, 1033U, 1036U, 1044U, 1046U,
                    1133U, 1122U, 1105U, 1091U, 1079U, 1073U, 1062U, 1053U, 1045U, 1042U, 1043U, 1039U, 1037U, 1037U, 1037U, 1046U, 1046U,
                    1142U, 1125U, 1110U, 1093U, 1085U, 1071U, 1062U, 1056U, 1041U, 1045U, 1042U, 1042U, 1037U, 1038U, 1039U, 1047U, 1047U,
                    1147U, 1130U, 1107U, 1097U, 1085U, 1077U, 1064U, 1055U, 1044U, 1046U, 1045U, 1043U, 1042U, 1038U, 1040U, 1046U, 1050U,
                    1154U, 1131U, 1117U, 1102U, 1090U, 1081U, 1070U, 1059U, 1049U, 1043U, 1043U, 1047U, 1040U, 1044U, 1038U, 1050U, 1047U,
                    1156U, 1138U, 1120U, 1105U, 1090U, 1084U, 1073U, 1063U, 1052U, 1052U, 1049U, 1048U, 1047U, 1041U, 1041U, 1051U, 1055U,
                    1162U, 1145U, 1128U, 1112U, 1095U, 1088U, 1074U, 1067U, 1059U, 1049U, 1051U, 1047U, 1046U, 1045U, 1044U, 1058U, 1054U,
                    1169U, 1152U, 1130U, 1114U, 1100U, 1090U, 1078U, 1069U, 1060U, 1056U, 1052U, 1050U, 1047U, 1047U, 1049U, 1056U, 1062U,
                    1176U, 1157U, 1138U, 1119U, 1102U, 1091U, 1080U, 1071U, 1064U, 1056U, 1053U, 1053U, 1049U, 1048U, 1051U, 1063U, 1067U,
                    1186U, 1164U, 1144U, 1123U, 1109U, 1096U, 1088U, 1077U, 1067U, 1059U, 1056U, 1053U, 1052U, 1052U, 1057U, 1067U, 1070U,
                    1198U, 1167U, 1153U, 1127U, 1115U, 1101U, 1088U, 1077U, 1068U, 1060U, 1057U, 1054U, 1054U, 1055U, 1066U, 1072U, 1078U,
                    1197U, 1175U, 1157U, 1137U, 1118U, 1100U, 1092U, 1075U, 1072U, 1061U, 1063U, 1060U, 1060U, 1066U, 1069U, 1074U, 1088U
               }
           }, 
    
           // ISI_COLOR_COMPONENT_GREENR
           {
               {
                    1127U, 1101U, 1094U, 1080U, 1064U, 1064U, 1056U, 1052U, 1050U, 1036U, 1031U, 1027U, 1024U, 1031U, 1037U, 1048U, 1057U,
                    1141U, 1116U, 1100U, 1088U, 1078U, 1075U, 1074U, 1068U, 1059U, 1054U, 1046U, 1040U, 1036U, 1038U, 1041U, 1060U, 1067U,
                    1139U, 1117U, 1101U, 1088U, 1078U, 1079U, 1077U, 1073U, 1068U, 1055U, 1047U, 1042U, 1036U, 1037U, 1044U, 1053U, 1057U,
                    1140U, 1118U, 1102U, 1092U, 1081U, 1081U, 1078U, 1076U, 1067U, 1064U, 1054U, 1045U, 1039U, 1041U, 1042U, 1051U, 1052U,
                    1145U, 1124U, 1107U, 1093U, 1085U, 1083U, 1085U, 1078U, 1074U, 1066U, 1061U, 1052U, 1044U, 1042U, 1039U, 1048U, 1049U,
                    1148U, 1130U, 1109U, 1099U, 1089U, 1089U, 1083U, 1080U, 1076U, 1070U, 1063U, 1059U, 1048U, 1040U, 1041U, 1048U, 1049U,
                    1156U, 1135U, 1112U, 1104U, 1096U, 1088U, 1085U, 1082U, 1075U, 1076U, 1068U, 1059U, 1048U, 1048U, 1041U, 1048U, 1051U,
                    1162U, 1138U, 1121U, 1108U, 1097U, 1095U, 1086U, 1080U, 1077U, 1074U, 1069U, 1062U, 1054U, 1047U, 1044U, 1054U, 1054U,
                    1172U, 1146U, 1127U, 1113U, 1099U, 1098U, 1091U, 1086U, 1076U, 1073U, 1071U, 1065U, 1057U, 1053U, 1048U, 1053U, 1054U,
                    1179U, 1152U, 1133U, 1118U, 1109U, 1102U, 1097U, 1085U, 1080U, 1075U, 1070U, 1071U, 1064U, 1056U, 1051U, 1054U, 1051U,
                    1180U, 1162U, 1141U, 1127U, 1116U, 1107U, 1094U, 1087U, 1082U, 1077U, 1074U, 1073U, 1067U, 1057U, 1052U, 1057U, 1058U,
                    1197U, 1168U, 1150U, 1136U, 1114U, 1109U, 1100U, 1088U, 1083U, 1085U, 1078U, 1074U, 1069U, 1060U, 1056U, 1063U, 1064U,
                    1206U, 1181U, 1157U, 1136U, 1124U, 1107U, 1094U, 1092U, 1088U, 1082U, 1077U, 1074U, 1072U, 1067U, 1062U, 1070U, 1068U,
                    1217U, 1191U, 1162U, 1145U, 1122U, 1110U, 1105U, 1096U, 1090U, 1082U, 1076U, 1075U, 1072U, 1071U, 1071U, 1076U, 1073U,
                    1222U, 1196U, 1171U, 1142U, 1128U, 1118U, 1107U, 1098U, 1088U, 1081U, 1079U, 1080U, 1077U, 1079U, 1079U, 1083U, 1078U,
                    1237U, 1200U, 1173U, 1161U, 1141U, 1127U, 1111U, 1098U, 1093U, 1083U, 1083U, 1083U, 1083U, 1081U, 1088U, 1088U, 1090U,
                    1232U, 1206U, 1195U, 1168U, 1147U, 1131U, 1114U, 1105U, 1096U, 1094U, 1091U, 1090U, 1091U, 1097U, 1096U, 1098U, 1102U 
               },
           },
    
           // ISI_COLOR_COMPONENT_GREENB
           {
               {
                    1130U, 1102U, 1093U, 1082U, 1065U, 1061U, 1056U, 1052U, 1048U, 1036U, 1029U, 1026U, 1024U, 1029U, 1035U, 1047U, 1055U,
                    1144U, 1116U, 1103U, 1089U, 1076U, 1078U, 1072U, 1067U, 1058U, 1052U, 1042U, 1038U, 1033U, 1036U, 1040U, 1056U, 1065U,
                    1143U, 1118U, 1104U, 1088U, 1079U, 1078U, 1076U, 1072U, 1066U, 1055U, 1045U, 1041U, 1035U, 1035U, 1043U, 1051U, 1056U,
                    1142U, 1121U, 1101U, 1093U, 1082U, 1080U, 1078U, 1075U, 1067U, 1061U, 1052U, 1044U, 1037U, 1040U, 1041U, 1049U, 1052U,
                    1146U, 1126U, 1109U, 1094U, 1084U, 1084U, 1084U, 1078U, 1072U, 1066U, 1058U, 1051U, 1044U, 1040U, 1038U, 1046U, 1049U,
                    1151U, 1131U, 1111U, 1100U, 1091U, 1087U, 1083U, 1080U, 1076U, 1069U, 1064U, 1056U, 1048U, 1039U, 1040U, 1046U, 1048U,
                    1159U, 1137U, 1114U, 1103U, 1096U, 1090U, 1083U, 1082U, 1073U, 1076U, 1066U, 1058U, 1047U, 1047U, 1040U, 1049U, 1051U,
                    1166U, 1139U, 1122U, 1109U, 1098U, 1092U, 1087U, 1080U, 1077U, 1073U, 1069U, 1060U, 1052U, 1046U, 1043U, 1050U, 1054U,
                    1172U, 1147U, 1129U, 1115U, 1101U, 1098U, 1091U, 1086U, 1075U, 1071U, 1069U, 1064U, 1055U, 1053U, 1047U, 1053U, 1053U,
                    1181U, 1153U, 1132U, 1120U, 1109U, 1101U, 1096U, 1085U, 1079U, 1073U, 1069U, 1070U, 1063U, 1055U, 1049U, 1053U, 1050U,
                    1183U, 1164U, 1141U, 1127U, 1116U, 1108U, 1095U, 1088U, 1083U, 1075U, 1074U, 1072U, 1066U, 1058U, 1051U, 1058U, 1057U,
                    1200U, 1169U, 1151U, 1137U, 1116U, 1109U, 1099U, 1086U, 1082U, 1083U, 1076U, 1074U, 1068U, 1059U, 1055U, 1062U, 1064U,
                    1206U, 1182U, 1158U, 1137U, 1123U, 1110U, 1093U, 1092U, 1088U, 1082U, 1077U, 1073U, 1071U, 1068U, 1060U, 1069U, 1069U,
                    1221U, 1192U, 1164U, 1144U, 1125U, 1109U, 1106U, 1095U, 1090U, 1080U, 1075U, 1074U, 1071U, 1070U, 1069U, 1075U, 1072U,
                    1226U, 1198U, 1172U, 1142U, 1128U, 1118U, 1107U, 1097U, 1088U, 1081U, 1078U, 1077U, 1076U, 1078U, 1079U, 1083U, 1077U,
                    1242U, 1202U, 1175U, 1160U, 1140U, 1128U, 1110U, 1097U, 1092U, 1083U, 1080U, 1082U, 1082U, 1081U, 1087U, 1087U, 1088U,
                    1235U, 1207U, 1194U, 1171U, 1146U, 1132U, 1113U, 1104U, 1096U, 1095U, 1091U, 1089U, 1090U, 1095U, 1095U, 1097U, 1103U
               },
           },
    
           // ISI_COLOR_COMPONENT_BLUE
           {
               {
                    1060U, 1052U, 1044U, 1036U, 1036U, 1031U, 1032U, 1039U, 1036U, 1030U, 1024U, 1025U, 1026U, 1026U, 1028U, 1040U, 1043U,
                    1078U, 1066U, 1057U, 1054U, 1046U, 1053U, 1058U, 1057U, 1056U, 1054U, 1043U, 1040U, 1033U, 1038U, 1042U, 1042U, 1051U,
                    1083U, 1066U, 1060U, 1053U, 1056U, 1061U, 1061U, 1061U, 1062U, 1057U, 1050U, 1048U, 1037U, 1037U, 1042U, 1045U, 1047U,
                    1090U, 1070U, 1064U, 1055U, 1063U, 1062U, 1067U, 1069U, 1067U, 1063U, 1053U, 1051U, 1044U, 1044U, 1040U, 1045U, 1048U,
                    1083U, 1076U, 1065U, 1061U, 1058U, 1067U, 1075U, 1070U, 1071U, 1065U, 1065U, 1058U, 1048U, 1046U, 1035U, 1043U, 1041U,
                    1088U, 1078U, 1067U, 1063U, 1064U, 1070U, 1075U, 1074U, 1072U, 1073U, 1066U, 1060U, 1051U, 1043U, 1040U, 1040U, 1045U,
                    1094U, 1081U, 1071U, 1067U, 1072U, 1073U, 1075U, 1079U, 1073U, 1075U, 1076U, 1067U, 1050U, 1049U, 1040U, 1044U, 1046U,
                    1096U, 1085U, 1076U, 1071U, 1071U, 1078U, 1075U, 1076U, 1072U, 1078U, 1068U, 1068U, 1056U, 1050U, 1045U, 1051U, 1049U,
                    1104U, 1089U, 1080U, 1076U, 1077U, 1076U, 1083U, 1078U, 1073U, 1071U, 1072U, 1066U, 1063U, 1051U, 1047U, 1050U, 1048U,
                    1103U, 1097U, 1082U, 1076U, 1077U, 1087U, 1082U, 1082U, 1068U, 1075U, 1075U, 1071U, 1065U, 1057U, 1050U, 1056U, 1051U,
                    1110U, 1103U, 1087U, 1088U, 1084U, 1086U, 1084U, 1078U, 1077U, 1074U, 1078U, 1077U, 1072U, 1057U, 1046U, 1055U, 1055U,
                    1116U, 1105U, 1098U, 1088U, 1082U, 1083U, 1084U, 1077U, 1074U, 1081U, 1083U, 1078U, 1072U, 1058U, 1053U, 1061U, 1053U,
                    1119U, 1115U, 1101U, 1083U, 1089U, 1077U, 1075U, 1075U, 1079U, 1081U, 1079U, 1075U, 1071U, 1062U, 1059U, 1063U, 1058U,
                    1132U, 1110U, 1101U, 1093U, 1073U, 1081U, 1079U, 1088U, 1076U, 1077U, 1081U, 1073U, 1074U, 1067U, 1061U, 1064U, 1061U,
                    1127U, 1111U, 1097U, 1084U, 1082U, 1083U, 1090U, 1081U, 1082U, 1074U, 1073U, 1083U, 1077U, 1070U, 1071U, 1074U, 1071U,
                    1133U, 1106U, 1089U, 1098U, 1088U, 1089U, 1082U, 1087U, 1080U, 1080U, 1081U, 1086U, 1086U, 1075U, 1082U, 1080U, 1072U,
                    1105U, 1086U, 1103U, 1097U, 1088U, 1085U, 1079U, 1086U, 1079U, 1083U, 1086U, 1077U, 1084U, 1089U, 1079U, 1086U, 1092U
               },
           },
       },
    },
};

IsiLscMatrixTable_t OV2715_LscMatrixTable_CIE_F2_1920x1080 = 
{
    .ArraySize          = AWB_LSCMATRIX_ARRAY_SIZE_CIE_F2,
    .psIsiVignLscMatrix = &OV2715_VignLscMatrix_CIE_F2_1920x1080[0],
    .LscXGradTbl        = { 285U, 280U, 278U, 266U, 273U, 266U, 271U, 266U },
    .LscYGradTbl        = { 482U, 475U, 496U, 475U, 489U, 482U, 496U, 489U },
    .LscXSizeTbl        = { 115U, 117U, 118U, 123U, 120U, 123U, 121U, 123U },
    .LscYSizeTbl        = {  68U,  69U,  66U,  69U,  67U,  68U,  66U,  67U }
};



#ifdef __cplusplus
}
#endif

/* @} ov5630_F2 */

#endif /* __OV2715_F2_H__ */

