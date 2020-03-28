#ifndef H_PLAYER_H
#define H_PLAYER_H

class H_Player : public Player {

public:

  // the piece number that is being selected or moved, used to make sure the changes are made to this piece
  int working_piece;

  // the position of the working piece, used to draw where the piece can go, and calculate its movement
  int piece_pos;


};

#endif // H_PLAYER_H
