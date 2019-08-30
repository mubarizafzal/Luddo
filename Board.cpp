#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <array>
#include "Player.h"
#include "C_Player.h"
#include "H_Player.h"
#include "Board.h"

// implement better random

Board* box;

void roll_callback (Fl_Widget* widget, void*) {

  box->human.die_rolls[0] = (rand() % 6) + 1;
  box->human.die_rolls[1] =  (rand() % 6) + 1;
  box->choosing = false;

  my_window->redraw();

  ((Fl_Button*)widget)->deactivate();

}

void next_callback (Fl_Widget* widget, void*) {

  m_board->label("Computer Turn - Please Wait");
  my_window->redraw();

  ((Fl_Button*)widget)->deactivate();

  box->choosing = false;
  box->human.die_rolls[0] = 0;
  box->human.die_rolls[1] = 0;
  my_window->redraw();


  for (int i = 0; i < 3; i++) {

    box->computer_turn(&box->comps[i]);
    time_t curr_time;
    time(&curr_time);

    while (difftime(time(NULL), curr_time) < 0.5) {
      // one second between computer player moves
    }
  }


  if (box->game_over) {
    roll_button->deactivate();
    ((Fl_Button*)widget)->deactivate();
    m_board->label("Game Over! - Click 'new game' to restart.");

  } else {
    ((Fl_Button*)widget)->activate();
    (roll_button)->activate();
    m_board->label("Click on 'Roll' to get your dice roll");
  }

  my_window->redraw();

}

void start_callback (Fl_Widget* widget, void*) {

  my_window->remove(box);
  box = new Board(0, 100, 600, 600);
  my_window->add(box);
  roll_button->deactivate();
  next_button->deactivate();
  box->redraw();
  my_window->redraw();
  m_board->label("Click on a corner to begin the game!");

}

int main (int argc, char ** argv) {

  srand(time(0));

  my_window = new Fl_Window (800, 700);
  my_window->color(fl_lighter(FL_GRAY));

  start_button = new Fl_Button (20,20,100,60);
  start_button->label("New Game");
  start_button->callback(start_callback, 0);

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
  m_board->label("Click on a corner to begin the game!");

  box = new Board(0, 100, 600, 600);
  box->box(FL_THIN_UP_BOX);

  my_window->end ();
  my_window->show (argc, argv);

  return(Fl::run());
}


