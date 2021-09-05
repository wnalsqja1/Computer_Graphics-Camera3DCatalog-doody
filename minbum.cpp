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
/*quadric object 생성*/
GLUquadricObj* qobj = gluNewQuadric(); // 단렌즈 만들기 cylinder, top bottom
GLUquadricObj* qobj1 = gluNewQuadric(); // 망원렌즈 만들기


/*obj 관련 함수*/
void Obj_list();

void init(void);
void draw(void);

/*call back 함수들*/
void mouse(int button, int state, int x, int y);
void mouseWheel(int button,int dir,int x,int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);

void sub_menu_function1(int option);
void sub_menu_function2(int option);
void main_menu_function(int option);

/*유휴시간 call back function*/
void idle(void);

void draw_axis(void);/*좌표계 visualization*/
void resize(int width, int height);//glutreshape 함수의 call back 함수

int angle1 = 30;

/*Texture mapping 관련 함수*/
void lenz1TextureMapping();//렌즈1, 렌즈2에대한 texturemapping

/*lab12 draw string */
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);

/*project draw function*/
void draw_camerabody_1();//using obj1
void draw_lenz1();//qobj 사용하는 단렌즈
void draw_lenz2();//qobj 사용하는 망원렌즈
void draw_tripod();//obj 사용하는 삼각대
void draw_parts();//obj 사용하는 플래시
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

/*idle 관련 함수*/
void lenz1_move(); //버튼 'a' 누르면 단렌즈 장착
void lenz2_move(); //버튼 's' 누르면 망원렌즈 장착
void lenz1_rotate();
void lenz2_rotate();
void screen_rotate();
void quick_move();
void flash_move();
/*idle 관련 전역변수*/
void DrawSphere();
void do_Picking(int x, int y);
void object_status();
void edit_control();
/*accumulation buffer 이용 blur 처리를 위한 section*/ 
void draw_model1();
void draw_model2();
void draw_model3();

void frame_buffer();

int main(int argc, char** argv) {
	/*window 초기화 */
	int submenu1, submenu2;
	glutInit(&argc, argv);
	/*depth test 사용하기 위한 첫 번째*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);//1000, 800
	glutInitWindowPosition(300, 300);
	glutCreateWindow("12151627 Joo Min Bum");
	init(); // 사용자 초기화 함수

	/*menu 관련*/
	submenu1 = glutCreateMenu(sub_menu_function1);//sub menu1 : mode 설정
	glutAddMenuEntry("global mode", 11);
	glutAddMenuEntry("viewfinder mode", 12);
	glutAddMenuEntry("edit mode",13);

	submenu2 = glutCreateMenu(sub_menu_function2);
	glutAddMenuEntry("Toondra", 21);
	glutAddMenuEntry("night city", 22);

	glutCreateMenu(main_menu_function); //menu 가 선택 됐을 때 call back 함수 설정
	glutAddSubMenu("Mode", submenu1);
	glutAddSubMenu("Map", submenu2);
	glutAddMenuEntry("Reset", 111);//초기설정
	glutAddMenuEntry("print_instruction", 112);
	glutAddMenuEntry("Quit", 999);//(메뉴이름, 메뉴 아이디)
	glutAttachMenu(GLUT_RIGHT_BUTTON);//어떤 button을 클릭했을 때, menu가 뜨게 만들 것인지.

	/*callback 함수 정의*/
	glutReshapeFunc(resize);
	glutDisplayFunc(draw); /*실제 그리는 함수 */
	glutMouseFunc(mouse);// 마우스 call back 함수
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);

	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

void init(void) {
	/*화면의 기본색으로 back 설정*/
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	/*default object color set : black*/
	glColor3f(1.0f, 1.0f, 1.0f);

	/*resize callback 함수 지정*/
	glutReshapeFunc(resize);
	light_default();
	printInstruction();

	/*TEXTURE MAPPING SET*/
	gluQuadricTexture(qobj, GL_TRUE);

	/*Texture mapping 방법을 setting*/
	Environment_mapping();
	Environment_mapping1();
	lenz1TextureMapping();

	/*frame buffer 이용 */
	//glGenFramebuffers(1, &fbo);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glFrontFace(GL_CCW);//Teapot은 CW으로 정의됨
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//MODULATE 조명효과 보이기가 가능
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	
}

void draw(void) { //12151627 주민범
	/*화면 좌표 정보 설정*/
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
	
	if (mode == 0||mode==2) {//global mode에서 구면좌표계 시점
		gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);
	}
	else if (mode == 1) {//viewfinde mode 에서 1인칭 시점
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



	if (mode == 1) { //viewfinder 모드
		preview_status();
		axis_status();
		text_status();
	}
	else if (mode == 2) {
		object_status();
	}

	glFlush();
	glutSwapBuffers();// Back buffer를 front buffer로 변경
}


