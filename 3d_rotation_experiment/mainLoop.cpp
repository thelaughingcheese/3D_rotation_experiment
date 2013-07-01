#include "common.h"
#include "math.h"

#define PI 3.14159265
float axisAngle = 0;
float cubeAxisx = 100;
float cubeAxisy = 100;
float cubeAxisz = 0;

struct vector4{
	float x;
	float y;
	float z;
	float w;

	/*vector4(){
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}*/
};

struct vector3{
	float x;
	float y;
	float z;

	/*vector4(){
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}*/
};

struct matrix4x4{
	float row1[4];
	float row2[4];
	float row3[4];
	float row4[4];

	/*matrix4x4(){
		row1[0] = 0;
		row1[1] = 0;
		row1[2] = 0;
		row1[3] = 0;
		row2[0] = 0;
		row2[1] = 0;
		row2[2] = 0;
		row2[3] = 0;
		row3[0] = 0;
		row3[1] = 0;
		row3[2] = 0;
		row3[3] = 0;
		row4[0] = 0;
		row4[1] = 0;
		row4[2] = 0;
		row4[3] = 0;
	}*/
};

struct edgePair{
	int a;
	int b;
};

vector4 matrixMul(matrix4x4 a, vector4 b){
	vector4 ans;
	ans.x = a.row1[0]*b.x + a.row1[1]*b.y + a.row1[2]*b.z + a.row1[3]*b.w;
	ans.y = a.row2[0]*b.x + a.row2[1]*b.y + a.row2[2]*b.z + a.row2[3]*b.w;
	ans.z = a.row3[0]*b.x + a.row3[1]*b.y + a.row3[2]*b.z + a.row3[3]*b.w;
	ans.w = a.row4[0]*b.x + a.row4[1]*b.y + a.row4[2]*b.z + a.row4[3]*b.w;
	return ans;
}

matrix4x4 matrixMul(matrix4x4 a, matrix4x4 b){
	matrix4x4 ans;
	ans.row1[0] = a.row1[0]*b.row1[0] + a.row1[1]*b.row2[0] + a.row1[2]*b.row3[0] + a.row1[3]*b.row4[0];
	ans.row1[1] = a.row1[0]*b.row1[1] + a.row1[1]*b.row2[1] + a.row1[2]*b.row3[1] + a.row1[3]*b.row4[1];
	ans.row1[2] = a.row1[0]*b.row1[2] + a.row1[1]*b.row2[2] + a.row1[2]*b.row3[2] + a.row1[3]*b.row4[2];
	ans.row1[3] = a.row1[0]*b.row1[3] + a.row1[1]*b.row2[3] + a.row1[2]*b.row3[3] + a.row1[3]*b.row4[3];

	ans.row2[0] = a.row2[0]*b.row1[0] + a.row2[1]*b.row2[0] + a.row2[2]*b.row3[0] + a.row2[3]*b.row4[0];
	ans.row2[1] = a.row2[0]*b.row1[1] + a.row2[1]*b.row2[1] + a.row2[2]*b.row3[1] + a.row2[3]*b.row4[1];
	ans.row2[2] = a.row2[0]*b.row1[2] + a.row2[1]*b.row2[2] + a.row2[2]*b.row3[2] + a.row2[3]*b.row4[2];
	ans.row2[3] = a.row2[0]*b.row1[3] + a.row2[1]*b.row2[3] + a.row2[2]*b.row3[3] + a.row2[3]*b.row4[3];

	ans.row3[0] = a.row3[0]*b.row1[0] + a.row3[1]*b.row2[0] + a.row3[2]*b.row3[0] + a.row3[3]*b.row4[0];
	ans.row3[1] = a.row3[0]*b.row1[1] + a.row3[1]*b.row2[1] + a.row3[2]*b.row3[1] + a.row3[3]*b.row4[1];
	ans.row3[2] = a.row3[0]*b.row1[2] + a.row3[1]*b.row2[2] + a.row3[2]*b.row3[2] + a.row3[3]*b.row4[2];
	ans.row3[3] = a.row3[0]*b.row1[3] + a.row3[1]*b.row2[3] + a.row3[2]*b.row3[3] + a.row3[3]*b.row4[3];

	ans.row4[0] = a.row4[0]*b.row1[0] + a.row4[1]*b.row2[0] + a.row4[2]*b.row3[0] + a.row4[3]*b.row4[0];
	ans.row4[1] = a.row4[0]*b.row1[1] + a.row4[1]*b.row2[1] + a.row4[2]*b.row3[1] + a.row4[3]*b.row4[1];
	ans.row4[2] = a.row4[0]*b.row1[2] + a.row4[1]*b.row2[2] + a.row4[2]*b.row3[2] + a.row4[3]*b.row4[2];
	ans.row4[3] = a.row4[0]*b.row1[3] + a.row4[1]*b.row2[3] + a.row4[2]*b.row3[3] + a.row4[3]*b.row4[3];
	return ans;
}

