#include "include/Engine.h"

#include "include/Camera.h"
#include "include/Shader.h"
#include "include/Model.h"


class MyLayer : public Layer
{
public:
	MyLayer() : Layer("MyLayer") {}

	void onUpdate() override
	{
		std::cout << this->getName() << " Updated" << std::endl;
	}

	void onEvent(Event& event) override
	{
		std::cout << "EVENT " << event.toString() << " on " << this->getName() << std::endl;
	}
};


;

bool shouldWindowClose = false;
glm::vec3 move = glm::vec3(0.0f, 0.0f, 0.0f);

class RenderLayer : public Layer
{
public:
	RenderLayer() : Layer("Renderlayer") {}

	void onAttach() override
	{
		std::cout << "ON ATTACHED CALLES" << std::endl;
		const unsigned int height = Engine::get().getWindow().getHeight();
		const unsigned int width = Engine::get().getWindow().getWidth();
		glViewport(0, 0, width, height );
		camera = new Camera(width, height, 0.1f, 70.0f, 100.0, glm::vec3(10.0f, 10.0f, 18.0f));

		models.push_back(new Model("res/test/crow/scene.gltf"));
		models.push_back(new Model("res/test/sword/scene.gltf"));
	}

	void onDetach() override
	{
		for (Model* model : models)
		{
			delete model;
		}

		delete camera;
	}

	void onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<KeyPressedEvent>(std::bind(&RenderLayer::moveCamera, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMovedEvent>(std::bind(&RenderLayer::lookCamera, this, std::placeholders::_1));
	}

	void onUpdate() override
	{	

		// TEST SHADER
		Shader myshader("res/shader/def.vert", "res/shader/def.frag");

		glEnable(GL_DEPTH_TEST);
		

		glClearColor(0.15f, 0.15f, 0.10f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->move(move);
		camera->updateMatrix();
		camera->Matrix(myshader, "camMatrix");
		for (Model* model : models)
		{
			model->Draw(myshader, *camera);
		}
	}

	

private:
	std::vector<Model*> models;
	Camera* camera;

	bool moveCamera(KeyPressedEvent& e)
	{
		float speed = 0.5;

		glm::vec3 move;
		if (Input::isKeyPressed(GLFW_KEY_W))
			move = (speed * (camera->orientation));
		if (Input::isKeyPressed(GLFW_KEY_S))
			move = (speed * -(camera->orientation));
		if (Input::isKeyPressed(GLFW_KEY_A))
			move = (speed * -glm::normalize(glm::cross(camera->orientation, camera->up)));
		if (Input::isKeyPressed(GLFW_KEY_D))
			move = (speed * glm::normalize(glm::cross(camera->orientation, camera->up)));
		if (Input::isKeyPressed(GLFW_KEY_SPACE))
			move = (speed * camera->up);
		if (Input::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
			move = (speed * -camera->up);
			
		camera->move(move);

		return true;
	}

	bool lookCamera(MouseMovedEvent& e)
	{
		
		if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			glfwSetInputMode(Engine::get().getWindow().getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return true;
		}
		glfwSetInputMode(Engine::get().getWindow().getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		float mouseX = e.getX();
		float mouseY = e.getY();

		int height = camera->heightpx;
		int width = camera->widthpx;

		float sensitivity = 10;

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(camera->orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera->orientation, camera->up)));

		if (abs(glm::angle(newOrientation, camera->up) - glm::radians(90.0f) <= glm::radians(85.0f)))
		{
			camera->orientation = newOrientation;
		}

		camera->orientation = glm::rotate(camera->orientation, glm::radians(-rotY), camera->up);

		glfwSetCursorPos(Engine::get().getWindow().getGLFWWindow(), (width / 2), (height / 2));
	}

};

class Ceres : public Engine
{
public:
	Ceres()
	{
		//pushLayer(new MyLayer());
		pushLayer(new RenderLayer());
	}
	~Ceres()
	{

	}
};


int main()
{
	// Main Engine Entry point
	Ceres* ceres = new Ceres();

	ceres->run();

	delete ceres;

	


	
	//WindowResizedEvent e(122, 33);
	//std::cout << e.toString() << std::endl;
	//std::cout << "Hello OpenGL" << std::endl;

	//// Initiate GLFW
	//glfwInit();

	////Tell glfw what version of OpenGL is used (3.3 in this case)
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//// Tell glfw what profile is used (core - only modern version)
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//// Create a new window (x, y, title, fullscreen, ?)
	//GLFWwindow* window = glfwCreateWindow(width, height, "TEST OPENGL", NULL, NULL);
	//if (window == NULL)
	//{
	//	std::cout << "Failed to create GLFW window" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}
	//// Use window
	//glfwMakeContextCurrent(window);

	//// Load OpenGL
	//gladLoadGL();

	//// Set viewport boundries
	//glViewport(0, 0, width, height);

	////// TESTING
	//
	//Model model("res/test/crow/scene.gltf");
	//
	//Camera camera(width, height, 0.1f, 100.0f ,45.0 , glm::vec3(0.0f, 10.0f, 18.0f));
	//// TEST SHADER
	//Shader myshader("res/shader/def.vert", "res/shader/def.frag");
	////testTex.texUnit(myshader, "diffuse0", 0);
	//// END TESTING

	//glEnable(GL_DEPTH_TEST);
	//while (!glfwWindowShouldClose(window))
	//{
	//	glClearColor(0.15f, 0.15f, 0.10f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	camera.updateMatrix();

	//	//myshader.activate();
	//	// Bind the VAO so OpenGL knows to use it
	//	//testTex.textureBind();
	//	//floor.draw(myshader, camera);
	//	model.Draw(myshader, camera);
	//	// Draw primitives, number of indices, datatype of indices, index of indices
	//	//glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}



	return 0;
}

