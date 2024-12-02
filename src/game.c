
#include "cub3D.h"
#include <math.h>
#include <stdio.h>
#define MOVE_SPEED 0.20
#define ROT_SPEED 0.10

int key_press(int keycode, t_game *game) {
    double newX, newY, oldDirX, oldPlaneX;

    // ESC tuşuna basıldığında oyun kapatılacak
    if (keycode == 53) {
        mlx_destroy_window(game->mlx.mlx, game->mlx.win_ptr);
        exit(0);
    }

    // Move forward (keycode 13 -> W)
    if (keycode == 13 || keycode == 2) {
        newX = game->map.player.pos.x + game->map.player.dir.x * MOVE_SPEED;
        newY = game->map.player.pos.y + game->map.player.dir.y * MOVE_SPEED;
        if (game->map.map[(int)newY][(int)newX] == '0') {
            game->map.player.pos.x = newX;
            game->map.player.pos.y = newY;
        }
    }

    // Move backward (keycode 1 -> S)
    if (keycode == 1 || keycode == 0) {
        newX = game->map.player.pos.x - game->map.player.dir.x * MOVE_SPEED;
        newY = game->map.player.pos.y - game->map.player.dir.y * MOVE_SPEED;
        if (game->map.map[(int)newY][(int)newX] == '0') {
            game->map.player.pos.x = newX;
            game->map.player.pos.y = newY;
        }
    }

    // Rotate left (keycode 0 -> A or Left Arrow -> 123)
    if (keycode == 0 || keycode == 123) {
        oldDirX = game->map.player.dir.x;
        game->map.player.dir.x = game->map.player.dir.x * cos(ROT_SPEED) - game->map.player.dir.y * sin(ROT_SPEED);
        game->map.player.dir.y = oldDirX * sin(ROT_SPEED) + game->map.player.dir.y * cos(ROT_SPEED);
        oldPlaneX = game->map.player.plane.x;
        game->map.player.plane.x = game->map.player.plane.x * cos(ROT_SPEED) - game->map.player.plane.y * sin(ROT_SPEED);
        game->map.player.plane.y = oldPlaneX * sin(ROT_SPEED) + game->map.player.plane.y * cos(ROT_SPEED);
    }

    // Rotate right (keycode 2 -> D or Right Arrow -> 124)
    if (keycode == 2 || keycode == 124) {
        oldDirX = game->map.player.dir.x;
        game->map.player.dir.x = game->map.player.dir.x * cos(-ROT_SPEED) - game->map.player.dir.y * sin(-ROT_SPEED);
        game->map.player.dir.y = oldDirX * sin(-ROT_SPEED) + game->map.player.dir.y * cos(-ROT_SPEED);
        oldPlaneX = game->map.player.plane.x;
        game->map.player.plane.x = game->map.player.plane.x * cos(-ROT_SPEED) - game->map.player.plane.y * sin(-ROT_SPEED);
        game->map.player.plane.y = oldPlaneX * sin(-ROT_SPEED) + game->map.player.plane.y * cos(-ROT_SPEED);
    }

    raycast(game);
    return 0;
}

void verLine(t_game *game, int x, int drawStart, int drawEnd, t_color_p color)
{
    int y;
    y = 0;
    while (y < SCREEN_HEIGHT)
    {
        if (y >= drawStart && y <= drawEnd)
            ft_put_pixel(game, x, y, color);  // Dikey çizgi renkli olacak
        else if (y < drawStart)
            ft_put_pixel(game, x, y, game->ceiling);  // Ekranın üst kısmı tavan renginde
        else
            ft_put_pixel(game, x, y, game->floor);  // Ekranın alt kısmı zemin renginde
        y++;
    }
}
t_color_p wallColors[] = 
{
    {0, 0, 150, 0},
    {0, 0, 150, 0},
    {0, 0, 150, 0},
    {0, 0, 150, 0},
    {0, 0, 150, 0}
};

// t_color_p get_wall_color(wallColors)
t_color_p get_wall_color(void)
{
    return wallColors[0];
    // if (wallType >= 1 && wallType <= 4)
    //     return wallColors[wallType - 1];
    // else
    //     return wallColors[4]; 
}

