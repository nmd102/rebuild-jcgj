//
// Created by Ethan Lee on 7/24/24.
//

#include "enemies.h"
#include "game.h"
#include "engine/gfx/renderable.h"
#include "engine/gfx/modelutil.h"
#include "engine/engine.h"
#include "gamephysicslib.h"
#include <random>
#include "engine/sound/audioutil.h"

int enemyMax = 0;

// By the time the bullet count loops back around, the heat death of the universe will have occurred.
// I do not think we will ever have to deal with this overflowing,
// In the off chance that it does, the maximum value of an unsigned long is high enough that by the time
// it even could loop back around bullet_0 would be free again.
// In the off chance that it ISN'T free somehow, the size of a GameObject and associated renderable in memory
// is large enough that you would need 2.2136092888×10²¹ bytes to store all of them.

// Needless to say, I think this will work fine, although a naive approach.
// TODO: better option?
unsigned long bulletCount = 0;

Renderable enemy1Renderable;
Renderable enemy2Renderable;
Renderable enemy3Renderable;
Renderable enemy_kill_me_please_renderable;
Renderable bulletRenderable;

std::vector<Transform> enemyWorldBoxColliders;
std::vector<Sound> currentGunshotSounds;

Transform temp_bullet_vals{};
unsigned long temp_bullet_flags = 0;

// Eject enemies from boxes they spawn inside.
void ejectFromWorld(Transform* t) {
    for (auto const& box : enemyWorldBoxColliders) {
        while (testPoint(t->position, box)) {
            t->position += vec3(0, 0.001, 0);
        }
    }
}

void bullet_phys_step(double deltaTime, GameObject* self) {
    self->transform.pos_vel *= vec3(0.999);
    self->transform.position += self->transform.pos_vel * vec3(deltaTime);
    if (pointCollidesWithAnyBoxes(self->transform.position, enemyWorldBoxColliders)) {
        self->transform.pos_vel = vec3(0); // Essentially mark self for deletion (see runtimeCleanup)
        return;
    }
    if (testSpheres(self->transform.position, self->transform.scale.x*3, cameraAccess()->position, 1.5)) {
        self->transform.pos_vel = vec3(0); // Essentially mark self for deletion (see runtimeCleanup)
        (*getHealthPtr()) -= self->flags;
        if (*getHealthPtr() < 0) *getHealthPtr() = 0;
    }
}

void bulletGameObject(GameObject* self) {
    self->transform = temp_bullet_vals;
    self->renderables.push_back(bulletRenderable);
    self->onUpdate.push_back(&bullet_phys_step);
    self->flags = temp_bullet_flags;
    bulletCount++;
}

