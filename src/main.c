#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define WIDTH 400
#define HEIGHT 400
#define TITLE "Balls and their admirers"
#define BALL_COUNT 100
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 20
#define RADIUS_MIN 5
#define COLOR_COUNT 21

Color COLORS[COLOR_COUNT] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};

// Definition of Ball
// Ball stores state and other properties
// YOUR CODE HERE
typedef struct Ball{
  int posx, posy, velx, vely;
  int radius;
  Color color;
  struct Ball* follows;
} Ball;


Ball balls[BALL_COUNT];

// Initializes a ball with random values
Ball *init_ball_random(Ball *p) {
  // Randomly initialize state and properties
  p->posx = rand() % WIDTH + 0;
  p->posy = rand() % HEIGHT + 0; 
  p->velx = rand() % VEL_MAX + 0;
  p->vely = rand() % VEL_MAX + 0;
  p->radius = rand() % RADIUS_MAX + RADIUS_MIN;
  p->color = COLORS[rand() % COLOR_COUNT + 0];
  p->follows = NULL;

  // Find a leading ball other than the initialized ball itself.
  Ball *leader = &balls[0]; // Represents the leading ball that this ball will follow
  // YOUR CODE HERE
  for (int i = 1; i < BALL_COUNT; i++){
    if (balls[i].radius > leader->radius){
      leader = &balls[i];
    }
  }

  for (int i = 0; i < BALL_COUNT; i++){
    if (&balls[i] != leader){
      balls[i].follows = leader;
    }
    else {
      balls[i].follows = leader;
    }
  }

  return p;
}

// Initialize all `balls`
void init_balls_random() {
  for (int i = 0; i < BALL_COUNT; i++)
  {
    init_ball_random(&balls[i]);
  }
}

Ball *draw_ball(Ball *p) {
  DrawCircle(p->posx, p->posy, p->radius, p->color);
  return p;
}

// Updates the positions of balls according to their velocities
Ball *update_pos(Ball *p) {
  p->posx = (WIDTH + p->posx + p->velx) %
            WIDTH; // `WIDTH +` because C uses truncated division
  p->posy = (HEIGHT + p->posy + p->vely) % HEIGHT;
  return p;
}

// Updates the velocity of a ball so that it follows the leading ball
Ball *update_vel_for_following(Ball *p) {
  int errx = p->follows->posx - p->posx;
  int erry = p->follows->posy - p->posy;
  p->velx = errx > 0 ? 1 : -1;
  p->vely = erry > 0 ? 1 : -1;
  return p;
}

// Update all elements
void update_elements() {
  for (size_t i = 0; i < BALL_COUNT; ++i) {
    draw_ball(update_pos(update_vel_for_following(&balls[i])));
  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  init_balls_random();

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    update_elements();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}