void raycast(t_game *game)
{
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        game->hit = 0; 
        game->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        game->rayDirX = game->map.player.dir.x + game->map.player.plane.x * game->cameraX;
        game->rayDirY = game->map.player.dir.y + game->map.player.plane.y * game->cameraX;
        game->rayMapX = (int)game->map.player.pos.x;
        game->rayMapY = (int)game->map.player.pos.y;

        game->deltaDistX = (game->rayDirX == 0) ? 1e30 : fabs(1 / game->rayDirX);
        game->deltaDistY = (game->rayDirY == 0) ? 1e30 : fabs(1 / game->rayDirY);

        if (game->rayDirX < 0)
        {
            game->stepX = -1;
            game->sideDistX = (game->map.player.pos.x - game->rayMapX) * game->deltaDistX;
        }
        else
        {
            game->stepX = 1;
            game->sideDistX = (game->rayMapX + 1.0 - game->map.player.pos.x) * game->deltaDistX;
        }

        if (game->rayDirY < 0)
        {
            game->stepY = -1;
            game->sideDistY = (game->map.player.pos.y - game->rayMapY) * game->deltaDistY;
        }
        else
        {
            game->stepY = 1;
            game->sideDistY = (game->rayMapY + 1.0 - game->map.player.pos.y) * game->deltaDistY;
        }

        while (game->hit == 0)
        {
            if (game->sideDistX < game->sideDistY)
            {
                game->sideDistX += game->deltaDistX;
                game->rayMapX += game->stepX;
                game->side = 0;
            }
            else
            {
                game->sideDistY += game->deltaDistY;
                game->rayMapY += game->stepY;
                game->side = 1;
            }

            if (game->rayMapX < 0 || game->rayMapY < 0 ||
                game->rayMapX >= game->map.map_width || game->rayMapY >= game->map.row)
            {
                game->hit = 1;
                break;
            }

            if (game->map.map[game->rayMapY][game->rayMapX] == '1')
                game->hit = 1;
        }

        if (game->side == 0)
            game->perpWallDist = game->sideDistX - game->deltaDistX;
        else
            game->perpWallDist = game->sideDistY - game->deltaDistY;

        game->lineHeight = (int)(SCREEN_HEIGHT / game->perpWallDist);
        game->drawStart = (-game->lineHeight / 2) + (SCREEN_HEIGHT / 2);
        if (game->drawStart < 0)
            game->drawStart = 0;
        game->drawEnd = (game->lineHeight / 2) + (SCREEN_HEIGHT / 2);
        if (game->drawEnd >= SCREEN_HEIGHT)
            game->drawEnd = SCREEN_HEIGHT - 1;

        
        int wallType;
        wallType = 0;
        if (game->rayMapX >= 0 && game->rayMapX < game->map.map_width &&
            game->rayMapY >= 0 && game->rayMapY < game->map.row)
                wallType = game->map.map[game->rayMapY][game->rayMapX] - '0';
        game->wallColor = get_wall_color();
        // game->wallColor = get_wall_color(wallType);
        if (game->side == 1)
        {
            game->wallColor.red /= 2;
            game->wallColor.green /= 2;
            game->wallColor.blue /= 2;
        }
        verLine(game, x, game->drawStart, game->drawEnd, game->wallColor);
    }
    // FPS Hesaplaması
    gettimeofday(&endTime, NULL); // Frame bitiminde zamanı alıyoruz
    game->frameTime = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0; // Her frame arasındaki süre hesabı
    game->fps = 1.0 / game->frameTime; // FPS hesaplama
    printf("FPS: %.2f\n", game->fps);

    double moveSpeed;
    moveSpeed = game->frameTime * 5.0; // Hareket hızı (kare/saniye cinsinden)
    double rotSpeed;
    rotSpeed = game->frameTime * 3.0;  // Dönüş hızı (radyan/saniye cinsinden)
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win_ptr, game->mlx.img.img, 0, 0); // ile render
    mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
    mlx_loop(game->mlx.mlx);
    mlx_clear_window(game->mlx.mlx, game->mlx.win_ptr);
}
void ft_put_pixel(t_game *game, int x, int y, t_color_p color)
{
    game->mlx.img.pixels[y * SCREEN_WIDTH + x] = color;
}
void draw_background(t_game *game)
{
    int x;
    int y;
    t_color_p color;
    x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            if (y < SCREEN_HEIGHT / 2)
                color = game->ceiling;
            else
                color = game->floor;
            ft_put_pixel(game, x, y, color);
            y++;
        }
        x++;
}
}

int	start_game(void *param)
{
    t_game *game;
    game = (t_game *)param;
    
    game->floor.red = 144;
    game->floor.green = 238;
    game->floor.blue = 144;
    game->floor.alpha = 0;

    game->ceiling.red = 173;
    game->ceiling.green = 216;
    game->ceiling.blue = 230;
    game->ceiling.alpha = 0;
    // printf("Floor Color: %d, %d, %d\n", game->floor.red, game->floor.green, game->floor.blue);
    // printf("Ceiling Color: %d, %d, %d\n", game->ceiling.red, game->ceiling.green, game->ceiling.blue);
    // printf("Floor: %d, %d, %d\n", game->map.texture.F.R, game->map.texture.F.G, game->map.texture.F.B);
    // printf("Ceiling: %d, %d, %d\n", game->map.texture.C.R, game->map.texture.C.G, game->map.texture.C.B);

    game->map.player.pos.x = 9.0;
    game->map.player.pos.y = 11.0;
    game->map.player.dir.x = -1;
    game->map.player.dir.y = 0;
    game->map.player.plane.x = 0;
    game->map.player.plane.y = 0.66;
    game->time = 0;
    game->oldTime = 0;

    draw_background(game);
    game->hit = 0;
    raycast(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win_ptr, game->mlx.img.img, 0, 0); //render edilen raycast görüntüsünü ekrana yerleştirmek için


    return (0);
}