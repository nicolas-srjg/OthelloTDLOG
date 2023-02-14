import pygame
from time import sleep
from pygameTools import *
from bindFunction import *


# init of pygame
pygame.init()
pygame.font.init()

# creation de la font
font1 = pygame.font.SysFont(None, int(window_h/8))
font2 = pygame.font.SysFont(None, int(window_h/15))
font3 = pygame.font.SysFont(None, int(window_h/18))

fonts = [
    font1,
    font2,
    font3
]
# affichage du fond
screen=pygame.display.set_mode((window_w, window_h))
pygame.display.set_caption("OTHELLO")
game_board= scaled_board_image.convert()
#board_shadow=pygame.image.load(path_shadow).convert()

# paht to buttons
b_jcj_p = pygame.image.load("images/b_JCJ.png").convert_alpha()
b_jcia_p = pygame.image.load("images/b_JCIA.png").convert_alpha()
b_facile_p = pygame.image.load("images/b_facile.png").convert_alpha()
b_moyen_p = pygame.image.load("images/b_moyen.png").convert_alpha()
b_difficle_p = pygame.image.load("images/b_difficile.png").convert_alpha()
b_pile_p = pygame.image.load("images/b_pile.png").convert_alpha()
b_face_p = pygame.image.load("images/b_face.png").convert_alpha()
b_point_p = pygame.image.load("images/b_point.png").convert_alpha()
b_replay_p = pygame.image.load("images/b_replay.png").convert_alpha()
b_retmenu_p = pygame.image.load("images/b_retmenu.png").convert_alpha()
b_opt_p = pygame.image.load("images/b_opt.png").convert_alpha()
b_othello_p = pygame.image.load("images/b_othello.png").convert_alpha()
b_play_p = pygame.image.load("images/b_play.png").convert_alpha()
b_forward_p = pygame.image.load("images/b_forward.png").convert_alpha()
b_backward_p = pygame.image.load("images/b_backward.png").convert_alpha()
b_possible_p = pygame.image.load("images/b_possible.png").convert_alpha()
b_exp_p = pygame.image.load("images/b_exp.png").convert_alpha()

# path to collided buttons
bc_jcj_p = pygame.image.load("images/bc_JCJ.png").convert_alpha()
bc_jcia_p = pygame.image.load("images/bc_JCIA.png").convert_alpha()
bc_facile_p = pygame.image.load("images/bc_facile.png").convert_alpha()
bc_moyen_p = pygame.image.load("images/bc_moyen.png").convert_alpha()
bc_difficle_p = pygame.image.load("images/bc_difficile.png").convert_alpha()
bc_pile_p = pygame.image.load("images/bc_pile.png").convert_alpha()
bc_face_p = pygame.image.load("images/bc_face.png").convert_alpha()
bc_replay_p = pygame.image.load("images/bc_replay.png").convert_alpha()
bc_retmenu_p = pygame.image.load("images/bc_retmenu.png").convert_alpha()
bc_opt_p = pygame.image.load("images/bc_opt.png").convert_alpha()
bc_othello_p = pygame.image.load("images/bc_othello.png").convert_alpha()
bc_play_p = pygame.image.load("images/b_pause.png").convert_alpha()
bc_forward_p = pygame.image.load("images/bc_forward.png").convert_alpha()
bc_backward_p = pygame.image.load("images/bc_backward.png").convert_alpha()
bc_possible_p = pygame.image.load("images/bc_possible.png").convert_alpha()
bc_exp_p = pygame.image.load("images/bc_exp.png").convert_alpha()

# creation du plateau
board = Board()
possible_move_board = Board()

# scale used for buttons
b_scale = scale + 0.2

# creation of buttons
b_jcj = Button(int((window_w-bc_jcj_p.get_width()*b_scale)/2), int(window_h/2)-int(1.5*bc_jcj_p.get_height()*b_scale), b_jcj_p, bc_jcj_p, b_scale)
b_jcia = Button(int((window_w-bc_jcia_p.get_width()*b_scale)/2), int(window_h/2)+int(0.5*bc_jcj_p.get_height()*b_scale), b_jcia_p, bc_jcia_p, b_scale)
b_difficle = Button(int((window_w-bc_difficle_p.get_width()*b_scale)/2), int((window_h-bc_difficle_p.get_height()*b_scale)/2)+150, b_difficle_p, bc_difficle_p, b_scale)
b_facile = Button(int((window_w-bc_facile_p.get_width()*b_scale)/2), int((window_h-bc_facile_p.get_height()*b_scale)/2)-150, b_facile_p, bc_facile_p, b_scale)
b_moyen = Button(int((window_w-bc_moyen_p.get_width()*b_scale)/2), int((window_h-bc_moyen_p.get_height()*b_scale)/2), b_moyen_p, bc_moyen_p, b_scale)
b_othello = Button(int((window_w-bc_othello_p.get_width()*2*b_scale)/2), int((window_h-bc_othello_p.get_height()*2*b_scale)/2), b_othello_p, bc_othello_p, 2*b_scale)
b_replay = Button(marge_droite+ image_w + marge_millieu, marge_haute*2, b_replay_p, bc_replay_p, b_scale*0.8)
b_retmenu = Button(marge_droite*0.3, marge_haute*0.2, b_retmenu_p, bc_retmenu_p, b_scale*0.7)
b_opt = Button(marge_droite + marge_millieu + image_w, marge_haute*5.5, b_opt_p, bc_opt_p, b_scale*0.8, True)
b_possible = Button(marge_droite + marge_millieu + image_w, marge_haute*3, b_possible_p, bc_possible_p, b_scale*0.8, True)
b_play = Button(marge_droite + marge_millieu*2 + image_w, marge_haute*4.8, b_play_p, bc_play_p, b_scale*0.7, True)
b_forward = Button(marge_droite + marge_millieu + image_w + marge_millieu*5, marge_haute*4.8, b_forward_p, bc_forward_p, b_scale*0.7)
b_backward = Button(marge_droite + marge_millieu + image_w+ marge_millieu*3, marge_haute*4.8, b_backward_p, bc_backward_p, b_scale*0.7)
b_exp = Button(marge_droite + marge_millieu + image_w, marge_haute*4, b_exp_p, bc_exp_p, b_scale*0.8, True)

# list of buttons
buttons = [
    b_jcj,
    b_jcia,
    b_facile,
    b_moyen,
    b_difficle,
    b_othello,
    b_replay,
    b_retmenu,
    b_opt,
    b_possible,
    b_play,
    b_forward,
    b_backward,
    b_exp
]

# rune the game
run_game(board, screen, game_board, fonts, buttons)