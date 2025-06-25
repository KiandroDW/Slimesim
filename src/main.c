#include "agent.h"
#include "raylib.h"
#include "consts.h"
#include <stdlib.h>

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Slime Diffusion Simulator");
    SetTargetFPS(60);

RenderTexture2D bufferA = LoadRenderTexture(WIDTH, HEIGHT);
RenderTexture2D bufferB = LoadRenderTexture(WIDTH, HEIGHT);

// Set filtering for both
SetTextureFilter(bufferA.texture, TEXTURE_FILTER_POINT);
SetTextureFilter(bufferB.texture, TEXTURE_FILTER_POINT);

    Shader diffusionShader = LoadShader(0, "shaders/diffusion.fs");

    Vector2 resolution = { WIDTH, HEIGHT };
    SetShaderValue(diffusionShader, GetShaderLocation(diffusionShader, "resolution"), &resolution, SHADER_UNIFORM_VEC2);

	Agent** agents = malloc(AGENTCOUNT * sizeof(Agent));
	for (int i = 0; i < AGENTCOUNT; i++) {
		agents[i] = initAgent((Vector2) {400, 400}, (float)rand()/(float)RAND_MAX * 2 * PI);
	}

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
				Vector2 res = { WIDTH, HEIGHT };
				SetShaderValue(diffusionShader, GetShaderLocation(diffusionShader, "resolution"), &res, SHADER_UNIFORM_VEC2);

				// Draw full screen quad
				DrawTextureRec(
					(useBufferA ? bufferA : bufferB).texture,
					(Rectangle){0, 0, (float)WIDTH, -(float)HEIGHT},
					(Vector2){0, 0},
					WHITE);

			EndShaderMode();
			for (int i = 0; i < AGENTCOUNT; i++) {
				DrawPixel(agents[i]->position.x, agents[i]->position.y, WHITE);
				updateAgent(agents[i]);
			}
		EndTextureMode();

		// Draw the current buffer to screen
		BeginDrawing();
			ClearBackground(BLACK);

			DrawTextureRec(
				(useBufferA ? bufferB : bufferA).texture,
				(Rectangle){0, 0, (float)WIDTH, -(float)HEIGHT},
				(Vector2){0, 0},
				WHITE);
		EndDrawing();

		useBufferA = !useBufferA;
	}

	UnloadShader(diffusionShader);
	UnloadRenderTexture(bufferA);
	UnloadRenderTexture(bufferB);
	CloseWindow();

	return 0;
}


