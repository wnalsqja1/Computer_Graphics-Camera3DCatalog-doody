#pragma once
#pragma comment(lib,"winmm")


#include<gl/glut.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include <GL/glext.h>//for environment mapping

#include<mmsystem.h>
#include<iostream>

#include "bmpfuncs.h"
#include "ObjParser.h"
#include "define.h"

using namespace std;
/*quadric object ����*/
GLUquadricObj* qobj = gluNewQuadric(); // �ܷ��� ����� cylinder, top bottom
GLUquadricObj* qobj1 = gluNewQuadric(); // �������� �����


/*obj ���� �Լ�*/
void Obj_list();

void init(void);
void draw(void);

/*call back �Լ���*/
void mouse(int button, int state, int x, int y);
void mouseWheel(int button,int dir,int x,int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);

void sub_menu_function1(int option);
void sub_menu_function2(int option);
void main_menu_function(int option);

/*���޽ð� call back function*/
void idle(void);

void draw_axis(void);/*��ǥ�� visualization*/
void resize(int width, int height);//glutreshape �Լ��� call back �Լ�

int angle1 = 30;

/*Texture mapping ���� �Լ�*/
void lenz1TextureMapping();//����1, ����2������ texturemapping

/*lab12 draw string */
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);

/*project draw function*/
void draw_camerabody_1();//using obj1
void draw_lenz1();//qobj ����ϴ� �ܷ���
void draw_lenz2();//qobj ����ϴ� ��������
void draw_tripod();//obj ����ϴ� �ﰢ��
void draw_parts();//obj ����ϴ� �÷���
void draw_parts2();
void draw_mirror();

/*relevant envirnment mapping*/
void Environment_mapping();
void Environment_mapping1();
void draw_skybox();

void light_default();
void printInstruction();

void preview_status();
void axis_status();

int map_mode = 0;//default toondra
void text_status();

/*idle ���� �Լ�*/
void lenz1_move(); //��ư 'a' ������ �ܷ��� ����
void lenz2_move(); //��ư 's' ������ �������� ����
void lenz1_rotate();
void lenz2_rotate();
void screen_rotate();
void quick_move();
void flash_move();
/*idle ���� ��������*/
void DrawSphere();
void do_Picking(int x, int y);
void object_status();
void edit_control();
/*accumulation buffer �̿� blur ó���� ���� section*/ 
void draw_model1();
void draw_model2();
void draw_model3();

void frame_buffer();

int main(int argc, char** argv) {
	/*window �ʱ�ȭ */
	int submenu1, submenu2;
	glutInit(&argc, argv);
	/*depth test ����ϱ� ���� ù ��°*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);//1000, 800
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12151627 Joo Min Bum");
	init(); // ����� �ʱ�ȭ �Լ�

	/*menu ����*/
	submenu1 = glutCreateMenu(sub_menu_function1);//sub menu1 : mode ����
	glutAddMenuEntry("global mode", 11);
	glutAddMenuEntry("viewfinder mode", 12);
	glutAddMenuEntry("edit mode",13);

	submenu2 = glutCreateMenu(sub_menu_function2);
	glutAddMenuEntry("Toondra", 21);
	glutAddMenuEntry("night city", 22);

	glutCreateMenu(main_menu_function); //menu �� ���� ���� �� call back �Լ� ����
	glutAddSubMenu("Mode", submenu1);
	glutAddSubMenu("Map", submenu2);
	glutAddMenuEntry("Reset", 111);//�ʱ⼳��
	glutAddMenuEntry("print_instruction", 112);
	glutAddMenuEntry("Quit", 999);//(�޴��̸�, �޴� ���̵�)
	glutAttachMenu(GLUT_RIGHT_BUTTON);//� button�� Ŭ������ ��, menu�� �߰� ���� ������.

	/*callback �Լ� ����*/
	glutReshapeFunc(resize);
	glutDisplayFunc(draw); /*���� �׸��� �Լ� */
	glutMouseFunc(mouse);// ���콺 call back �Լ�
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);

	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

void init(void) {
	/*ȭ���� �⺻������ back ����*/
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	/*default object color set : black*/
	glColor3f(1.0f, 1.0f, 1.0f);

	/*resize callback �Լ� ����*/
	glutReshapeFunc(resize);
	light_default();
	printInstruction();

	/*TEXTURE MAPPING SET*/
	gluQuadricTexture(qobj, GL_TRUE);

	/*Texture mapping ����� setting*/
	Environment_mapping();
	Environment_mapping1();
	lenz1TextureMapping();

	/*frame buffer �̿� */
	//glGenFramebuffers(1, &fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glFrontFace(GL_CCW);//Teapot�� CW���� ���ǵ�
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//MODULATE ����ȿ�� ���̱Ⱑ ����
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	
}

