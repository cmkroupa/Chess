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
    if (shift && 0x08) // Shift NE
    {
        representation &= 0x00FEFEFE;
        representation << 7;
    }
    if (shift && 0x04) // Shift SE
    {
        representation &= 0x7F7F7F00;
        representation >> 7;
    }
    if (shift && 0x02) // Shift NW
    {
        representation &= 0x007F7F7F;
        representation << 9;
    }
    if (shift && 0x01) // Shift SW
    {
        representation &= 0x00FEFEFE;
        representation >> 9;
    }
}

uint64_t get_legal_moves(Pieces pieces[], int i){
    uint8_t moves = pieces[i].moves;
    uint64_t legal_moves = pieces[i].position;

    switch(moves){
        case 0x1:{
            legal_moves = move(pieces[i].position, 0x80) | move(pieces[i].position, 0x40) | move(pieces[i].position, 0x20) | move(pieces[i].position, 0x10) | move(pieces[i].position, 0x8) | move(pieces[i].position, 0x4) | move(pieces[i].position, 0x2) | move(pieces[i].position, 0x1);
        }
        case 0x2:{

        }
        case 0x3:{//bishop
            
        }
        case 0x4:{//knight
            //North
            uint64_t north_2 = move(move(legal_moves, 0x80), 0x80);
            north_2 |= move(north_2, 0x40) | move(north_2, 0x10);
            //East
            uint64_t east_2 = move(move(legal_moves, 0x40), 0x40);
            east_2 |= move(north_2, 0x80) | move(north_2, 0x20);
            //South
            uint64_t south_2 = move(move(legal_moves, 0x20), 0x20);
            south_2 |= move(north_2, 0x40) | move(north_2, 0x10);
            //West
            uint64_t west_2 = move(move(legal_moves, 0x10), 0x10);
            west_2 |= move(north_2, 0x80) | move(north_2, 0x20);

            legal_moves = north_2 | east_2 | south_2 | west_2;
        }
        case 0x5:{//rook
            uint64_t vertical = pieces[i].position;
            uint64_t horizontal = pieces[i].position;
            for (int i = 0; i < 7; i++){
                vertical |= move(legal_moves, 0x80);
            }
            for (int i = 0; i < 7; i++){
                horizontal |= move(legal_moves, 0x40);
            }
            legal_moves = vertical | horizontal;
        }
        default:{//pawn
            legal_moves = move(pieces[i].position, 0x80);
            //take positions
        }
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