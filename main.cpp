#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include <FL/fl_draw.H>
#include <cstdlib>
#include <time.h>

/**

// select a corner
// that becomes your player

// ai lists choices
// favours one if can kill player, get piece into game, get into safe spot etc.

// no sudden loading, draw computer moves continously (at a pace?

// dice roll

// player object defines its area on the board

// player turn function and computer turn function

some sort of Processor that processes interaction with screen, and calls appropriate methods


*/

Fl_Button *next_button;
Fl_Button *roll_button;
Fl_Window *my_window;


class Board : public Fl_Box {
public:

  //int x, y, w, h;

  // 0 for yellow 3 for green

  int pieces [4][4];
  int die1;
  int die2;

  int remaining;

  // -1 = 0, -9 = 8

  int base_squares [4][18] = {
    {0,0,0,0,0,0,0,0, 240 + 60, 700 - 60,240 + 60, 700 - 100,240 + 60, 700 - 140,240 + 60, 700 - 180,240 + 60, 700 - 220},
    {0,0,0,0,0,0,0,0,240 - 180, 700 - 300, 240 - 140, 700 - 300, 240 - 100, 700 - 300, 240 - 60, 700 - 300, 240 - 20, 700 - 300},
    {0,0,0,0,0,0,0,0,240 + 60, 700 - 540, 240 + 60, 700 - 500, 240 + 60, 700 - 460, 240 + 60, 700 - 420, 240 + 60, 700 - 380},
    {0,0,0,0,0,0,0,0,240 + 300, 700 - 300, 240 + 260, 700 - 300, 240 + 220, 700 - 300, 240 + 180, 700 - 300, 240 + 140, 700 - 300}
  };

  int square_cords[52][2] = {
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

  int chosen = -1;

  bool choosing = false;

  bool attacking = false;

  int attack_i, attack_j;

  int working_piece;


  int selection;

  /*

  Corner *yellow = new Corner(0, 460, 0, FL_YELLOW);
  Corner *blue = new Corner (0, 100, 13, FL_BLUE);
  Corner *red = new Corner(360, 100, 26, FL_RED);
  Corner *green = new Corner(360, 460, 39, FL_GREEN);

  Corner * chosen;
  */

  Board (int x, int y, int w, int h) : Fl_Box(x, y, w, h) {

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {

        pieces[i][j] = (j+1)*-1;

      }

    }



    std::cout << pieces[0][0] << "\n";


  }


  int handle (int event) {

    int ret = Fl_Box::handle(event);

    int x, y;


    if (event == FL_PUSH ) {

      x = Fl::event_x();
      y = Fl::event_y();

      // at the beginning of the game
      if (chosen < 0) {

        if (x >= this->x() && x <= this->x()+240 && y >= this->y()+360 && y<= this->y()+600) {

          chosen = 0;
          std::cout << "Chosen Yellow" << "\n";
        }
        if (x >= this->x() && x <= this->x()+240 && y >= this->y() && y<= this->y()+240) {

          chosen = 1;
          std::cout << "Chosen Blue" << "\n";
        }
        if (x >= this->x()+360 && x <= this->x()+600 && y >= this->y() && y<= this->y()+240) {

          chosen = 2;
          std::cout << "Chosen Red" << "\n";
        }
        if (x >= this->x()+360 && x <= this->x()+600 && y >= this->y()+360 && y<= this->y()+600) {

          chosen = 3;
          std::cout << "Chosen Green" << "\n";
        }

        roll_button->activate();
        next_button->activate();
      } else {

        // if haven't begun choosing, i.e. still clicking
        if (!choosing) { // selector_on ?
          // if you have clicked on a piece
          if (selected()) {
            //std::cout << "HMMM" << "\n";
            choosing = true;
            redraw();
          }
        } else {

          //std::cout << "yes" << "\n";

          if (valid_move()) {

            choosing = false;
            redraw();


          } else {

            choosing = false;
            redraw();
          }

          // click on the spot you want to go to



        }


      }


    }

  }

