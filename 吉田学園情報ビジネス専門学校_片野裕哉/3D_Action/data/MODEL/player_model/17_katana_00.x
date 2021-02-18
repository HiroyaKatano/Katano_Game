xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 115;
 0.00000;71.07272;-0.06583;,
 0.11200;71.07272;0.12173;,
 0.56000;66.82181;-2.16317;,
 0.00000;66.82181;-2.53829;,
 0.19399;71.07272;0.63417;,
 0.96995;66.82181;-1.13829;,
 0.22400;71.07272;1.33417;,
 1.12000;66.82181;0.26171;,
 0.19399;71.07272;2.03417;,
 0.96995;66.82181;1.66171;,
 0.11200;71.07272;2.68658;,
 0.56000;66.82181;2.68658;,
 0.00000;71.07272;3.06171;,
 0.00000;66.82181;3.06171;,
 -0.11200;71.07272;2.68658;,
 -0.56000;66.82181;2.68658;,
 -0.19399;71.07272;2.03417;,
 -0.96995;66.82181;1.66171;,
 -0.22400;71.07272;1.33417;,
 -1.12000;66.82181;0.26171;,
 -0.19399;71.07272;0.63417;,
 -0.96995;66.82181;-1.13829;,
 -0.11200;71.07272;0.12173;,
 -0.56000;66.82181;-2.16316;,
 0.00000;71.07272;-0.06583;,
 0.00000;66.82181;-2.53829;,
 0.56000;9.74996;-2.16317;,
 0.00000;9.74996;-2.53829;,
 0.96995;9.74996;-1.13829;,
 1.12000;9.74996;0.26171;,
 0.96995;9.74996;1.66171;,
 0.56000;9.74996;2.68658;,
 0.00000;9.74996;3.06171;,
 -0.56000;9.74996;2.68658;,
 -0.96995;9.74996;1.66171;,
 -1.12000;9.74996;0.26171;,
 -0.96995;9.74996;-1.13829;,
 -0.56000;9.74996;-2.16316;,
 0.00000;9.74996;-2.53829;,
 1.68000;9.73875;-4.58803;,
 0.00000;9.73875;-5.33829;,
 2.90985;9.73875;-2.53829;,
 3.36000;9.73875;0.26171;,
 2.90985;9.73875;3.06171;,
 1.68000;9.73875;5.11145;,
 0.00000;9.73875;5.86171;,
 -1.68000;9.73875;5.11145;,
 -2.90984;9.73875;3.06171;,
 -3.36000;9.73875;0.26171;,
 -2.90985;9.73875;-2.53829;,
 -1.68000;9.73875;-4.58803;,
 0.00000;9.73875;-5.33829;,
 1.68000;7.87208;-4.58803;,
 0.00000;7.87208;-5.33829;,
 2.90985;7.87208;-2.53829;,
 3.36000;7.87208;0.26171;,
 2.90985;7.87208;3.06171;,
 1.68000;7.87208;5.11145;,
 0.00000;7.87208;5.86171;,
 -1.68000;7.87208;5.11145;,
 -2.90984;7.87208;3.06171;,
 -3.36000;7.87208;0.26171;,
 -2.90985;7.87208;-2.53829;,
 -1.68000;7.87208;-4.58803;,
 0.00000;7.87208;-5.33829;,
 0.50400;8.00200;-1.67819;,
 0.00000;8.00200;-1.97829;,
 0.87295;8.00200;-0.85829;,
 1.00800;8.00200;0.26171;,
 0.87295;8.00200;1.38171;,
 0.50400;8.00200;2.20161;,
 0.00000;8.00200;2.50171;,
 -0.50400;8.00200;2.20161;,
 -0.87295;8.00200;1.38171;,
 -1.00800;8.00200;0.26171;,
 -0.87295;8.00200;-0.85829;,
 -0.50400;8.00200;-1.67819;,
 0.00000;8.00200;-1.97829;,
 0.50400;-7.14444;-1.67819;,
 0.00000;-7.14444;-1.97829;,
 0.87295;-7.14444;-0.85829;,
 1.00800;-7.14444;0.26171;,
 0.87295;-7.14444;1.38171;,
 0.50400;-7.14444;2.20161;,
 0.00000;-7.14444;2.50171;,
 -0.50400;-7.14444;2.20161;,
 -0.87295;-7.14444;1.38171;,
 -1.00800;-7.14444;0.26171;,
 -0.87295;-7.14444;-0.85829;,
 -0.50400;-7.14444;-1.67819;,
 0.00000;-7.14444;-1.97829;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;71.07272;1.33417;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;,
 0.00000;-7.14444;0.26171;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;3,2,26,27;,
 4;2,5,28,26;,
 4;5,7,29,28;,
 4;7,9,30,29;,
 4;9,11,31,30;,
 4;11,13,32,31;,
 4;13,15,33,32;,
 4;15,17,34,33;,
 4;17,19,35,34;,
 4;19,21,36,35;,
 4;21,23,37,36;,
 4;23,25,38,37;,
 4;27,26,39,40;,
 4;26,28,41,39;,
 4;28,29,42,41;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;37,38,51,50;,
 4;40,39,52,53;,
 4;39,41,54,52;,
 4;41,42,55,54;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;50,51,64,63;,
 4;53,52,65,66;,
 4;52,54,67,65;,
 4;54,55,68,67;,
 4;55,56,69,68;,
 4;56,57,70,69;,
 4;57,58,71,70;,
 4;58,59,72,71;,
 4;59,60,73,72;,
 4;60,61,74,73;,
 4;61,62,75,74;,
 4;62,63,76,75;,
 4;63,64,77,76;,
 4;66,65,78,79;,
 4;65,67,80,78;,
 4;67,68,81,80;,
 4;68,69,82,81;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;76,77,90,89;,
 3;91,1,0;,
 3;92,4,1;,
 3;93,6,4;,
 3;94,8,6;,
 3;95,10,8;,
 3;96,12,10;,
 3;97,14,12;,
 3;98,16,14;,
 3;99,18,16;,
 3;100,20,18;,
 3;101,22,20;,
 3;102,24,22;,
 3;103,79,78;,
 3;104,78,80;,
 3;105,80,81;,
 3;106,81,82;,
 3;107,82,83;,
 3;108,83,84;,
 3;109,84,85;,
 3;110,85,86;,
 3;111,86,87;,
 3;112,87,88;,
 3;113,88,89;,
 3;114,89,90;;
 
 MeshMaterialList {
  4;
  96;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.220000;0.235200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.586667;0.586667;0.586667;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  94;
  0.000000;1.000000;0.000000;,
  0.668245;0.398105;-0.628459;,
  0.822590;0.340598;-0.455345;,
  0.956046;0.242147;-0.165352;,
  0.980061;0.198696;0.000309;,
  0.975415;0.149985;0.161462;,
  0.900136;0.077455;0.428667;,
  0.804653;0.031124;0.592929;,
  -0.900136;0.077455;0.428667;,
  -0.975415;0.149985;0.161462;,
  -0.980061;0.198696;0.000309;,
  -0.956045;0.242147;-0.165353;,
  -0.822591;0.340596;-0.455343;,
  0.629286;0.204545;-0.749774;,
  0.815355;0.174999;-0.551880;,
  0.971113;0.122349;-0.204866;,
  0.994989;0.099987;0.000155;,
  0.976479;0.075457;0.201978;,
  0.846004;0.039543;0.531708;,
  0.690965;0.015799;0.722716;,
  -0.846004;0.039543;0.531708;,
  -0.976479;0.075457;0.201978;,
  -0.994989;0.099987;0.000155;,
  -0.971113;0.122349;-0.204867;,
  -0.815357;0.174998;-0.551877;,
  0.556534;0.000000;-0.830825;,
  0.777229;0.000000;-0.629218;,
  0.970467;0.000000;-0.241235;,
  1.000000;0.000000;0.000000;,
  0.970466;0.000000;0.241236;,
  0.777232;0.000000;0.629214;,
  0.556544;0.000000;0.830818;,
  -0.777232;0.000000;0.629214;,
  -0.970466;0.000000;0.241236;,
  -1.000000;0.000000;0.000000;,
  -0.970466;0.000000;-0.241236;,
  -0.777232;0.000000;-0.629214;,
  -0.000000;0.999993;-0.003767;,
  0.003248;0.999990;-0.002985;,
  0.004802;0.999987;-0.001446;,
  0.005184;0.999987;0.000000;,
  0.004802;0.999987;0.001446;,
  0.003248;0.999990;0.002985;,
  0.000000;0.999993;0.003767;,
  -0.003248;0.999990;0.002985;,
  -0.004755;0.999988;0.001444;,
  -0.005138;0.999987;-0.000003;,
  -0.004802;0.999987;-0.001446;,
  -0.003248;0.999990;-0.002985;,
  0.000000;0.000000;-1.000000;,
  0.663279;0.000000;-0.748372;,
  0.939403;0.000000;-0.342816;,
  1.000000;0.000000;0.000000;,
  0.939403;0.000000;0.342816;,
  0.663279;0.000000;0.748372;,
  0.000000;0.000000;1.000000;,
  -0.663280;0.000000;0.748371;,
  -0.939403;0.000000;0.342816;,
  -1.000000;0.000000;0.000002;,
  -0.939403;0.000000;-0.342816;,
  -0.663279;0.000000;-0.748372;,
  0.000000;-0.999304;0.037301;,
  -0.032385;-0.999009;0.030538;,
  -0.050562;-0.998596;0.015810;,
  -0.055690;-0.998448;0.000000;,
  -0.050562;-0.998596;-0.015810;,
  -0.032385;-0.999009;-0.030538;,
  0.000000;-0.999304;-0.037301;,
  0.032385;-0.999009;-0.030538;,
  0.050562;-0.998596;-0.015810;,
  0.055690;-0.998448;-0.000000;,
  0.050562;-0.998596;0.015810;,
  0.032385;-0.999009;0.030538;,
  0.511610;0.000000;-0.859218;,
  0.746311;0.000000;-0.665597;,
  0.963390;0.000000;-0.268104;,
  1.000000;0.000000;0.000000;,
  0.963390;0.000000;0.268104;,
  0.746311;0.000000;0.665597;,
  0.511610;0.000000;0.859218;,
  -0.746311;0.000000;0.665597;,
  -0.963390;0.000000;0.268104;,
  -1.000000;0.000000;0.000000;,
  -0.963390;0.000000;-0.268104;,
  -0.746311;0.000000;-0.665597;,
  0.000000;-1.000000;-0.000000;,
  -0.804653;0.031124;0.592929;,
  -0.690965;0.015799;0.722716;,
  -0.668250;0.398103;-0.628456;,
  -0.629293;0.204543;-0.749768;,
  -0.556544;0.000000;0.830818;,
  -0.556544;0.000000;-0.830818;,
  -0.511610;0.000000;0.859218;,
  -0.511610;0.000000;-0.859218;;
  96;
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;86,8,20,87;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,12,24,23;,
  4;12,88,89,24;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;87,20,32,90;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;23,24,36,35;,
  4;24,89,91,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,37,37,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,49,49,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,61,61,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;92,80,80,92;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,93,93,84;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;;
 }
 MeshTextureCoords {
  115;
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;0.166670;,
  0.000000;0.166670;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.250000;0.000000;,
  0.250000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.416670;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.583330;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.750000;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  0.916670;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.083330;0.333330;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.250000;0.333330;,
  0.333330;0.333330;,
  0.416670;0.333330;,
  0.500000;0.333330;,
  0.583330;0.333330;,
  0.666670;0.333330;,
  0.750000;0.333330;,
  0.833330;0.333330;,
  0.916670;0.333330;,
  1.000000;0.333330;,
  0.083330;0.500000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.250000;0.500000;,
  0.333330;0.500000;,
  0.416670;0.500000;,
  0.500000;0.500000;,
  0.583330;0.500000;,
  0.666670;0.500000;,
  0.750000;0.500000;,
  0.833330;0.500000;,
  0.916670;0.500000;,
  1.000000;0.500000;,
  0.083330;0.666670;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.250000;0.666670;,
  0.333330;0.666670;,
  0.416670;0.666670;,
  0.500000;0.666670;,
  0.583330;0.666670;,
  0.666670;0.666670;,
  0.750000;0.666670;,
  0.833330;0.666670;,
  0.916670;0.666670;,
  1.000000;0.666670;,
  0.083330;0.833330;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.250000;0.833330;,
  0.333330;0.833330;,
  0.416670;0.833330;,
  0.500000;0.833330;,
  0.583330;0.833330;,
  0.666670;0.833330;,
  0.750000;0.833330;,
  0.833330;0.833330;,
  0.916670;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.250000;1.000000;,
  0.333330;1.000000;,
  0.416670;1.000000;,
  0.500000;1.000000;,
  0.583330;1.000000;,
  0.666670;1.000000;,
  0.750000;1.000000;,
  0.833330;1.000000;,
  0.916670;1.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;;
 }
}
