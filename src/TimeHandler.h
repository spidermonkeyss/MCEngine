#pragma once

static class TimeHandler
{
private:
    static double startTime;
    static double currentTime;
    static double gameTime;
    static double deltaTime;
public:
    static void Init();
    static void UpdateTime();

    static inline double GameTime() { return gameTime; }
    static inline double DeltaTime() { return deltaTime; }
};