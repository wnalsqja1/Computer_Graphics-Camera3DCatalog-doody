/*
Quadric : ī�޶� ���� (��������, �ܷ���)
obj : ī�޶� �ٵ�, ��ư, �ﰢ�� ����
*/

#pragma once

#define PI 3.14159265
#define WIDTH 800
#define HEIGHT 600

#define ShutterSound "./sound/shutter.wav"


volatile double eyex = 15.0;
volatile double eyey = 15.0;
volatile double eyez = 15.0;
volatile double theta = 45.0;
volatile double phi = 45.0;
volatile double radius = 20;
volatile double upVector = cos(phi * PI / 180);

double lenz_theta1 = 0.0f;
double lenz_theta2 = 0.0f;
double lenz_position1[3] = { -1.4f,0.0f,-10.0f };
double lenz_position2[3] = { -1.4f,0.0f,-10.0f };
double lenz_zoom_control[3] = { 0.0f,0.0f,3.0f };//�ص� �Ǹ��� ȸ��, ���� �Ǹ��� ȸ��, ��� �Ǹ��� ����
double quick[3] = { 0.33f, -5.3f, -1.28f };
double flash[3] = { -0.5f,0.0f,-0.96f };
double mirror_position[3] = {0.8f,0.19f,-1.35f};

float g_pPosition[6] = {300.0f,50.0f,300.0f,120.0f,300.0f,200.0f };
float g_pPosition1[9] = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
int g_nX=0, g_nY=0;
int g_nSelect = 0;

double cameravector[3] = { 0,0,0 }; //1��Ī camera zoom in, zoom out �ϱ� ���ؼ�

double screen_angle = 0; //��ũ�� ���ݱ�

bool lenz1__ = false;//�׷��ִ� ����ġ
bool lenz2__ = false;//�׷��ִ� ����ġ
bool lenz1_switch = false;
bool lenz2_switch = false;
bool lenz1_switch_1 = false; //translation�� rotation�ϴ� ����ġ
bool lenz2_switch_1 = false; //translation�� rotation�ϴ� ����ġ
bool lenz2_switch_in = false;
bool lenz2_switch_out = false;
bool screen_open = false;
bool quick_switch = false;
bool quick_draw = false;
bool tripod_draw = false;
bool flash_move1 = false;
bool flash_draw = false;
bool flash_switch = false;

bool F_switch = false;
bool shutter_switch = false;
bool blend_switch = false;

bool model1_switch = false;
bool model2_switch = false;
bool model3_switch = false;
int mode = 0; //0���� ī�޶� ���� (�ָ���ǥ��) 1���� �����δ� ��� + viewport�� ����

int zoom = 45; // field of view

/*F���� ���ͽ��ǵ�, Reciprocity*/
double F=4.0f;
int shutter_speed=60;
double Reciprocity=0;

int ii1 = 3; //wheel ���� Ƚ�� with F
int jj1 = 3; //wheel ���� Ƚ�� with J
int kk1 = 7;

int shine1 = 64;

double F_step[7] = { 2.0f,2.8f,4.0f,5.6f,8.0f,11.0f,16.0f };//7step shutter speed
int shutter_step[7] = {500,250,125,60,30,15,8};//7step shutter speed
int shine[8] = {8, 10, 12, 14, 16, 32, 64, 128 };
//F_step{n} * shutter_step{n} when n = 0:6  same r

/*GLUint (Texture mapping ��)*/
GLuint g_nCubeTex; //for environment mapping
GLuint g_nCubeTex1; //for environment mapping2
GLuint g_nbody;
GLuint lenz2[4]; //�ܷ��� ��������
GLuint bodytexture; //for obj camera body


/*obj ����*/
ObjParser* camera_body1;
ObjParser* camera_screen1;
ObjParser* camera_button1;//shutter

ObjParser* camera_parts1; //�ﰢ�� ����
ObjParser* camera_parts2; //flash

ObjParser* tripod_horder;
ObjParser* tripod_joint6;
ObjParser* tripod_joint9;
ObjParser* tripod_joint10;
ObjParser* tripod_pipe1;
ObjParser* tripod_pipe2;
ObjParser* tripod_pipe3;
ObjParser* tripod_pipe7;
ObjParser* tripod_pipe11;


