#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>

using namespace std;

const float GRAVITY = 1.2f;
const float JUMP_FORCE = 10.0f;
const int FRAME_DELAY = 20;
const float OBSTACLE_SPEED = 5.0f;
const float paddle = -80.0f;

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) //Hàm khởi tạo SDL2
    {
        std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) //Hàm khởi tạo SDL2 Image
    {
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    RenderWindow window("Super T-Rex v1.0", 640, 480); // Tạo cửa sổ game

    //Load ảnh liên quan cho game

    SDL_Texture* StartButton = window.loadTexture("res/gfx/Start_Button.png");
    Entity Start(100, 79, StartButton);

    SDL_Texture* ExitButton = window.loadTexture("res/gfx/Exit_Button.png");
    Entity Exit(100, 99, ExitButton);

    SDL_Texture* GameTitle = window.loadTexture("res/gfx/Game_Title.png");
    Entity Title(100, 49, GameTitle);

    SDL_Texture* LobbySite = window.loadTexture("res/gfx/Menu_Background.png");
    Entity Lobby(0,0, LobbySite);

    SDL_Texture* BackgroundTexture = window.loadTexture("res/gfx/T-Rex_Background.png");
    Entity entity0(0, 0, BackgroundTexture);

    SDL_Texture* TRexTexture = window.loadTexture("res/gfx/TRex_Standing-removebg.png");
    int tRexWidth, tRexHeight;
    //Load ảnh con khủng long cùng với kích thước của nó
    SDL_QueryTexture(TRexTexture, NULL, NULL, &tRexWidth, &tRexHeight);
    // Thiết đặt vị trí cho khủng long
    Entity tRexEntity(20, 70, TRexTexture);
    // Định hình kích thước khủng long = kích thước ảnh gốc
    tRexEntity.setSize(tRexWidth, tRexHeight);

    vector<Obstacle> obstacles; // Tạo xương rồng

    for (int i = 0; i < 1000; ++i)
    {
        SDL_Texture* obstacleTexture = window.loadTexture("res/gfx/cactus.png");
        int obstacleHeight, obstacleWidth;
        SDL_QueryTexture(obstacleTexture, NULL, NULL, &obstacleWidth, &obstacleHeight);

        Obstacle obstacle(tRexEntity.getX() + 200 + i * 200, 180 - obstacleHeight, obstacleTexture); // Tọa độ xương rồng chạy dần về khủng long
        obstacle.setSize(obstacleWidth, obstacleHeight); // Định hình kích thước xương rồng
        obstacles.push_back(obstacle);
    }
   
    // Xử lý nhảy
    bool isJumping = false;
    float jumpSpeed = 0.0f;

    SDL_Event event;

    bool gameRunning = true;

    Uint32 gameStartTime = SDL_GetTicks(); // tính thời gian game chạy rồi quy đổi ra số điểm của người chơi
    Uint32 gameTime = 0;

    while (gameRunning)
    {
        Uint32 startTime = SDL_GetTicks(); // set thời gian để control khung hình game phù hợp

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE && !isJumping) // Nhận lệnh ấn phím space để bắt đầu xử lý nhảy của T-Rex
                {
                    isJumping = true;
                    jumpSpeed = -JUMP_FORCE;
                }
            }
        }

        if (isJumping)
        {
            tRexEntity.setY(tRexEntity.getY() + jumpSpeed); // Khi ấn space khủng long sẽ nhảy đến một tọa độ Y mới 
            jumpSpeed += GRAVITY; // set độ cao max khi nhảy

            if (tRexEntity.getY() >= 70) // nếu rơi về tọa độ ban đầu, đặt lại mọi thứ về như cũ, kết thúc quá trình nhảy
            {
                isJumping = false;
                tRexEntity.setY(70);
                jumpSpeed = 0.0f;
            }
        }

        window.clear();

        window.render(Lobby);
        window.render(Start);
        window.render(Exit);
        window.render(Title);
        window.render(entity0);

        for (auto& obstacle : obstacles) 
        {
            obstacle.setX(obstacle.getX() - OBSTACLE_SPEED);
            window.render(obstacle);
        }

        window.render(tRexEntity);

        window.display();

        
        for (auto& obstacle : obstacles) // Xử lí tọa độ của xương rồng, nếu gặp tọa độ mà khúng long đang đứng, dừng game
        {
            if (tRexEntity.getX() < obstacle.getX() + obstacle.getWidth() + paddle &&
                tRexEntity.getX() + tRexEntity.getWidth() > obstacle.getX() - paddle&&
                tRexEntity.getY() < obstacle.getY() + obstacle.getHeight() + paddle &&
                tRexEntity.getY() + tRexEntity.getHeight() > obstacle.getY() - paddle) 
            {
                gameRunning = false;
            }
        }

        if (!gameRunning)
        {
            gameTime = SDL_GetTicks() - gameStartTime;

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", ("Your score: " + to_string(gameTime/72) ).c_str(), window.getSDLWindow());
        }

        Uint32 endTime = SDL_GetTicks();
        
        Uint32 elapsedTime = endTime - startTime;
        if (elapsedTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - elapsedTime);
        }


    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}