void draw(void) { //12151627 �ֹι�
	/*ȭ�� ��ǥ ���� ����*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, WIDTH, HEIGHT);
	eyex = radius * sin(theta * PI / 180) + cos(phi * PI / 180);
	eyey = radius * sin(phi * PI / 180);
	eyez = radius * cos(theta * PI / 180) + cos(phi * PI / 180);
	upVector = cos(phi * PI / 180);

	light_default();
	GLfloat light_position[] = { 200.0f,10.0f,0.0f,1.0f };
	GLfloat light_position1[] = { 0.0f,0.0f,0.0f,1.0f };
	
	if (mode == 0||mode==2) {//global mode���� ������ǥ�� ����
		gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);
	}
	else if (mode == 1) {//viewfinde mode ���� 1��Ī ����
		gluLookAt(0, 0, 0, eyex, eyey, eyez, 0, upVector, 0);
	}

	draw_skybox();
	
	if (mode == 2) {
		edit_control();
	}
	if (model1_switch == true) {
		draw_model1();
	}
	if (model2_switch == true) {
		draw_model2();
	}
	if (model3_switch == true) {
		draw_model3();
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	draw_mirror();

	if (mode == 0||mode==2) {
		glColor3f(1.0f, 1.0f, 1.0f);
		draw_camerabody_1();
		glColor3f(1.0f, 1.0f, 1.0f);

		if (lenz1__ == TRUE) {
			draw_lenz1();
		}

		else if (lenz2__ == TRUE) {
			draw_lenz2();
		}

		if (quick_draw == TRUE) {
			draw_parts();
			if (tripod_draw == TRUE) {
				draw_tripod();
			}
		}
		draw_parts2();
	}

	if (flash_switch == true) {
		glTranslatef(0.0f, 5.12f, 0.0f);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
		glEnable(GL_LIGHT1);
		glTranslatef(0.0f, -5.12f, 0.0f);
	}

	else if (flash_switch == false) {
		glDisable(GL_LIGHT1);
	}



	if (mode == 1) { //viewfinder ���
		preview_status();
		axis_status();
		text_status();
	}
	else if (mode == 2) {
		object_status();
	}

	glFlush();
	glutSwapBuffers();// Back buffer�� front buffer�� ����
}


/*���콺 �Է� ó�� */
void mouse(int button, int state, int x, int y) {
	if (mode == 2) {
		y = HEIGHT - y;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			do_Picking(x, y); //picking�� ȣ����
			g_nX = x;
			g_nY = y;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			//g_nSelect = 0;
		}
	}
}