void enemyMovementAI(double deltaTime, GameObject* self) {
    if ((self->flags & 0x1000000000000000) == 0) {
        Transform *cameraPtr = cameraAccess();
        // Look at player
        double xdif = self->transform.position.x - cameraPtr->position.x;
        double zdif = self->transform.position.z - cameraPtr->position.z;
        self->transform.rotation.y = glm::degrees(atan(xdif / zdif)) + (zdif > 0 ? 90 : 270);

        double horizontal_dist = -sqrt(xdif * xdif + zdif * zdif);
        double ydif = self->transform.position.y - cameraPtr->position.y;
        float rot = glm::degrees(atan(ydif / (horizontal_dist)));
        self->transform.rotation.z = glm::max(glm::min(rot, 45.0f), -45.0f);

        // Physics ease TODO: More dumbness
        self->transform.pos_vel *= (vec3(1) - self->transform.scale) * vec3(1.7);

        // Horizontal positioning
        self->transform.pos_vel +=
                (normalize(vec3(xdif, 0, zdif)) * vec3(8)) / vec3(horizontal_dist > -10 ? 0.25 : -0.25) *
                vec3(deltaTime);

        // Vertical positioning
        if (rot != self->transform.rotation.z && horizontal_dist > -8) {
            if (self->transform.position.y < cameraPtr->position.y - 1) {
                self->transform.pos_vel.y += deltaTime * 100;
            } else if (self->transform.position.y > cameraPtr->position.y + 1) {
                self->transform.pos_vel.y -= deltaTime * 100;
            }
        }

        std::vector<Transform> enemyColliders(enemyMax);
        int i = 0;
        for (auto const &g: *getGameObjects()) {
            if (g.first.starts_with("enemy") &&
                (static_cast<vec3>(g.second.transform.position) != self->transform.position)) {
                enemyColliders[i] = g.second.transform;
                i++;
            }
        }

        //self->transform.position += self->transform.direction() * vec3(deltaTime);
        if (pointCollidesWithAnyBoxes   (self->transform.position, enemyWorldBoxColliders) ||
            sphereCollidesWithAnySpheres(self->transform, enemyColliders)) // This is faster than boxes because of rotation taking so damn long on the CPU
            self->transform.pos_vel *= vec3(-1);
        self->transform.position += self->transform.pos_vel * vec3(deltaTime);
    } else {
        // Reset timer
        self->flags = static_cast<uint64_t>(rand()%200) << 32;


        // Set up bullet transform
        temp_bullet_vals = Transform{};
        temp_bullet_vals.position = self->transform.position;
        temp_bullet_vals.pos_vel = normalize(cameraAccess()->position-self->transform.position) * vec3(deltaTime) * vec3(3000/self->transform.scale.x);
        temp_bullet_vals.rotation = self->transform.rotation;
        if (self->transform.scale.x > 0.5) {
            // Play sound
            currentGunshotSounds.emplace_back(self->transform.position, vec3(0), "./sounds/gunfire0.ogg",  false, 3, 0.1, 2, 2);
            currentGunshotSounds[currentGunshotSounds.size()-1].play();
            temp_bullet_vals.scale = vec3(0.15);
        } else {
            // Play sound
            currentGunshotSounds.emplace_back(self->transform.position, vec3(0), "./sounds/gunfire1.ogg",  false, 3, 0.1, 2, 0.5);
            currentGunshotSounds[currentGunshotSounds.size()-1].play();
            temp_bullet_vals.scale = vec3(0.05);
        }

        temp_bullet_flags = static_cast<unsigned int>(3.0f/self->transform.scale.x);
        putGameObject("bullet" + std::to_string(bulletCount), GameObject(&bulletGameObject));
    }
}

void enemy1GunAI(double deltaTime, GameObject* self) {
    if (std::bit_cast<float>(static_cast<uint32_t>(self->flags)) > (static_cast<float>((self->flags & 0x000000FF00000000) >> 32)*self->transform.scale.x)/20.0f) {
        self->flags = 0x1000000000000000;
    } else {
        self->flags =
                (self->flags & 0xFFFFFFFF00000000) // Maintain upper half data
                /*     bit cast to low bits    bit cast the existing data to a float                 add statically casted deltatime  */
                | std::bit_cast<uint32_t>(std::bit_cast<float>(static_cast<uint32_t>(self->flags)) + static_cast<float>(deltaTime));
    }
}

void enemy1Object(GameObject* self){
    self->transform.position = vec3(15-(rand()%30), (rand()%12)*2 + cameraAccess()->position.y, 15-(rand()%30));
    self->transform.scale    = vec3(0.5);
    self->renderables.push_back(enemy1Renderable);
    self->onUpdate.push_back(&enemyMovementAI);
    self->onUpdate.push_back(&enemy1GunAI);
    ejectFromWorld(&self->transform);
    self->flags = static_cast<uint64_t>(rand()%200) << 32;
}
void enemyKMSObject(GameObject* self){
    self->transform.position = vec3(15-(rand()%30), (rand()%12)*2 + cameraAccess()->position.y, 15-(rand()%30));
    self->transform.scale    = vec3(0.5);
    self->renderables.push_back(enemy_kill_me_please_renderable);
    self->onUpdate.push_back(&enemyMovementAI);
    self->onUpdate.push_back(&enemy1GunAI);
    ejectFromWorld(&self->transform);
    self->flags = static_cast<uint64_t>(rand()%200) << 32;
}

void enemy2Object(GameObject* self){
    self->transform.position = vec3(20-(rand()%40), (rand()%12)*2 + cameraAccess()->position.y, 20-(rand()%40));
    self->transform.scale    = vec3(0.65);
    self->renderables.push_back(enemy2Renderable);
    self->onUpdate.push_back(&enemyMovementAI);
    self->onUpdate.push_back(&enemy1GunAI);
    ejectFromWorld(&self->transform);
    self->flags = static_cast<uint64_t>(rand()%200) << 32;
}

