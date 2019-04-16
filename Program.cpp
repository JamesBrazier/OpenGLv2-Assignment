#include "MyExtentions/MyExtentions.h"
#include "Objects/Objects.h"

using namespace std;

namespace Project // This is just a namespace I'm using to sperate my code from the default namespace
{
	// Constants
	constexpr int fps = 60; // the animation and screen refresh rate
	constexpr int windowWidth = 1600, windowHeight = 900; // The window dimentions
	constexpr float angleStep = 0.05; // The 3D spherical movement constants
	constexpr int worldRadius = 100; // world size
	constexpr int zoomStep = 1, maxZoom = 200, minZoom = 1; // The zoom constants
	constexpr float sunX = 15, sunHeight = 100, sunStep = 0.001; // day/night cycle variables
	constexpr int cannonAngleFreedom = 15;

	// Program Globals
	GLUquadricObj* quadric; // the quadric used to draw all glu shapes
	Camera camera = Camera(0, 1, 0, CameraMode::THIRDPERSON);
	TextureManager textureManager = TextureManager();

	// Scene Globals
	static float sunAngle = 0.75; //The angle of the suns rotation around the world
	static bool dayNight = false; // Whether the day night cycle is on
	static float SSlanded = true;
	static float movementSpeed = 0.25;
	static char cameraState = 0;

	// scene objects
	static vector<GLobject*> objects = vector<GLobject*>();
	static vector<GLanimated*> animatedObjects = vector<GLanimated*>();
	static vector<GLtextured*> texturedObjects = vector<GLtextured*>();
	static vector<GLlight*> lightObjects = vector<GLlight*>();

	// accessors
	static SkyBox* skyBox;
	static Castle* castle;
	static SpaceShip* spaceShip;
	static Cannon* cannon;

	// Randomly places foliage around the map except in the go-no zone
	void genFoliage(int amount, float noGoCenterX, float noGoCenterZ, float noGoWidth, float noGoHeight)
	{
		float rectX = noGoCenterZ - (noGoWidth / 2), rectY = noGoCenterX - (noGoHeight / 2); // the top left corner of the nogo zone
		float x, z; // x and z location of the foliage on the floor
		static int amountHalf = amount / 2; // when we swap to bushes

		for (int i = 0; i < amount; i++) {
			do { // gen coords, regen while in the nogo zone
				x = (rand() % (2 * floorRadius) - floorRadius);
				z = (rand() % (2 * floorRadius) - floorRadius);
			} while (x > rectX && x < (rectX + noGoWidth) && z > rectY && z < (rectY + noGoHeight));

			if (i > amountHalf) { // swap to trees
				Bush* bush = new Bush(x, 0, z, rand() % 4 + 0.5);
				objects.push_back(bush);
				texturedObjects.push_back(bush);
			} else {
				Tree* tree = new Tree(x, 0, z, rand() % 5 + 6, rand() % 10 + 5);
				objects.push_back(tree);
				texturedObjects.push_back(tree);
			}
		}
	}

	// Generates all the world objects and assigns the accessors
	inline void generateObjects(void)
	{
		// floor, which is textured
		Floor* floor = new Floor();
		objects.push_back(floor);
		texturedObjects.push_back(floor);

		// skybox, which is textured
		skyBox = new SkyBox();
		objects.push_back(skyBox);
		texturedObjects.push_back(skyBox);

		//castle, which is a textured object
		castle = new Castle(0, floorHight, -30, 180, 60);
		objects.push_back(castle);
		texturedObjects.push_back(castle);

		// spaceship, which is animated and has lights
		spaceShip = new SpaceShip(0, 0, -35, -90);
		objects.push_back(spaceShip);
		animatedObjects.push_back(spaceShip);
		lightObjects.push_back(spaceShip);

		// robots, which are animated
		Guard1* guard1 = new Guard1(-4, 0, 4, 45);
		objects.push_back(guard1);
		animatedObjects.push_back(guard1);

		Guard2* guard2 = new Guard2(4, 0, 4, -45);
		objects.push_back(guard2);
		animatedObjects.push_back(guard2);

		Scout1* scout1 = new Scout1(14.3, 0, 15, -90);
		objects.push_back(scout1);
		animatedObjects.push_back(scout1);

		Scout2* scout2 = new Scout2(0, 0, 40, 90);
		objects.push_back(scout2);
		animatedObjects.push_back(scout2);

		// foliaged, which are textured
		genFoliage(200, -15, 0, 80, 120);

		// cannon, which is textured and animated
		cannon = new Cannon(7, 0, 15, -100, 10);
		objects.push_back(cannon);
		animatedObjects.push_back(cannon);
		texturedObjects.push_back(cannon);
	}

