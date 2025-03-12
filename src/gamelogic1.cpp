//#include "gamelogic.h"
//#include <iostream>
//#include <Windows.h>
//#include <cmath>
//#include <algorithm>
//
//
//float clamp(float val, float minVal, float maxVal)
//{
//    if (val < minVal) return minVal;
//    if (val > maxVal) return maxVal;
//    return val;
//}
//
//// Checks circle-rectangle collision
//bool circleRectCollision(float cx, float cy, float radius,
//                         float rx, float ry, float rw, float rh)
//{
//
//    float closestX = clamp(cx, rx, rx + rw);
//    float closestY = clamp(cy, ry, ry + rh);
//    float dx = cx - closestX;
//    float dy = cy - closestY;
//    float penetration = radius - sqrt(cx * cx + cy * cy);
//    if (penetration > 0) {
//        // Push circle out of collision
//        float angle = atan2(cy, cx);
//        cx += cos(angle) * penetration;
//        cy += sin(angle) * penetration;
//        return true;
//    }
//    return false;
////    return (dx * dx + dy * dy <= radius * radius);
//}
//
//struct ShipPart {
//    float offsetX;
//    float offsetY;
//    int width;
//    int height;
//    int r, g, b; 
//};
//
//struct Ship {
//    float posX;
//    float posY;
//    float velX;
//    float velY;
//    bool isActive;
//    static const int PARTS_COUNT = 3;
//    ShipPart parts[PARTS_COUNT];
//};
//
//
//
//struct GameData
//{
//    // Bird (circle)
//    float birdPosX = 100;
//    float birdPosY = 300;
//    float birdVelX = 0;
//    float birdVelY = 0;
//    bool  isDragging = false;
//    bool  isLaunched = false;
//    float gravity = 300.0f;
//    int   birdRadius = 15;
//
//    // Trajectory drag
//    float startX, startY;
//    float releaseX, releaseY;
//
//    // Ship
//    Ship ship;
//};
//
//static GameData data;
//
//
//void drawCircle(GameWindowBuffer& buffer, int centerX, int centerY, int radius, int r, int g, int b) {
//    for (int y = -radius; y <= radius; y++) {
//        for (int x = -radius; x <= radius; x++) {
//            if (x * x + y * y <= radius * radius) {
//                buffer.drawAtSafe(centerX + x, centerY + y, r, g, b);
//            }
//        }
//    }
//}
//
//void drawLine(GameWindowBuffer& buffer, int x0, int y0, int x1, int y1, int r, int g, int b) {
//    int dx = abs(x1 - x0);
//    int dy = abs(y1 - y0);
//    int sx = x0 < x1 ? 1 : -1;
//    int sy = y0 < y1 ? 1 : -1;
//    int err = dx - dy;
//
//    while (true) {
//        buffer.drawAtSafe(x0, y0, r, g, b);
//        if (x0 == x1 && y0 == y1) break;
//        int e2 = 2 * err;
//        if (e2 > -dy) {
//            err -= dy;
//            x0 += sx;
//        }
//        if (e2 < dx) {
//            err += dx;
//            y0 += sy;
//        }
//    }
//}
//
//// ---------------------------------------------------
//// Initialization
//// ---------------------------------------------------
//bool initGameplay() {
//data = GameData();
//    
//    // Bigger ship configuration
//    data.ship.parts[0] = { 0.0f, 0.0f, 120, 30, 60, 60, 60 };      // Main hull
//    
//    data.ship.parts[0] = { 0.0f, 0.0f, 120, 30, 60, 60, 60 };   // Main hull
//    data.ship.parts[1] = { 30.0f, -20.0f, 5, 40, 139, 69, 19 };  // Mast
//    data.ship.parts[2] = { 30.0f, -40.0f, 30, 5, 255, 255, 255 };// Sail
//
//    data.ship.isActive = true;
//    data.ship.posX = 400.0f;
//    data.ship.posY = 300.0f;
//
//    // Adjust bird start position
//    const float shipRight = data.ship.posX + data.ship.parts[0].width;
//    data.birdPosX = shipRight - 30.0f;
//    data.birdPosY = data.ship.posY + data.ship.parts[0].height + data.birdRadius;
//
//    return true;
//}
//
//bool gameplayFrame(float deltaTime, int w, int h, Input& input, GameWindowBuffer& gameWindowBuffer)
//{
//    static bool firstFrame = true;
//    if (firstFrame)
//    {
//        // Ensure the positions are set when the game starts
//        data.birdPosX = w / 2.0f;
//        data.birdPosY = h / 2.0f;
//
//        // Place the ship at the bottom-right corner
//        data.ship.posX = w - 120;  // Adjust according to ship width
//        data.ship.posY = h - 80;   // Adjust according to ship height
//
//        firstFrame = false; // Ensure it runs only once
//    }
//
//    // ---------------------------------------------------
//    // 1. Handle Bird Input
//    // ---------------------------------------------------
//    if (input.lMouseButton.held && !data.isLaunched)
//    {
//        data.isDragging = true;
//        data.startX = data.birdPosX;
//        data.startY = data.birdPosY;
//        data.releaseX = input.cursorX;
//        data.releaseY = input.cursorY;
//    }
//    else if (data.isDragging)
//    {
//        data.isDragging = false;
//        data.isLaunched = true;
//        data.birdVelX = (data.startX - data.releaseX) * 2.0f;
//        data.birdVelY = (data.startY - data.releaseY) * 2.0f;
//    }
//
//    // ---------------------------------------------------
//    // 2. Update Bird Physics
//    // ---------------------------------------------------
//    if (data.isLaunched)
//    {
//        data.birdVelY += data.gravity * deltaTime;
//        data.birdPosX += data.birdVelX * deltaTime;
//        data.birdPosY += data.birdVelY * deltaTime;
//
//        if (data.birdPosY + data.birdRadius > h)
//        {
//            data.birdPosY = h - data.birdRadius;
//            data.birdVelY = -data.birdVelY * 0.6f;
//        }
//
//        if (data.birdPosX - data.birdRadius < 0 || data.birdPosX + data.birdRadius > w)
//        {
//            data.birdVelX = -data.birdVelX * 0.6f;
//        }
//    }
//
//    // ---------------------------------------------------
//    // 3. Update Ship Physics
//    // ---------------------------------------------------
//    if (data.ship.isActive) {
//        data.ship.velY += data.gravity * deltaTime;
//        data.ship.posX += data.ship.velX * deltaTime;
//        data.ship.posY += data.ship.velY * deltaTime;
//
//        // Ground collision using main hull
//        const auto& hull = data.ship.parts[0];
//        float hullBottom = data.ship.posY + hull.offsetY + hull.height;
//        if (hullBottom > h) {
//            data.ship.posY = h - hull.height - hull.offsetY;
//            data.ship.velY = -data.ship.velY * 0.5f;
//            data.ship.velX *= 0.8f; // More friction when grounded
//        }
//
//        // Wall collisions with buffer
//        float hullLeft = data.ship.posX + hull.offsetX;
//        float hullRight = hullLeft + hull.width;
//        const float WALL_BUFFER = 20.0f;
//
//        if (hullLeft < WALL_BUFFER) {
//            data.ship.posX = WALL_BUFFER - hull.offsetX;
//            data.ship.velX = -data.ship.velX * 0.6f;
//        }
//        else if (hullRight > w - WALL_BUFFER) {
//            data.ship.posX = w - WALL_BUFFER - hull.width - hull.offsetX;
//            data.ship.velX = -data.ship.velX * 0.6f;
//        }
//    }
//
//    // ---------------------------------------------------
//    // 4. Bird vs. Ship Collision
//    // ---------------------------------------------------
//// ---------------------------------------------------
//// 4. Bird vs. Ship Collision
//// ---------------------------------------------------
//    if (data.ship.isActive) {
//        for (int i = 0; i < Ship::PARTS_COUNT; i++) {
//            const auto& part = data.ship.parts[i];
//            float partX = data.ship.posX + part.offsetX;
//            float partY = data.ship.posY + part.offsetY;
//
//            if (circleRectCollision(
//                data.birdPosX, data.birdPosY, data.birdRadius,
//                partX, partY, part.width, part.height))
//            {
//                // Calculate reflection
//                float overlapX = data.birdPosX - (partX + part.width / 2.0f);
//                float overlapY = data.birdPosY - (partY + part.height / 2.0f);
//
//                // Bounce with energy preservation
//                data.birdVelX = -data.birdVelX * 0.7f;
//                data.birdVelY = -data.birdVelY * 0.7f;
//
//                // Apply force to ship
//                data.ship.velX += overlapX * 0.2f;
//                data.ship.velY += overlapY * 0.2f;
//            }
//        }
//    }
//
//
//    // ---------------------------------------------------
//    // Rendering
//    // ---------------------------------------------------
//    gameWindowBuffer.clear();
//
//    // Draw background
//    for (int i = 0; i < gameWindowBuffer.w; i++) {
//        for (int j = 0; j < gameWindowBuffer.h; j++) {
//            gameWindowBuffer.drawAtSafe(i, j, 0, 0, 0);
//        }
//    }
//
//    // Draw bird
//    int birdX = (int)data.birdPosX;
//    int birdY = (int)data.birdPosY;
//    int radius = data.birdRadius;
//    for (int y = birdY - radius; y <= birdY + radius; y++) {
//        for (int x = birdX - radius; x <= birdX + radius; x++) {
//            int dx = x - birdX;
//            int dy = y - birdY;
//            if (dx * dx + dy * dy <= radius * radius) {
//                gameWindowBuffer.drawAtSafe(x, y, 255, 0, 0);
//            }
//        }
//    }
//
//    // Draw trajectory
//    if (data.isDragging) {
//        float predictX = data.startX;
//        float predictY = data.startY;
//        float predictVelX = (data.startX - data.releaseX) * 2.0f;
//        float predictVelY = (data.startY - data.releaseY) * 2.0f;
//
//        for (int i = 0; i < 50; i++) {
//            predictVelY += data.gravity * 0.02f;
//            predictX += predictVelX * 0.02f;
//            predictY += predictVelY * 0.02f;
//            gameWindowBuffer.drawAtSafe((int)predictX, (int)predictY, 255, 255, 0);
//        }
//    }
//
//    // Draw ship
//    if (data.ship.isActive) {
//        for (int i = 0; i < Ship::PARTS_COUNT; i++) {
//            const auto& part = data.ship.parts[i];
//            int startX = static_cast<int>(data.ship.posX + part.offsetX);
//            int startY = static_cast<int>(data.ship.posY + part.offsetY);
//            int endX = startX + part.width;
//            int endY = startY + part.height;
//
//            for (int x = startX; x < endX; x++) {
//                for (int y = startY; y < endY; y++) {
//                    if (i == 0) gameWindowBuffer.drawAtSafe(x, y, 100, 100, 100); // Gray hull
//                    else if (i == 1) gameWindowBuffer.drawAtSafe(x, y, 139, 69, 19);  // Brown mast
//                    else gameWindowBuffer.drawAtSafe(x, y, 255, 255, 255); // White sail
//                }
//            }
//        }
//    }
//
//    return true;
//}
//
//void closeGameLogic()
//{
//    // Cleanup if needed
//}