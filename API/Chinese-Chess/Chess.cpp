﻿#include "Chess.h" 

Chess::Chess() {}
Chess::Chess(Position pos, ColorEnum color, ChessEnum id, int uni) {
	this->pos = pos;
	this->color = color;
	this->id = id;
	this->uni = uni;
	switch (id)
	{
	case ChessEnum::General:
		this->chessName = color == ColorEnum::Red ? "帥" : "將";
		this->enName = "General";
		break;
	case ChessEnum::Advisor:
		this->chessName = color == ColorEnum::Red ? "仕" : "士";
		this->enName = "Advisor";
		break;
	case ChessEnum::Elephant:
		this->chessName = color == ColorEnum::Red ? "相" : "象";
		this->enName = "Elephant";
		break;
	case ChessEnum::Chariot:
		this->chessName = color == ColorEnum::Red ? "俥" : "車";
		this->enName = "Chariot";
		break;
	case ChessEnum::Horse:
		this->chessName = color == ColorEnum::Red ? "傌" : "馬";
		this->enName = "Horse";
		break;
	case ChessEnum::Cannon:
		this->chessName = color == ColorEnum::Red ? "炮" : "砲";
		this->enName = "Cannon";
		break;
	case ChessEnum::Soldier:
		this->chessName = color == ColorEnum::Red ? "兵" : "卒";
		this->enName = "Soldier";
		break;
	}
}

General::General(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::General, uni) {}
Advisor::Advisor(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Advisor, uni) {}
Elephant::Elephant(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Elephant, uni) {}
Chariot::Chariot(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Chariot, uni) {}
Horse::Horse(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Horse, uni) {}
Cannon::Cannon(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Cannon, uni) {}
Soldier::Soldier(Position pos, ColorEnum color, int uni) : Chess(pos, color, ChessEnum::Soldier, uni) {}


void Chess::move(Board& board, Position fromPos, Position toPos) {
	this->pos.x = toPos.x;
	this->pos.y = toPos.y;
	board.board[fromPos.y][fromPos.x] = 0;
	board.board[toPos.y][toPos.x] = static_cast<int>(this->id) * (this->color == ColorEnum::Red ? 1 : -1);
	return;
}

