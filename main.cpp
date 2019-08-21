#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <iostream>
#include <FL/fl_draw.H>
#include <cstdlib>


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


class Board : public Fl_Box {
public:

  //int x, y, w, h;

  // 0 for yellow 3 for green

  int pieces [4][4];
  int die1;
  int die2;

  int remaining = 10;

  // -1 = 0, -9 = 8

  int base_squares [4][18] = {
    {0,0,0,0,0,0,0,0, 240 + 60, 600 - 60,240 + 60, 600 - 100,240 + 60, 600 - 140,240 + 60, 600 - 180,240 + 60, 600 - 220},
    {0,0,0,0,0,0,0,0,240 - 180, 600 - 300, 240 - 140, 600 - 300, 240 - 100, 600 - 300, 240 - 60, 600 - 300, 240 - 20, 600 - 300},
    {0,0,0,0,0,0,0,0,240 + 60, 600 - 540, 240 + 60, 600 - 500, 240 + 60, 600 - 460, 240 + 60, 600 - 420, 240 + 60, 600 - 380},
    {0,0,0,0,0,0,0,0,240 + 300, 600 - 300, 240 + 260, 600 - 300, 240 + 220, 600 - 300, 240 + 180, 600 - 300, 240 + 140, 600 - 300}
  };

  int square_cords[52][2] = {
    {240 + 20, 600 - 60},
    {240 + 20, 600 - 100},
    {240 + 20, 600 - 140},
    {240 + 20, 600 - 180},
    {240 + 20, 600 - 220},
    {240 - 20, 600 - 260},
    {240 - 60, 600 - 260},
    {240 - 100, 600 - 260},
    {240 - 140, 600 - 260},
    {240 - 180, 600 - 260},
    {240 - 220, 600 - 260},
    {240 - 220, 600 - 300},
    {240 - 220, 600 - 340},
    {240 - 180, 600 - 340},
    {240 - 140, 600 - 340},
    {240 - 100, 600 - 340},
    {240 - 60, 600 - 340},
    {240 - 20, 600 - 340},
    {240 + 20, 600 - 380},
    {240 + 20, 600 - 420},
    {240 + 20, 600 - 460},
    {240 + 20, 600 - 500},
    {240 + 20, 600 - 540},
    {240 + 20, 600 - 580},
    {240 + 60, 600 - 580},
    {240 + 100, 600 - 580},
    {240 + 100, 600 - 540},
    {240 + 100, 600 - 500},
    {240 + 100, 600 - 460},
    {240 + 100, 600 - 420},
    {240 + 100, 600 - 380},
    {240 + 140, 600 - 340},
    {240 + 180, 600 - 340},
    {240 + 220, 600 - 340},
    {240 + 260, 600 - 340},
    {240 + 300, 600 - 340},
    {240 + 340, 600 - 340},
    {240 + 340, 600 - 300},
    {240 + 340, 600 - 260},
    {240 + 300, 600 - 260},
    {240 + 260, 600 - 260},
    {240 + 220, 600 - 260},
    {240 + 180, 600 - 260},
    {240 + 140, 600 - 260},
    {240 + 100, 600 - 220},
    {240 + 100, 600 - 180},
    {240 + 100, 600 - 140},
    {240 + 100, 600 - 100},
    {240 + 100, 600 - 60},
    {240 + 100, 600 - 20},
    {240 + 60, 600 - 20},
    {240 + 20, 600 - 20}
  };

  int chosen = -1;