  /**

  add attack function

  computer turn

  repeat roll

  game ending mechanics

  new game code


  */


  bool valid_move () {

    //std::cout<< "piece value: " << pieces[chosen][working_piece] << "\n";

    int x;
    int y;
    int temp;
    int m_x = Fl::event_x();
    int m_y = Fl::event_y();

    if (selection < 0) {



      if (selection < -4) {

        temp = selection*-1 -1;

        for (int i = 1; i <= remaining; i++) {

          if (temp + i < 9) {

            x = base_squares[chosen][(temp + i)*2];
            y = base_squares[chosen][(temp + i)*2 + 1];


            if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {


              if (!contains_piece(temp + i, chosen)) {

                pieces[chosen][working_piece] = (temp + i + 1)*-1;
                remaining = remaining - i;
                my_window->redraw();
                return true;

              }


            }



          } else if (temp + i == 9) {


            if (m_x >= 240 && m_x <= 460 && m_y >= 340 && m_y <= 560) {

              pieces[chosen][working_piece] = -10;
              remaining = remaining -i;
              my_window->redraw();
              return true;

            }

            // finish!!!

          }

        }




      } else {

        x = square_cords[chosen*13][0];
        y = square_cords[chosen*13][1];

        if ((die1 == 6 || die2 == 6) && remaining >= 6) {

          if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

            if (!contains_piece(chosen*13, chosen)) {

              pieces[chosen][working_piece] = chosen*13;
              remaining = remaining - 6;
              my_window->redraw();

              return true;

            }




          }


        }


      }


    } else {

      bool final_moves = false;
      int end_point = (chosen*13 - 1) % 52;
      if (end_point < 0) {

        end_point = 52 + end_point;

      }

      for (int i = 1; i <= remaining; i++) {

        temp = (selection + i) % 52;

        std::cout << temp << "TEMPIS" << "\n";
        //----

        if (temp == end_point || final_moves == true) {
          final_moves = true;

          std::cout << "HERE?22222222" << "\n";

          int temp2;

          if (chosen == 0 && temp != end_point) {
            temp2 = temp + 5;

          } else {

             temp2 = temp - end_point + 4; // 4 5 6 7 8 (9) problem is this i think

          }

          if (temp2 <= 8) {

            x = base_squares[chosen][temp2*2];
            y = base_squares[chosen][temp2*2 + 1];

            std::cout << "will now mouse check" << "\n";

            if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

              std::cout << "WITHIN AREA" << "\n";

              if (!contains_piece(temp2, chosen)) {

                pieces[chosen][working_piece] = (temp2 + 1)*-1;
                remaining = remaining - i;
                my_window->redraw();
                return true;

              }


            }

          } else if (temp2 == 9) {


            if (m_x >= 240 && m_x <= 460 && m_y >= 340 && m_y <= 560) {

              pieces[chosen][working_piece] = -10;
              remaining = remaining -i;
              my_window->redraw();
              return true;

            }

          }



        } else {


          x = square_cords[temp][0];
          y = square_cords[temp][1];

          if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

            std::cout << attacking << " ATK VAL" << "\n";

            if (!contains_piece(temp, chosen)) {

              if (attacking == true) {

                pieces[attack_i][attack_j] = (attack_j + 1)*-1;

              }

              pieces[chosen][working_piece] = temp;
              remaining = remaining - i;
              my_window->redraw();
              return true;

            }


          }

        }






      }

    }

    return false;

    // move piece
  }


  // return true if mouse over your own piece
  bool selected () {

    int location;

    int x, y;

    int m_x, m_y;

    for (int i = 0; i < 4; i++) {

      location = pieces[chosen][i];
      m_x = Fl::event_x();
      m_y = Fl::event_y();

      // don't worry about the pieces at -10, they are out of the game
      if (location == -10) {
        continue;
      }

      if (location < 0) {

        location = (location*-1) -1;
        x = base_squares[chosen][location*2];
        y = base_squares[chosen][location*2 + 1];
        location = (location + 1)*-1;

      } else {

        x = square_cords[location][0];
        y = square_cords[location][1];
      }

      if (m_x >= x-20 && m_x <= x+20 && m_y >= y-20 && m_y <= y+20) {

        //std::cout << location << "\n";
        selection = location;
        working_piece = i;
        return true;


      }



    }
    return false;


  }

  void computer_turn () {

    int c_die1;
    int c_die2;
    int c_remaining;
    int location;
    int c_temp;
    // for double turn after attack, add if statement on attack to add roll to remaining

    for (int i = 0; i < 4; i++) {

      if (i != chosen) {
        c_die1 = (rand() % 6) + 1;
        c_die2 = (rand() % 6) + 1;
        c_remaining = c_die1 + c_die2;

        std::cout << c_die1 << " die rolls " << c_die2 << " for {" << i << "}" << "\n";


        // if anyone home move them in

        for (int j = 0; j < 4; j++) {
          location = pieces[i][j];


          if (location < 0 && location > -5) {
            if ((c_die1 == 6 || c_die2 == 6) && (c_remaining >= 6) && (!contains_piece(i*13, i))) {


              std::cout << " brings it in" << "\n";


              pieces[i][j] = i*13;
              c_remaining = c_remaining - 6;
            }


          }

        }

        // if with remaining moves we can attack, attack
        for (int j = 0; j < 4; j++) {

          location = pieces[i][j];
          int end_point = (i*13 - 1) % 52;
          if (end_point < 0) {
            end_point = 52 + end_point;
          }

          if (location >= 0) {

            for (int k = 1; k <= c_remaining; k++) {

              c_temp = (location + k) % 52;


              if (c_temp == end_point) {

                break;
              }


              if (!contains_piece(c_temp, i) && attacking == true) {

                std::cout << i << " attacks by moving " << k << "\n";

                pieces[attack_i][attack_j] = (attack_j + 1)*-1;
                pieces[i][j] = c_temp;
                c_remaining = c_remaining - k;
                break;

              }


            }

          }


        }

        // move a piece at home first

        if (c_remaining > 0) {

          for (int j = 0; j < 4; j++) {

            location = pieces[i][j];

            if (location >= 0 && location == i*13) {

              for (int k = c_remaining; k > 0; k--) {

                c_temp = (location + k) % 52;

                if (!contains_piece(c_temp, i)) {

                  std::cout << i << " moves home piece by " << k << "\n";
                  pieces[i][j] = c_temp;
                  c_remaining = c_remaining - k;
                  break;
                }

              }

            }


          }

        }



        // otherwise just move a random one


        if (c_remaining > 0) {

          int rand_first = (rand() % 4);
          int temp_j;
          int end_point = (i*13 - 1) % 52;
          if (end_point < 0) {
            end_point = 52 + end_point;
          }

          for (int j = 0; j < 4; j++) {

            temp_j = (j + rand_first) % 4;
            bool final_moves = false;
            location = pieces[i][temp_j];

            // also moving within end
            if (location >= 0) {

              for (int k = 1; k <= c_remaining; k++) {
                c_temp = (location + k) % 52;



                if (c_temp == end_point) {
                  std::cout << "SHOULD NOT" << "\n";
                  final_moves = true;
                  break;

                }
              }


              for (int k = c_remaining; k > 0; k--) {

                c_temp = (location + k) % 52;

                if (final_moves == true) {

                  int temp2;

                  if (i == 0 && c_temp != end_point) {

                    temp2 = c_temp + 5;

                  } else {

                    temp2 = c_temp - end_point + 4;

                  }


                  if (temp2 <= 8) {

                    if (!contains_piece(temp2, i)) {

                      std::cout << i << " does final ending move into " << temp2 << "\n";
                      pieces[i][temp_j] = (temp2 + 1)*-1;
                      c_remaining = c_remaining - k;
                      break;

                    }


                  } else if (temp2 == 9){

                      std::cout << i << "finishes a piece!" << "\n";
                      pieces[i][temp_j] = -10;
                      c_remaining = c_remaining - k;
                      break;


                  }



                } else {


                  if (!contains_piece(c_temp, i)) {

                    std::cout << i << " does final move by " << k << "\n";
                    pieces[i][temp_j] = c_temp;
                    c_remaining = c_remaining - k;
                    break;
                  }



                }





              }

            } else if (location < -4 && location != -10) {

              for (int k = c_remaining; k >= 0; k--) {

                if (location - k >= -10) {

                  pieces[i][temp_j] = location - k;
                  c_remaining = c_remaining -k;
                  break;

                }

              }


            }


          }

        }


        redraw();

      }




    }





  }





  void draw () {

    // safe squares - 0 13 26 39 - 47 8 21 34

    fl_rectf(this->x(), this->y(), this->w(), this->h(), FL_WHITE);
    draw_lines(this->x(), this->y());
    draw_rects(this->x(), this->y());

    fl_draw ("You rolled:", 650, 260);
    fl_draw(std::to_string(die1).c_str(), 680,300);
    fl_draw(std::to_string(die2).c_str(), 720,300);

    //std::cout << "remaining is" << remaining << "\n";
    fl_draw ("Remaining:", 650, 360);
    fl_draw(std::to_string(remaining).c_str(), 700,400);


    if (choosing) {
      // draw choices

      fl_draw(std::to_string(selection).c_str(), 400, 400);

      draw_choices();


    }

    //fl_color(FL_YELLOW);
    //draw_pieces(1);




    //fill_board(square_cords[0]);
  }

  int contains_piece (int location, int corner) {

    attacking = false;

    if (location == 0 || location == 8 || location == 13 || location == 21 || location == 26 || location == 34 || location == 39 || location == 47 || location < -4) {

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (location == pieces[i][j]) {
            return 1;
          }
        }

      }
      return false;


    } else {

      for (int i = 0; i < 4; i++) {
        if (location == pieces[corner][i]) {
          return 2;
          std::cout << "NO" << "\n";

        }
        for (int j = 0; j < 4; j++) {
          if (location == pieces[i][j] && i != corner) {
          //std::cout<< "ATTACK!" << i << "\n";
          // this would signal a false
          std::cout << "Can attack! " << location << "\n";
          attacking = true;
          attack_i = i;
          attack_j = j;
          //pieces[i][j] = (j + 1)*-1;
          return false;
             // attack
          }
        }

      }

    }

    return false;
  }


  void draw_choices () {

    int x;
    int y;
    int temp;


    if (selection < 0) {

      if (selection < -4) {
        temp = selection*-1 - 1;
        // should not be allowed to select a piece with -10

        for (int i = 1; i <= remaining; i++) {

          if (temp + i < 9) {

            x = base_squares[chosen][(temp + i)*2];
            y = base_squares[chosen][(temp + i)*2 + 1];

            fl_rectf(x, y, 30, 30);

          } else if (temp + i == 9) {

            fl_rectf(300,400,30,30, FL_WHITE);

          }

        }


      } else {

        x = square_cords[chosen*13][0];
        y = square_cords[chosen*13][1];

        if (((die1 == 6 || die2 == 6) && remaining >= 6)) {

          if (!contains_piece(chosen*13, chosen)) {
            fl_rectf(x, y, 30, 30);
          }

        }



      }



    } else {

      bool final_moves = false;
      int end_point = (chosen*13 - 1) % 52;
      if (end_point < 0) {
        end_point = 52 + end_point;
      }


      for (int i = 1; i <= remaining; i++) {


        temp = (selection + i) % 52;


        if (temp == end_point || final_moves == true) {
          final_moves = true;

          int temp2;

          if (chosen == 0 && temp != end_point) {
            temp2 = temp + 5;

          } else {

             temp2 = temp - end_point + 4; // 4 5 6 7 8 (9) problem is this i think

          }



          if (temp2 <= 8) {

            x = base_squares[chosen][temp2*2];
            y = base_squares[chosen][temp2*2 + 1];
            fl_rectf(x, y, 30, 30);


          } else if (temp2 == 9) {

            fl_rectf(300, 400, 30, 30, FL_WHITE);

          }



        } else {

          x = square_cords[temp][0];
          y = square_cords[temp][1];


          if (!contains_piece(temp, chosen)) {
            attacking = false;
            fl_rectf(x, y, 30, 30);
          }

        }





      }

    }



  }



  void draw_rects (int x, int y) {

    fl_color(237, 204, 19);
    fl_rectf(x, y + 360, 240, 240);
    fl_rectf(square_cords[0][0] - 15, square_cords[0][1] - 15, 30,30);
    fl_rectf(square_cords[47][0] - 15, square_cords[47][1] - 15, 30,30);
    draw_special(0);
    draw_4(0, x, y + 360);


    fl_color(19, 117, 237);
    fl_rectf(x, y, 240, 240);
    fl_rectf(square_cords[13][0] - 15, square_cords[13][1] - 15, 30,30);
    fl_rectf(square_cords[8][0] - 15, square_cords[8][1] - 15, 30,30);
    draw_special(1);
    draw_4(1, x, y);

    fl_color(237, 37, 19);
    fl_rectf(x + 360, y, 240, 240);
    fl_rectf(square_cords[26][0] - 15, square_cords[26][1] - 15, 30,30);
    fl_rectf(square_cords[21][0] - 15, square_cords[21][1] - 15, 30,30);
    draw_special(2);
    draw_4(2, x + 360, y);


    fl_color(67, 219, 33);
    fl_rectf(x + 360, y + 360, 240, 240);
    fl_rectf(square_cords[39][0] - 15, square_cords[39][1] - 15, 30,30);
    fl_rectf(square_cords[34][0] - 15, square_cords[34][1] - 15, 30,30);
    draw_special(3);
    draw_4(3, x + 360, y + 360);

    draw_pieces(0, 237, 204, 19);
    draw_pieces(1, 19, 117, 237);
    draw_pieces(2, 237, 37, 19);
    draw_pieces(3, 67, 219, 33);


  }

  void draw_4 (int i, int x, int y) {

    fl_color(FL_WHITE);

    fl_draw(std::to_string(pieces[i][0]).c_str(), x+60,y+60);
    fl_rectf(x + 60, y + 60, 40, 40);
    base_squares[i][0] = x + 60 + 20;
    base_squares[i][1] = y + 60 + 20;

    fl_draw(std::to_string(pieces[i][1]).c_str(), x+140,y+60);
    fl_rectf(x + 140, y + 60, 40, 40);
    base_squares[i][2] = x + 140 + 20;
    base_squares[i][3] = y + 60 + 20;

    fl_draw(std::to_string(pieces[i][2]).c_str(), x+60,y+140);
    fl_rectf(x + 60, y + 140, 40, 40);
    base_squares[i][4] = x + 60 + 20;
    base_squares[i][5] = y + 140 + 20;

    fl_draw(std::to_string(pieces[i][3]).c_str(), x+140,y+140);
    fl_rectf(x + 140, y + 140, 40, 40);
    base_squares[i][6] = x + 140 + 20;
    base_squares[i][7] = y + 140 + 20;


  }


  void draw_lines (int x, int y) {
    fl_color(FL_BLACK);
    fl_rectf(x + 240, y + 240, 120, 120);

    for (int i = 1; i <= 2; i++) {

      fl_line(x + 240 + 40*i, y, x + 240 + 40*i, y + 600);
      fl_line(x, y + 240 + 40*i, x + 600, y + 240 + 40*i);
    }

    for (int i = 1; i <= 14; i++) {

      fl_line(x + 240, y + 40*i, x + 360, y + 40*i);
      fl_line(x + 40*i, y + 240, x + 40*i, y + 360);
    }




  }

  void fill_board (int * arr) {

    fl_color(FL_GRAY);

    for (int i = 0; i < 52*2; i = i + 2) {

      double x = (double)*(arr + i);
      double y = (double)*(arr + i + 1);

      fl_circle(x, y, 15.0);



    }


  }

  void draw_special (int i) {

    int x, y;

    for (int j = 4; j < 9; j++) {

      x = base_squares[i][j*2];
      y = base_squares[i][j*2 + 1];

      fl_rectf(x - 15, y - 15, 30, 30);
    }

  }


  void draw_pieces (int i, int r, int g, int b) {

    int location;
    double x, y;

    for (int j = 0; j < 4; j++) {

      location = pieces[i][j];


      if (location < 0) {

        if (location == -10) {
          int temp_x = 0;
          int temp_y = 100;

          if (i > 1) {

            temp_x = 360;
          }

          if (i == 0 || i == 3) {

            temp_y = 460;
          }

          if (j == 1 || j == 3) {
            temp_x = temp_x + 140;
          } else {
            temp_x = temp_x + 60;
          }

          if (j > 1) {

            temp_y = temp_y + 140;
          } else {
            temp_y = temp_y + 60;

          }


          fl_rectf(temp_x, temp_y, 40, 40, r, g, b);


          //rectf()

          continue;
        } else {

          location = (location*-1) - 1;

          x = (double)base_squares[i][location*2];
          y = (double)base_squares[i][location*2 + 1];


        }


      } else {

        x = (double)square_cords[location][0];
        y = (double)square_cords[location][1];

      }

      fl_color(r, g, b);
      fl_circle (x, y, 16.0);
      fl_circle (x, y, 15.0);

      fl_color(FL_BLACK);
      fl_circle (x, y, 12.0);

    }
  }


};

