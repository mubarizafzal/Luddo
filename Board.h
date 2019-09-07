#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>

#ifndef BOARD_H
#define BOARD_H

Fl_Button* start_button;
Fl_Button* next_button;
Fl_Button* roll_button;
Fl_Window* my_window;
Fl_Box* m_board;


class Board : public Fl_Box {

public:

  C_Player comps[3];

  H_Player human;

  bool choosing = false;

  bool attacking = false;

  bool game_over = false;

  int attack_i, attack_j;

  int base_tiles[4][18] = {
    {0 + 80, 460 + 80, 0 + 80, 460 + 160, 0 + 160, 460 + 80, 0 + 160, 460 + 160, 240 + 60, 700 - 60,240 + 60, 700 - 100,240 + 60, 700 - 140,240 + 60, 700 - 180,240 + 60, 700 - 220},
    {0 + 80, 100 + 80, 0 + 160, 100 + 80, 0 + 80, 100 + 160, 0 + 160, 100 + 160, 240 - 180, 700 - 300, 240 - 140, 700 - 300, 240 - 100, 700 - 300, 240 - 60, 700 - 300, 240 - 20, 700 - 300},
    {360 + 80, 100 + 80, 360 + 160, 100 + 80, 360 + 80, 100 + 160, 360 + 160, 100 + 160, 240 + 60, 700 - 540, 240 + 60, 700 - 500, 240 + 60, 700 - 460, 240 + 60, 700 - 420, 240 + 60, 700 - 380},
    {360 + 80, 460 + 80, 360 + 160, 460 + 80, 360 + 80, 460 + 160, 360 + 160, 460 + 160, 240 + 300, 700 - 300, 240 + 260, 700 - 300, 240 + 220, 700 - 300, 240 + 180, 700 - 300, 240 + 140, 700 - 300}
  };

  int board_tiles[52][2] = {
    {240 + 20, 700 - 60},
    {240 + 20, 700 - 100},
    {240 + 20, 700 - 140},
    {240 + 20, 700 - 180},
    {240 + 20, 700 - 220},
    {240 - 20, 700 - 260},
    {240 - 60, 700 - 260},
    {240 - 100, 700 - 260},
    {240 - 140, 700 - 260},
    {240 - 180, 700 - 260},
    {240 - 220, 700 - 260},
    {240 - 220, 700 - 300},
    {240 - 220, 700 - 340},
    {240 - 180, 700 - 340},
    {240 - 140, 700 - 340},
    {240 - 100, 700 - 340},
    {240 - 60, 700 - 340},
    {240 - 20, 700 - 340},
    {240 + 20, 700 - 380},
    {240 + 20, 700 - 420},
    {240 + 20, 700 - 460},
    {240 + 20, 700 - 500},
    {240 + 20, 700 - 540},
    {240 + 20, 700 - 580},
    {240 + 60, 700 - 580},
    {240 + 100, 700 - 580},
    {240 + 100, 700 - 540},
    {240 + 100, 700 - 500},
    {240 + 100, 700 - 460},
    {240 + 100, 700 - 420},
    {240 + 100, 700 - 380},
    {240 + 140, 700 - 340},
    {240 + 180, 700 - 340},
    {240 + 220, 700 - 340},
    {240 + 260, 700 - 340},
    {240 + 300, 700 - 340},
    {240 + 340, 700 - 340},
    {240 + 340, 700 - 300},
    {240 + 340, 700 - 260},
    {240 + 300, 700 - 260},
    {240 + 260, 700 - 260},
    {240 + 220, 700 - 260},
    {240 + 180, 700 - 260},
    {240 + 140, 700 - 260},
    {240 + 100, 700 - 220},
    {240 + 100, 700 - 180},
    {240 + 100, 700 - 140},
    {240 + 100, 700 - 100},
    {240 + 100, 700 - 60},
    {240 + 100, 700 - 20},
    {240 + 60, 700 - 20},
    {240 + 20, 700 - 20}
  };

  Board (int x, int y, int w, int h) : Fl_Box(x, y, w, h) {


  }

