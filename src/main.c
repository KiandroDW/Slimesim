#include "agent.h"
#include "raylib.h"
#include "conf.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Slime Diffusion Simulator");
    SetTargetFPS(60);

	RenderTexture2D bufferA = LoadRenderTexture(screenWidth, screenHeight);
	RenderTexture2D bufferB = LoadRenderTexture(screenWidth, screenHeight);

	// Set filtering for both
	SetTextureFilter(bufferA.texture, TEXTURE_FILTER_POINT);
	SetTextureFilter(bufferB.texture, TEXTURE_FILTER_POINT);

    Shader diffusionShader = LoadShader(0, "shaders/diffusion.fs");

    Vector2 resolution = { screenWidth, screenHeight };
    SetShaderValue(diffusionShader, GetShaderLocation(diffusionShader, "resolution"), &resolution, SHADER_UNIFORM_VEC2);

	Agent** agents = malloc(agentCount * sizeof(Agent));
	spawnAgents(agents);

	bool useBufferA = true;

	while (!WindowShouldClose()) {
		BeginTextureMode(useBufferA ? bufferB : bufferA);
			ClearBackground(BLACK);

			// Bind the shader
			BeginShaderMode(diffusionShader);

				// Pass the texture to sample
				SetShaderValueTexture(diffusionShader,
								GetShaderLocation(diffusionShader, "texture0"),
								useBufferA ? bufferA.texture : bufferB.texture);

				// Pass resolution uniform...
				Vector2 res = { screenWidth, screenHeight };
				SetShaderValue(diffusionShader, GetShaderLocation(diffusionShader, "resolution"), &res, SHADER_UNIFORM_VEC2);

				// Draw full screen quad
				DrawTextureRec(
					(useBufferA ? bufferA : bufferB).texture,
					(Rectangle){0, 0, (float)screenWidth, -(float)screenHeight},
					(Vector2){0, 0},
					WHITE);

			EndShaderMode();
			Image frame = LoadImageFromTexture((useBufferA ? bufferB : bufferA).texture); // GPU → CPU
			Color *pixels = LoadImageColors(frame);
			for (int i = 0; i < agentCount; i++) {
				DrawPixel(agents[i]->position.x, agents[i]->position.y, GREEN);
				updateAgent(agents[i], pixels);
			}
			UnloadImageColors(pixels);
			UnloadImage(frame);
		EndTextureMode();

		// Draw the current buffer to screen
		BeginDrawing();
			ClearBackground(BLACK);

			DrawTextureRec(
				(useBufferA ? bufferB : bufferA).texture,
				(Rectangle){0, 0, (float)screenWidth, -(float)screenHeight},
				(Vector2){0, 0},
				WHITE);
			DrawFPS(10, 10);
		EndDrawing();

		useBufferA = !useBufferA;
	}

	UnloadShader(diffusionShader);
	UnloadRenderTexture(bufferA);
	UnloadRenderTexture(bufferB);
	CloseWindow();

	for (int i = 0; i < agentCount;i++) {
		free(agents[i]);
	}
	free(agents);

	return 0;
}


