import pygame
from OthelloTDLOG.app.pygameTools import *
from time import sleep

def show_possible_moves(cpp_board, screen):
    if cpp_board.getCurrPlayer().isHuman():
        list_of_moves = bi.getListOfPossibleMoves(cpp_board)
        for move in range(len(list_of_moves)):
            case_to_show = Case(marge_gauche + (list_of_moves[move].getCol() - 1) * image_h / nbr_case,
                                marge_haute + (list_of_moves[move].getRow() - 1) * image_w / nbr_case)
            case_to_show.print_case(screen, 10)


def play_current_turn(board, screen, cpp_board, valid_move, backward_board):
    turn_played = False

    if cpp_board.cannotPlay():
        cpp_board.nextPlayer()

    if cpp_board.getCurrPlayer().isHuman() and pygame.mouse.get_pressed()[0]==1:
        potential_move = bi.Move(1, 1)
        for case in range(len(board.cases)):
            if board.cases[case].rect.collidepoint(pygame.mouse.get_pos()):
                potential_move.setCol(case % 8 + 1)
                potential_move.setRow(int(case / 8) + 1)

        left_border = pygame.mouse.get_pos()[0] >= marge_gauche
        right_border = pygame.mouse.get_pos()[0] <= marge_gauche + image_w
        up_border = pygame.mouse.get_pos()[1] >= marge_haute
        down_border = pygame.mouse.get_pos()[1] <= marge_haute + image_h
        click_inside_board = left_border and right_border and up_border and down_border

        val_move = False
        list_of_moves = bi.getListOfPossibleMoves(cpp_board)

        for move in range(len(list_of_moves)):
            if potential_move.getRow() == list_of_moves[move].getRow() and potential_move.getCol() == list_of_moves[move].getCol():
                val_move = True
        if val_move:
            cpp_board.refresh(potential_move)
            cpp_board.nextPlayer()
            backward_board.append(cpp_board.deepCopy())
            board.colors = bi.get_grid(cpp_board)
            return True
        elif not val_move and click_inside_board:
            return False
        turn_played = True

    if not cpp_board.getCurrPlayer().isHuman() and not turn_played:
        if 'r' == cpp_board.getCurrPlayer().getDifficulty():
            cpp_board.refresh(bi.random_move(cpp_board))
            backward_board.append(cpp_board.deepCopy())
            board.colors = bi.get_grid(cpp_board)
        else:
            if 'e' == cpp_board.getCurrPlayer().getDifficulty():
                minimax_depth = 3
            else:
                minimax_depth = 8

            move_to_do = bi.Move(1, 1)
            bi.minimax(cpp_board, minimax_depth, -1e8, 1e8, cpp_board.getCurrPlayer(), minimax_depth, move_to_do)
            cpp_board.refresh(move_to_do)
            backward_board.append(cpp_board.deepCopy())
            board.colors = bi.get_grid(cpp_board)
        cpp_board.nextPlayer()

    return valid_move