vector3 vector4to3(vector4 a){
	vector3 ans;
	ans.x = a.x;
	ans.y = a.y;
	ans.z = a.z;
	return ans;
}

vector4 vectorAdd(vector4 a,vector4 b){
	vector4 ans;
	ans.x = a.x+b.x;
	ans.y = a.y+b.y;
	ans.z = a.z+b.z;
	ans.w = a.w+b.w;
	return ans;
}

float vectorDot(vector3 a, vector3 b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vector3 vectorCross(vector3 a, vector3 b){
	vector3 ans;
	ans.x = a.y*b.z - a.z*b.y;
	ans.y = a.z*b.x - a.x*b.z;
	ans.z = a.x*b.y - a.y*b.x;
	return ans;
}

float vectorLength(vector3 a){
	return sqrt(pow(a.x,2)+pow(a.y,2)+pow(a.z,2));
}

vector4 camPos;
float camXRot = 0;
float camYRot = 0;

bool prevLMouse = false;
int mousePosStart[2] = {}; 
float camXRotStart = 0;
float camYRotStart = 0;

vector4 verticies[1024] = 
{
	{0,0,0,1},
	{100,0,0,1},
	{0,100,0,1},
	{0,0,100,1},

	{50,50,50,1},
	{-50,50,50,1},
	{50,-50,50,1},
	{-50,-50,50,1},
	{50,50,-50,1},
	{-50,50,-50,1},
	{50,-50,-50,1},
	{-50,-50,-50,1},
	{1,1,1,1}
};

vector4 cube[9] = {
	{50,50,50,1},
	{-50,50,50,1},
	{50,-50,50,1},
	{-50,-50,50,1},
	{50,50,-50,1},
	{-50,50,-50,1},
	{50,-50,-50,1},
	{-50,-50,-50,1},
	{100,100,100,1}
};

vector4 projVerts[1024];

edgePair edges[4096] = 
{
	{0,1},
	{0,2},
	{0,3},

	{4,5},
	{4,6},
	{6,7},
	{5,7},
	{4,8},
	{5,9},
	{6,10},
	{7,11},
	{8,9},
	{8,10},
	{10,11},
	{9,11},

	{0,12},
};

vector4 moveVectors[6] = 
{
	{0,0,0.2,1},
	{0,0,-0.2,1},
	{0.2,0,0,1},
	{-0.2,0,0,1},
	{0,0.2,0,1},
	{0,-0.2,0,1},
};

unsigned long rgb(unsigned char red, unsigned char green, unsigned char blue){
	return 0x00000000 | blue | green << 8 | red << 16;
}

void setPixel(int x, int y, unsigned long color){
	if(x < 0){
		x = 0;
	}
	else if(x > 799){
		x = 799;
	}

	if(y < 0){
		y = 0;
	}
	else if(y > 599){
		y = 599;
	}

	buffer_b[(599-y)*800 + x] = color;
}

void drawLine(int xstart, int ystart, int xend, int yend){
	float slope = (float)(yend-ystart)/(float)(xend-xstart);

	if(abs(slope) > 1){
		if(yend-ystart < 0){
			for(int i=0;i<-(yend-ystart);i++){
				setPixel(-i*(1/slope)+xstart,ystart-i,rgb(0,255,0));
			}
		}
		else{
			for(int i=0;i<yend-ystart;i++){
				setPixel(i*(1/slope)+xstart,ystart+i,rgb(0,255,0));
			}
		}
	}
	else{
		if(xend-xstart < 0){
			for(int i=0;i<-(xend-xstart);i++){
				setPixel(xstart-i,-i*slope+ystart,rgb(0,255,0));
			}
		}
		else{
			for(int i=0;i<xend-xstart;i++){
				setPixel(xstart+i,i*slope+ystart,rgb(0,255,0));
			}
		}
	}
}

void drawLine(int xstart, int ystart, int xend, int yend, unsigned long color){
	float slope = (float)(yend-ystart)/(float)(xend-xstart);

	if(abs(slope) > 1){
		if(yend-ystart < 0){
			for(int i=0;i<-(yend-ystart);i++){
				setPixel(-i*(1/slope)+xstart,ystart-i,color);
			}
		}
		else{
			for(int i=0;i<yend-ystart;i++){
				setPixel(i*(1/slope)+xstart,ystart+i,color);
			}
		}
	}
	else{
		if(xend-xstart < 0){
			for(int i=0;i<-(xend-xstart);i++){
				setPixel(xstart-i,-i*slope+ystart,color);
			}
		}
		else{
			for(int i=0;i<xend-xstart;i++){
				setPixel(xstart+i,i*slope+ystart,color);
			}
		}
	}
}

void cls(){
	memset(buffer_b,0,1920000);
}

void mainLoop(void *arg){
	camPos.x = 0;
	camPos.y = 0;
	camPos.z = -100;

	for(;;){
		unsigned long *temp = buffer_b;
		buffer_b = buffer_f;
		buffer_f = temp;

		//input
		//camXRot = (mousePos[0]-400)*0.2;
		//camYRot = (mousePos[1]-300)*0.2;

		if(mouseButton[0] == true && prevLMouse == false){
			mousePosStart[0] = mousePos[0];
			mousePosStart[1] = mousePos[1];

			camXRotStart = camXRot;
			camYRotStart = camYRot;
		}
		else if(mouseButton[0] == true){
			camXRot = camXRotStart + ((mousePos[0]-mousePosStart[0])*0.1);
			camYRot = camYRotStart + ((mousePos[1]-mousePosStart[1])*0.1);
		}

		prevLMouse = mouseButton[0];

		//camera rotation
		matrix4x4 cxRot;
		matrix4x4 cyRot;
		memset(&cxRot,0,sizeof(matrix4x4));
		memset(&cyRot,0,sizeof(matrix4x4));

		cxRot.row1[0] = cos(camXRot*PI/180);
		cxRot.row1[2] = sin(camXRot*PI/180);
		cxRot.row2[1] = 1;
		cxRot.row3[0] = -sin(camXRot*PI/180);
		cxRot.row3[2] = cos(camXRot*PI/180);
		cxRot.row4[3] = 1;

		cyRot.row1[0] = 1;
		cyRot.row2[1] = cos(-camYRot*PI/180);
		cyRot.row2[2] = -sin(-camYRot*PI/180);
		cyRot.row3[1] = sin(-camYRot*PI/180);
		cyRot.row3[2] = cos(-camYRot*PI/180);
		cyRot.row4[3] = 1;

		matrix4x4 camRot = matrixMul(cyRot,cxRot);

		if(keyboard[0x57] == true){
			camPos = vectorAdd(camPos,matrixMul(camRot,moveVectors[0]));
		}
		else if(keyboard[0x53] == true){
			camPos = vectorAdd(camPos,matrixMul(camRot,moveVectors[1]));
		}

		if(keyboard[0x44] == true){
			camPos = vectorAdd(camPos,matrixMul(cxRot,moveVectors[2]));
		}
		else if(keyboard[0x41] == true){
			camPos = vectorAdd(camPos,matrixMul(cxRot,moveVectors[3]));
		}

		if(keyboard[VK_SPACE] == true){
			camPos.y += 0.2;
		}
		else if(keyboard[VK_CONTROL] == true){
			camPos.y -= 0.2;
		}

		//object transformations
		matrix4x4 cubeFinal;
		memset(&cubeFinal,0,sizeof(matrix4x4));

		cube[8].x = cubeAxisx;
		cube[8].y = cubeAxisy;
		cube[8].z = cubeAxisz;

		matrix4x4 cRotx;
		matrix4x4 cRotxI;
		matrix4x4 cRoty;
		matrix4x4 cRotyI;
		matrix4x4 cRotz;
		memset(&cRotx,0,sizeof(matrix4x4));
		memset(&cRotxI,0,sizeof(matrix4x4));
		memset(&cRoty,0,sizeof(matrix4x4));
		memset(&cRotyI,0,sizeof(matrix4x4));
		memset(&cRotz,0,sizeof(matrix4x4));

		//x rot axis
		vector3 axisProj;
		vector3 zAxis;
		memset(&axisProj,0,sizeof(vector3));
		memset(&zAxis,0,sizeof(vector3));
		axisProj.y = cube[8].y;
		axisProj.z = cube[8].z;
		zAxis.z = 1;

		float cRotxSin;
		float cRotxCos;

		if(axisProj.y == 0){
			cRotxSin = 0;
			cRotxCos = 1;
		}
		else{
			cRotxSin = vectorLength(vectorCross(axisProj,zAxis))/vectorLength(axisProj);
			cRotxCos = vectorDot(axisProj,zAxis)/vectorLength(axisProj);
		}

		cRotx.row1[0] = 1;
		cRotx.row2[1] = cRotxCos;
		if(axisProj.y > 0){
			cRotx.row2[2] = -cRotxSin;
			cRotx.row3[1] = cRotxSin;
		}
		else{
			cRotx.row2[2] = cRotxSin;
			cRotx.row3[1] = -cRotxSin;
		}
		cRotx.row3[2] = cRotxCos;
		cRotx.row4[3] = 1;

		cRotxI.row1[0] = 1;
		cRotxI.row2[1] = cRotxCos;
		if(axisProj.y > 0){
			cRotxI.row2[2] = cRotxSin;
			cRotxI.row3[1] = -cRotxSin;
		}
		else{
			cRotxI.row2[2] = -cRotxSin;
			cRotxI.row3[1] = cRotxSin;
		}
		cRotxI.row3[2] = cRotxCos;
		cRotxI.row4[3] = 1;

		//y rot axis
		float cRotySin;
		float cRotyCos;

		if(vectorLength(axisProj) == 0){
			cRotySin = 1;
			cRotyCos = 0;
		}
		else{
			cRotySin = vectorLength(vectorCross(axisProj,vector4to3(cube[8])))/(vectorLength(axisProj)*vectorLength(vector4to3(cube[8])));
			cRotyCos = vectorDot(axisProj,vector4to3(cube[8]))/(vectorLength(axisProj)*vectorLength(vector4to3(cube[8])));
		}

		cRoty.row1[0] = cRotyCos;
		if(vector4to3(cube[8]).x > 0){
			cRoty.row1[2] = -cRotySin;
			cRoty.row3[0] = cRotySin;
		}
		else{
			cRoty.row1[2] = cRotySin;
			cRoty.row3[0] = -cRotySin;
		}
		cRoty.row2[1] = 1;
		cRoty.row3[2] = cRotyCos;
		cRoty.row4[3] = 1;

		cRotyI.row1[0] = cRotyCos;
		if(vector4to3(cube[8]).x > 0){
			cRotyI.row1[2] = cRotySin;
			cRotyI.row3[0] = -cRotySin;
		}
		else{
			cRotyI.row1[2] = -cRotySin;
			cRotyI.row3[0] = cRotySin;
		}
		cRotyI.row2[1] = 1;
		cRotyI.row3[2] = cRotyCos;
		cRotyI.row4[3] = 1;

		//z rotation axis
		axisAngle += 0.06;

		cRotz.row1[0] = cos(axisAngle*PI/180);
		cRotz.row1[1] = -sin(axisAngle*PI/180);
		cRotz.row2[0] = sin(axisAngle*PI/180);
		cRotz.row2[1] = cos(axisAngle*PI/180);
		cRotz.row3[2] = 1;
		cRotz.row4[3] = 1;

		//cubeFinal = cRoty;
		//cubeFinal = cRotx;
		//cubeFinal = matrixMul(cRoty,cRotx);
		//cubeFinal = matrixMul(matrixMul(cRotz,cRoty),cRotx);
		//cubeFinal = matrixMul(matrixMul(matrixMul(cRotyI,cRotz),cRoty),cRotx);
		cubeFinal = matrixMul(matrixMul(matrixMul(matrixMul(cRotxI,cRotyI),cRotz),cRoty),cRotx);
		//cubeFinal = matrixMul(cRoty,cRotx);

		for(int i=0;i<9;i++){
			verticies[i+4] = matrixMul(cubeFinal,cube[i]);
		}

		//verticies[12] = cube[8];

		cls();
		//drawLine(400,300,mousePos[0],mousePos[1]);

		//project verts
		//camera translation
		matrix4x4 trans;
		memset(&trans,0,sizeof(matrix4x4));
		trans.row1[3] = -camPos.x;
		trans.row2[3] = -camPos.y;
		trans.row3[3] = -camPos.z;
		trans.row1[0] = 1;
		trans.row2[1] = 1;
		trans.row3[2] = 1;
		trans.row4[3] = 1;
		//camera rotation
		matrix4x4 xRot;
		matrix4x4 yRot;
		memset(&xRot,0,sizeof(matrix4x4));
		memset(&yRot,0,sizeof(matrix4x4));

		xRot.row1[0] = cos(camXRot*PI/180);
		xRot.row1[2] = -sin(camXRot*PI/180);
		xRot.row2[1] = 1;
		xRot.row3[0] = sin(camXRot*PI/180);
		xRot.row3[2] = cos(camXRot*PI/180);
		xRot.row4[3] = 1;

		yRot.row1[0] = 1;
		yRot.row2[1] = cos(camYRot*PI/180);
		yRot.row2[2] = -sin(camYRot*PI/180);
		yRot.row3[1] = sin(camYRot*PI/180);
		yRot.row3[2] = cos(camYRot*PI/180);
		yRot.row4[3] = 1;
		//create camera projection matrix
		matrix4x4 proj;
		memset(&proj,0,sizeof(matrix4x4));

		proj.row1[0] = 1;
		proj.row2[1] = 0.75;
		proj.row3[2] = -1;
		proj.row3[3] = -2;
		proj.row4[2] = -1;

		matrix4x4 final = matrixMul(matrixMul(yRot,xRot),trans);
		//apply projection and perform perspective divide
		for(int i=0;i<1024;i++){
			projVerts[i] = matrixMul(final,verticies[i]);
			if(projVerts[i].z > 0.5){
				projVerts[i].x = projVerts[i].x*800/(projVerts[i].z);
				projVerts[i].y = projVerts[i].y*800/(projVerts[i].z);
			}
		}

//std::cout << std::fixed << camXRot << std::endl;
		//draw edges
		if(projVerts[edges[0].a].z > 0.5 && projVerts[edges[0].b].z > 0.5){
			//setPixel(projVerts[i].x+400,projVerts[i].y+300,rgb(0,255,0));
			drawLine(projVerts[edges[0].a].x+400,projVerts[edges[0].a].y+300,projVerts[edges[0].b].x+400,projVerts[edges[0].b].y+300,rgb(255,0,0));
		}
		if(projVerts[edges[1].a].z > 0.5 && projVerts[edges[1].b].z > 0.5){
			//setPixel(projVerts[i].x+400,projVerts[i].y+300,rgb(0,255,0));
			drawLine(projVerts[edges[1].a].x+400,projVerts[edges[1].a].y+300,projVerts[edges[1].b].x+400,projVerts[edges[1].b].y+300,rgb(0,255,0));
		}
		if(projVerts[edges[2].a].z > 0.5 && projVerts[edges[2].b].z > 0.5){
			//setPixel(projVerts[i].x+400,projVerts[i].y+300,rgb(0,255,0));
			drawLine(projVerts[edges[2].a].x+400,projVerts[edges[2].a].y+300,projVerts[edges[2].b].x+400,projVerts[edges[2].b].y+300,rgb(0,0,255));
		}
		for(int i=3;i<1024;i++){
			if(projVerts[edges[i].a].z > 0.5 && projVerts[edges[i].b].z > 0.5){
				//setPixel(projVerts[i].x+400,projVerts[i].y+300,rgb(0,255,0));
				drawLine(projVerts[edges[i].a].x+400,projVerts[edges[i].a].y+300,projVerts[edges[i].b].x+400,projVerts[edges[i].b].y+300);
			}
		}
	}
}