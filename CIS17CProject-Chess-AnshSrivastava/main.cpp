#include "Board.hpp"
#include "coordinate.hpp"
#include "Move.hpp"
#include "BloomFilter.hpp"
#include <iostream>
#include <string>


void gameLoop(chess::Board&);

int main()
{
    std::cout << "Welcome to chess! To play type in the coordinate of the square the \n piece you want to move is in e.g., e2 and then press enter. It should ask you for the piece you want to move the piece to, type it in and press enter.\n\nSpecial Moves: For kingside castling use 0-0, 0-0-0 for Queenside castling and type ENP for En passant. \nFor the best experience, make the game take up most of your screen and zoom in. Enjoy!!! \n\n\n";
  
  BloomFilter usernameBF(1024);
  std::cout << "Type in your username: ";
  std::string username = chess::cin();

  if (usernameBF.isProbableToExist(username))
  {
    std::cout << "You have probably played the game before based on our bloom filter (that uses a tree).\n";
  }
  else
  {
    std::cout << "Our bloom filter indicate you have not played before.\n";
    usernameBF.addString(username);
  }
  chess::Board board;
  board.printBoard();
  gameLoop(board);
}

void gameLoop(chess::Board &board)
{
  if (board.isGameOver())
    return;
  chess::coordinate initial;
  chess::coordinate finalcord;
  std::cout << "It is " << ((board.getPlayer() == chess::WHITE) ? "white" : "black" ) << "'s move.\n";
  std::cout << "Type in chess coordinate for the piece you want to move: ";
  std::string input;
  input = chess::cin();
  if (input == "0-0")
  {
    if (board.castleKingside())
    {
      board.printBoard();
      gameLoop(board);return;
    }
    else
    std::cout << "You cannot castle kingside right now.\n";
    gameLoop(board);return;
  }
  if (input == "0-0-0")
  {
    if (board.castleQueenside())
    {
      board.printBoard();
      gameLoop(board);return;
      }
    else
      std::cout << "You cannot castle queenside right now.\n";
      gameLoop(board);return;
    }
    if (input == "ENP")
    {
      if (board.enpassant())
      {
        board.printBoard();
        gameLoop(board);return;
      }
      else
        std::cout << "You cannot enpassant right now.\n";
      gameLoop(board);return;
    }
    if (input.size() != 2)
      std::cout << "We are unable to understand your input. Please enter a letter A-H followed by a number 1-8.\n";
    else
    {
      initial.rank = chess::getRankFromChar(input[1]); 
      initial.file = chess::getFileFromChar(input[0]); 
      if (initial.rank == -1 || initial.file == -1)
        {
          std::cout << "Not a valid coordinate!\n";
          gameLoop(board);return;
        }
      if (chess::pieceToPlayer(board.getPiece(initial.file, initial.rank)) != board.getPlayer())
      {
        std::cout << "It is " << ((board.getPlayer() == chess::Player::WHITE) ? "white" : "black") << "'s turn. Move your own piece.\n";
        gameLoop(board);return;
      }
      std::cout << "Type in chess coordinate for the square you want to move your piece to: ";
      std::string input;
      input = chess::cin();
    
      if (input.size() != 2)
        std::cout << "We are unable to understand your input. Please enter a letter A-H followed by a number 1-8.\n";
      else
      {
        finalcord.rank = chess::getRankFromChar(input[1]); 
        finalcord.file = chess::getFileFromChar(input[0]); 
        if (finalcord.rank == -1 || finalcord.file == -1)
          {
            std::cout << "Not a valid coordinate!\n";
            gameLoop(board);return;
          }
      }
    }
    chess::Move mov;
    mov.firstSquare = initial;
    mov.lastSquare = finalcord;
    if (!board.makeAMove(mov))
      {
      std::cout << "You made an illegal move. Try making your move again.\n"; gameLoop(board);return; }
    board.printBoard(); 
    gameLoop(board);
}