std::vector<Position> General::canMove(Board& board) {
	std::vector<Position> movePos;
	int gen = 0;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 7; y <= 9; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					if (board.board[0][x] == -1 || board.board[1][x] == -1 || board.board[2][x] == -1) {
						int check = 0, yAdd = -1;
						while (1) {
							if (board.board[y + yAdd][x] == -1) {
								break;
							}
							if (board.board[y + yAdd][x] != 0 && board.board[y + yAdd][x] != -1) {
								check = 1;
								break;
							}
							yAdd--;
						}
						if (check == 1) {
							movePos.push_back(Position(x, y));
						}
					}
					else {
						movePos.push_back(Position(x, y));
					}
				}
			}
		}
		else {
			for (int y = 0; y <= 2; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					if (board.board[9][x] == 1 || board.board[8][x] == 1 || board.board[7][x] == 1) {
						int check = 0, yAdd = 1;
						while (1) {
							if (board.board[y + yAdd][x] == 1) {
								break;
							}
							if (board.board[y + yAdd][x] != 0 && board.board[y + yAdd][x] != 1) {
								check = 1;
								break;
							}
							yAdd++;
						}
						if (check == 1) {
							movePos.push_back(Position(x, y));
						}
					}
					else {
						movePos.push_back(Position(x, y));
					}
				}
			}
		}
	}
	if (this->color == ColorEnum::Red) {
		if (board.board[0][pos.x] == -1 || board.board[1][pos.x] == -1 || board.board[2][pos.x] == -1) {
			int check1 = 0;
			int yAdd1 = -1;
			while (1) {
				if (board.board[pos.y + yAdd1][pos.x] != 0 && board.board[pos.y + yAdd1][pos.x] != -1) {
					check1 = 1;
					break;
				}
				if (board.board[pos.y + yAdd1][pos.x] == -1) {
					gen = pos.y + yAdd1;
					break;
				}
				yAdd1--;
			}
			if (check1 == 0) {
				movePos.push_back(Position(pos.x, gen));
			}
		}
	}
	else {
		if (board.board[9][pos.x] == 1 || board.board[8][pos.x] == 1 || board.board[7][pos.x] == 1) {
			int check1 = 0;
			int yAdd1 = 1;
			while (1) {
				if (board.board[pos.y + yAdd1][pos.x] != 0 && board.board[pos.y + yAdd1][pos.x] != 1) {
					check1 = 1;
					break;
				}
				if (board.board[pos.y + yAdd1][pos.x] == 1) {
					gen = pos.y + yAdd1;
					break;
				}
				yAdd1++;
			}
			if (check1 == 0) {
				movePos.push_back(Position(pos.x, gen));
			}
		}
	}
	return movePos;
}
std::vector<Position> General::canEat(Board& board) {
	int gen = 0;
	std::vector<Position> movePos;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 7; y <= 9; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					if (board.board[0][x] == -1 || board.board[1][x] == -1 || board.board[2][x] == -1) {
						int check = 0, yAdd = -1;
						while (1) {
							if (y + yAdd < 0) {
								break;
							}
							if (board.board[y + yAdd][x] != 0 && board.board[y + yAdd][x] != -1) {
								check = 1;
								break;
							}
							yAdd--;
						}
						if (check == 1) {
							movePos.push_back(Position(x, y));
						}
					}
					else {
						movePos.push_back(Position(x, y));
					}
				}
			}
		}
		else {
			for (int y = 0; y <= 2; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) + abs(this->pos.y - y) == 1) {
					if (board.board[9][x] == 1 || board.board[8][x] == 1 || board.board[7][x] == 1) {
						int check = 0, yAdd = 1;
						while (1) {
							if (y + yAdd > 9) {
								break;
							}
							if (board.board[y + yAdd][x] != 0 && board.board[y + yAdd][x] != 1) {
								check = 1;
								break;
							}
							yAdd++;
						}
						if (check == 1) {
							movePos.push_back(Position(x, y));
						}
					}
					else
						movePos.push_back(Position(x, y));
				}
			}
		}
	}
	if (this->color == ColorEnum::Red) {
		if (board.board[0][pos.x] == -1 || board.board[1][pos.x] == -1 || board.board[2][pos.x] == -1) {
			int check1 = 0;
			int yAdd1 = -1;
			while (1) {
				if (board.board[pos.y + yAdd1][pos.x] != 0 && board.board[pos.y + yAdd1][pos.x] != -1) {
					check1 = 1;
					break;
				}
				if (board.board[pos.y + yAdd1][pos.x] == -1) {
					gen = pos.y + yAdd1;
					break;
				}
				yAdd1--;
			}
			if (check1 == 0) {
				movePos.push_back(Position(pos.x, gen));
			}
		}
	}
	else {
		if (board.board[9][pos.x] == 1 || board.board[8][pos.x] == 1 || board.board[7][pos.x] == 1) {
			int check1 = 0;
			int yAdd1 = 1;
			while (1) {
				if (board.board[pos.y + yAdd1][pos.x] != 0 && board.board[pos.y + yAdd1][pos.x] != 1) {
					check1 = 1;
					break;
				}
				if (board.board[pos.y + yAdd1][pos.x] == 1) {
					gen = pos.y + yAdd1;
					break;
				}
				yAdd1++;
			}
			if (check1 == 0) {
				movePos.push_back(Position(pos.x, gen));
			}
		}
	}
	return movePos;
}