void Obj_list() {
	camera_body1 = new ObjParser("obj/DSLRBODY1.obj");
	camera_screen1 = new ObjParser("obj/DSLRSCREEN1.obj");
	camera_button1 = new ObjParser("obj/DSLRBUTTON1.obj");
	camera_parts1 = new ObjParser("obj/PARTS1.obj");
	camera_parts2 = new ObjParser("obj/PARTS2.obj");

	tripod_horder = new ObjParser("obj/tripod_horder.obj");
	tripod_joint6 = new ObjParser("obj/tripod_joint6.obj");
	tripod_joint9 = new ObjParser("obj/tripod_joint9.obj");
	tripod_joint10 = new ObjParser("obj/tripod_joint10.obj");

	tripod_pipe1 = new ObjParser("obj/tripod_pipe1.obj");
	tripod_pipe2 = new ObjParser("obj/tripod_pipe2.obj");
	tripod_pipe3 = new ObjParser("obj/tripod_pipe3.obj");
	tripod_pipe7 = new ObjParser("obj/tripod_pipe7.obj");
	tripod_pipe11 = new ObjParser("obj/tripod_pipe11.obj");
}

void init_program() {
	F = 5.6f;
	shutter_speed = 60;
	zoom = 45;
	mode = 0;

	eyex = 15.0;
	eyey = 15.0;
	eyez = 15.0;
	theta = 45.0;
	phi = 45.0;
	radius = 20;
	upVector = cos(phi * PI / 180);

	lenz_theta1 = 0.0f;
	lenz_theta2 = 0.0f;

	lenz1__ = false;//�׷��ִ� ����ġ
	lenz2__ = false;//�׷��ִ� ����ġ
	lenz1_switch = false;
	lenz2_switch = false;
	lenz1_switch_1 = false; //translation�� rotation�ϴ� ����ġ
	lenz2_switch_1 = false; //translation�� rotation�ϴ� ����ġ
	lenz2_switch_in = false;
	lenz2_switch_out = false;
	screen_open = false;
	quick_switch = false;
	quick_draw = false;
	tripod_draw = false;
	flash_move1 = false;
	flash_draw = false;
	flash_switch = false;

	F_switch = false;
	shutter_switch = false;

	model1_switch = false;
	model2_switch = false;
	model3_switch = false;
}

/*obj�� draw�ϴ� �Լ�*/
void draw_obj(ObjParser* objParser)
{
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

void light_default() {
	GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f,1.0f,1.0f };
	GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };


	GLfloat ambientflash[] = {0.2f,0.2f,0.2f,1.0f};
	GLfloat diffuseflash[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specularflash[] = { 1.0f,1.0f,1.0,1.0f };

	GLfloat diffuse_Sun[] = { 1.0f,0.0f,0.0f,1.0f };
	GLfloat ambient_Sun[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat specular_Sun[] = { 1.0f,1.0f,1.0f,1.0f };

	/*�����Դϴ�*/
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientflash);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseflash);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularflash);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMateriali(GL_FRONT, GL_SHININESS,shine1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


void CaptureScreen()
{
    BITMAPFILEHEADER bmpfile; // ��Ʈ���������
    BITMAPINFOHEADER bmpinfo; // ��Ʈ���������

    int Width, Height;
	Width = 400;
	Height = 300;

    unsigned char* pixels = new unsigned char[sizeof(unsigned char) * Width * Height * 3]; //unsigned char = BYTE 0-255
    FILE* file = fopen("capture.bmp", "wb");

    glReadPixels(200, 125, Width, Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

    memset(&bmpfile, 0, sizeof(bmpfile)); // 14����Ʈ 0 ��.
    memset(&bmpinfo, 0, sizeof(bmpinfo)); // 
    printf("%d", sizeof(bmpfile));
    bmpfile.bfType = 'MB';
    bmpfile.bfSize = sizeof(bmpfile) + sizeof(bmpinfo) + Width * Height * 3;
    bmpfile.bfOffBits = sizeof(bmpfile) + sizeof(bmpinfo);

    bmpinfo.biSize = sizeof(bmpinfo); // ����üũ��
    bmpinfo.biWidth = Width; // �̹��� ����
    bmpinfo.biHeight = Height; // �̹��� ����
    bmpinfo.biPlanes = 1; // �÷��μ�
    bmpinfo.biBitCount = 24; // ��Ʈ�� 
    bmpinfo.biSizeImage = Width * Height * 3; // �̹�����ũ��

    fwrite(&bmpfile, sizeof(bmpfile), 1, file);
    fwrite(&bmpinfo, sizeof(bmpinfo), 1, file);
    fwrite(pixels, sizeof(unsigned char), Height * Width * 3, file);

    fclose(file);

    free(pixels);
}

void draw_obj_camera(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture �� ������ ���� enable
	glBindTexture(GL_TEXTURE_2D, bodytexture);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}