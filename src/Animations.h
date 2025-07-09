#pragma once

struct CellAnimation
{
    bool active = false;
    float elapsedTime = 0.0f;
    float duration = 0.5f;

    float scale = 0.0f;
    float alpha = 0.0f;

    void start()
    {
        active = true;
        elapsedTime = 0.0f;
        scale = 0.0f;
        alpha = 0.0f;
    }

    void update(float deltaTime)
    {
        if (!active)
            return;

        elapsedTime += deltaTime;
        float t = elapsedTime / duration;
        if (t >= 1.0f)
        {
            t = 1.0f;
            active = false;
        }

        scale = bounceOut(t);

        alpha = t;
    }

    float bounceOut(float t)
    {
        if (t < (1 / 2.75f)) {
            return 7.5625f * t * t;
        }
        else if (t < (2 / 2.75f)) {
            t -= (1.5f / 2.75f);
            return 7.5625f * t * t + 0.75f;
        }
        else if (t < (2.5f / 2.75f)) {
            t -= (2.25f / 2.75f);
            return 7.5625f * t * t + 0.9375f;
        }
        else {
            t -= (2.625f / 2.75f);
            return 7.5625f * t * t + 0.984375f;
        }
    }
};