std::vector<Position> Advisor::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 7; y <= 9; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) * abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
		else {
			for (int y = 0; y <= 2; y++) {
				if (board.applyMove(Position(x, y), this->color) && abs(this->pos.x - x) * abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
	}
	return movePos;
}
std::vector<Position> Advisor::canEat(Board& board) {
	std::vector<Position> movePos;
	for (int x = 3; x <= 5; x++) {
		if (this->color == ColorEnum::Red) {
			for (int y = 7; y <= 9; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) * abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
		else {
			for (int y = 0; y <= 2; y++) {
				if (board.applyEat(Position(x, y), this->color) && abs(this->pos.x - x) * abs(this->pos.y - y) == 1) {
					movePos.push_back(Position(x, y));
				}
			}
		}
	}
	return movePos;
}

std::vector<Position> Elephant::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 0, yAdd = 0; i < 4; i++) {
		if (i < 2) {
			xAdd = 1;
		}
		else {
			xAdd = -1;
		}
		if (i == 0 || i == 3) {
			yAdd = -1;
		}
		else {
			yAdd = 1;
		}
		if (this->color == ColorEnum::Black) {
			if (pos.y + yAdd * 2 > 4 || pos.y + yAdd * 2 < 0 || pos.x + xAdd * 2 < 0 || pos.x + xAdd * 2 > 8) {
				continue;
			}
			if (board.applyMove(Position(pos.x + xAdd * 2, pos.y + yAdd * 2), this->color) && board.board[pos.y + yAdd][pos.x + xAdd] == 0) {
				movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd * 2));
			}
		}
		else {
			if (pos.y + yAdd * 2 < 5 || pos.y + yAdd * 2 > 9 || pos.x + xAdd * 2 < 0 || pos.x + xAdd * 2 > 8) {
				continue;
			}
			if (board.applyMove(Position(pos.x + xAdd * 2, pos.y + yAdd * 2), this->color) && board.board[pos.y + yAdd][pos.x + xAdd] == 0) {
				movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd * 2));
			}
		}
	}
	return movePos;
}
std::vector<Position> Elephant::canEat(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 0, yAdd = 0; i < 4; i++) {
		if (i < 2) {
			xAdd = 1;
		}
		else {
			xAdd = -1;
		}
		if (i == 0 || i == 3) {
			yAdd = -1;
		}
		else {
			yAdd = 1;
		}
		if (this->color == ColorEnum::Black) {
			if (pos.y + yAdd * 2 > 4 || pos.y + yAdd * 2 < 0 || pos.x + xAdd * 2 < 0 || pos.x + xAdd * 2 > 8) {
				continue;
			}
			if (board.applyEat(Position(pos.x + xAdd * 2, pos.y + yAdd * 2), this->color) && board.board[pos.y + yAdd][pos.x + xAdd] == 0) {
				movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd * 2));
			}
		}
		else {
			if (pos.y + yAdd * 2 < 5 || pos.y + yAdd * 2 > 9 || pos.x + xAdd * 2 < 0 || pos.x + xAdd * 2 > 8) {
				continue;
			}
			if (board.applyEat(Position(pos.x + xAdd * 2, pos.y + yAdd * 2), this->color) && board.board[pos.y + yAdd][pos.x + xAdd] == 0) {
				movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd * 2));
			}
		}
	}
	return movePos;
}

std::vector<Position> Chariot::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 0, yAdd = 0; i < 4; i++) {
		if (i == 0) {
			xAdd = 0;
			yAdd = -1;
		}
		else if (i == 1) {
			xAdd = 1;
			yAdd = 0;
		}
		else if (i == 2) {
			xAdd = 0;
			yAdd = 1;
		}
		else if (i == 3) {
			xAdd = -1;
			yAdd = 0;
		}
		while (board.applyMove(Position(pos.x + xAdd, pos.y + yAdd), this->color) && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			int check = 0;
			movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd));
			if (this->color == ColorEnum::Black && board.board[pos.y + yAdd][pos.x + xAdd] > 0) {
				check = 1;
			}
			if (this->color == ColorEnum::Red && board.board[pos.y + yAdd][pos.x + xAdd] < 0) {
				check = 1;
			}
			if (check == 1) {
				break;
			}
			if (i == 0) {
				yAdd--;
			}
			else if (i == 1) {
				xAdd++;
			}
			else if (i == 2) {
				yAdd++;
			}
			else {
				xAdd--;
			}
		}
	}
	return movePos;
}
std::vector<Position> Chariot::canEat(Board& board) {
	std::vector<Position> eatPos;
	for (auto& pos : Chariot::canMove(board)) {
		if (board.applyEat(pos, this->color)) {
			eatPos.push_back(pos);
		}
	}
	return eatPos;
}