def run_game(board, screen, game_board, fonts, buttons):
    p1 = bi.Player('black', True)
    p2 = bi.Player('white', True)
    cpp_board = bi.Board(p1, p2)


    do_show_possible_moves = True

    running = True
    menu0 = True
    menu1 = False
    menu2 = False
    gaming = False

    valid_move = True
    winner = 0
    pause = False

    click = False
    optimal = False

    backward_board = []
    forward_board = []
    stored = False
    previous_player_color = p1.getColor()
    current_player = p1.getColor()

    while running:
        click = pygame.mouse.get_pressed()[0]==1
        for event in pygame.event.get():
            # quit the game if needed
            running = quitCommand(event)
        pygame.event.clear()

        while running and not click:
            for event in pygame.event.get():
                # quit the game if needed
                running = quitCommand(event)
                if event.type == MOUSEBUTTONDOWN:
                    click = pygame.mouse.get_pressed()[0] == 1
            pygame.event.clear()

            current_player = cpp_board.getCurrPlayer().getColor()

            # fill the background with white
            screen.fill(case_colors[0])

            if menu2:
                # print the 3 buttons on the screen to chose the difficulty
                easy = buttons[2].draw(screen)
                mid = buttons[3].draw(screen)
                hard = buttons[4].draw(screen)
                if easy or mid or hard:
                    difficulty = ""
                    if easy:
                        difficulty = "r"
                    elif mid:
                        difficulty = "e"
                    elif hard:
                        difficulty = "h"
                    menu2 = False
                    gaming = True
                    p1 = bi.Player('black', True)
                    p2 = bi.Player('white', False, difficulty)
                    cpp_board = bi.Board(p1, p2)
                    backward_board = [cpp_board.deepCopy()]
                    board.colors = bi.get_grid(cpp_board)

            if gaming:
                # show the chat surface
                chat_surf = pygame.Surface((taille_menu, 0.8 * marge_haute))
                chat_surf.fill(case_colors[3])
                screen.blit(chat_surf, (marge_gauche + marge_millieu + image_w, marge_haute))

                if winner == 0:
                    current_player_color = "blanc"
                    if current_player == -1:
                        current_player_color = "noir"
                    if not pause:
                        print_current_player = fonts[2].render(f"tour {current_player_color}", True, (50, 50, 50))
                    else:
                        print_current_player = fonts[2].render(f"tour {current_player_color} (jeu en pause)", True,
                                                               (50, 50, 50))
                    screen.blit(print_current_player, (marge_gauche * 1.1 + marge_millieu + image_w, marge_haute * 1.5))

                    if not pause:
                    # test if player can play or if the game is finished
                        if cpp_board.stopGame():
                            if cpp_board.winner():
                                winner = cpp_board.getCurrPlayer()
                            else:
                                winner = cpp_board.getOtherPlayer()
                        if winner == 0:
                            valid_move = play_current_turn(board, screen, cpp_board, valid_move, backward_board)


                # print the board
                screen.blit(game_board, (marge_gauche, marge_haute))
                board.print_board(screen)

                # show the return to menu button
                return_menu = buttons[7].draw(screen)
                if return_menu:
                    buttons[13].clicked = False
                    gaming = False
                    menu1 = True

                # bouton d'entrainement
                exp = buttons[13].draw(screen)
                if not exp:
                    buttons[10].clicked = True
                if exp:
                    pause = buttons[10].draw(screen)
                    forward = buttons[11].draw(screen)
                    backward = buttons[12].draw(screen)
                    optimal = buttons[8].draw(screen)

                    if backward and len(backward_board)>1:
                        buttons[10].clicked = True

                        forward_board.append(backward_board.pop(-1))
                        cpp_board = backward_board[-1].deepCopy()
                        board.colors = bi.get_grid(cpp_board)
                        winner = 0

                    elif forward and len(forward_board)!=0:
                        backward_board.append(forward_board.pop(-1))
                        cpp_board = backward_board[-1].deepCopy()
                        board.colors = bi.get_grid(cpp_board)

                    if not pause:
                        forward_board = []


                do_show_possible_moves = buttons[9].draw(screen)
                # show possible moves for the player
                if do_show_possible_moves:
                    show_possible_moves(cpp_board, screen)

                if stored:
                    stored = previous_player_color == current_player

                if optimal and not stored:
                    minimax_depth = 7
                    move_to_do = bi.Move(1, 1)
                    bi.minimax(cpp_board, minimax_depth, -1e8, 1e8, cpp_board.getCurrPlayer(), minimax_depth,move_to_do)
                    case_move_to_do = Case(marge_gauche + (move_to_do.getCol() - 1) * image_h / nbr_case,
                         marge_haute + (move_to_do.getRow() - 1) * image_w / nbr_case)
                    stored = True
                    previous_player_color = cpp_board.getCurrPlayer().getColor()

                if optimal:
                    case_move_to_do.print_case(screen, 11)

                # show the winner
                if winner != 0:
                    winner_color = ""
                    winner_txt_color = (190,80,80)
                    if winner.isHuman():
                        winner_txt_color = (80, 170, 80)
                    if winner.getColor()==1:
                        winner_color = "blanc"
                    else:
                        winner_color = "noir"
                    if not winner.getColor() == cpp_board.getCurrPlayer().getColor():
                        cpp_board.nextPlayer()

                    count_winner = cpp_board.countColor()
                    cpp_board.nextPlayer()
                    count_loser = cpp_board.countColor()
                    cpp_board.nextPlayer()

                    if not winner.getColor() == cpp_board.getCurrPlayer().getColor():
                        cpp_board.nextPlayer()

                    txt_winner = fonts[1].render(f"Joueur {winner_color} à gagné avec", True, winner_txt_color)
                    txt_winner2 = fonts[1].render(f"{count_winner} pièces contre {count_loser}", True, winner_txt_color)
                    screen.blit(txt_winner, (marge_gauche * 1.1 + marge_millieu + image_w, marge_haute * 1.1))
                    screen.blit(txt_winner2, (marge_gauche * 1.1 + marge_millieu + image_w, marge_haute * 1.5))

                    replay = buttons[6].draw(screen)
                    if replay:
                        buttons[13].clicked = False
                        cpp_board = bi.Board(p1, p2)
                        backward_board = [cpp_board.deepCopy()]
                        forward_board = []
                        board.colors = bi.get_grid(cpp_board)
                        winner = 0

                if winner == 0:
                    # show if a move is invalid on the chat surface
                    if not valid_move and not pause:
                        txt_inval_move = fonts[1].render("Coup invalide", True, (170,80,80))
                        screen.blit(txt_inval_move, (marge_gauche * 1.1 + marge_millieu + image_w, marge_haute * 1.1))


                # print title OTHELLO
                txt = fonts[0].render("OTHELLO", True, case_colors[1])
                screen.blit(txt, (marge_gauche + image_w +marge_millieu, marge_haute*0.3))

            if menu1:
                jcj = buttons[0].draw(screen)
                jcia = buttons[1].draw(screen)
                winner = 0

                if jcj:
                    screen.fill(case_colors[0])
                    menu1 = False
                    gaming = True
                    p1 = bi.Player('black', True)
                    p2 = bi.Player('white', True)
                    cpp_board = bi.Board(p1, p2)

                    backward_board = [cpp_board.deepCopy()]
                    board.colors = bi.get_grid(cpp_board)

                elif jcia:
                    menu1 = False
                    menu2 = True

            if menu0:
                othello = buttons[5].draw(screen)
                if othello:
                    menu0 = False
                    menu1 = True

            pygame.display.flip()
