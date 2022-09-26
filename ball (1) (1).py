import sys
import pygame

def fix_path(p):
    import os
    return os.path.dirname(os.path.realpath(__file__)) + "/" + p

pygame.init()

width = 980
height = 720
window_size = (width, height)

screen = pygame.display.set_mode(window_size)

ball_image = pygame.image.load(fix_path("blue1.png")).convert()
ball_image1 = pygame.image.load(fix_path("green1.png")).convert()
ball_image2 = pygame.image.load(fix_path("red1.png")).convert()

ball_rect = ball_image.get_rect()
print("Ball rect:", ball_rect)
ball_rect1 = ball_image1.get_rect()
print("Ball rect:", ball_rect1)
ball_rect2 = ball_image2.get_rect()
print("Ball rect:", ball_rect2)


clock = pygame.time.Clock()

velocity = pygame.Vector2(15, 9)
velocity1 = pygame.Vector2(8, 18)
velocity2 = pygame.Vector2(12,5)
gravity = 0.7
friction = 1

color = pygame.Color(255, 255, 255)

while True:

    for event in pygame.event.get():
        
        if event.type == pygame.QUIT:
            sys.exit()

    
    ball_rect = ball_rect.move(velocity)
    ball_rect1 = ball_rect1.move(velocity1)
    ball_rect2 = ball_rect2.move(velocity2)

    if ball_rect.left < 0 or ball_rect.right > width:
        velocity.x = -(velocity.x * friction)
   
    if ball_rect.top < 0 or ball_rect.bottom > height:
        velocity.y = -velocity.y

    if ball_rect1.left < 0 or ball_rect1.right > width:
        velocity1.x = -(velocity1.x * friction)
        
    if ball_rect1.top < 0 or ball_rect1.bottom > height:
        velocity1.y = -velocity1.y
        
    if ball_rect2.left < 0 or ball_rect2.right > width:
        velocity2.x = -(velocity1.x * friction)

    if ball_rect2.top < 0 or ball_rect2.bottom > height:
        velocity2.y = -velocity2.y
    
    screen.fill(color)

    screen.blit(ball_image, ball_rect)
    screen.blit(ball_image1, ball_rect1)
    screen.blit(ball_image2, ball_rect2)
  
    pygame.display.flip()

    velocity.y += gravity
    velocity1.y += gravity
    velocity2.y += gravity

    clock.tick(60)