std::vector<Position> Horse::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 1, yAdd = 1; i < 4; i++) {
		if (i == 0) {
			if (pos.y + yAdd * 2 < 10 && board.board[pos.y + yAdd][pos.x] == 0) {
				if (pos.x + xAdd < 9 && board.applyMove(Position(pos.x + xAdd, pos.y + yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd * 2));
				}
				if (pos.x - xAdd > -1 && board.applyMove(Position(pos.x - xAdd, pos.y + yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x - xAdd, pos.y + yAdd * 2));
				}
			}
		}
		else if (i == 1) {
			if (pos.x + xAdd * 2 < 9 && board.board[pos.y][pos.x + xAdd] == 0) {
				if (pos.y + yAdd < 10 && board.applyMove(Position(pos.x + xAdd * 2, pos.y + yAdd), this->color)) {
					movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd));
				}
				if (pos.y - yAdd > -1 && board.applyMove(Position(pos.x + xAdd * 2, pos.y - yAdd), this->color)) {
					movePos.push_back(Position(pos.x + xAdd * 2, pos.y - yAdd));
				}
			}
		}
		else if (i == 2) {
			if (pos.y - yAdd * 2 > -1 && board.board[pos.y - yAdd][pos.x] == 0) {
				if (pos.x + xAdd < 9 && board.applyMove(Position(pos.x + xAdd, pos.y - yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x + xAdd, pos.y - yAdd * 2));
				}
				if (pos.x - xAdd > -1 && board.applyMove(Position(pos.x - xAdd, pos.y - yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x - xAdd, pos.y - yAdd * 2));
				}
			}
		}
		else {
			if (pos.x - xAdd * 2 > -1 && board.board[pos.y][pos.x - xAdd] == 0) {
				if (pos.y + yAdd < 10 && board.applyMove(Position(pos.x - xAdd * 2, pos.y + yAdd), this->color)) {
					movePos.push_back(Position(pos.x - xAdd * 2, pos.y + yAdd));
				}
				if (pos.y - yAdd > -1 && board.applyMove(Position(pos.x - xAdd * 2, pos.y - yAdd), this->color)) {
					movePos.push_back(Position(pos.x - xAdd * 2, pos.y - yAdd));
				}
			}
		}
	}
	return movePos;
}
std::vector<Position> Horse::canEat(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 1, yAdd = 1; i < 4; i++) {
		if (i == 0) {
			if (pos.y + yAdd * 2 < 10 && board.board[pos.y + yAdd][pos.x] == 0) {
				if (pos.x + xAdd < 9 && board.applyEat(Position(pos.x + xAdd, pos.y + yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd * 2));
				}
				if (pos.x - xAdd > -1 && board.applyEat(Position(pos.x - xAdd, pos.y + yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x - xAdd, pos.y + yAdd * 2));
				}
			}
		}
		else if (i == 1) {
			if (pos.x + xAdd * 2 < 9 && board.board[pos.y][pos.x + xAdd] == 0) {
				if (pos.y + yAdd < 10 && board.applyEat(Position(pos.x + xAdd * 2, pos.y + yAdd), this->color)) {
					movePos.push_back(Position(pos.x + xAdd * 2, pos.y + yAdd));
				}
				if (pos.y - yAdd > -1 && board.applyEat(Position(pos.x + xAdd * 2, pos.y - yAdd), this->color)) {
					movePos.push_back(Position(pos.x + xAdd * 2, pos.y - yAdd));
				}
			}
		}
		else if (i == 2) {
			if (pos.y - yAdd * 2 > -1 && board.board[pos.y - yAdd][pos.x] == 0) {
				if (pos.x + xAdd < 9 && board.applyEat(Position(pos.x + xAdd, pos.y - yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x + xAdd, pos.y - yAdd * 2));
				}
				if (pos.x - xAdd > -1 && board.applyEat(Position(pos.x - xAdd, pos.y - yAdd * 2), this->color)) {
					movePos.push_back(Position(pos.x - xAdd, pos.y - yAdd * 2));
				}
			}
		}
		else {
			if (pos.x - xAdd * 2 > -1 && board.board[pos.y][pos.x - xAdd] == 0) {
				if (pos.y + yAdd < 10 && board.applyEat(Position(pos.x - xAdd * 2, pos.y + yAdd), this->color)) {
					movePos.push_back(Position(pos.x - xAdd * 2, pos.y + yAdd));
				}
				if (pos.y - yAdd > -1 && board.applyEat(Position(pos.x - xAdd * 2, pos.y - yAdd), this->color)) {
					movePos.push_back(Position(pos.x - xAdd * 2, pos.y - yAdd));
				}
			}
		}
	}
	return movePos;
}

