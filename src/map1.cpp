//
// Created by Ethan Lee on 7/21/24.
//

#include "map1.h"
#include "engine/gfx/modelutil.h"

//#define SHOW_COLLIDER

std::vector<Transform> map1BoxColliders{};

std::vector<Transform>& getMap1BoxColliders() {
    return map1BoxColliders;
}

void g1(GameObject* self){
    self->transform.position = vec3(0, -5, 0);
    self->transform.scale = vec3(1.5);
    std::vector<Renderable> oogaboogashitfuck2 = loadObj("./models/m1_geo_v2.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_geo"), getTexture("empty_specmis")});
    for (const Renderable& r : oogaboogashitfuck2) { self->renderables.push_back(r);}
}

void f1(GameObject* self){
    self->transform.position = vec3(0, -5, 0);
    self->transform.scale = vec3(1.5);
    std::vector<Renderable> oogaboogashitfuck1 = loadObj("./models/m1_floor.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_floor"), getTexture("empty_specmis")});
    //std::vector<Renderable> oogaboogashitfuck2 = loadObj("./models/m1_geo_v2.obj",   getProgram("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_geo"), getTexture("m1_geo_specmis")});
    for (const Renderable& r : oogaboogashitfuck1) { self->renderables.push_back(r);}
    //for (const Renderable& r : oogaboogashitfuck2) { self->renderables.push_back(r);}
}

void f2(GameObject* self){
    self->transform.position = vec3(-42, -7.5, 0);
    self->transform.scale = vec3(1);
    std::vector<Renderable> oogaboogashitfuck1 = loadObj("./models/m1_floor.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_floor"), getTexture("m1_floor_specmis")});
    for (const Renderable& r : oogaboogashitfuck1) { self->renderables.push_back(r);}
}

void f3(GameObject* self){
    self->transform.position = vec3(42, -7.5, 0);
    self->transform.scale = vec3(1);
    std::vector<Renderable> oogaboogashitfuck1 = loadObj("./models/m1_floor.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_floor"), getTexture("m1_floor_specmis")});
    for (const Renderable& r : oogaboogashitfuck1) { self->renderables.push_back(r);}
}

void f4(GameObject* self){
    self->transform.position = vec3(0, 0, 42);
    self->transform.scale = vec3(1);
    std::vector<Renderable> oogaboogashitfuck1 = loadObj("./models/m1_floor.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_floor"), getTexture("m1_floor_specmis")});
    for (const Renderable& r : oogaboogashitfuck1) { self->renderables.push_back(r);}
}

void f5(GameObject* self){
    self->transform.position = vec3(0, 0, -42);
    self->transform.scale = vec3(1);
    std::vector<Renderable> oogaboogashitfuck1 = loadObj("./models/m1_floor.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_floor"), getTexture("m1_floor_specmis")});
    for (const Renderable& r : oogaboogashitfuck1) { self->renderables.push_back(r);}
}


void lava(GameObject* self){
    self->transform.position = vec3(0, -24, 0);
    self->transform.rotation = vec3(270, 0, 0);
    self->transform.scale    = vec3(750);
    self->renderables.push_back(createQuad(getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_lava"), getTexture("unlit_specmis")}));

    setSunProperties(glm::vec3(0, -1, 0), glm::vec3(0.5f, 0.45f, 0.2f));
    setAmbient(0.0025f, 0.001f, 0.0005f);
    setClearColor(0.025f, 0.01f, 0.01f);
    setClippingPlanes(0.01f, 1000.0f);
    setFogPlanes(-20, 500);
}

void volcanoProp1(GameObject* self) {
    self->transform.position = glm::vec3(-400.000000, 0.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 90.000000, 0.000000);
    self->transform.scale    = glm::vec3(75.000000, 50.000000, 75.000000);
    self->renderables.push_back(loadObj("./models/volcano_prop.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_volcaner"), getTexture("m1_volcaner_specmis")})[0]);
}

void volcanoProp2(GameObject* self) {
    self->transform.position = glm::vec3(-200.000000, 0.000000, 500.000000);
    self->transform.rotation = glm::vec3(0.000000, -45.000000, 0.000000);
    self->transform.scale    = glm::vec3(50.000000, 75.000000, 50.000000);
    self->renderables.push_back(loadObj("./models/volcano_prop.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_volcaner"), getTexture("m1_volcaner_specmis")})[0]);
}

void volcanoProp3(GameObject* self) {
    self->transform.position = glm::vec3(400.000000, 0.000000, 300.000000);
    self->transform.rotation = glm::vec3(0.000000, -89.000000, 0.000000);
    self->transform.scale    = glm::vec3(60.000000, 60.000000, 60.000000);
    self->renderables.push_back(loadObj("./models/volcano_prop.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_volcaner"), getTexture("m1_volcaner_specmis")})[0]);
}