	//The animation timer
	void animationLoop(int value)
	{
		// update animation variables
		for (GLanimated* animated : animatedObjects) {
			animated->updateAnimation();
		}

		camera.update();

		// a very basic day/night cycle
		if (dayNight) {
			sunAngle += sunStep;

			if (sunAngle > 6.28) { // if the sun has risen
				glEnable(GL_LIGHT0);
				skyBox->setDay(true);
				sunAngle = 0;
			} else if (sunAngle > 3.14) { // if the sun has set
				glDisable(GL_LIGHT0);
				skyBox->setDay(false);
			} else if (sunAngle > 2.8) { // turn off shadows early and start late because they get obnoxious
				castle->disableShadow();
			} else if (sunAngle > 0.3) {
				castle->enableShadow();
			}
		}

		glutTimerFunc(value, animationLoop, value); //organize next cycle
		glutPostRedisplay(); // Redisplay the screen and as this happens often we don't redisplay elsewhere
	}

	// The special keyboard keypress callback function
	void specialKeyPress(int key, int x, int y)
	{
		static bool running = false;
		// since the trigonometric functions in cpp are based on radians, we only cause a small change to these values

		if (key == GLUT_KEY_LEFT) {
			camera.moveLookAt(0, angleStep);
		} else if (key == GLUT_KEY_RIGHT) {
			camera.moveLookAt(0, -angleStep);
		} else if (key == GLUT_KEY_DOWN) {
			camera.moveLookAt(-angleStep, 0);
		} else if (key == GLUT_KEY_UP) {
			camera.moveLookAt(angleStep, 0);
		} else if (key == GLUT_KEY_ALT_R) {
			camera.changeZoom(zoomStep);
		} else if (key == GLUT_KEY_CTRL_R) {
			camera.changeZoom(-zoomStep);
		}

		if (key == GLUT_KEY_SHIFT_L) { // Toggle run
			if (running) {
				movementSpeed = 0.25;
			} else {
				movementSpeed = 1;
			}
			running = !running;
		}
	}

	// The normal keyboard key press function
	void keyPress(unsigned char key, int x, int y)
	{
		if (cameraState == 3) {
			if (key == 's') {
				cannon->setRotationAroundX(fmaxf(-cannonAngleFreedom, cannon->getRotationAroundX() - 1));
			} else if (key == 'w') {
				cannon->setRotationAroundX(fminf(cannonAngleFreedom, cannon->getRotationAroundX() + 1));
			}
		}
		// we want to move the look position in the four directions from the orientation we are looking
		if (key == 'w') { // these are all set up for correct movement in 1st person, doesn't quite equate to 3rd
			camera.movePosition(0, 0, movementSpeed);
		} else if (key == 's') {
			camera.movePosition(0, 0, -movementSpeed);
		} else if (key == 'd') {
			camera.movePosition(-movementSpeed, 0, 0);
		} else if (key == 'a') {
			camera.movePosition(movementSpeed, 0, 0);
		}

		if (key == 'f') { // fire the cannon
			cannon->fire();
		} else if (key == 'l') { // fly or land the UFO
			if (SSlanded) {
				spaceShip->liftOff();
				SSlanded = false;
			} else {
				spaceShip->land();
				SSlanded = true;
			}
		} else if (key == 'p') { // pause/play the day/night cycle
			dayNight = !dayNight;
		} else if (key == 'o') { // hold to speed up the day/night cycle, also activates it
			sunAngle += 0.01;
			if (!dayNight) {
				dayNight = true;
			}
		} else if (key == 'r') { // swap view from 3rd to 1st or back
			cameraState = (cameraState + 1) % 4;
			switch (cameraState) {
				case 0:
					camera.setMode(CameraMode::THIRDPERSON);
					break;
				case 1:
					camera.setMode(CameraMode::FIRSTPERSON);
					break;
				case 2:
					camera.setBindedObject(spaceShip, 0, 5, 0);
					camera.setLookAt(0, 0, 0);
					camera.setMode(CameraMode::OBJECTBINDFIXEDPOINT);
					break;
				case 3:
					camera.setBindedObject(cannon, 0, 5, 0);
					camera.setMode(CameraMode::OBJECTBIND);
					break;
			}
		}
	}

