#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

/**

// select a corner
// that becomes your player

// ai lists choices
// favours one if can kill player, get piece into game, get into safe spot etc.

// no sudden loading, draw computer moves continously (at a pace?

// dice roll

// player object defines its area on the board

// player turn function and computer turn function


*/


class Corner {
public:

  int x;

  int y;

  int home;

  const char* colour;

  int numMoves;

  // each move has a cost
  // when u click on piece, highlight its available moves


  Corner (int x, int y, int home, const char* colour) {

    this->x = x;
    this->y = y;
    this->home = home;
    this->colour = colour;

  }


};




class Board {
public:

  Corner players[4];
  players[0] = new Corner(0, 460, 0, "yellow");
  players[1] = new Corner(0, 100, 13, "bllue");
  players[2] = new Corner(360, 100, 26, "red");
  players[3] = new Corner(350, 460, 39, "green");

  int chosen;

  /**
  0 13 26 39 (chosen will be one of these) yellow, blue, red, green


  can end turn if at least one move is made;

  while (Board.gameON)

  */




  Board (int chosen) {

    this->chosen = chosen;


  // 1 = top left



  }

  void turn (int die1, int die2) {




  }




};



int main (int argc, char ** argv)
{
  Fl_Window *window;
  Fl_Box *box;
  Fl_Button *start_button;
  Fl_Button *roll_button;
  Fl_Button *next_button;
  Fl_Box *m_board;

  window = new Fl_Window (800, 700);

  start_button = new Fl_Button (20,20,100,60);

  roll_button = new Fl_Button (620,20,160,160);

  next_button = new Fl_Button (620, 500, 160, 160);

  m_board = new Fl_Box(150, 20, 450, 60);
  m_board->box(FL_THIN_UP_BOX);
  m_board->color(FL_BLACK);

  box = new Fl_Box(0, 100, 600, 600);
  box->box(FL_THIN_UP_BOX);
  box->color(FL_BLACK);

  window->end ();
  window->show (argc, argv);

  return(Fl::run());
}