/*마우스 입력 처리 */
void mouse(int button, int state, int x, int y) {
	if (mode == 2) {
		y = HEIGHT - y;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			do_Picking(x, y); //picking을 호출함
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
	if (dir > 0) { //wheel 상향
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
	else {//wheel 하향
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
			printf("%d 번 모델 배치 완료!\n",g_nSelect);
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
			printf("%d 번 모델 배치 해제!\n",g_nSelect);
		}
	}//=============mode2 에 대한 keyboard===================

	/*아래는 mode 0,1에 대한*/
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

		/*렌즈관련 단축키*/
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
			printf("캡쳐가 완료되었습니다. capture.bmp\n");
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
				printf("flash가 on 되었습니다\n");
				flash_switch = true;
			}
			else if (flash_switch == true) {
				printf("falsh가 off 되었습니다.\n");
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
		printf("program이 종료되었습니다.\n");
		exit(0);
	}//Quit의 menu id가 999이기 때문이다.
	else if (option == 112) {
		printf("mode instruction을 호출하였습니다.\n");
		printInstruction();
	}
	else if (option == 111) {
		printf("초기설정으로 reset 되었습니다.\n");
		map_mode = 0;
		init_program();
		glutPostRedisplay();
	}
}

void sub_menu_function1(int option) {
	if (option == 11) {
		printf("============================================\n");
		printf("global mode가 선택되었습니다.\n");
		printf("[1] 카메라 위치 변경 \n");
		printf("	Global mode : 방향키를 이용하여 조정 가능\n\n");
		printf("[2] 카메라 Zoom in, Zoom out\n");
		printf("	O : Zoom out\n	P : Zoom in\n");
		printf("	'a' : 단렌즈 장착, 's' : 망원렌즈 장착\(zoom in : 'd', zoom out : 'f'\),  \n	장착해체 : 눌렀던 버튼 누르기\n");
		printf("[3] 카메라 Screen 열기, 닫기 스위치\n");
		printf("	'z' : Screen open/close \n");
		printf("[4] 카메라 부속품\n");
		printf("	'q' : 삼각대 퀵슈 그리기 'w' : 삼각대 퀵슈 부착하기, 'e' : 삼각대 장착하기\n");
		printf("	'x' : 플래시 up/down, 'v' : 플래시 조명 on/off\n");
		printf("============================================\n");

		zoom = 45;
		mode = 0;
	}
	else if (option == 12) {
		printf("============================================\n");
		printf("viewfinder mode가 선택되었습니다.\n");
		printf("	'd', 'f'key로 zoom in, zoom out이 가능합니다.\n");
		printf("	'n' key로 F값, 'm' key로 shutter speed 조정이 가능합니다.\n");
		printf("	수치는 mouse wheel로 조정할 수 있습니다.\n");
		printf("	'c' key로 capture 할 수 있습니다.\n");
		printf("============================================\n");

		mode = 1;
	}
	else if (option == 13) {
		printf("============================================\n");
		printf("edit mode가 선택되었습니다.\n");
		printf("	먼저 우측 상단의 3개의 피사체 중 원하는 것을 누릅니다.\n");
		printf("	edit mode에서는 global mode에서 시점이 고정이 됩니다.\n");
		printf("	'w','a','s','d' 를 이용해 x-z평면에서 피사체를 움직일 수 있습니다\n");
		printf("	'f' key로 배치를 할 수 있고, 'g' key로 배치를 취소할 수 있습니다.\n");
		printf("============================================\n");
		zoom = 45;
		mode = 2;
	}
	glutPostRedisplay();
}

void sub_menu_function2(int option) {
	if (option == 21) {
		printf("toondra map이 선택되었습니다.\n");
		map_mode = 0;
		glutPostRedisplay();
	} 
	else if (option == 22) {
		printf("night city map이 선택되었습니다.\n");
		map_mode = 1;
		glutPostRedisplay();
	}
}

/*====================================================================*/
void idle(void) {
	/*렌즈 무빙 관련*/
	lenz1_move();
	lenz2_move();
	lenz1_rotate();
	lenz2_rotate();
	screen_rotate();
	quick_move();
	flash_move();
}//유휴시간 call back 함수


