#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

// TODO : make a calculator class
class Calculator{
private:
	std::vector<Button> buttons;
	double currentValueDisplayed = 0; 
public:
};

float scale = 1, x = 0.0, y = 0.0, cal_angle = 0.0;
float animation_angle = 0;
double xpos, ypos;
int animation_flag = 0;
double posX, posY, posZ;
int right_click = 0; 
int rightclickindex=0 ;
int reset = 0;

struct Vertex{
    float _x, _y, _z, _r, _g, _b, _alpha;
    Vertex(){}
    Vertex(float x, float y, float z, float r, float g, float b, float alpha)
	:_x(x), _y(y), _z(z),
	 _r(r), _g(g), _b(b),
	 _alpha(alpha)
	{}
};

struct Button{
	char _value;
    Vertex _v1, _v2, _v3, _v4;
	float center_x, center_y;
    Button(){}
    Button(Vertex v1,Vertex v2, Vertex v3, Vertex v4, char value){
        _v1 = v1; _v2 = v2;
        _v3 = v3; _v4 = v4;
        _value = value;
		center_x = (v1._x+v2._x)/2;
		center_y = (v2._y+v3._y)/2;
    }
};

void drawButton(Button b){
	glLoadIdentity();//load identity matrix
    
    glTranslatef(x, y, 0);//move forward 4 units
    glScalef(scale, scale, scale);
    glRotatef( cal_angle,0,0,1);
	// cal_angle+=1;
 
    
	glBegin(GL_QUADS);

	glColor4f(b._v1._r, b._v1._g, b._v1._b, b._v1._alpha);
    glVertex3f(b._v1._x, b._v1._y, b._v1._z);

    glColor4f(b._v2._r, b._v2._g, b._v2._b, b._v2._alpha);
    glVertex3f(b._v2._x, b._v2._y, b._v2._z);
    
    glColor4f(b._v3._r, b._v3._g, b._v3._b, b._v3._alpha);
    glVertex3f(b._v3._x, b._v3._y, b._v3._z);

    glColor4f(b._v4._r, b._v4._g, b._v4._b, b._v4._alpha);
    glVertex3f(b._v4._x, b._v4._y, b._v4._z);

    glEnd();

}
float distance(float x1, float y1, float x2, float y2){
	return sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2)); 
}


void GetGLOBALPos()
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = xpos;
    winY = viewport[3] - ypos;
    //glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, 0, modelview, projection, viewport, &posX, &posY, &posZ);
	// cout<<posX<<" "<<posY<<endl;
    //return CVector3(posX, posY, posZ);
}
void animation( std::vector<Button> arr){
	// if(posX<=.5 && posX>=-.5 && posY<=.5 && posY>=-.5){
		int index=0;
		float min = 1000;
		for(int i=0;i<16;i++){
			float dis = distance(posX,posY,arr[i].center_x,arr[i].center_y);
			if(dis<min){
				min = dis;
				index = i;
			}
		}

		glLoadIdentity();//load identity matrix
		
		glTranslatef(x, y, 0);
		glRotatef( cal_angle,0,0,1); 
		glScalef(scale, scale, scale);
		glTranslatef(arr[index].center_x, arr[index].center_y, 0);//move forward 4 units
		glRotatef( animation_angle,0,0,1);
		animation_angle+=5;
		if(animation_angle ==200){
			std::cout<<arr[index]._value<<" Pressed\n";
			animation_flag = 0;
			animation_angle = 0;
		}
		glTranslatef(-arr[index].center_x, -arr[index].center_y , 0);//move forward 4 units
	//move forward 4 units
		
		
		glBegin(GL_QUADS);

		glColor4f(1, 1, 1, .3);
		glVertex3f(arr[index]._v1._x, arr[index]._v1._y, arr[index]._v1._z);

		glColor4f(1, 1, 1, .3);
		glVertex3f(arr[index]._v2._x, arr[index]._v2._y, arr[index]._v2._z);

		glColor4f(1, 1, 1, .3);
		glVertex3f(arr[index]._v3._x, arr[index]._v3._y, arr[index]._v3._z);

		glColor4f(1, 1, 1, .3);
		glVertex3f(arr[index]._v4._x, arr[index]._v4._y, arr[index]._v4._z);

		glEnd();
	// }
	// return arr[index];
}

void first_right_click( std::vector<Button> arr){
	// int index=0;
	float min = 1000;
	for(int i=0;i<16;i++){
		float dis = distance(posX,posY,arr[i].center_x,arr[i].center_y);
		if(dis<min){
			min = dis;
			rightclickindex = i;
		}
	}

	
}

std::vector<Button> update_buttons(std::vector<Button> arr){
	float newx = posX; float newy = posY;
	float xdis = newx-arr[rightclickindex].center_x;
	float ydis = newy-arr[rightclickindex].center_y;
	arr[rightclickindex]._v1._x += xdis; 
	arr[rightclickindex]._v2._x += xdis;
	arr[rightclickindex]._v3._x += xdis;
	arr[rightclickindex]._v4._x += xdis;

	arr[rightclickindex]._v1._y += ydis; 
	arr[rightclickindex]._v2._y += ydis;
	arr[rightclickindex]._v3._y += ydis;
	arr[rightclickindex]._v4._y += ydis;
	arr[rightclickindex].center_x = newx;
	arr[rightclickindex].center_y = newy;

	return 	arr;
}