std::vector<Position> Cannon::canMove(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 0, yAdd = 0; i < 4; i++) {
		if (i == 0) {
			xAdd = 0;
			yAdd = -1;
		}
		else if (i == 1) {
			xAdd = 1;
			yAdd = 0;
		}
		else if (i == 2) {
			xAdd = 0;
			yAdd = 1;
		}
		else if (i == 3) {
			xAdd = -1;
			yAdd = 0;
		}
		while (board.board[pos.y + yAdd][pos.x + xAdd] == 0 && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			if (board.applyMove(Position(pos.x + xAdd, pos.y + yAdd), this->color))
				movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd));
			if (i == 0) {
				yAdd--;
			}
			else if (i == 1) {
				xAdd++;
			}
			else if (i == 2) {
				yAdd++;
			}
			else {
				xAdd--;
			}
		}
		if (i == 0) {
			yAdd--;
		}
		else if (i == 1) {
			xAdd++;
		}
		else if (i == 2) {
			yAdd++;
		}
		else {
			xAdd--;
		}
		while (board.board[pos.y + yAdd][pos.x + xAdd] == 0 && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			if (i == 0) {
				yAdd--;
			}
			else if (i == 1) {
				xAdd++;
			}
			else if (i == 2) {
				yAdd++;
			}
			else {
				xAdd--;
			}
		}
		if (board.applyMove(Position(pos.x + xAdd, pos.y + yAdd), this->color) && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd));
		}
	}
	return movePos;
}
std::vector<Position> Cannon::canEat(Board& board) {
	std::vector<Position> movePos;
	for (int i = 0, xAdd = 0, yAdd = 0; i < 4; i++) {
		if (i == 0) {
			xAdd = 0;
			yAdd = -1;
		}
		else if (i == 1) {
			xAdd = 1;
			yAdd = 0;
		}
		else if (i == 2) {
			xAdd = 0;
			yAdd = 1;
		}
		else if (i == 3) {
			xAdd = -1;
			yAdd = 0;
		}
		while (board.board[pos.y + yAdd][pos.x + xAdd] == 0 && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			if (i == 0) {
				yAdd--;
			}
			else if (i == 1) {
				xAdd++;
			}
			else if (i == 2) {
				yAdd++;
			}
			else {
				xAdd--;
			}
		}
		if (i == 0) {
			yAdd--;
		}
		else if (i == 1) {
			xAdd++;
		}
		else if (i == 2) {
			yAdd++;
		}
		else {
			xAdd--;
		}
		while (board.board[pos.y + yAdd][pos.x + xAdd] == 0 && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			if (i == 0) {
				yAdd--;
			}
			else if (i == 1) {
				xAdd++;
			}
			else if (i == 2) {
				yAdd++;
			}
			else {
				xAdd--;
			}
		}
		if (board.applyEat(Position(pos.x + xAdd, pos.y + yAdd), this->color) && (pos.x + xAdd) >= 0 && (pos.x + xAdd) <= 8 && (pos.y + yAdd) >= 0 && (pos.y + yAdd) <= 9) {
			movePos.push_back(Position(pos.x + xAdd, pos.y + yAdd));
		}
	}
	return movePos;
}

std::vector<Position> Soldier::canMove(Board& board) {
	std::vector<Position> movePos;
	if (this->color == ColorEnum::Red) {
		if (pos.y > 4) {
			if (board.applyMove(Position(pos.x, pos.y - 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y - 1));
			}
		}
		else if (pos.y <= 4 && pos.y > 0) {
			if (board.applyMove(Position(pos.x, pos.y - 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y - 1));
			}
			if (board.applyMove(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyMove(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
		else {
			if (board.applyMove(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyMove(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
	}
	else {
		if (pos.y < 5) {
			if (board.applyMove(Position(pos.x, pos.y + 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y + 1));
			}
		}
		else if (pos.y >= 5 && pos.y < 9) {
			if (board.applyMove(Position(pos.x, pos.y + 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y + 1));
			}
			if (board.applyMove(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyMove(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
		else {
			if (board.applyMove(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyMove(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
	}
	return movePos;
}
std::vector<Position> Soldier::canEat(Board& board) {
	std::vector<Position> movePos;
	if (this->color == ColorEnum::Red) {
		if (pos.y > 4) {
			if (board.applyEat(Position(pos.x, pos.y - 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y - 1));
			}
		}
		else if (pos.y <= 4 && pos.y > 0) {
			if (board.applyEat(Position(pos.x, pos.y - 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y - 1));
			}
			if (board.applyEat(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyEat(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
		else {
			if (board.applyEat(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyEat(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
	}
	else {
		if (pos.y < 5) {
			if (board.applyEat(Position(pos.x, pos.y + 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y + 1));
			}
		}
		else if (pos.y >= 5 && pos.y < 9) {
			if (board.applyEat(Position(pos.x, pos.y + 1), this->color)) {
				movePos.push_back(Position(pos.x, pos.y + 1));
			}
			if (board.applyEat(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyEat(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
		else {
			if (board.applyEat(Position(pos.x + 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x + 1, pos.y));
			}
			if (board.applyEat(Position(pos.x - 1, pos.y), this->color)) {
				movePos.push_back(Position(pos.x - 1, pos.y));
			}
		}
	}
	return movePos;
}