void volcanoProp4(GameObject* self) {
    self->transform.position = glm::vec3(90.000000, 0.000000, -300.000000);
    self->transform.rotation = glm::vec3(0.000000, 180.000000, 0.000000);
    self->transform.scale    = glm::vec3(60.000000, 60.000000, 60.000000);
    self->renderables.push_back(loadObj("./models/volcano_prop.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("m1_volcaner"), getTexture("m1_volcaner_specmis")})[0]);
}
// Auto generated physbox gameobjects
void floor1_phys_box(GameObject* self){
    self->transform.position = glm::vec3(0.000000, -5.000000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(17.000000, 0.700000, 17.000000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void floor2_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-42.000000, -7.500000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(11.33333, 0.700000, 11.33333);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void floor3_phys_box(GameObject* self){
    self->transform.position = glm::vec3(42.000000, -7.500000, 0.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(11.33333, 0.700000, 11.33333);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void floor4_phys_box(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 0.000000, -42.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(11.33333, 0.700000, 11.33333);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void floor5_phys_box(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 0.000000, 42.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(11.33333, 0.700000, 11.33333);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void small_block_phys_box(GameObject* self){
    self->transform.position = glm::vec3(1.750000, -3.000000, 11.500000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(1.500000, 1.200000, 1.500000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void med1_block_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-2.500000, -1.700000, 8.600000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(1.400000, 2.300000, 1.500000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void med2_block_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-3.000000, -1.000000, 13.150000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(1.500000, 5.000000, 1.500000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void tall_block_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-8.100000, 0.000000, 9.400000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(1.450000, 7.000000, 1.450000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void small_ramp_phys_box(GameObject* self){
    self->transform.position = glm::vec3(4.350000, -4.000000, 11.500000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, -34.000000);
    self->transform.scale    = glm::vec3(2.100000, 1.200000, 1.500000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void elevated_phys_box(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 0.400000, -14.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(16.299999, 5.000000, 2.600000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void overhang_phys_box(GameObject* self){
    self->transform.position = glm::vec3(0.000000, 2.600000, -10.500000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(16.299999, 2.800000, 0.900000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void big_ramp_phys_box(GameObject* self){
    self->transform.position = glm::vec3(12.400000, -3.600000, 0.500000);
    self->transform.rotation = glm::vec3(24.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(4.000000, 4.000000, 13.000000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void chunk_base_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-8.000000, -3.150000, -9.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(8.200000, 3.150000, 2.430000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}
void chunk_tall_phys_box(GameObject* self){
    self->transform.position = glm::vec3(-12.200000, 1.300000, -10.000000);
    self->transform.rotation = glm::vec3(0.000000, 0.000000, 0.000000);
    self->transform.scale    = glm::vec3(3.950000, 1.300000, 3.600000);
    map1BoxColliders.push_back(self->transform);
#ifdef SHOW_COLLIDER
    self->renderables.push_back(loadObj("./models/cube.obj", getProgram("physBox"), {getUBOID()}, true)[0]);
#endif
}

void loadMap1(){
    /* Moved to lava GameObject to prevent lighting early initialization
    setSunProperties(glm::vec3(0, -1, 0), glm::vec3(0.5f, 0.45f, 0.2f));
    setAmbient(0.0025f, 0.001f, 0.0005f);
    setClearColor(0.025f, 0.01f, 0.01f);
    setClippingPlanes(0.01f, 1000.0f);
    setFogPlanes(-20, 500);
     */

    createTexture("m1_floor",                   "./textures/m1_floor.png", "./tex_bundle.jbd");
    //createTexture("m1_floor_specmis",           "./textures/m1_floor_specmis.png");
    createTexture("m1_geo",                     "./textures/m1_geo.png", "./tex_bundle.jbd");
    createTexture("m1_lava",                    "./textures/better_moldy_fanta.png", "./tex_bundle.jbd");
    createTexture("m1_volcaner",                "./textures/volcaner_tex.png", "./tex_bundle.jbd");
    createTexture("m1_volcaner_specmis",        "./textures/volcaner_specmis.png", "./tex_bundle.jbd");

    putGameObject("geo1",               GameObject(&g1));
    putGameObject("floor1",             GameObject(&f1));
    //putGameObject("floor2",             GameObject(&f2));
    //putGameObject("floor3",             GameObject(&f3));
    //putGameObject("floor4",             GameObject(&f4));
    //putGameObject("floor5",             GameObject(&f5));
    putGameObject("lava",               GameObject(&lava));
    putGameObject("volcano_prop1",      GameObject(&volcanoProp1));
    putGameObject("volcano_prop2",      GameObject(&volcanoProp2));
    putGameObject("volcano_prop3",      GameObject(&volcanoProp3));
    putGameObject("volcano_prop4",      GameObject(&volcanoProp4));

    putGameObject("phys_floor1",        GameObject(&floor1_phys_box));
    //putGameObject("phys_floor2",        GameObject(&floor2_phys_box));
    //putGameObject("phys_floor3",        GameObject(&floor3_phys_box));
    //putGameObject("phys_floor4",        GameObject(&floor4_phys_box));
    //putGameObject("phys_floor5",        GameObject(&floor5_phys_box));

    putGameObject("phys_smallblk",      GameObject(&small_block_phys_box));
    putGameObject("phys_smallrmp",      GameObject(&small_ramp_phys_box));
    putGameObject("phys_med1blk",       GameObject(&med1_block_phys_box));
    putGameObject("phys_med2blk",       GameObject(&med2_block_phys_box));
    putGameObject("phys_tallblk",       GameObject(&tall_block_phys_box));

    putGameObject("phys_elevated",      GameObject(&elevated_phys_box));
    putGameObject("phys_overhang",      GameObject(&overhang_phys_box));
    putGameObject("phys_bigramp",       GameObject(&big_ramp_phys_box));
    putGameObject("phys_chunk_base",    GameObject(&chunk_base_phys_box));
    putGameObject("phys_chunk_tall",    GameObject(&chunk_tall_phys_box));

}