void mouseWheel(int button, int dir, int x, int y) {
	if (dir > 0) { //wheel ����
		if (kk1 > 0&&(F_switch==true||shutter_switch==true)&&(ii1!=0)&&(jj1!=6)) {
			kk1 = kk1 - 1;
			shine1 = shine[kk1];
		}

		if (F_switch == true) {
			if (ii1 > 0) {
				ii1 = ii1 - 1;
				F = F_step[ii1];
			}

		}
		else if (shutter_switch == true) {
			if (jj1 < 6) {
				jj1 = jj1 + 1;
				shutter_speed = shutter_step[jj1];
			}
		}
	}
	else {//wheel ����
		if (kk1 < 7 && (F_switch == true || shutter_switch == true && (ii1 != 6) && (jj1 != 0))) {
			kk1 = kk1 + 1;
			shine1 = shine[kk1];
		}
		if (F_switch == true) {
			if (ii1 < 6) {
				ii1 = ii1 + 1;
				F = F_step[ii1];
			}
		}
		else if (shutter_switch == true) {
			if (jj1 > 0) {
				jj1 = jj1 - 1;
				shutter_speed = shutter_step[jj1];
			}
		}
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (mode == 1) {
		if (key == 'n') {
			if (F_switch == true) {
				F_switch = false;
				printf("F.N mode off\n");
			}
			else if (F_switch == false&&shutter_switch==false) {
				F_switch = true;
				printf("F.N mode on\n");
			}
		}
		else if (key == 'm') {
			if (shutter_switch == true) {
				shutter_switch = false;
				printf("shutter speed mode off\n");
			}
			else if (shutter_switch == false&&F_switch == false) {
				shutter_switch = true;
				printf("shutter speed mode on\n");
			}
		}
	}

	if (mode == 2) {
		if (key == 'w') {
			if (g_nSelect == 1) {
				blend_switch = true;
				g_pPosition1[0] = g_pPosition1[0] + 2;
			}
			else if (g_nSelect == 2) {
				blend_switch = true;

				g_pPosition1[3] = g_pPosition1[3] + 2;
			}
			else if (g_nSelect == 3) {
				blend_switch = true;

				g_pPosition1[6] = g_pPosition1[6] + 2;
			}
		}
		else if (key == 'a') {
			if (g_nSelect == 1) {
				blend_switch = true;
				g_pPosition1[2] = g_pPosition1[2] - 2;

			}
			else if (g_nSelect == 2) {
				blend_switch = true;
				g_pPosition1[5] = g_pPosition1[5] - 2;

			}
			else if (g_nSelect == 3) {
				blend_switch = true;
				g_pPosition1[8] = g_pPosition1[8] - 2;
			}
		}
		else if (key == 'd') {
			if (g_nSelect == 1) {
				blend_switch = true;
				g_pPosition1[2] = g_pPosition1[2] + 2;

			}
			else if (g_nSelect == 2) {
				blend_switch = true;
				g_pPosition1[5] = g_pPosition1[5] + 2;

			}
			else if (g_nSelect == 3) {
				blend_switch = true;
				g_pPosition1[8] = g_pPosition1[8] + 2;
			}
		}
		else if (key == 's') {
			if (g_nSelect == 1) {
				blend_switch = true;
				g_pPosition1[0] = g_pPosition1[0] - 2;
			}
			else if (g_nSelect == 2) {
				blend_switch = true;
				g_pPosition1[3] = g_pPosition1[3] - 2;
			}
			else if (g_nSelect == 3) {
				blend_switch = true;
				g_pPosition1[6] = g_pPosition1[6] - 2;
			}
		}
		else if (key == 'f') {
			if (g_nSelect == 1) {
				model1_switch = true;
				blend_switch = false;
			}
			else if (g_nSelect == 2) {
				model2_switch = true;
				blend_switch = false;

			}
			else if (g_nSelect == 3) {
				model3_switch = true;
				blend_switch = false;
			}
			glDisable(GL_BLEND);
			printf("%d �� �� ��ġ �Ϸ�!\n",g_nSelect);
		}
		else if (key == 'g') {
			if (g_nSelect == 1) {
				model1_switch = false;
			}
			else if (g_nSelect == 2) {
				model2_switch = false;

			}
			else if (g_nSelect == 3) {
				model3_switch = false;
			}
			printf("%d �� �� ��ġ ����!\n",g_nSelect);
		}
	}//=============mode2 �� ���� keyboard===================

	/*�Ʒ��� mode 0,1�� ����*/
	if (mode == 0 || mode == 1) {
		if (key == 'o') {
			if (mode == 0) {
				radius++;
				glutPostRedisplay();
			}
		}
		else if (key == 'p') {
			if (mode == 0) {
				radius--;
				glutPostRedisplay();
			}
		}

		/*������� ����Ű*/
		else if (key == 'a') {
			if (lenz1__ == FALSE) {
				lenz1__ = true;
				lenz1_switch = true;
				lenz2_switch = false;
				glutPostRedisplay();
			}
			else if (lenz1__ == TRUE) {
				lenz1__ = false;
				lenz1_switch = false;
				lenz2_switch = false;
				lenz_position1[2] = -10.0f;
				lenz_theta1 = 0;
				lenz_position2[2] = -10.0f;
				lenz_theta2 = 0;
				glutPostRedisplay();
			}
		}
		else if (key == 's') {
			if (lenz2__ == FALSE) {
				lenz2__ = true;
				lenz2_switch = true;
				lenz1_switch = false;
				glutPostRedisplay();
			}
			else if (lenz2__ == TRUE) {
				lenz2__ = false;
				lenz2_switch = false;
				lenz1_switch = false;
				lenz_position2[2] = -10.0f;
				lenz_theta2 = 0;
				lenz_position1[2] = -10.0f;
				lenz_theta1 = 0;
				glutPostRedisplay();
			}
		}
		else if (key == 'd') {
			if (zoom >= 1.0f && zoom <= 45.0f) {
				if (lenz_zoom_control[0] == 360) {
					lenz_zoom_control[0] = 0;
				}
				if (lenz_zoom_control[1] == 0) {
					lenz_zoom_control[1] = 360;
				}
				lenz_zoom_control[0] = lenz_zoom_control[0] + 1.0f;
				lenz_zoom_control[1] = lenz_zoom_control[1] - 1.0f;
				lenz_zoom_control[2] = lenz_zoom_control[2] - 0.1f;
			}

			if (mode == 1&&lenz2__==true) {
				if(zoom>=1.0f&&zoom<=45.0f) zoom = zoom + 1;
				if (zoom <= 1.0f) zoom = 1.0f;
				if (zoom >= 45.0f) zoom = 45.0f;
				printf("zoom: %d\n", zoom);
				resize(800,600);
			}

			glutPostRedisplay();
		}
		else if (key == 'f') {
			if (zoom >= 1.0f && zoom <= 45.0f) {
				lenz_zoom_control[0] = lenz_zoom_control[0] - 1.0f;
				lenz_zoom_control[1] = lenz_zoom_control[1] + 1.0f;
				lenz_zoom_control[2] = lenz_zoom_control[2] + 0.1f;
			}

			if (mode == 1&&lenz2__ == true) {
				if (zoom >= 1.0f && zoom <= 45.0f) zoom = zoom - 1;
				if (zoom <= 1.0f) zoom = 1.0f;
				if (zoom >= 45.0f) zoom = 45.0f;
				printf("zoom: %d\n", zoom);
				resize(800, 600);
			}

			glutPostRedisplay();
		}

		else if (key == 'z') {
			if (screen_open == false) {
				screen_open = true;
				glutPostRedisplay();
			}
			else if (screen_open == true) {
				screen_open = false;
				glutPostRedisplay();
			}
		}

		else if (key == 'q') {
			if (quick_draw == false) {
				quick_draw = true;
				glutPostRedisplay();
			}
			else if (quick_draw == true) {
				quick_draw = false;
				glutPostRedisplay();
				quick[1] = -5.3f;
			}
		}
		else if ((key == 'w') && (quick_draw == true)) {
			if (quick_switch == false) {
				quick_switch = true;
				glutPostRedisplay();
			}
			else if (quick_switch == true) {
				quick_switch = false;
				glutPostRedisplay();
			}
		}
		else if ((key == 'e') && (quick_switch == true)) {
			if (tripod_draw == true) {
				tripod_draw = false;
				glutPostRedisplay();
			}

			else if (tripod_draw == false) {
				tripod_draw = true;
				glutPostRedisplay();
			}
		}
		else if (key == 'c' && mode == 1) { //capture
			printf("ĸ�İ� �Ϸ�Ǿ����ϴ�. capture.bmp\n");
			CaptureScreen();
			PlaySound(TEXT(ShutterSound), NULL, SND_ASYNC | SND_ALIAS); //for sound
		}

		else if (key == 'x') { //capture
			if (flash_move1 == true) {
				flash_move1 = false;
				glutPostRedisplay();
			}

			else if (flash_move1 == false) {
				flash_move1 = true;
				glutPostRedisplay();
			}
		}

		else if (key == 'v') { //capture
			if ((flash_switch == false) && (flash_move1 == true)) {
				printf("flash�� on �Ǿ����ϴ�\n");
				flash_switch = true;
			}
			else if (flash_switch == true) {
				printf("falsh�� off �Ǿ����ϴ�.\n");
				flash_switch = false;
			}
			glutPostRedisplay();
		}
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
	if (mode == 0) {
		if (key == GLUT_KEY_DOWN) {
			if (phi == 0) {
				phi = 360;
			}
			phi = phi - 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_UP) {
			if (phi == 360) {
				phi = 0;
			}
			phi = phi + 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_LEFT) {
			if (theta == 0) {
				theta = 360;
			}
			theta = theta - 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_RIGHT) {
			if (theta == 360) {
				theta = 0;
			}
			theta = theta + 1;
			glutPostRedisplay();
		}
	}
	else if (mode == 1) {
		if (key == GLUT_KEY_DOWN) {
			if (phi == 0) {
				phi = 360;
			}
			phi = phi - 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_UP) {
			if (phi == 360) {
				phi = 0;
			}
			phi = phi + 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_RIGHT) {
			if (theta == 0) {
				theta = 360;
			}
			theta = theta - 1;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_LEFT) {
			if (theta == 360) {
				theta = 0;
			}
			theta = theta + 1;
			glutPostRedisplay();
		}
	}
}

/*======================menu function==============================*/
void main_menu_function(int option) {
	if (option == 999) {
		printf("program�� ����Ǿ����ϴ�.\n");
		exit(0);
	}//Quit�� menu id�� 999�̱� �����̴�.
	else if (option == 112) {
		printf("mode instruction�� ȣ���Ͽ����ϴ�.\n");
		printInstruction();
	}
	else if (option == 111) {
		printf("�ʱ⼳������ reset �Ǿ����ϴ�.\n");
		map_mode = 0;
		init_program();
		glutPostRedisplay();
	}
}

void sub_menu_function1(int option) {
	if (option == 11) {
		printf("============================================\n");
		printf("global mode�� ���õǾ����ϴ�.\n");
		printf("[1] ī�޶� ��ġ ���� \n");
		printf("	Global mode : ����Ű�� �̿��Ͽ� ���� ����\n\n");
		printf("[2] ī�޶� Zoom in, Zoom out\n");
		printf("	O : Zoom out\n	P : Zoom in\n");
		printf("	'a' : �ܷ��� ����, 's' : �������� ����\(zoom in : 'd', zoom out : 'f'\),  \n	������ü : ������ ��ư ������\n");
		printf("[3] ī�޶� Screen ����, �ݱ� ����ġ\n");
		printf("	'z' : Screen open/close \n");
		printf("[4] ī�޶� �μ�ǰ\n");
		printf("	'q' : �ﰢ�� ���� �׸��� 'w' : �ﰢ�� ���� �����ϱ�, 'e' : �ﰢ�� �����ϱ�\n");
		printf("	'x' : �÷��� up/down, 'v' : �÷��� ���� on/off\n");
		printf("============================================\n");

		zoom = 45;
		mode = 0;
	}
	else if (option == 12) {
		printf("============================================\n");
		printf("viewfinder mode�� ���õǾ����ϴ�.\n");
		printf("	'd', 'f'key�� zoom in, zoom out�� �����մϴ�.\n");
		printf("	'n' key�� F��, 'm' key�� shutter speed ������ �����մϴ�.\n");
		printf("	��ġ�� mouse wheel�� ������ �� �ֽ��ϴ�.\n");
		printf("	'c' key�� capture �� �� �ֽ��ϴ�.\n");
		printf("============================================\n");

		mode = 1;
	}
	else if (option == 13) {
		printf("============================================\n");
		printf("edit mode�� ���õǾ����ϴ�.\n");
		printf("	���� ���� ����� 3���� �ǻ�ü �� ���ϴ� ���� �����ϴ�.\n");
		printf("	edit mode������ global mode���� ������ ������ �˴ϴ�.\n");
		printf("	'w','a','s','d' �� �̿��� x-z��鿡�� �ǻ�ü�� ������ �� �ֽ��ϴ�\n");
		printf("	'f' key�� ��ġ�� �� �� �ְ�, 'g' key�� ��ġ�� ����� �� �ֽ��ϴ�.\n");
		printf("============================================\n");
		zoom = 45;
		mode = 2;
	}
	glutPostRedisplay();
}

void sub_menu_function2(int option) {
	if (option == 21) {
		printf("toondra map�� ���õǾ����ϴ�.\n");
		map_mode = 0;
		glutPostRedisplay();
	} 
	else if (option == 22) {
		printf("night city map�� ���õǾ����ϴ�.\n");
		map_mode = 1;
		glutPostRedisplay();
	}
}

/*====================================================================*/
void idle(void) {
	/*���� ���� ����*/
	lenz1_move();
	lenz2_move();
	lenz1_rotate();
	lenz2_rotate();
	screen_rotate();
	quick_move();
	flash_move();
}//���޽ð� call back �Լ�


//lab 06
void resize(int width, int height) {//glutReshapeFunc()�� ����
	glViewport(0, 0, WIDTH, HEIGHT);//V T
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(zoom, float(width) / float(height), 1, 2500);//P T
	glMatrixMode(GL_MODELVIEW);
	
	// ������ ���� �� ũ�� ��ȭ ó���ϱ� ���� ���� �Լ�
	// viewport �缳��, projection t���� aspect ration ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	Obj_list();
}

void draw_axis(void) {//XYZ ��ǥ�� �׸��� �Լ�
	glLineWidth(3);//��ǥ�� �� ��
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);//x red
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);//y green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);//z blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
	glLineWidth(1);//�β� �ٽ� ȯ��
}