  bool choosing = false;

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
      } else {

        // if haven't begun choosing, i.e. still clicking
        if (!choosing) {
          // if you have clicked on a piece
          if (selected()) {
            std::cout << "HMMM" << "\n";
            choosing = true;
            redraw();
          }
        } else {



        }


      }


    }

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

        std::cout << location << "\n";
        selection = location;
        return true;


      }



    }
    return false;


  }





  void draw () {

    // safe squares - 0 13 26 39 - 47 8 21 34

    fl_rectf(this->x(), this->y(), this->w(), this->h(), FL_WHITE);
    draw_lines(this->x(), this->y());
    draw_rects(this->x(), this->y());

    fl_draw ("You rolled:", 650, 360);
    fl_draw(std::to_string(die1).c_str(), 680,400);
    fl_draw(std::to_string(die2).c_str(), 720,400);

    if (choosing) {
      // draw choices

      fl_draw(std::to_string(selection).c_str(), 400, 400);

      draw_choices();

      choosing = false;

    }

    //fl_color(FL_YELLOW);
    //draw_pieces(1);




    //fill_board(square_cords[0], this->x(), this->y());
  }

  void draw_choices () {

    int x;
    int y;

    int y_shift = 100;


    if (selection < 0) {

      selection = (selection*-1) -1;
      x = square_cords[chosen*13][0];
      y = square_cords[chosen*13][1];

      if (remaining >= 6) {
        fl_rectf(x, y + y_shift, 30, 30);
      }
      //location = (location + 1)*-1;

    } else {

      x = square_cords[selection][0];
      y = square_cords[selection][1];



      for (int i = 0; i < remaining; i++) {


      }

    }



  }



  void draw_rects (int x, int y) {

    fl_color(237, 204, 19);
    fl_rectf(x, y + 360, 240, 240);
    fl_rectf(x + square_cords[0][0] - 15, y + square_cords[0][1] - 15, 30,30);
    fl_rectf(x + square_cords[47][0] - 15, y + square_cords[47][1] - 15, 30,30);
    draw_special(0);
    draw_4(0, x, y + 360);
    draw_pieces(0, 237, 204, 19);

    fl_color(19, 117, 237);
    fl_rectf(x, y, 240, 240);
    fl_rectf(x + square_cords[13][0] - 15, y + square_cords[13][1] - 15, 30,30);
    fl_rectf(x + square_cords[8][0] - 15, y + square_cords[8][1] - 15, 30,30);
    draw_special(1);
    draw_4(1, x, y);
    draw_pieces(1, 19, 117, 237);

    fl_color(237, 37, 19);
    fl_rectf(x + 360, y, 240, 240);
    fl_rectf(x + square_cords[26][0] - 15, y + square_cords[26][1] - 15, 30,30);
    fl_rectf(x + square_cords[21][0] - 15, y + square_cords[21][1] - 15, 30,30);
    draw_special(2);
    draw_4(2, x + 360, y);
    draw_pieces(2, 237, 37, 19);


    fl_color(67, 219, 33);
    fl_rectf(x + 360, y + 360, 240, 240);
    fl_rectf(x + square_cords[39][0] - 15, y + square_cords[39][1] - 15, 30,30);
    fl_rectf(x + square_cords[34][0] - 15, y + square_cords[34][1] - 15, 30,30);
    draw_special(3);
    draw_4(3, x + 360, y + 360);
    draw_pieces(3, 67, 219, 33);


  }

  void draw_4 (int i, int x, int y) {



    fl_color(FL_WHITE);

    fl_rectf(x + 60, y + 60, 40, 40);
    base_squares[i][0] = x + 60 + 20;
    base_squares[i][1] = y + 60 + 20;

    fl_rectf(x + 140, y + 60, 40, 40);
    base_squares[i][2] = x + 140 + 20;
    base_squares[i][3] = y + 60 + 20;

    fl_rectf(x + 60, y + 140, 40, 40);
    base_squares[i][4] = x + 60 + 20;
    base_squares[i][5] = y + 140 + 20;

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

  void fill_board (int * arr, int x, int y) {

    fl_color(FL_GRAY);

    for (int i = 0; i < 52*2; i = i + 2) {

      double X = (double)*(arr + i);
      double Y = (double)*(arr + i + 1);

      fl_circle(X + x, Y + y, 15.0);



    }


  }

  void draw_special (int i) {

    int x, y;

    for (int j = 4; j < 9; j++) {

      x = base_squares[i][j*2];
      y = base_squares[i][j*2 + 1];

      fl_rectf(x - 15, y + 100 - 15, 30, 30);
    }

  }


  void draw_pieces (int i, int r, int g, int b) {

    int location;
    double x, y;

    for (int j = 0; j < 4; j++) {

      location = pieces[i][j];

      if (location < 0) {
        location = (location*-1) - 1;

        x = (double)base_squares[i][location*2];
        y = (double)base_squares[i][location*2 + 1];

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

Fl_Window *window;
Board *box;

Fl_Button *roll_button;


void roll_callback (Fl_Widget* widget, void*) {


  box->die1 = (rand() % 6) + 1;
  box->die2 = (rand() % 6) + 1;
  window->redraw();


  ((Fl_Button*)widget)->deactivate();

}

void next_callback (Fl_Widget* widget, void*) {

  (roll_button)->activate();
}



int main (int argc, char ** argv)
{
  Fl_Button *start_button;

  Fl_Button *next_button;
  Fl_Box *m_board;

  window = new Fl_Window (800, 700);
  window->color(fl_lighter(FL_GRAY));

  start_button = new Fl_Button (20,20,100,60);
  start_button->label("New Game");

  roll_button = new Fl_Button (620,20,160,160);
  roll_button->labelsize(20);
  roll_button->labelfont(FL_HELVETICA_BOLD);
  roll_button->label("ROLL DICE");
  roll_button->callback(roll_callback, 0);

  next_button = new Fl_Button (620, 500, 160, 160);
  next_button->labelsize(20);
  next_button->labelfont(FL_HELVETICA_BOLD);
  next_button->label("NEXT TURN");
  next_button->callback(next_callback, 0);





  m_board = new Fl_Box(150, 20, 450, 60);
  m_board->box(FL_THIN_UP_BOX);
  m_board->color(FL_WHITE);

  box = new Board(0, 100, 600, 600);
  box->box(FL_THIN_UP_BOX);

  window->end ();
  window->show (argc, argv);

  return(Fl::run());
}