  int handle (int event) {


    if (event == FL_PUSH) {

      int x = Fl::event_x();
      int y = Fl::event_y();


      if (human.id < 0) {

        if (x >= this->x() && x <= this->x()+240 && y >= this->y()+360 && y<= this->y()+600) {

          human.set_player(0, 0, 0, 460, 237, 204, 19);
          std::cout << "Chosen Yellow" << "\n";
        }
        if (x >= this->x() && x <= this->x()+240 && y >= this->y() && y<= this->y()+240) {

          human.set_player(1, 13, 0, 100, 19, 117, 237);
          std::cout << "Chosen Blue" << "\n";
        }
        if (x >= this->x()+360 && x <= this->x()+600 && y >= this->y() && y<= this->y()+240) {

          human.set_player(2, 26, 360, 100, 237, 37, 19);
          std::cout << "Chosen Red" << "\n";
        }
        if (x >= this->x()+360 && x <= this->x()+600 && y >= this->y()+360 && y<= this->y()+600) {

          human.set_player(3, 39, 360, 460, 67, 219, 33);
          std::cout << "Chosen Green" << "\n";
        }

        // if chosen has actually been selected change message board
        if (human.id >= 0) {
          set_comps();
          m_board->label("Click on 'Roll' to get your dice roll");
        }

        roll_button->activate();
        next_button->activate();
      } else {

        if (!choosing) {

          if (selected()) {

            choosing = true;
          }
        } else {

          // can just do valid_move() and choosing = false;
          valid_move();
          choosing = false;
        }


      }
      redraw();
    }
  }


  void set_comps () {


    int n = 0;

    for (int i = 0; i < 4; i++) {


      if (i == human.id) {
        continue;
      } else {
        if (i == 0) {
          comps[n].set_player(i, 0, 0, 460, 237, 204, 19);

        } else if (i == 1) {
          comps[n].set_player(i, 13, 0, 100, 19, 117, 237);

        } else if (i == 2) {
          comps[n].set_player(i, 26, 360, 100, 237, 37, 19);

        } else if (i == 3) {
          comps[n].set_player(i, 39, 360, 460, 67, 219, 33);

        }
        n++;
      }
    }
  }

  // valid move is what determines whether your piece can move or not, so it contains all the game rules and positioning, and thus is a large function
  // also makes the movement if it is a valid move