Board *box;




void roll_callback (Fl_Widget* widget, void*) {


  box->die1 = (rand() % 6) + 1;
  box->die2 = (rand() % 6) + 1;
  box->remaining = box->die1 + box->die2;
  box->choosing = false;

  my_window->redraw();


  ((Fl_Button*)widget)->deactivate();

}

void next_callback (Fl_Widget* widget, void*) {

  box->choosing = false;
  box->remaining = 0;
  box->die1 = 0;
  box->die2 = 0;
  my_window->redraw();
  box->computer_turn();

  (roll_button)->activate();
}



int main (int argc, char ** argv)
{

  srand(time(0));

  Fl_Button *start_button;

  Fl_Box *m_board;

  my_window = new Fl_Window (800, 700);
  my_window->color(fl_lighter(FL_GRAY));

  start_button = new Fl_Button (20,20,100,60);
  start_button->label("New Game");

  roll_button = new Fl_Button (620,20,160,160);
  roll_button->labelsize(20);
  roll_button->labelfont(FL_HELVETICA_BOLD);
  roll_button->label("ROLL DICE");
  roll_button->callback(roll_callback, 0);
  roll_button->deactivate();

  next_button = new Fl_Button (620, 500, 160, 160);
  next_button->labelsize(20);
  next_button->labelfont(FL_HELVETICA_BOLD);
  next_button->label("NEXT TURN");
  next_button->callback(next_callback, 0);
  next_button->deactivate();




  m_board = new Fl_Box(150, 20, 450, 60);
  m_board->box(FL_THIN_UP_BOX);
  m_board->color(FL_WHITE);

  box = new Board(0, 100, 600, 600);
  box->box(FL_THIN_UP_BOX);

  my_window->end ();
  my_window->show (argc, argv);

  return(Fl::run());
}
