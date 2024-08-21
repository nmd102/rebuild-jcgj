//
// Created by Ember Lee on 4/14/24.
//

#include "test.h"
#include "engine/engine.h"
#include "engine/sound/audioutil.h"
#include "engine/gfx/modelutil.h"
#include "engine/debug/debugutil.h"

bool mouseLocked = false;
bool pressed = false;

const float speed = 3.0f; // 3 units / second
const float mouseSpeed = 10.0f;

struct CBO {
    alignas(16) glm::vec3 color1;
    alignas(16) glm::vec3 color2;
    alignas(4)  float blend;
};

unsigned int cbo1;
unsigned int cbo2;
CBO colorData1{{1, 0, 0}, {0, 0, 1}, 0};
CBO colorData2{{1, 0, 0}, {0, 0, 1}, 1};

void gameCamera(double dt) {
    if (mouseLocked) {
        Transform* camera = cameraAccess();

        glm::vec2 cursor = getRawCursorPos();
        setRawCursorPos({static_cast<float>(getCurrentWidth()) / 2.0f, static_cast<float>(getCurrentHeight()) / 2.0f});
        camera->rotation.x +=
                mouseSpeed * static_cast<float>(dt) * (static_cast<float>(getCurrentWidth()) / 2.0f - cursor.x);
        camera->rotation.y +=
                mouseSpeed * static_cast<float>(dt) * (static_cast<float>(getCurrentHeight()) / 2.0f - cursor.y);
        camera->rotation.y = clamp(camera->rotation.y, -70.0f, 70.0f);


        // Right vector
        glm::vec3 right = glm::vec3(
                sin(glm::radians(camera->rotation.x - 90)),
                0,
                cos(glm::radians(camera->rotation.x - 90))
        );


        // Move forward
        if (isKeyDown(GLFW_KEY_W)) {
            camera->position += camera->direction() * glm::vec3(static_cast<float>(dt) * speed);
        }
        // Move backward
        if (isKeyDown(GLFW_KEY_S)) {
            camera->position -= camera->direction() * glm::vec3(static_cast<float>(dt) * speed);
        }
        // Strafe right
        if (isKeyDown(GLFW_KEY_D)) {
            camera->position += right * glm::vec3(static_cast<float>(dt) * speed);
        }
        // Strafe left
        if (isKeyDown(GLFW_KEY_A)) {
            camera->position -= right * glm::vec3(static_cast<float>(dt) * speed);
        }

        if (isKeyDown(GLFW_KEY_SPACE)) {
            camera->position += glm::vec3(0, static_cast<float>(dt) * speed, 0);
        }
        if (isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
            camera->position -= glm::vec3(0, static_cast<float>(dt) * speed, 0);
        }
    }
}

void lockUnlock(int key, bool wasKeyPressed, double dt) {
    if (key == GLFW_KEY_ESCAPE) {
        if (wasKeyPressed && !pressed) {
            mouseLocked = !mouseLocked;
            pressed = true;
        } else if (!wasKeyPressed) {
            pressed = false;
        }
        // If locked, set mouse to invisible
        setMouseVisible(!mouseLocked);
    }
}

void move(double deltaTime, GameObject* self) {
    if (self->transform.position.y > 2) {
        self->transform.position.y = 0;
    }
    self->transform.position += vec3(0, 1*deltaTime, 0);
}

void enemyAI(double deltaTime, GameObject* self) {
    if (self->transform.rotation.y > 360) {
        self->transform.rotation.y -= 360;
    }
    self->transform.rotation += vec3(0, 40*deltaTime, 0);
}

void initChild(GameObject* selfObject) {
    selfObject->transform = Transform(glm::vec3(0));
    std::vector<Renderable> modelRenderables = loadObj("./models/bunny.obj", getProgram("gameShader"), {getUBOID(), getLBOID(), cbo1, getTexture("crosshatchLines"), getTexture("dots")});
    selfObject->renderables.insert(selfObject->renderables.end(), modelRenderables.begin(), modelRenderables.end());
    selfObject->onUpdate.push_back(&spin);
}

void initOpposingChild(GameObject* selfObject) {
    selfObject->transform = Transform(glm::vec3(0, 0, -2));
    std::vector<Renderable> modelRenderables = loadObj("./models/bunny.obj", getProgram("gameShader"), {getUBOID(), getLBOID(), cbo2, getTexture("crosshatchLines"), getTexture("dots")});
    selfObject->renderables.insert(selfObject->renderables.end(), modelRenderables.begin(), modelRenderables.end());
    selfObject->onUpdate.push_back(&spin);
}

double changeOverTime = 0;
bool isSwapping = false;
bool inverted = false;

void contrastSwap(double dt) {
    if (isSwapping) {
        if (inverted) changeOverTime -= dt;
        else changeOverTime += dt;
        colorData1.blend = changeOverTime;
        colorData2.blend = 1 - changeOverTime;
        updateUniformBuffer(cbo1, &colorData1, sizeof(CBO), true);
        updateUniformBuffer(cbo2, &colorData2, sizeof(CBO), true);
    }

    if (changeOverTime >= 1 || changeOverTime <= 0) {
        isSwapping = false;
        inverted = !inverted;
        if (inverted) changeOverTime = 1;
        else changeOverTime = 0;
    }
}

void clickDetect(int button, bool down, double dt) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && down) {
        isSwapping = true;
    }
}

void setupTest() {
    // Engine features
    //     sun-ish direction from skybox, slightly warm white
    setSunProperties(glm::vec3(-1, 1, -1), glm::vec3(1, 1, 0.85));

    registerOnUpdate(&cameraFly);
    registerOnKey(&lockUnlock);

    registerFunctionToDebug("spin", reinterpret_cast<void*>(&spin));

    setMouseVisible(false); // Mouse starts locked
    mouseLocked = true;


    // English project
    registerOnUpdate(&contrastSwap);
    registerOnMouse(&clickDetect);

    cbo1 = createUniformBuffer(sizeof(CBO));
    cbo2 = createUniformBuffer(sizeof(CBO));

    updateUniformBuffer(cbo1, &colorData1, sizeof(CBO), true);
    updateUniformBuffer(cbo2, &colorData2, sizeof(CBO), true);

    JEShaderProgramSettings a{};
    a.testDepth = true;
    a.transparencySupported = false;
    a.doubleSided = false;
    a.shaderInputs =
               JEShaderInputUniformBit
            | (JEShaderInputUniformBit << 1)
            | (JEShaderInputUniformBit << 2)
            | (JEShaderInputTextureBit << 3)
            | (JEShaderInputTextureBit << 4);
    a.shaderInputCount = 5;

    registerProgram("gameShader", "./shaders/vertex3d.glsl", "./shaders/game_shader.glsl", a);
    createTexture("crosshatchLines", "./textures/lines.jpg");
    createTexture("dots", "./textures/dots.png");

    putGameObject("child1", GameObject(&initChild));
    putGameObject("child2", GameObject(&initOpposingChild));
}