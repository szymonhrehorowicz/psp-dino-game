#include "game/controller_manager.h"
#include "game/player.h"
#include "pspmoduleinfo.h"
#include "pspthreadman.h"
#include "system/exit.h"
#include <memory.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspuser.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Required PSP_MODULE_INFO
PSP_MODULE_INFO("Game", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

// Screen
#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 272
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT BUFFER_HEIGHT

// Textures
typedef struct
{
    float u, v;
    uint32_t colour;
    float x, y, z;
} Texture_Vertex;

typedef struct
{
    int width, height;
    uint32_t *data;
} Texture;

char list[0x20000] __attribute__((aligned(64)));

void *fbp0;
void *fbp1;

void init_gu()
{
    sceGuInit();

    fbp0 = guGetStaticVramBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, GU_PSM_8888);
    fbp1 = guGetStaticVramBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, GU_PSM_8888);

    // Set up buffers
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, BUFFER_WIDTH);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, fbp1, BUFFER_WIDTH);

    // We do not care about the depth buffer in this example
    sceGuDepthBuffer(fbp0, 0);   // Set depth buffer to a length of 0
    sceGuDisable(GU_DEPTH_TEST); // Disable depth testing

    // Set up viewport
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Start a new frame and enable the display
    sceGuFinish();
    sceGuDisplay(GU_TRUE);
}

void end_gu()
{
    sceGuDisplay(GU_FALSE);
    sceGuTerm();
}

void start_frame()
{
    sceGuStart(GU_DIRECT, list);
    sceGuClearColor(0xFFFFFFFF); // White background
    sceGuClear(GU_COLOR_BUFFER_BIT);
}

void end_frame()
{
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}

Texture *load_texture(const char *filename)
{
    Texture *texture = (Texture *)calloc(1, sizeof(Texture));

    texture->data = (uint32_t *)stbi_load(filename, &(texture->width), &(texture->height), NULL, STBI_rgb_alpha);

    // Make sure the texture cache is reloaded
    sceKernelDcacheWritebackInvalidateAll();

    return texture;
}

void draw_texture(Texture *texture, float x, float y, float w, float h)
{
    static Texture_Vertex vertices[2];

    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;
    vertices[0].colour = 0xFFFFFFFF;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0.0f;

    vertices[1].u = w;
    vertices[1].v = h;
    vertices[1].colour = 0xFFFFFFFF;
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].z = 0.0f;

    sceGuTexMode(GU_PSM_8888, 0, 0, GU_FALSE);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
    sceGuTexImage(0, texture->width, texture->height, texture->width, texture->data);

    sceGuEnable(GU_TEXTURE_2D);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
    sceGuDisable(GU_TEXTURE_2D);
}

int main(void)
{
    PS::System::exit_init();
    pspDebugScreenInit();
    init_gu();

    // Controls
    PS::Game::Controller_Manager controller_manager{};

    // Actors
    PS::Game::Player player{};

    // Scene
    Texture *texture = load_texture("grass.png");

    // Signals
    controller_manager.on_button_pressed(PspCtrlButtons::PSP_CTRL_CROSS).connect(&player, &PS::Game::Player::jump);

    while (PS::System::running)
    {
        start_frame();

        draw_texture(texture, SCREEN_WIDTH / 2 - (texture->width / 2), SCREEN_HEIGHT / 2 - (texture->height / 2),
                     static_cast<float>(texture->width), static_cast<float>(texture->height));

        // Update pad
        controller_manager.update();

        end_frame();
    }

    end_gu();
    stbi_image_free(texture->data);
    free(texture);

    return 0;
}