void lenz1TextureMapping() {//����1,2������ texture mapping
	glGenTextures(4, lenz2); //cylinder top bottom
	glBindTexture(GL_TEXTURE_2D, lenz2[0]);
	int width, height, channels;
	//TOP
	uchar* img = readImageData("img/LENZ1_T.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	/*bmp image �ҷ�����*/
	//CYLINDER
	img = readImageData("img/LENZ1_C.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, lenz2[2]);
	img = readImageData("img/LENZ1_T.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, lenz2[3]);
	img = readImageData("img/LENZ2_C.bmp", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void printInstruction() {
	printf("===============menu ����============\n");
	printf("���� ���콺 Ŭ������ �޴� ������ �����ϸ�, �׸��� Ŭ���ϸ� \n����� �Բ�, interface�� �� �� �ֽ��ϴ�.\n\n");
	printf("global mode : ī�޶� ���� ��ǥ��� ������ �� �ֽ��ϴ�.\n");
	printf("viewfinder mode : 1��Ī �������� �ǻ�ü�� ĸ���� �� �ֽ��ϴ�.\n");
	printf("edit mode : 3���� �ǻ�ü ���� x-z���� ��ġ�� �� �ֽ��ϴ�.\n\n");
	printf("map mode : toondra, night city map�� �ϳ��� ������ �� �ֽ��ϴ�.\n\n");
	printf("print_instruction : menu������ �ٽ� �ҷ��� �� �ֽ��ϴ�.\n");
	printf("reset : �ʱ���·� ������ �� �ֽ��ϴ�.\n");
	printf("exit : program�� ������ �� �ֽ��ϴ�.\n");
}

void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-WIDTH/2.0f, WIDTH/2.0f, -HEIGHT/2.0f, HEIGHT/2.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void draw_camerabody_1() {
	glLoadName(7);
	glPushMatrix();
	glColor3f(0.1f, 0.1f, 0.1f);
	draw_obj(camera_body1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.095f, 0.0f, -5.5f);
	glRotatef(screen_angle, 0, -1, 0);
	glTranslatef(-2.095f, 0.006f, -1.68f);
	glTranslatef(2.095f, 0.0f, 5.5f);
	/*camera screen���� ���Ŀ� rotate �̿��� ������ ����*/
	draw_obj(camera_screen1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.1f, 2.6f, 3.78f);
	glColor3f(0.9f, 0.9f, 0.9f);
	draw_obj(camera_button1); //shutter button for peeking
	glPopMatrix();
}

void draw_lenz1() {//�ܷ���
	glColor3f(1.0f, 1.0f, 1.0f);//white�� color set�� ���־�� texture ������ ����� ���� ��
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//polygon�� ���� ����� texture ������ ���Ͽ� ����, texture�� ������ ǥ�鿡 ���� ȿ�� ���� ����


	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GL_TRUE);

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(lenz_position1[0], lenz_position1[1],lenz_position1[2]);
	glRotatef(lenz_theta1, 0, 0, 1);

	/*���� top*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[0]);
	gluDisk(qobj, 0.0f, 1.8f, 16, 1);
	glPopMatrix();

	/*���� �Ǹ���*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	gluCylinder(qobj, 1.8f, 1.8f, 1.8f, 16, 16);
	glPopMatrix();

	/*���� �Ѳ�*/
	glPushMatrix();
	glTranslatef(0, 0, 1.8f);
	glBindTexture(GL_TEXTURE_2D, lenz2[2]);
	gluDisk(qobj, 0.0f, 1.8f, 16, 1);
	glPopMatrix();

	glTranslatef(2, 0, 5);
	glRotatef(90, 0, 1, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_FALSE);

}//�ܷ���

void draw_lenz2() {//��������
	glColor3f(1.0f, 1.0f, 1.0f);//white�� color set�� ���־�� texture ������ ����� ���� ��
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//polygon�� ���� ����� texture ������ ���Ͽ� ����, texture�� ������ ǥ�鿡 ���� ȿ�� ���� ����

	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_FILL);
	gluQuadricNormals(qobj1, GLU_FLAT);
	gluQuadricTexture(qobj1, GL_TRUE);
	
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(lenz_position2[0], lenz_position2[1], lenz_position2[2]);
	glRotatef(lenz_theta2, 0, 0, 1);
	glRotatef(lenz_zoom_control[1], 0, 0, 1);

	/*���� �ص� �Ǹ���*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	gluCylinder(qobj1, 1.8f, 1.8f, 2.0f, 16, 16);
	glPopMatrix();

	/*���� �ص� �Ѳ�*/
	glPushMatrix();
	glTranslatef(0, 0, 1.8f);
	glBindTexture(GL_TEXTURE_2D, lenz2[2]);
	gluDisk(qobj1, 0.0f, 1.8f, 16, 1);
	glPopMatrix();

	/*���� �߰� �Ǹ���*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[3]);
	glRotatef(180, 0, 1, 0);
	gluCylinder(qobj1, 1.7f, 1.7f, lenz_zoom_control[2], 16, 16);
	glPopMatrix();
	
	/*���� ���� �Ǹ���*/
	glPushMatrix();
	glTranslatef(0, 0, -lenz_zoom_control[2]);
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	glRotatef(lenz_zoom_control[2], 0, 0, 1);
	gluCylinder(qobj1, 2.3f, 2.3f, 1.2f, 16, 16);
	glPopMatrix();

	/*���� ���� �Ѳ�*/
	glPushMatrix();
	glTranslatef(0, 0, -lenz_zoom_control[2]);
	glBindTexture(GL_TEXTURE_2D, lenz2[0]);
	gluDisk(qobj1, 0.0f, 2.3f, 16, 1);
	glPopMatrix();


	glTranslatef(2, 0, 5);
	glRotatef(90, 0, 1, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_FALSE);
}//�ܷ���

void draw_parts() {
	glLoadName(6);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(quick[0], quick[1], quick[2]);
	glColor3f(0.5f, 0.5f, 0.5f);
	draw_obj(camera_parts1); //�ﰢ�� ����
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void draw_parts2() {
	glLoadName(4);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(flash[0], flash[1], flash[2]);
	glColor3f(0.1f, 0.1f, 0.1f);
	glLoadName(4);
	draw_obj(camera_parts2);// �÷���
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void draw_mirror() {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(mirror_position[0], mirror_position[1], mirror_position[2]);
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void draw_tripod() {
	glLoadName(5);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f, -32.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	draw_obj(tripod_horder);
	draw_obj(tripod_joint6);
	draw_obj(tripod_joint9);
	draw_obj(tripod_joint10);
	glColor3f(0.9f, 0.9f, 0.9f);
	draw_obj(tripod_pipe1);
	draw_obj(tripod_pipe2);
	draw_obj(tripod_pipe3);
	draw_obj(tripod_pipe7);
	draw_obj(tripod_pipe11);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
/*
	tripod_horder = new ObjParser("obj/tripod_horder.obj");
	tripod_joint6 = new ObjParser("obj/tripod_joint6.obj");
	tripod_joint9 = new ObjParser("obj/tripod_joint9.obj");
	tripod_joint10 = new ObjParser("obj/tripod_joint10.obj");
	tripod_pipe1 = new ObjParser("obj/tripod_pipe1");
	tripod_pipe2 = new ObjParser("obj/tripod_pipe2");
	tripod_pipe3 = new ObjParser("obj/tripod_pipe3");
	tripod_pipe7 = new ObjParser("obj/tripod_pipe7");
	tripod_pipe11 = new ObjParser("obj/tripod_pipe11");*/

//lab16
void Environment_mapping() {
		glGenTextures(1, &g_nCubeTex); //�ѹ��� ���ε�
		int imgWidth, imgHeight, channels;

		/*6���� ������ �̿��Ͽ� cube ������ �ؽ�ó�� ����*/
		/*�ѹ��� ���ε����� ���� ���� ���� ����*/
		uchar* img0 = readImageData("img/skybox/left.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img1 = readImageData("img/skybox/right.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img2 = readImageData("img/skybox/top.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img3 = readImageData("img/skybox/bottom.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img4 = readImageData("img/skybox/front.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img5 = readImageData("img/skybox/back.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��


		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

		/*�ؽ�ó �Ӽ� ����*/
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		/*�ؽ�ó ��ǥ �ڵ� ����*/
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	
}

void Environment_mapping1() {
		glGenTextures(1, &g_nCubeTex1); //�ѹ��� ���ε�
		int imgWidth, imgHeight, channels;

		/*6���� ������ �̿��Ͽ� cube ������ �ؽ�ó�� ����*/
		/*�ѹ��� ���ε����� ���� ���� ���� ����*/
		uchar* img0 = readImageData("img/skybox1/left.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img1 = readImageData("img/skybox1/right.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img2 = readImageData("img/skybox1/top.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img3 = readImageData("img/skybox1/bottom.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img4 = readImageData("img/skybox1/front.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��
		uchar* img5 = readImageData("img/skybox1/back.bmp", &imgWidth, &imgHeight, &channels);//image�� ���� �д� ��


		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imgWidth,
			imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

		/*�ؽ�ó �Ӽ� ����*/
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex1);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		/*�ؽ�ó ��ǥ �ڵ� ����*/
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	
}

void draw_skybox() {
	glColor3f(1.0f, 1.0f, 1.0f);//white�� color set�� ���־�� texture ������ ����� ���� ��
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);

	if (map_mode == 0) glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);

	else if (map_mode == 1) glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex1);

	float g_nskysize = 500.0f;

	glBegin(GL_QUADS);

	//right
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);
	//left
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	//top
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);
	//bottom
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	//front
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	//left
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);

	glEnd();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_LIGHTING);
}


/*idle ���� �Լ�*/
void lenz1_move() {
	if (lenz1_switch == true) {
		if (lenz_position1[2] < -5.0f) {
			lenz_position1[2] = lenz_position1[2] + 0.01;
		}
		else {
			lenz1_switch_1 = true;
		}
		glutPostRedisplay();
	}
}
void lenz2_move() {
	if (lenz2_switch == true) {
		if (lenz_position2[2] < -5.0f) {
			lenz_position2[2] = lenz_position2[2] + 0.01;
		}
		else {
			lenz2_switch_1 = true;
		}
		glutPostRedisplay();
	}
}
void lenz1_rotate() {
	if ((lenz1_switch_1 == TRUE)&&(lenz_position1[2]>-5.0f)) {
		if (lenz_theta1 < 90) {
			lenz_theta1 = lenz_theta1 + 0.2;
		}
		else {
			lenz1_switch == FALSE;
			lenz1_switch_1 == FALSE;
		}
		glutPostRedisplay();
	}
}
void lenz2_rotate() {
	if ((lenz2_switch_1 == TRUE)&&(lenz_position2[2]>-5.0f)) {
		if (lenz_theta2  < 90) {
			lenz_theta2 = lenz_theta2 + 0.2;
		}
		else {
			lenz2_switch == FALSE;
			lenz2_switch_1 == FALSE;
		}
		glutPostRedisplay();
	}
}

void screen_rotate() {
	if (screen_open == TRUE) {
		if (screen_angle < 180) {
			screen_angle = screen_angle + 0.5;
			glutPostRedisplay();
		}
	}
	else if (screen_open == FALSE) {
		if (screen_angle > 0) {
			screen_angle = screen_angle - 0.5;
			glutPostRedisplay();
		}
	}
}
/*screen_open, screen_close, screen_angle */

void quick_move() {
	if (quick_switch == TRUE) {
		if (quick[1] < -2.5f) {
			quick[1] = quick[1] + 0.01f;
			glutPostRedisplay();
		}
	}
}

void flash_move() {
	if (flash_move1 == TRUE) {
		if (flash[1] < 5.15f) {
			flash[1] = flash[1] + 0.01f;
			glutPostRedisplay();
		}
	}
	if (flash_move1 == false) {
		if (flash[1] > 0.0f) {
			flash[1] = flash[1] - 0.01f;
			glutPostRedisplay();
		}
	}
}

void preview_status() {
	glViewport(WIDTH*3/4, HEIGHT*3/4 , WIDTH*1/4 ,HEIGHT*1/4);
	glLoadIdentity();
	gluLookAt(10, 10, -10, 0, 0, 0, 0, 1, 0);
	draw_camerabody_1();

	glColor3f(1.0f, 1.0f, 1.0f);
	draw_camerabody_1();
	glColor3f(1.0f, 1.0f, 1.0f);

	if (lenz1__ == TRUE) {
		draw_lenz1();
	}
	else if (lenz2__ == TRUE) {
		draw_lenz2();
	}
	if (quick_draw == TRUE) {
		draw_parts();
		if (tripod_draw == TRUE) {
			draw_tripod();
		}
	}
	draw_parts2();

	glFlush();
}

void axis_status() {
	glDisable(GL_TEXTURE_2D);
	glViewport(WIDTH*3/4, 0, WIDTH/4,HEIGHT/4);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

	draw_axis();
	glFlush();
	glEnable(GL_TEXTURE_2D);
}

void text_status() {
	glDisable(GL_TEXTURE_2D);
	glViewport(0, HEIGHT* 3/ 4, 0, HEIGHT/4);
	char buf1[50];
	char buf2[50];
	
	sprintf(buf1, "F/N value is %f", F);
	sprintf(buf2, "Shutter Speed value is : 1/%d sec", shutter_speed);

	glLoadIdentity();
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, buf1, 20.0f, 50.0f, 1.0f, 1.0f, 0.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, buf2, 20.0f, 150.0f, 1.0f, 1.0f, 0.0f);
	glFlush();
	glEnable(GL_TEXTURE_2D);
}

void object_status() {
	glViewport(0,0,WIDTH,HEIGHT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2.0f,WIDTH/2.0f,-HEIGHT/2.0f,HEIGHT/2.0f,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawSphere();
	glFlush();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, float(WIDTH) / float(HEIGHT), 1, 2500);//P T
}

void DrawSphere() {
	glDisable(GL_TEXTURE_2D);
	glLoadName(1);
	glPushMatrix();
	glTranslatef(g_pPosition[0], g_pPosition[1], 0.0f);
	glColor3f(1, 0, 0);
	glutSolidSphere(25.0f,30,30); // ���� ���� �׷�����
	glPopMatrix();

	glLoadName(2);
	glPushMatrix();
	glTranslatef(g_pPosition[2], g_pPosition[3], 1.0f);
	glColor3f(0, 1, 0);
	glutSolidSphere(25.0f,30,30); // �ʷ� ���� �׷�����
	glPopMatrix();

	glLoadName(3);
	glPushMatrix();
	glTranslatef(g_pPosition[4], g_pPosition[5], 2.0f);
	glColor3f(0, 0, 1);
	glutSolidSphere(25.0f,30,30); // �Ķ� ���� �׷�����
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void do_Picking(int x, int y) {
	GLuint selectBuf[255]; //select buffer�� �����ϰ�
	glSelectBuffer(255, selectBuf);
	//buffer�� GLuint ���� �迭�� picking �� ��ü�� ���� ������ ����
	glRenderMode(GL_SELECT);
	//GL_SELECT�� ����Ͽ� ���� ��� ����
	glMatrixMode(GL_PROJECTION);
	//������ ó���� ���� ��ǥ�迡�� �ǽ��ϹǷ� ���� ��ȯ ��� ����
	glInitNames();
	/*��ü�� �̸� (����)�� ����صθ� �̸� ������ �ʱ�ȭ
	�ݵ�� glRenderMode(GL_SELECT)�� ȣ���� �����ؾ� �Ѵ�.*/
	glPushName(-1);
	/*glPushName�� ���� parameter�� ��ü�� �̸��� ��Ÿ����.
	glInitName()�� �� ȣ���ϸ� �̸� ������ ���ο� �ӽ÷� -1�� �־�д�.*/

	glPushMatrix();
	glLoadIdentity();//������ķ� �ʱ�ȭ �ϰ� 
	GLint viewport[4];// viewport�� ����� �ְ�
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(x, y, 0.1, 0.1, viewport);
	glOrtho(-WIDTH / 2.0f, WIDTH / 2.0f, -HEIGHT / 2.0f, HEIGHT / 2.0f, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	DrawSphere();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();

	GLint hits = glRenderMode(GL_RENDER);
	// sixth step
	if (hits <= 0) return;
	int stack = selectBuf[0];
	unsigned int zMin = selectBuf[1];
	unsigned int zMax = selectBuf[2];
	g_nSelect = selectBuf[3];
	int index = 3 + stack;
	int i;
	for (i = 1; i < hits; i++) {
		stack = selectBuf[index];
		if (zMin > selectBuf[index + 1]) {
			zMin = selectBuf[index + 1];
			g_nSelect = selectBuf[index + 3];
		}
		index += 3 + stack;
	}

}


void edit_control() {
	if (g_nSelect == 1) {
		draw_model1();
	}
	else if (g_nSelect == 2) {
		draw_model2();
	}
	else if (g_nSelect == 3) {
		draw_model3();
	}
	glutPostRedisplay();
}

void draw_model1() {
	if (blend_switch == true) glEnable(GL_BLEND);
	else if (blend_switch == false) glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(g_pPosition1[0], g_pPosition1[1], g_pPosition1[2]);
	glColor4f(1, 0, 0,0.3);
	glutSolidSphere(3.0f, 30, 30); // ���� ���� �׷�����
	glPopMatrix();
}
void draw_model2() {
	if (blend_switch == true) glEnable(GL_BLEND);
	else if (blend_switch == false) glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(g_pPosition1[3], g_pPosition1[4], g_pPosition1[5]);
	glColor4f(0, 1, 0,0.3);
	glutSolidSphere(3.0f, 30, 30); // �ʷ� ���� �׷�����
	glPopMatrix();
}
void draw_model3() {
	if (blend_switch == true) glEnable(GL_BLEND);
	else if (blend_switch == false) glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(g_pPosition1[6], g_pPosition1[7], g_pPosition1[8]);
	glColor4f(0, 0, 1,0.3);
	glutSolidSphere(3.0f, 30, 30); // �Ķ� ���� �׷�����
	glPopMatrix();
}