//lab 06
void resize(int width, int height) {//glutReshapeFunc()의 인자
	glViewport(0, 0, WIDTH, HEIGHT);//V T
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(zoom, float(width) / float(height), 1, 2500);//P T
	glMatrixMode(GL_MODELVIEW);
	
	// 윈도우 생성 및 크기 변화 처리하기 위해 만든 함수
	// viewport 재설정, projection t에서 aspect ration 조절
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	Obj_list();
}

void draw_axis(void) {//XYZ 좌표계 그리기 함수
	glLineWidth(3);//좌표축 두 꼐
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
	glLineWidth(1);//두께 다시 환원
}

void lenz1TextureMapping() {//렌즈1,2에대한 texture mapping
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
	/*bmp image 불러오기*/
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
	printf("===============menu 설명============\n");
	printf("우측 마우스 클릭으로 메뉴 생성이 가능하며, 항목을 클릭하면 \n실행과 함께, interface를 볼 수 있습니다.\n\n");
	printf("global mode : 카메라를 구면 좌표계로 관찰할 수 있습니다.\n");
	printf("viewfinder mode : 1인칭 시점으로 피사체를 캡쳐할 수 있습니다.\n");
	printf("edit mode : 3개의 피사체 모델을 x-z평면상에 배치할 수 있습니다.\n\n");
	printf("map mode : toondra, night city map중 하나를 선택할 수 있습니다.\n\n");
	printf("print_instruction : menu설명을 다시 불러올 수 있습니다.\n");
	printf("reset : 초기상태로 설정할 수 있습니다.\n");
	printf("exit : program을 종료할 수 있습니다.\n");
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
	/*camera screen으로 추후에 rotate 이용해 돌려줄 예정*/
	draw_obj(camera_screen1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.1f, 2.6f, 3.78f);
	glColor3f(0.9f, 0.9f, 0.9f);
	draw_obj(camera_button1); //shutter button for peeking
	glPopMatrix();
}

void draw_lenz1() {//단렌즈
	glColor3f(1.0f, 1.0f, 1.0f);//white로 color set을 해주어야 texture 색상이 제대로 적용 됨
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//polygon의 원래 색상과 texture 색상을 곱하여 덮음, texture가 입혀진 표면에 광원 효과 설정 가능


	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GL_TRUE);

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(lenz_position1[0], lenz_position1[1],lenz_position1[2]);
	glRotatef(lenz_theta1, 0, 0, 1);

	/*렌즈 top*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[0]);
	gluDisk(qobj, 0.0f, 1.8f, 16, 1);
	glPopMatrix();

	/*렌즈 실린더*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	gluCylinder(qobj, 1.8f, 1.8f, 1.8f, 16, 16);
	glPopMatrix();

	/*렌즈 뚜껑*/
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

}//단렌즈

void draw_lenz2() {//망원렌즈
	glColor3f(1.0f, 1.0f, 1.0f);//white로 color set을 해주어야 texture 색상이 제대로 적용 됨
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//polygon의 원래 색상과 texture 색상을 곱하여 덮음, texture가 입혀진 표면에 광원 효과 설정 가능

	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_FILL);
	gluQuadricNormals(qobj1, GLU_FLAT);
	gluQuadricTexture(qobj1, GL_TRUE);
	
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(lenz_position2[0], lenz_position2[1], lenz_position2[2]);
	glRotatef(lenz_theta2, 0, 0, 1);
	glRotatef(lenz_zoom_control[1], 0, 0, 1);

	/*렌즈 밑동 실린더*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	gluCylinder(qobj1, 1.8f, 1.8f, 2.0f, 16, 16);
	glPopMatrix();

	/*렌즈 밑동 뚜껑*/
	glPushMatrix();
	glTranslatef(0, 0, 1.8f);
	glBindTexture(GL_TEXTURE_2D, lenz2[2]);
	gluDisk(qobj1, 0.0f, 1.8f, 16, 1);
	glPopMatrix();

	/*렌즈 중간 실린더*/
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, lenz2[3]);
	glRotatef(180, 0, 1, 0);
	gluCylinder(qobj1, 1.7f, 1.7f, lenz_zoom_control[2], 16, 16);
	glPopMatrix();
	
	/*렌즈 윗동 실린더*/
	glPushMatrix();
	glTranslatef(0, 0, -lenz_zoom_control[2]);
	glBindTexture(GL_TEXTURE_2D, lenz2[1]);
	glRotatef(lenz_zoom_control[2], 0, 0, 1);
	gluCylinder(qobj1, 2.3f, 2.3f, 1.2f, 16, 16);
	glPopMatrix();

	/*렌즈 윗동 뚜껑*/
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
}//단렌즈

