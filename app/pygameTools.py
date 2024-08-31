import pygame
import bindOthello as bi

from pygame.locals import (
    K_ESCAPE,
    KEYDOWN,
    QUIT,
    MOUSEBUTTONDOWN,
)

# used to scale the all window (only parameter to change manualy)
scale = 0.7


#path = "PlateauOthello.png"
path_board = "plateau_800_800.png"
path_shadow = "ombre_plateau_800.png"
board_image = pygame.image.load(path_board)
scaled_board_image = pygame.transform.scale(board_image, (int(board_image.get_width()*scale), int(board_image.get_height()*scale)))
image_h,image_w = scaled_board_image.get_size()
#shadow_h,shadow_w = pygame.image.load(path_shadow).get_size()



#pourcentage des marges
marge_basse = 0.1*image_h
marge_haute = 0.2*image_h
marge_gauche = 0.1*image_w
marge_millieu = 0.1*image_w
marge_droite = 0.1*image_w
taille_menu = 0.8*image_w

#taille de la femetre complete
window_w = marge_gauche+marge_droite+marge_millieu+taille_menu+image_w
window_h = marge_haute+marge_basse+image_h

nbr_case = 8
case_size = image_w/nbr_case
piece_size = image_w/20
optimal_move_size = image_w/35

case_colors = [(220,220,220),(20,20,20),(100,160,100),(200, 200, 200), (220, 50, 50), (50, 220, 50)]

class Case:
    def __init__(self, x0, y0):

        #sprite of the case
        self.surf = pygame.Surface((case_size,case_size))
        self.rect = self.surf.get_rect()

        self.rect.x=x0
        self.rect.y=y0

    def print_case(self, screen, color):
        if color == 1:
            pygame.draw.circle(screen,case_colors[0],self.rect.center, piece_size)
        elif color == -1:
            pygame.draw.circle(screen, case_colors[1], self.rect.center, piece_size)
        elif color == 10:
            pygame.draw.circle(screen, case_colors[2], self.rect.center, piece_size)
        elif color == 11:
            pygame.draw.circle(screen, (190,60,60), self.rect.center, optimal_move_size)

class Board:
    def __init__(self):
        self.cases = []
        self.colors = [0]*nbr_case*nbr_case

        for i in range(nbr_case):
            for j in range(nbr_case):
                x_ij = marge_gauche + j * image_h / nbr_case
                y_ij = marge_haute + i * image_w / nbr_case
                case_i = Case(x_ij, y_ij)
                self.cases.append(case_i)

        self.colors[27] = 1
        self.colors[28] = -1
        self.colors[35] = -1
        self.colors[36] = 1

    def print_board(self,screen):
        for case in range(len(self.cases)):
            self.cases[case].print_case(screen, self.colors[case])

class Button:
    def __init__(self, x, y, image, imagec, scale, stay_pressed = False):
        self.stay_pressed = stay_pressed
        w = image.get_width()
        h = image.get_height()
        self.image = image
        self.imagec = imagec
        self.image = pygame.transform.scale(image, (int(w*scale), int(h*scale)))
        self.imagec = pygame.transform.scale(imagec, (int(w * scale), int(h * scale)))
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)
        self.clicked = False
        self.collide = False

    def draw(self, screen):
        action = False
        #pos of mouse
        pos = pygame.mouse.get_pos()

        self.collide = False
        if self.rect.collidepoint(pos):
            self.collide = True

            if pygame.mouse.get_pressed()[0] == 1 and not self.clicked:
                self.clicked = True
                action = True
            elif pygame.mouse.get_pressed()[0] == 1 and self.clicked and self.stay_pressed:
                self.clicked = False
                action = False


        if pygame.mouse.get_pressed()[0] == 0 and not self.stay_pressed:
            self.clicked = False

        #print the button on the screen
        if self.collide or self.clicked:
            screen.blit(self.imagec, self.rect.topleft)
        else:
            screen.blit(self.image, self.rect.topleft)
        if self.clicked and self.stay_pressed:
            return True
        return action

# commands to quit the game
def quitCommand(event):
    if event.type == KEYDOWN:
        if event.key == K_ESCAPE:
            return False

    elif event.type == QUIT:
        return False

    return True


