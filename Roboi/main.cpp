//Setting up main variables
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <sstream>

int windowWidth = 400;
int windowHeight = 300;

using namespace sf;
using namespace std;






class playerClass{
public:
    bool playerFaceRight = true;

    float xvel = 0;
    float yvel = 0;
    float xpos = 0;
    float ypos = 0;


    playerClass(){


    }


    //Updating values based on inputs
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight){
        if(playerRight){
            xvel = 0.1;
            playerFaceRight = true;

        }
        if(playerLeft){
            xvel = -0.1;
            playerFaceRight = false;
        }

        if(playerUp){
            yvel = -0.1;

        }

        if(playerDown){
            yvel = 0.1;
        }

        if(!(playerRight or playerLeft)){
            xvel = 0;
        }


        if(!(playerDown or playerUp)){
            yvel = 0;
        }








        xpos += xvel;
        ypos += yvel;

    }


};

int main()
{

    //Setting up values for goal and enemy positions
    srand(time(NULL));
    float goalPosx = rand()%400;
    float goalPosy = rand()%300;


    srand(time(NULL) * 30);
    float enemPosx1 = rand()%400;
    float enemPosy1 = rand()%300;

    int score = 0;









    // Create the main window
    RenderWindow app(VideoMode(windowWidth, windowHeight), "Plattformer");


	bool playerUp, playerDown, playerLeft, playerRight = false;
    playerClass playerObject;

    //Loading sprites
    Texture roboiTexture;
    roboiTexture.loadFromFile("data/images/Roboi.png");
    Sprite roboiSprite(roboiTexture);

    Texture enemTexture;
    enemTexture.loadFromFile("data/images/enem.png");
    Sprite enemSprite(enemTexture);

    Texture goalTexture;
    goalTexture.loadFromFile("data/images/goal.png");
    Sprite goalSprite(goalTexture);

    Texture winTexture;
    winTexture.loadFromFile("data/images/win.png");
    Sprite winSprite(winTexture);

    Font font;
    font.loadFromFile("data/fonts/AGENCYB.TTF");
    Text text;
    text.setFont(font);





    //Main game loop
    while (app.isOpen())
    {
        //Score
        String scores = to_string(score);
        text.setString(scores);






        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }

        //Keyboard Inputs
        if(Keyboard::isKeyPressed(Keyboard::Right)) playerRight = true;
        if(Keyboard::isKeyPressed(Keyboard::Left)) playerLeft = true;
        if(Keyboard::isKeyPressed(Keyboard::Up)) playerUp = true;
        if(Keyboard::isKeyPressed(Keyboard::Down)) playerDown = true;


        if(!Keyboard::isKeyPressed(Keyboard::Right)) playerRight = false;
        if(!Keyboard::isKeyPressed(Keyboard::Left)) playerLeft = false;
        if(!Keyboard::isKeyPressed(Keyboard::Up)) playerUp = false;
        if(!Keyboard::isKeyPressed(Keyboard::Down)) playerDown = false;


        playerObject.update(playerUp, playerDown, playerLeft, playerRight);



        app.clear();

        //goal randomization
        srand(time(NULL));
        if(playerObject.xpos < goalPosx + 20 and playerObject.xpos > goalPosx - 20 and playerObject.ypos < goalPosy + 20 and playerObject.ypos > goalPosy - 20){

        srand(time(NULL) * 20);
        goalPosx = rand()%350;
        goalPosy = rand()%250;


        srand(time(NULL) * 30);
        enemPosx1 = rand()%350;
        enemPosy1 = rand()%250;




        //first frame kill check
        if(playerObject.xpos < enemPosx1 + 20 and playerObject.xpos > enemPosx1 - 20 and playerObject.ypos < enemPosy1 + 20 and playerObject.ypos > enemPosy1 - 20){
        enemPosx1 = rand()%350;
        enemPosy1 = rand()%250;

        }

        if(playerObject.xpos < goalPosx + 20 and playerObject.xpos > goalPosx - 20 and playerObject.ypos < goalPosy + 20 and playerObject.ypos > goalPosy - 20){
        srand(time(NULL) * 20);
        goalPosx = rand()%350;
        goalPosy = rand()%250;


        srand(time(NULL) * 30);
        enemPosx1 = rand()%350;
        enemPosy1 = rand()%250;
        }

        else{
            score += 1;
            Sleep(5);
        }


        }



        //Out of bounds goal check
        if(goalPosx < 50 or goalPosx > 350){
        srand(time(NULL) * 20);
        goalPosx = rand()%350;


        srand(time(NULL) * 30);
        enemPosx1 = rand()%350;
        }

        //Out of bounds goal check two
        if(goalPosy < 50 or goalPosy > 300){
        srand(time(NULL) * 20);
        goalPosy = rand()%350;


        srand(time(NULL) * 30);
        enemPosy1 = rand()%350;
        }

            //Enemy collision detection
            if(playerObject.xpos < enemPosx1 + 20 and playerObject.xpos > enemPosx1 - 20 and playerObject.ypos < enemPosy1 + 20 and playerObject.ypos > enemPosy1 - 20){
            enemSprite.setPosition(Vector2f(enemPosx1, enemPosy1));
            playerObject.xvel = 0;
            playerObject.yvel = 0;
            Sleep(1000);
            app.close();
        }

        //Drawing and positioning the sprites
        app.draw(goalSprite);
        app.draw(roboiSprite);
        app.draw(enemSprite);
        app.draw(text);

        enemSprite.setPosition(Vector2f(enemPosx1, enemPosy1));
        goalSprite.setPosition(Vector2f(goalPosx, goalPosy));
        roboiSprite.move(Vector2f(playerObject.xvel, playerObject.yvel));

        app.display();
    }

    return EXIT_SUCCESS;
}