std::vector<Button> reset_cal(std::vector<Button> vec, Button arr[]){
	for (int i=0;i<16;i++){
		vec[i] = arr[i];
	}
	return vec;
}        

void handleKeys(GLFWwindow* window, int key, int code, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS){
		scale += 0.05;
	}
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS){	
		if (scale <= 0.1){}
		else{
			scale -= 0.05;
		}
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
		x -= 0.05;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		x += 0.05;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS){
		y += 0.05;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
		y -= 0.05;
	}
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
		cal_angle += 10;
	} 
	if (key == GLFW_KEY_M && action == GLFW_PRESS){
		reset = 1;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		glfwGetCursorPos(window, &xpos, &ypos);
		GetGLOBALPos();
		animation_flag = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		glfwGetCursorPos(window, &xpos, &ypos);
		GetGLOBALPos();
		if(right_click == 0){
			right_click=1;
		}
		else if(right_click == 2){
			right_click = 3;
		}
	}
}



int main(){
    const GLint WIDTH = 800, HEIGHT = 800;

	// Initializing GLFW
	if(!glfwInit()){
		std::cout<<"GLFW initialization failed."<<std::endl;
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "CALCULATOR", NULL, NULL);
	if(!mainWindow){
		std::cout<<"GLFW window creation failed."<<std::endl;
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK){
		std::cout<<"GLEW initialization failed."<<std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	float co_or[8] = {.99/2,.51/2,.49/2,.01/2,-.01/2,-.49/2,-.51/2,-.99/2};
	Vertex vertices[8][8];
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			vertices[i][j]= *(new Vertex(-co_or[j],co_or[i],0,.7,.7,.7,1.0));
		}
	}

	for (int i=0;i<8;i++){
		for (int j=6;j<8;j++){
			vertices[i][j]._r = .95; vertices[i][j]._g = .57; vertices[i][j]._b = .15; 
		}
	}

    Button zero = *(new Button(vertices[7][0],vertices[7][1],vertices[6][1],vertices[6][0],'0'));
	Button dot = *(new Button(vertices[7][2],vertices[7][3],vertices[6][3],vertices[6][2],'.'));
    Button equal = *(new Button(vertices[7][4],vertices[7][5],vertices[6][5],vertices[6][4],'='));
	Button plus =  *(new Button(vertices[7][6],vertices[7][7],vertices[6][7],vertices[6][6],'+'));

	Button one = *(	new Button(vertices[5][0],vertices[5][1],vertices[4][1],vertices[4][0],'1'));
	Button two = *(new Button(vertices[5][2],vertices[5][3],vertices[4][3],vertices[4][2],'2'));
    Button three = *(new Button(vertices[5][4],vertices[5][5],vertices[4][5],vertices[4][4],'3'));
	Button minus =  *(new Button(vertices[5][6],vertices[5][7],vertices[4][7],vertices[4][6],'-'));   

	Button four = *(new Button(vertices[3][0],vertices[3][1],vertices[2][1],vertices[2][0],'4'));
	Button five = *(new Button(vertices[3][2],vertices[3][3],vertices[2][3],vertices[2][2],'5'));
    Button six = *(new Button(vertices[3][4],vertices[3][5],vertices[2][5],vertices[2][4],'6'));
	Button multiply =  *(new Button(vertices[3][6],vertices[3][7],vertices[2][7],vertices[2][6],'*'));

	Button seven = *(new Button(vertices[1][0],vertices[1][1],vertices[0][1],vertices[0][0],'7'));
	Button eight = *(new Button(vertices[1][2],vertices[1][3],vertices[0][3],vertices[0][2],'8'));
    Button nine = *(new Button(vertices[1][4],vertices[1][5],vertices[0][5],vertices[0][4],'9'));
	Button divide =  *(new Button(vertices[1][6],vertices[1][7],vertices[0][7],vertices[0][6],'/'));
    
	Button buttons[16] = {zero, dot, equal, plus, one, two, three, minus, four, five, six, multiply, seven, eight, nine, divide};
	std::vector<Button> vbuttons(16);
	for(int i=0;i<16;i++){
		vbuttons[i] = buttons[i];
	}
	// for transperancy.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    // Loop until window is closed
	while(!glfwWindowShouldClose(mainWindow)){
	
		// Get and handle user input
		glfwPollEvents();
		glfwSetKeyCallback(mainWindow, handleKeys);
		glfwSetMouseButtonCallback(mainWindow , mouse_button_callback);

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clear colour buffer before next frame
		glClear(GL_COLOR_BUFFER_BIT);

		for(int i=0;i<16;i++){
			drawButton(vbuttons[i]);
		}
		if(animation_flag == 1){
			animation(vbuttons);
		}
		if(right_click == 1){
			first_right_click(vbuttons);
			right_click = 2;
		}
		if(right_click == 3){
			vbuttons  = update_buttons(vbuttons);
			right_click = 0;
		}
		if(reset ==1){
			vbuttons = reset_cal(vbuttons, buttons);
			reset = 0;
		}
		glfwSwapBuffers(mainWindow);
	}

    return 0;
}
