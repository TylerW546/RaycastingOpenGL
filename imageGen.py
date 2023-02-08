import pygame
from pygame.locals import *
from pygame import image

back = image.load("Background.jpeg")

width = 64
height = 64

pygame.font.init()
myfont = pygame.font.SysFont('Arial', 40)

for i in range(16):
    surf = pygame.Surface((width,height), pygame.SRCALPHA, 32)
    surf.blit(back, (0,0))
    
    textsurface = myfont.render(str(i), False, (0,0,0))
    rect = textsurface.get_rect(center=(width//2,height//2))
    surf.blit(textsurface, rect)

    surf = pygame.transform.flip(surf, False, True)
    
    pygame.image.save(surf, "sprites/test_sprite/"+str(i)+".jpg")
