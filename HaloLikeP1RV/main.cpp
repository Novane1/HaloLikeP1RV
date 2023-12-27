//Librairies
#include "main.h"
using namespace std;








int main() {
    // Initialize GLFW
        /// Audio
   // Initialize OpenAL


   
    const char* dsmusic = "dsmusic.wav";
    const char* laser = "laser.wav";
    audioManager->AddSong(dsmusic,0.3f);
    audioManager->AddSong(laser,1.0f);

    // Play the source
    


    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

   
    GLFWwindow* window = glfwCreateWindow(800, 600, "My GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Shader shader(vertexShaderSource, fragmentShaderSource);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        // Handle error
        glfwTerminate();
        return -1;
    }
   
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, souris_au_centre);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    
    //// LOAD OBJETS DE NATHAN
    death.LoadOBJ("Modele/death.obj");
    death.LoadTexture("death.jpg");

    monde.LoadOBJ("Modele/map.obj");
    spawnPoints.LoadOBJ("Modele/spawnPoints.obj");

    navMesh.LoadOBJ("Modele/map.obj");
    navMesh.LoadTexture("Terrain.png");
    monde.LoadTexture("Terrain.png");
    heart.LoadOBJ("Modele/heart.obj");
    skybox.LoadOBJ("Modele/skybox.obj");

    
    player.LoadTexture("zelda.png");
    player.LoadOBJ("Modele/zeldo.obj");
    player.LoadCOllider("Modele/zeldoCollider.obj");
    otherEnnemiCollider.push_back(&player);
    knifeHandle.LoadTexture("knifeHandle.png");
    knifeHandle.LoadOBJ("Modele/knifeHandle.obj");

    knifeBlade.LoadTexture("knifeBlade.png");
    knifeBlade.LoadOBJ("Modele/knifeBlade.obj");

    glove.LoadTexture("glove.png");
    glove.LoadOBJ("Modele/glove.obj");
    camera.setCollider("Modele/cameraCollider.obj");

    meteor.LoadTexture("meteor.png");
    meteor.LoadOBJ("Modele/meteor.obj");
    meteor.LoadCOllider("Modele/meteorCollider.obj");
    otherEnnemiCollider.push_back(&meteor);

    smog.LoadOBJ("Modele/smog.obj");
   
    listUI.AddObject(gun);
    listUI.AddObject(knifeHandle);
    listUI.AddObject(knifeBlade);
    listUI.AddObject(glove);
    listUI.AddObject(heart);
    listUI.AddObject(death);
    listUI.changeState(false, 0);
    listUI.changeState(false,5);
    camera.setUI(listUI);
   
    PatternManager pMeteor(&meteor);
    
    MovementManager movManager(&player);

    
  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 800.0f / 600.0f, 0.1f, 10000.0f);

    Shader redDamageShader(vertexShaderSource, fragmentShaderSource);
    Shader skyboxShader(vertexShaderSourceSkyBox, fragmentShaderSourceSkyBox);
    Shader healthShader(vertexShaderSourceHealth, fragmentShaderSourceHealth);
    Shader smogShader(vertexShaderSourceSmog, fragmentShaderSourceSmog);
    Shader groundShader(vertexShaderSourceGround, fragmentShaderSourceGround);
    Shader baseShader(vertexShaderSourceBase, fragmentShaderSourceBase);
    Shader alphaShader(vertexShaderSourceAlpha, fragmentShaderSourceAlpha);
    Shader playerShader(vertexShaderSourceBaseP, fragmentShaderSourceBaseP);

    rayon downSnap(navMesh.getvraiFaces());
    glm::vec3 intersection(0.0f);

    // Lancement du OST original
    audioManager->playSong(0);

    ReloadManager reloadManager(smog, smogShader, spawnPoints.getvraiFaces(),&shootBar);


    while (!glfwWindowShouldClose(window)) {
        if (camera.getHealth() <= 0) 
        {
            glEnable(GL_BLEND);
            
            // Set the blending function
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glfwSetCursorPosCallback(window, nullptr);
            camera.changeState(false, 0);
            camera.changeState(false, 1);
            camera.changeState(false ,2);
            camera.changeState(false, 3);
            camera.changeState(false, 4);
            camera.changeState(true, 5);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_TEXTURE_2D);
            clavier();
            monde.affichageShader(groundShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            camera.affichageUI(keys, mouseClick, healthShader,alphaShader);

            
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            glfwSwapBuffers(window);
            glfwPollEvents();
            
        }
        else 
        {
            glEnable(GL_BLEND);

            // Set the blending function
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            camera.updateCamera();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Enable texturing

            glEnable(GL_TEXTURE_2D);

            clavier();


            
            movManager.updatePos(camera, pMeteor);
            pMeteor.updateMeteor(baseShader, camera.getPosition(), camera.getTarget());
            
            monde.affichageGround(groundShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), pMeteor.getT() * 10.0f , pMeteor.getActivePoint(),player.getPos(),movManager.getlongRadius(), movManager.getcloseRadius());
            float a = movManager.getCloseRange();

            if (a == 0) {
                a = 1.0f;
            }
            if (a >= 1) {
                a = 1.0f;
            }

            if ((player.getDamageFrame() / 10) % 2 == 0) 
            { 
               
                player.affichageShaderPlayer(playerShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), player.getPos(),a);
            }
            else { player.affichageShaderPlayer(redDamageShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0), player.getPos(),a); }
           
           
            //meteor.affichage();
            camera.affichageUI(keys, mouseClick, healthShader,  alphaShader);
            
            skybox.affichageSkybox(skyboxShader, camera.getPosition(), camera.getTarget(), glm::vec3(0.0, 1.0, 0.0));
            if (camera.getUI().isGun()) {
                shootBar.affichage();
            }

            

            // Crosshair
            crosshair.affichageCrosshair();
            //reload
            reloadManager.actTime(camera.getPosition(), camera.getTarget());
            reloadManager.affichage(camera.getPosition(), camera.getTarget());
            //

            camera.go(dZ, dX, otherEnnemiCollider);
            

            // Intersection Joueur
            intersection = downSnap.ptIntersectionF(player.getPos());

            if (intersection != glm::vec3{ -100,-100,-100 })
            {
                
                 player.setPos(glm::vec3(player.getPos().x,intersection.y, player.getPos().z));
                 
                
            }
           

            // Intersection Ennemi
            intersection = downSnap.ptIntersectionF(camera.getPosition());

            if (intersection != glm::vec3{ -100,-100,-100 })
            {
                if (!camera.isJumping())
                {
                    camera.sethauteur(intersection, _HEIGHT);
                }
                
            }



            for (vector<Ennemi*>::iterator it = player.listEnnemi.begin(); it != player.listEnnemi.end(); it++) {
                (*it)->increaseDamageFrame();
            }


            camera.updateFrame();
            camera.updateJump(intersection.y);
            camera.updateCheckInvicibility();

            glDisable(GL_TEXTURE_2D);

            glfwSwapBuffers(window);
            glfwPollEvents();

        }
        
        // Exit on Echap
        if (shouldExit) {
            break;
        }
        glDisable(GL_BLEND);
        
    }



    
    // Clean up
    glfwTerminate();
    audioManager->destroy();
    return 0;
}