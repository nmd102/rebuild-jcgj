//
// Created by Ethan Lee on 7/21/24.
//

#include "map2.h"
#include "engine/gfx/modelutil.h"

//#define SHOW_COLLIDER

std::vector<Transform> map2BoxColliders{};

std::vector<Transform>& getMap2BoxColliders() {
    return map2BoxColliders;
}

void ground0(GameObject* self){
    self->transform.position = vec3(0, -24, 0);
    self->transform.rotation = vec3(270, 0, 0);
    self->transform.scale    = vec3(750);
    self->renderables.push_back(createQuad(getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_ground"), getTexture("empty_specmis")}));

    setSunProperties(normalize(glm::vec3(0, 1, 0)), glm::vec3(0.2f, 0.2f, 0.2f));
    setAmbient(0.002f, 0.00225f, 0.0035f);
    setClearColor(0.025f, 0.025f, 0.05f);
    setClippingPlanes(0.01f, 500.0f);
    setFogPlanes(10, 80);
}

void ground1(GameObject* self){
    self->transform.position = glm::vec3(0.000000, -50.000000, 0.000000);
    self->transform.rotation = glm::vec3(270.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(750.000000, 750.000000, 750.000000);
    self->renderables.push_back(createQuad(getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_ground"), getTexture("empty_specmis")}));
}

void walkboard0(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 20.250000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 76.000000, 0.000000);
    self->transform.scale    = glm::vec3(1.500000, 0.250000, 7.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/plank_cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_walkboard"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void walkboard1(GameObject* self){
    self->transform.position = glm::vec3(-29.000000, 24.500000, 0.000000);
    self->transform.rotation = glm::vec3(90.000000, 50.000000, 90.000000);
    self->transform.scale    = glm::vec3(2.000000, 0.500000, 8.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/plank_cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_walkboard"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building0_0(GameObject* self){
    self->transform.position = glm::vec3(-15.000000, 0.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building0"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building0_1(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 0.000000, -30.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 40.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building0"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building0_2(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 0.000000, 30.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 40.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building0"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building0_3(GameObject* self){
    self->transform.position = glm::vec3(45.000000, 0.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 50.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building0"), getTexture("empty_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building1_0(GameObject* self){
    self->transform.position = glm::vec3(15.000000, 0.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building1"), getTexture("m2_building1_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building1_1(GameObject* self){
    self->transform.position = glm::vec3(-45.000000, 10.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building1"), getTexture("m2_building1_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building1_2(GameObject* self){
    self->transform.position = glm::vec3(-45.000000, -30.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building1"), getTexture("m2_building1_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building1_3(GameObject* self){
    self->transform.position = glm::vec3(45.000000, 1.000000, 45.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building1"), getTexture("m2_building1_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void building1_4(GameObject* self){
    self->transform.position = glm::vec3(45.000000, -4.000000, -30.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(10.000000, 20.000000, 10.000000);
    map2BoxColliders.push_back(self->transform);
    self->renderables.push_back(loadObj("./models/cube.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m2_building1"), getTexture("m2_building1_specmis")})[0]);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void loadMap2(){
    /* Moved to ground GameObject so lighting doesn't initialize a frame early
    setSunProperties(normalize(glm::vec3(0, 1, 0)), glm::vec3(0.2f, 0.2f, 0.2f));
    setAmbient(0.002f, 0.00225f, 0.0035f);
    setClearColor(0.025f, 0.025f, 0.05f);
    setClippingPlanes(0.01f, 500.0f);
    setFogPlanes(10, 80);
     */

    createTexture("m2_walkboard",        "./textures/m2_walkboard.png", "./tex_bundle.jbd");
    createTexture("m2_building0",        "./textures/m2_building0.png", "./tex_bundle.jbd");
    createTexture("m2_building1",        "./textures/m2_building1.png", "./tex_bundle.jbd");
    createTexture("m2_building1_specmis","./textures/m2_building1_specmis.png", "./tex_bundle.jbd");
    createTexture("m2_ground",           "./textures/m2_ground.png", "./tex_bundle.jbd");

    putGameObject("ground",       GameObject(&ground0));
    putGameObject("ground_under", GameObject(&ground1));

    putGameObject("walkboard0",   GameObject(&walkboard0));
    putGameObject("walkboard1",   GameObject(&walkboard1));

    putGameObject("b0_0",         GameObject(&building0_0));
    putGameObject("b0_1",         GameObject(&building0_1));
    putGameObject("b0_2",         GameObject(&building0_2));
    putGameObject("b0_3",         GameObject(&building0_3));

    putGameObject("b1_0",         GameObject(&building1_0));
    putGameObject("b1_1",         GameObject(&building1_1));
    putGameObject("b1_2",         GameObject(&building1_2));
    putGameObject("b1_3",         GameObject(&building1_3));
    putGameObject("b1_4",         GameObject(&building1_4));
}