void enemy3Object(GameObject* self){
    self->transform.position = vec3(15-(rand()%30), (rand()%12)*2 + cameraAccess()->position.y, 15-(rand()%30));
    self->transform.scale    = vec3(0.45);
    self->renderables.push_back(enemy3Renderable);
    self->onUpdate.push_back(&enemyMovementAI);
    self->onUpdate.push_back(&enemy1GunAI);
    ejectFromWorld(&self->transform);
    self->flags = static_cast<uint64_t>(rand()%200) << 32;
}

void runtimeCleanup(double dt) {
    if (currentGunshotSounds.size() > 0 && !currentGunshotSounds[0].isPlaying()) currentGunshotSounds[0].deleteSource();
    std::vector<std::string> cleanNames{};
    const float removeBulletSpeed = 8; // Bullets that fly into the distance usually go under about here after getting into the 200s
    for (auto const &g: *getGameObjects()) {
        if (g.first.starts_with("bullet") && (abs(g.second.transform.pos_vel.x) < removeBulletSpeed) && (abs(g.second.transform.pos_vel.z) < removeBulletSpeed)) {
            cleanNames.push_back(g.first);
        }
    }
    for (auto const& name : cleanNames) {
        deleteGameObject(name);
    }
}

void enemySystemInit(){
    // Load the ogg file early by creating a Sound
    Sound preloadAudio = Sound(vec3(0), vec3(0), "./sounds/gunfire0.ogg",  false, 3, 0.1, 2, 0.25);
    preloadAudio = Sound(vec3(0), vec3(0), "./sounds/gunfire1.ogg",  false, 3, 0.1, 2, 0.25);
    preloadAudio.stop(); // Force the compiler to care about the Sound object.

    createTexture("enemy1", "./textures/enemy1_tex.png", "./tex_bundle.jbd");
    createTexture("enemy2", "./textures/enemy2_tex.png", "./tex_bundle.jbd");
    createTexture("enemy3", "./textures/enemy3_tex.png", "./tex_bundle.jbd");
    createTexture("bullet", "./textures/bullet_tex.png", "./tex_bundle.jbd");
    createTexture("bullet_specmis", "./textures/bullet_specmis.png", "./tex_bundle.jbd");
    createTexture("enemy_specmis", "./textures/enemy_specmis.png", "./tex_bundle.jbd");
    enemy1Renderable = loadObj("./models/enemy1.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("enemy1"), getTexture("enemy_specmis")})[0];
    enemy2Renderable = loadObj("./models/enemy1.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("enemy2"), getTexture("enemy_specmis")})[0];
    enemy3Renderable = loadObj("./models/enemy1.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("enemy3"), getTexture("enemy_specmis")})[0];
    bulletRenderable = loadObj("./models/enemy1_bullet.obj", getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("bullet"), getTexture("bullet_specmis")})[0];

    // Welp, accidentally left these notes while streaming development to Gamer girl ultrakill.
    // So much for the funny easter egg.
    createTexture("enemy_why_are_you_reading_the_ram_dump_laika", "./textures/stop_going_through_game_files_via_this_isnt_ddlc.png", "./tex_bundle.jbd");
    enemy_kill_me_please_renderable = loadObj("./models/stop_going_through_game_files_via_this_isnt_ddlc.obj",
                                              getShader("3dtoon"), {getUBOID(), getLBOID(), getTexture("enemy_why_are_you_reading_the_ram_dump_laika")})[0];

    registerOnUpdate(&runtimeCleanup);
}

void instantiateRandomEnemyWave(int count){
    enemyMax = count;
    for (int i = 0; i < count; i++){
        int random = rand();
        if (random%7250 == 420) { // 7250 is oddly specific but argued with via over this number
            // Secret uwu enemy
            putGameObject("enemy_stop_reading_ram_dumps_rose" + std::to_string(i), GameObject(&enemyKMSObject));
        } else {
            switch (random%3) {
                case (2): {
                    if (enemyMax > 30) { // Natural progression to keep the game interesting
                        // Chunky Boi
                        putGameObject("enemy2_" + std::to_string(i), GameObject(&enemy2Object));
                        break;
                    }
                }
                case (1): {
                    if (enemyMax > 10) {
                        // Little Bitchass
                        putGameObject("enemy3_" + std::to_string(i), GameObject(&enemy3Object));
                        break;
                    }
                }
                default: {
                    // Default
                    putGameObject("enemy1_" + std::to_string(i), GameObject(&enemy1Object));
                }
            }
        }
    }
}

void initWorldBoxColliders(std::vector<Transform> boxes){
    enemyWorldBoxColliders = boxes; // wow what creative code
}