	// The display callback function
	void display(void)
	{
		float lightPos[4] = { sunX, sunHeight * sin(sunAngle), sunHeight * cos(sunAngle), 1 };
		float shadowMat[16] = { // the shadow transformation matrix for the objects from the sun
			lightPos[1], 0, 0, 0,
			-lightPos[0], 0, -lightPos[2], -1,
			0, 0, lightPos[1], 0,
			0, 0, 0, lightPos[1]
		};

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		camera.loadMatrix();

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // place the sun

		for (GLobject* object : objects) {
			object->display(shadowMat);
		}

		glutSwapBuffers(); // swap and clear the current display buffer
	}

	// Loads the textures and sets up openGL for texturing
	void loadContent(void)
	{
		for (GLtextured* textured : texturedObjects) {
			textured->loadTextures(textureManager);
		}

		// set up texture environment
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); // this doesn't seem to work for me
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glAlphaFunc(GL_GREATER, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Performs all the opengl core initialization
	void initialize(void)
	{
		glClearColor(0, 0, 0, 0);

		// Enable GL options
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // glColor[3|4]f affect the diffuse and ambient colours of an object
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);

		// Initalize objects
		for (GLlight* light : lightObjects) {
			light->initialize();
		}

		// Create and set GLU quadric settings
		quadric = gluNewQuadric(); 
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricNormals(quadric, GLU_SMOOTH);
		gluQuadricTexture(quadric, GL_TRUE);

		// Setup lighting
		glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, black);
		glMaterialf(GL_FRONT, GL_SHININESS, 50);

		// Set up look matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 1.7778, 0.01, 1000); // Fov at 60, aspect ratio at 16:9
	}

#ifdef LINUX
	void freeObjects(int, void*)
#else
	int freeObjects(void)
#endif
	{
		for (GLobject* object : objects) {
			delete object;
		}
#ifndef LINUX
		return 0;
#endif
	}
}

// Performs all the glut window initialization and starts the glut main loop
int main(int argc, char** argv)
{
	try {
		int refreshRate = 1000 / Project::fps;

		// Initialize program
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(Project::windowWidth, Project::windowHeight);
		glutInitWindowPosition(200, 5);
		glutCreateWindow("Alien Invasion! jbr185");
		Project::generateObjects();
		Project::initialize();
		Project::loadContent();

		// Register callbacks
#ifdef LINUX
		on_exit(Project::freeObjects, 0);
#else
		onexit(Project::freeObjects);
#endif
		glutDisplayFunc(Project::display);
		glutSpecialFunc(Project::specialKeyPress);
		glutKeyboardFunc(Project::keyPress);
		glutTimerFunc(refreshRate, Project::animationLoop, refreshRate);

		// Start
		glutMainLoop();
		return 0;

	} catch (exception err) {
		cerr << err.what();
	}
}