  void valid_move () {

    int x, y;
    // temp is used for calculating correct positions, in various parts of this function
    int temp;
    int m_x = Fl::event_x();
    int m_y = Fl::event_y();

    if (human.piece_pos < 0) {

      if (human.piece_pos < -4) {

        temp = human.piece_pos*-1 -1;

        for (int& die : human.die_rolls) {

          if (die == 0) {
            continue;
          }

          if (temp + die < 9) {

            x = base_tiles[human.id][(temp + die)*2];
            y = base_tiles[human.id][(temp + die)*2 + 1];

            if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

              if (!contains_piece((temp + die + 1)*-1, &human)) {

                human.pieces[human.working_piece] = (temp + die + 1)*-1;
                die = 0;
                my_window->redraw();
                return;
              }
            }

          } else if (temp + die == 9) {

            if (m_x >= 240 && m_x <= 460 && m_y >= 340 && m_y <= 560) {

              human.pieces[human.working_piece] = -10;

              if (winner(&human)) {

                roll_button->deactivate();
                next_button->deactivate();
                m_board->label("Game Over! - Click 'new game' to restart.");

              }
              die = 0;
              my_window->redraw();
              return;
            }
          }
        }

      } else {

        x = board_tiles[human.id*13][0];
        y = board_tiles[human.id*13][1];

        for (int& die : human.die_rolls) {

          if (die == 6) {

            if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

              if (!contains_piece(human.id*13, &human)) {

                human.pieces[human.working_piece] = human.id*13;
                die = 0;
                my_window->redraw();
                return;
              }
            }
          }
        }

      }

    } else {

      int end_point = (human.id*13 - 1 + 52) % 52;

      for (int& die : human.die_rolls) {

        if (die == 0) {
          continue;
        }

        temp = human.piece_pos + die;

        if ((end_point - human.piece_pos) <= 6 && (end_point - human.piece_pos) > 0 && (end_point - temp) <= 0) {

          temp = temp % 52;
          int temp2;

          // temp2 is the values of the exit tiles
          if (human.id == 0 && temp != end_point) {
            temp2 = temp + 5;
          } else {
            temp2 = temp - end_point + 4;
          }

          if (temp2 <= 8) {

            x = base_tiles[human.id][temp2*2];
            y = base_tiles[human.id][temp2*2 + 1];

            if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

              if (!contains_piece((temp2 + 1)*-1, &human)) {

                human.pieces[human.working_piece] = (temp2 + 1)*-1;
                die = 0;
                my_window->redraw();
                return;
              }
            }

          } else if (temp2 == 9) {

            if (m_x >= 240 && m_x <= 460 && m_y >= 340 && m_y <= 560) {

              human.pieces[human.working_piece] = -10;

              if (winner(&human)) {

                roll_button->deactivate();
                next_button->deactivate();
                m_board->label("Game Over! - Click 'new game' to restart.");

              }
              die = 0;
              my_window->redraw();
              return;
            }
          }

        } else {

          temp = temp % 52;
          x = board_tiles[temp][0];
          y = board_tiles[temp][1];

          if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

            if (!contains_piece(temp, &human)) {

              if (attacking == true) {

                comps[attack_i].pieces[attack_j] = (attack_j + 1)*-1;

              }

              human.pieces[human.working_piece] = temp;
              die = 0;
              my_window->redraw();
              return;
            }
          }
        }
      }
    }
    return;
  }

  bool selected () {

    int x, y;
    int location;
    int m_x, m_y;

    for (int i = 0; i < 4; i++) {

      location = human.pieces[i];
      m_x = Fl::event_x();
      m_y = Fl::event_y();

      if (location == -10) {
        continue;
      }

      if (location < 0) {

        location = (location*-1) -1;
        x = base_tiles[human.id][location*2];
        y = base_tiles[human.id][location*2 + 1];
        location = (location + 1)*-1;

      } else {

        x = board_tiles[location][0];
        y = board_tiles[location][1];
      }

      if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

        human.piece_pos = location;
        human.working_piece = i;
        return true;
      }
    }
    return false;
  }

  bool winner (Player* p) {
    int val = 0;

    for (int& piece : p->pieces) {
      if (piece == -10) {
        val++;
      }
    }

    if (val == 4) {
      return true;
    }
    return false;

  }

  // location is the place we want to go to

  int contains_piece (int location, Player* p) {

    attacking = false;

    if (location == 0 || location == 8 || location == 13 || location == 21 || location == 26 || location == 34 || location == 39 || location == 47 || location < -4) {

      for (int i = 0; i < 4; i++) {

        if (location == human.pieces[i]) {
          return true;
        }

        for (int j = 0; j < 3; j++) {
          if (location == comps[j].pieces[i]) {
            return true;
          }
        }
      }
      return false;

    } else {

      for (int& piece : p->pieces) {

        if (location == piece) {
          return true;
        }
      }

      for (int j = 0; j < 4; j++) {

        if (location == human.pieces[j]) {
          attacking = true;
          attack_i = human.id;
          attack_j = j;

          return false;
        }

        for (int i = 0; i < 3; i++) {

          if (location == comps[i].pieces[j]) {
            attacking = true;
            attack_i = i;
            attack_j = j;

            return false;
          }


        }
      }
    }

    return false;
  }

  void computer_turn (C_Player* p) {

    int location;
    int c_temp;

    p->set_die();

    // if any piece can be brought into play, bring it into play

    for (int j = 0; j < 4; j++) {

      location = p->pieces[j];

      if (location < 0 && location > -5) {

        for (int& die : p->die_rolls) {

          if (!contains_piece(p->id*13, p) && die == 6) {

            p->pieces[j] = p->id*13;
            die = 0;

          }

        }
      }
    }

    // if possible to attack another piece, attack it

    for (int j = 0; j < 4; j++) {

      location = p->pieces[j];
      int end_point = (p->id*13 - 1 + 52) % 52;


      if (location >= 0) {

        for (int& die : p->die_rolls) {

          if (die == 0) {
            continue;
          }

          c_temp = location + die;

          if ((end_point - p->pieces[j]) <= 6 && (end_point - p->pieces[j]) > 0 && (end_point - c_temp) <= 0) {

            break;

          } else {

            c_temp = c_temp % 52;

            if (!contains_piece(c_temp, p) && attacking == true) {

              if (attack_i == human.id) {
                human.pieces[attack_j] = (attack_j + 1)*-1;
              } else {
                comps[attack_i].pieces[attack_j] = (attack_j + 1)*-1;
              }

              p->pieces[j] = c_temp;
              die = 0;
              break;

            }
          }
        }
      }
    }

    // if any piece is on the beginning tile, move it out

    if (p->die_rolls[0] > 0 || p->die_rolls[1] > 0) {

      for (int j = 0; j < 4; j++) {

        location = p->pieces[j];

        if (location == p->id*13) {

          for (int& die : p->die_rolls) {

            c_temp = (location + die) % 52;

            if (!contains_piece(c_temp, p)) {

              p->pieces[j] = c_temp;
              die = 0;
              break;
            }
          }
        }
      }
    }

    // with remaining moves, move pieces at random, the max amount they can go ahead


    if (p->die_rolls[0] > 0 || p->die_rolls[1] > 0) {

      int rand_first = (rand() % 4);
      int temp_j;

      int end_point = (p->id*13 - 1 + 52) % 52;

      for (int j = 0; j < 4; j++) {

        temp_j = (j + rand_first) % 4;

        location = p->pieces[temp_j];

        if (location >= 0) {

          for (int& die : p->die_rolls) {

            c_temp = location + die;

            if ((end_point - p->pieces[temp_j]) <= 6 && (end_point - p->pieces[temp_j]) > 0 && (end_point - c_temp) <= 0) {

              c_temp = c_temp % 52;
              int temp2;

              if (p->id == 0 && c_temp != end_point) {
                temp2 = (c_temp + 6)*-1;
              } else {
                temp2 = (c_temp - end_point + 5)*-1;
              }

              if (temp2 > -10) {

                if (!contains_piece(temp2, p)) {

                  p->pieces[temp_j] = temp2;
                  die = 0;
                  break;

                }

              } else if (temp2 == -10){

                p->pieces[temp_j] = -10;

                if (winner(p)) {
                  game_over = true;
                  return;

                }

                die = 0;
                break;

              }

            } else {

              c_temp = c_temp % 52;

              if (!contains_piece(c_temp, p)) {

                p->pieces[temp_j] = c_temp;
                die = 0;
                break;
              }
            }
          }

        } else if (location < -4 && location != -10) {

          for (int& die : p->die_rolls) {

            if (location - die > -10) {

              if (!contains_piece(location - die, p)) {

                  p->pieces[temp_j] = location - die;
                  die = 0;
                  break;

                }

            } else if (location - die == -10) {

              p->pieces[temp_j] = -10;

              if (winner(p)) {

                game_over = true;
                return;
              }

              die = 0;
              break;

            }
          }
        }
      }
    }

    redraw();
    Fl::flush();

  }

  void draw () {

    fl_rectf(this->x(), this->y(), this->w(), this->h(), FL_WHITE);
    draw_lines(this->x(), this->y());

    if (human.id >= 0) {

      draw_base(&human);
      draw_base(&comps[0]);
      draw_base(&comps[1]);
      draw_base(&comps[2]);

      draw_pieces(&human);
      draw_pieces(&comps[0]);
      draw_pieces(&comps[1]);
      draw_pieces(&comps[2]);

      fl_color(FL_BLACK);
      fl_font(FL_HELVETICA_BOLD, 20);

      fl_draw ("You rolled:", 650, 260);
      fl_draw(std::to_string(human.die_rolls[0]).c_str(), 680, 300);
      fl_draw(std::to_string(human.die_rolls[1]).c_str(), 720, 300);

      if (choosing) {

        draw_choices();

      }

    } else {

      fl_rectf(0, 460, 240, 240, 237, 204, 19);
      fl_rectf(0, 100, 240, 240, 19, 117, 237);
      fl_rectf(360, 100, 240, 240, 237, 37, 19);
      fl_rectf(360, 460, 240, 240, 67, 219, 33);

    }
  }

  void draw_choices () {

    fl_color(FL_BLACK);

    int x, y;
    int temp;

    if (human.piece_pos < 0) {

      if (human.piece_pos < -4) {

        temp = human.piece_pos;

        for (int& die : human.die_rolls) {

          if (die == 0) {
            continue;
          }

          if (temp - die > -10) {

            if (!contains_piece(temp - die, &human)) {
              x = base_tiles[human.id][(temp*-1 - 1)*2];
              y = base_tiles[human.id][(temp*-1 - 1)*2 + 1];
              fl_rectf(x - 15, y - 15, 30, 30);

            }
          } else if (temp - die == -10) {

            fl_rectf(300 - 15, 400 - 15, 30, 30, FL_WHITE);

          }
        }

      } else {

        x = board_tiles[human.id*13][0];
        y = board_tiles[human.id*13][1];

        if (human.die_rolls[0] == 6 || human.die_rolls[1] == 6) {

          if (!contains_piece(human.id*13, &human)) {

            fl_rectf(x - 15, y - 15, 30, 30);

          }
        }
      }

    } else {

      int end_point = (human.id*13 - 1 + 52) % 52;

      for (int& die : human.die_rolls) {

        if (die == 0) {
          continue;
        }

        temp = human.piece_pos + die;

        // if only 6 or less away and will fall on or after endpoint then
        if ((end_point - human.piece_pos) <= 6 && (end_point - human.piece_pos) > 0 && (end_point - temp) <= 0) {

          temp = temp % 52;
          int temp2;

          if (human.id == 0 && temp != end_point) {
            temp2 = temp + 5;

          } else {

             temp2 = temp - end_point + 4;
          }

          if (temp2 <= 8) {

            if (!contains_piece(temp2*-1 -1, &human)) {
              x = base_tiles[human.id][temp2*2];
              y = base_tiles[human.id][temp2*2 + 1];
              fl_rectf(x - 15, y - 15, 30, 30);

            }


          } else if (temp2 == 9) {

            fl_rectf(300 - 30, 400 - 30, 60, 60, FL_WHITE);

          }

        } else {

          temp = temp % 52;

          x = board_tiles[temp][0];
          y = board_tiles[temp][1];


          if (!contains_piece(temp, &human)) {
            attacking = false;
            fl_rectf(x - 15, y - 15, 30, 30);
          }
        }
      }
    }
  }


  void draw_pieces (Player* p) {

    int location;
    double x, y;

    for (int i = 0; i < 4; i++) {

      location = p->pieces[i];

      if (location < 0) {

        if (location == -10) {

          //draw square 'piece' covering home location

          fl_rectf(base_tiles[p->id][i*2] - 20, base_tiles[p->id][i*2 + 1] - 20, 40, 40, p->r, p->g, p->b);

          continue;

        } else {
          location = (location*-1) - 1;
          x = (double)base_tiles[p->id][location*2];
          y = (double)base_tiles[p->id][location*2 + 1];

        }

      } else {

        x = (double)board_tiles[location][0];
        y = (double)board_tiles[location][1];

      }

      fl_color(p->r, p->g, p->b);
      fl_circle (x, y, 16.0);
      fl_circle (x, y, 15.0);

      fl_color(FL_BLACK);
      fl_circle (x, y, 12.0);
    }
  }


  // drawing home base and all its pieces
  void draw_base (Player* p) {

    // drawing base
    fl_color(p->r, p->g, p->b);
    fl_rectf(p->x, p->y, 240, 240);

    // drawing 2 safe tiles
    fl_rectf(board_tiles[p->home][0] - 15, board_tiles[p->home][1] - 15, 30, 30);
    fl_rectf(board_tiles[p->safe][0] - 15, board_tiles[p->safe][1] - 15, 30, 30);

    // drawing exit tiles
    for (int i = 4; i < 9; i++) {
      fl_rectf(base_tiles[p->id][i*2] - 15, base_tiles[p->id][i*2 + 1] - 15, 30, 30);
    }

    // drawing 4 white tiles within base
    fl_color(FL_WHITE);
    fl_rectf(p->x + 60, p->y + 60, 40, 40);
    fl_rectf(p->x + 140, p->y + 60, 40, 40);
    fl_rectf(p->x + 60, p->y + 140, 40, 40);
    fl_rectf(p->x + 140, p->y + 140, 40, 40);

  }

  void draw_lines (int x, int y) {

    fl_color(FL_BLACK);
    fl_rectf(x + 240, y + 240, 120, 120);

    for (int i = 1; i <= 4; i++) {

      fl_line(x + 200 + 40*i, y, x + 200 + 40*i, y + 600);
      fl_line(x, y + 200 + 40*i, x + 600, y + 200 + 40*i);
    }

    for (int i = 1; i <= 14; i++) {

      fl_line(x + 240, y + 40*i, x + 360, y + 40*i);
      fl_line(x + 40*i, y + 240, x + 40*i, y + 360);
    }
  }
};

#endif // BOARD_H