void draw_parts() {
	glLoadName(6);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(quick[0], quick[1], quick[2]);
	glColor3f(0.5f, 0.5f, 0.5f);
	draw_obj(camera_parts1); //삼각대 퀵슈
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
	draw_obj(camera_parts2);// 플래시
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
		glGenTextures(1, &g_nCubeTex); //한번의 바인딩
		int imgWidth, imgHeight, channels;

		/*6장의 영상을 이용하여 cube 형태의 텍스처로 지정*/
		/*한번의 바인딩으로 여섯 개의 영상 지정*/
		uchar* img0 = readImageData("img/skybox/left.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img1 = readImageData("img/skybox/right.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img2 = readImageData("img/skybox/top.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img3 = readImageData("img/skybox/bottom.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img4 = readImageData("img/skybox/front.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img5 = readImageData("img/skybox/back.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것


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

		/*텍스처 속성 지정*/
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		/*텍스처 좌표 자동 생성*/
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	
}

void Environment_mapping1() {
		glGenTextures(1, &g_nCubeTex1); //한번의 바인딩
		int imgWidth, imgHeight, channels;

		/*6장의 영상을 이용하여 cube 형태의 텍스처로 지정*/
		/*한번의 바인딩으로 여섯 개의 영상 지정*/
		uchar* img0 = readImageData("img/skybox1/left.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img1 = readImageData("img/skybox1/right.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img2 = readImageData("img/skybox1/top.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img3 = readImageData("img/skybox1/bottom.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img4 = readImageData("img/skybox1/front.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것
		uchar* img5 = readImageData("img/skybox1/back.bmp", &imgWidth, &imgHeight, &channels);//image를 각각 읽는 것


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

		/*텍스처 속성 지정*/
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex1);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		/*텍스처 좌표 자동 생성*/
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	
}

void draw_skybox() {
	glColor3f(1.0f, 1.0f, 1.0f);//white로 color set을 해주어야 texture 색상이 제대로 적용 됨
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


/*idle 관련 함수*/
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
	glutSolidSphere(25.0f,30,30); // 빨강 구를 그려주자
	glPopMatrix();

	glLoadName(2);
	glPushMatrix();
	glTranslatef(g_pPosition[2], g_pPosition[3], 1.0f);
	glColor3f(0, 1, 0);
	glutSolidSphere(25.0f,30,30); // 초록 구를 그려주자
	glPopMatrix();

	glLoadName(3);
	glPushMatrix();
	glTranslatef(g_pPosition[4], g_pPosition[5], 2.0f);
	glColor3f(0, 0, 1);
	glutSolidSphere(25.0f,30,30); // 파란 구를 그려주자
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void do_Picking(int x, int y) {
	GLuint selectBuf[255]; //select buffer를 생성하고
	glSelectBuffer(255, selectBuf);
	//buffer에 GLuint 형의 배열에 picking 한 개체에 대한 정보를 저장
	glRenderMode(GL_SELECT);
	//GL_SELECT를 사용하여 선택 모드 설정
	glMatrixMode(GL_PROJECTION);
	//선택의 처리는 시점 좌표계에서 실시하므로 투시 변환 행렬 설정
	glInitNames();
	/*개체의 이름 (정수)를 등록해두면 이름 스택을 초기화
	반드시 glRenderMode(GL_SELECT)를 호출후 실행해야 한다.*/
	glPushName(-1);
	/*glPushName에 들어가는 parameter는 개체의 이름을 나타낸다.
	glInitName()직 후 호출하면 이름 스택의 선두에 임시로 -1을 넣어둔다.*/

	glPushMatrix();
	glLoadIdentity();//단위행렬로 초기화 하고 
	GLint viewport[4];// viewport도 만들어 주고
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
	glutSolidSphere(3.0f, 30, 30); // 빨강 구를 그려주자
	glPopMatrix();
}
void draw_model2() {
	if (blend_switch == true) glEnable(GL_BLEND);
	else if (blend_switch == false) glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(g_pPosition1[3], g_pPosition1[4], g_pPosition1[5]);
	glColor4f(0, 1, 0,0.3);
	glutSolidSphere(3.0f, 30, 30); // 초록 구를 그려주자
	glPopMatrix();
}
void draw_model3() {
	if (blend_switch == true) glEnable(GL_BLEND);
	else if (blend_switch == false) glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(g_pPosition1[6], g_pPosition1[7], g_pPosition1[8]);
	glColor4f(0, 0, 1,0.3);
	glutSolidSphere(3.0f, 30, 30); // 파란 구를 그려주자
	glPopMatrix();
}