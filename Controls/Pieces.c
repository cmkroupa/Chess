#include <stdint.h>

// 00 01 02 03 | 04 05 06 07
// 08 09 10 11 | 12 13 14 15
// 16 17 18 19 | 20 21 22 23
// 24 25 26 27 | 28 29 30 31
// 32 33 34 35 | 36 37 38 39 
// 40 41 42 43 | 44 45 46 47
// 48 49 50 51 | 52 53 54 55
// 56 57 58 59 | 60 61 62 63



typedef struct {
    uint64_t position;
    uint8_t moves; // (King)(Knight)(Diagonal)(Vertical/Horizontal)
} Pieces;

uint64_t move(uint64_t representation, uint8_t shift){
    if (shift && 0x80) // Shift North
    {
        representation << 8;
    }
    if (shift && 0x40) // Shift East
    {
        representation &= 0xFEFEFEFE;
        representation >> 1;
    }
    if (shift && 0x20) // Shift South
    {
        representation >> 8;
    }
    if (shift && 0x10) // Shift West
    {
        representation &= 0x7F7F7F7F;
        representation << 1;
    }
    if (shift && 0x8) // Shift NE
    {
        representation &= 0x00FEFEFE;
        representation << 7;
    }
    if (shift && 0x4) // Shift SE
    {
        representation &= 0x7F7F7F00;
        representation >> 7;
    }
    if (shift && 0x2) // Shift NW
    {
        representation &= 0x007F7F7F;
        representation << 9;
    }
    if (shift && 0x1) // Shift SW
    {
        representation &= 0x00FEFEFE;
        representation >> 9;
    }
}

uint64_t get_legal_moves(Pieces pieces[], int i){
    uint8_t moves = pieces[i].moves;
    uint64_t legal_moves = 0x0;

    if(moves == 0x1){ // King

    }
    else if (moves == 0x2)//Queen
    { 

    }
    else if (moves == 0x3) // Bishop
    {

    }
    else if (moves == 0x4) // Knight
    {

    }
    else if (moves == 0x5) // Rook
    {

    }
    else //Pawn
    {

    }

    return moves;
}

int main()
{ 
    Pieces pawn = {0xFF000, 0x6};
    Pieces rook = {0x00000081, 0x5};
    Pieces knight = {0x00000042, 0x4};
    Pieces bishop = {0x00000024, 0x3};
    Pieces queen = {0x00000010, 0x2};
    Pieces king = {0x00000008, 0x1};
    Pieces pieces[] = {rook, knight, bishop, queen, king};

    uint64_t moves = get_legal_moves(pieces, 0);
    return 0;
}