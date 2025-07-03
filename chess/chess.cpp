/**
 * Requirements:
 * 1. 8 * 8 chessboard
 * 2. Each square can be empty or occupied by a piece
 * 3. Pieces (Pawn, Rook, Knight, Bishop, Queen, King)
 * 4. Players (White, Black)
 * 5. Game Logic (move pieces, check for check/checkmate)
 * 6. Game Controller (main service layer)
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Forward declarations
class Piece;
class Position;

enum class PieceType {
    PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum class Color {
    WHITE, BLACK
};

class Position {
public:
    int x, y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Player {
public:
    string name;
    Color color;

    Player(const string& name, Color color) : name(name), color(color) {}
};

class Cell {
public:
    int x, y;
    shared_ptr<Piece> piece;

    Cell() : x(0), y(0), piece(nullptr) {}
    Cell(int x, int y) : x(x), y(y), piece(nullptr) {}

    bool isEmpty() const {
        return piece == nullptr;
    }

    shared_ptr<Piece> getPiece() const {
        return piece;
    }

    void setPiece(shared_ptr<Piece> p) {
        piece = p;
    }
};

// Abstract base class for chess pieces
class Piece {
public:
    Position position;
    Color color;

    Piece(Position pos, Color c) : position(pos), color(c) {}
    virtual ~Piece() = default;

    virtual bool isValidMove(const Position& initial, const Position& final) = 0;
    virtual char getSymbol() const = 0;
};

class King : public Piece {
public:
    King(const Position& pos, Color c) : Piece(pos, c) {}

    bool isValidMove(const Position& initial, const Position& final) override {
        int dx = abs(final.x - initial.x);
        int dy = abs(final.y - initial.y);
        return (dx <= 1 && dy <= 1) && !(dx == 0 && dy == 0); // King can move one square in any direction
    }

    char getSymbol() const override {
        return (color == Color::WHITE) ? 'K' : 'k'; // Uppercase for white, lowercase for black
    }
};

class Rook : public Piece {
public:
    Rook(const Position& pos, Color c) : Piece(pos, c) {}

    bool isValidMove(const Position& initial, const Position& final) override {
        // Rook can move any number of squares along a row or column
        return (initial.x == final.x && initial.y != final.y) || 
               (initial.y == final.y && initial.x != final.x);
    }

    char getSymbol() const override {
        return (color == Color::WHITE) ? 'R' : 'r'; // Uppercase for white, lowercase for black
    }
};

class Bishop : public Piece {
public:
    Bishop(const Position& pos, Color c) : Piece(pos, c) {}

    bool isValidMove(const Position& initial, const Position& final) override {
        int dx = abs(final.x - initial.x);
        int dy = abs(final.y - initial.y);
        // Bishop moves diagonally
        return dx == dy && dx != 0;
    }
    
    char getSymbol() const override {
        return (color == Color::WHITE) ? 'B' : 'b';
    }
};

class Knight : public Piece {
public:
    Knight(const Position& pos, Color c) : Piece(pos, c) {}

    bool isValidMove(const Position& initial, const Position& final) override {
        int dx = abs(final.x - initial.x);
        int dy = abs(final.y - initial.y);
        // Knight moves in an "L" shape
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    char getSymbol() const override {
        return (color == Color::WHITE) ? 'N' : 'n';
    }
};

class Queen : public Piece {
public:
    Queen(const Position& position, Color color) : Piece(position, color) {}
    
    bool isValidMove(const Position& initial, const Position& final) override {
        int dx = abs(final.x - initial.x);
        int dy = abs(final.y - initial.y);
        // Queen combines rook and bishop moves
        return (initial.x == final.x || initial.y == final.y || dx == dy) && 
               !(dx == 0 && dy == 0);
    }
    
    char getSymbol() const override {
        return (color == Color::WHITE) ? 'Q' : 'q';
    }
};

class Pawn : public Piece {
public:
    public:
    Pawn(const Position& position, Color color) : Piece(position, color) {}
    
    bool isValidMove(const Position& initial, const Position& final) override {
        int direction = (color == Color::WHITE) ? 1 : -1;
        int dy = final.y - initial.y;
        int dx = abs(final.x - initial.x);
        
        // Basic forward move
        if (dx == 0 && dy == direction) return true;
        // Initial two-square move
        if (dx == 0 && dy == 2 * direction && 
            ((color == Color::WHITE && initial.y == 1) || 
             (color == Color::BLACK && initial.y == 6))) return true;
        
        return false;
    }
    
    char getSymbol() const override {
        return (color == Color::WHITE) ? 'P' : 'p';
    }
};

class PieceFactory {
public:
    static std::shared_ptr<Piece> createPiece(PieceType type, Color color, const Position& position) {
        switch (type) {
            case PieceType::KING:
                return std::make_shared<King>(position, color);
            case PieceType::QUEEN:
                return std::make_shared<Queen>(position, color);
            case PieceType::ROOK:
                return std::make_shared<Rook>(position, color);
            case PieceType::BISHOP:
                return std::make_shared<Bishop>(position, color);
            case PieceType::KNIGHT:
                return std::make_shared<Knight>(position, color);
            case PieceType::PAWN:
                return std::make_shared<Pawn>(position, color);
            default:
                throw std::invalid_argument("Invalid piece type");
        }
    }
};

class ChessBoard {
private:
    static std::shared_ptr<ChessBoard> instance;
    std::vector<std::vector<Cell>> board;
    
    ChessBoard() : board(8, std::vector<Cell>(8)) {
        initializeBoard();
    }
    
public:
    static std::shared_ptr<ChessBoard> getInstance() {
        if (instance == nullptr) {
            instance = std::shared_ptr<ChessBoard>(new ChessBoard());
        }
        return instance;
    }
    
    void initializeBoard() {
        // Initialize board with starting positions
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = Cell(i, j);
            }
        }
        
        // Place white pieces
        board[0][0].setPiece(PieceFactory::createPiece(PieceType::ROOK, Color::WHITE, Position(0, 0)));
        board[0][1].setPiece(PieceFactory::createPiece(PieceType::KNIGHT, Color::WHITE, Position(0, 1)));
        board[0][2].setPiece(PieceFactory::createPiece(PieceType::BISHOP, Color::WHITE, Position(0, 2)));
        board[0][3].setPiece(PieceFactory::createPiece(PieceType::QUEEN, Color::WHITE, Position(0, 3)));
        board[0][4].setPiece(PieceFactory::createPiece(PieceType::KING, Color::WHITE, Position(0, 4)));
        board[0][5].setPiece(PieceFactory::createPiece(PieceType::BISHOP, Color::WHITE, Position(0, 5)));
        board[0][6].setPiece(PieceFactory::createPiece(PieceType::KNIGHT, Color::WHITE, Position(0, 6)));
        board[0][7].setPiece(PieceFactory::createPiece(PieceType::ROOK, Color::WHITE, Position(0, 7)));
        
        // Place white pawns
        for (int i = 0; i < 8; i++) {
            board[1][i].setPiece(PieceFactory::createPiece(PieceType::PAWN, Color::WHITE, Position(1, i)));
        }
        
        // Place black pieces
        board[7][0].setPiece(PieceFactory::createPiece(PieceType::ROOK, Color::BLACK, Position(7, 0)));
        board[7][1].setPiece(PieceFactory::createPiece(PieceType::KNIGHT, Color::BLACK, Position(7, 1)));
        board[7][2].setPiece(PieceFactory::createPiece(PieceType::BISHOP, Color::BLACK, Position(7, 2)));
        board[7][3].setPiece(PieceFactory::createPiece(PieceType::QUEEN, Color::BLACK, Position(7, 3)));
        board[7][4].setPiece(PieceFactory::createPiece(PieceType::KING, Color::BLACK, Position(7, 4)));
        board[7][5].setPiece(PieceFactory::createPiece(PieceType::BISHOP, Color::BLACK, Position(7, 5)));
        board[7][6].setPiece(PieceFactory::createPiece(PieceType::KNIGHT, Color::BLACK, Position(7, 6)));
        board[7][7].setPiece(PieceFactory::createPiece(PieceType::ROOK, Color::BLACK, Position(7, 7)));
        
        // Place black pawns
        for (int i = 0; i < 8; i++) {
            board[6][i].setPiece(PieceFactory::createPiece(PieceType::PAWN, Color::BLACK, Position(6, i)));
        }
    }
    
    std::shared_ptr<Piece> getPiece(const Position& position) {
        if (position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8) {
            return board[position.x][position.y].getPiece();
        }
        return nullptr;
    }
    
    Cell& getCell(const Position& position) {
        return board[position.x][position.y];
    }
    
    std::vector<std::vector<Cell>>& getBoard() {
        return board;
    }
    
    void displayBoard() {
        std::cout << "  0 1 2 3 4 5 6 7\n";
        for (int i = 7; i >= 0; i--) {
            std::cout << i << " ";
            for (int j = 0; j < 8; j++) {
                if (board[i][j].isEmpty()) {
                    std::cout << ". ";
                } else {
                    std::cout << board[i][j].getPiece()->getSymbol() << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};

// Static member definition
std::shared_ptr<ChessBoard> ChessBoard::instance = nullptr;

class Game {
private:
    std::shared_ptr<ChessBoard> chessboard;
    Player player1, player2;
    Player* currentPlayer;
    
public:
    Game(const Player& p1, const Player& p2) : player1(p1), player2(p2) {
        chessboard = ChessBoard::getInstance();
        currentPlayer = &player1;
    }
    
    void play() {
        while (true) {
            chessboard->displayBoard();
            std::cout << "User: " << currentPlayer->name << " Turn\n";
            std::cout << "Enter Move (startX startY endX endY): ";
            
            int startX, startY, endX, endY;
            std::cin >> startX >> startY >> endX >> endY;
            
            Position start(startX, startY);
            Position end(endX, endY);
            
            if (makeMove(start, end)) {
                if (isGameOver()) {
                    std::cout << "Game Over!\n";
                    break;
                }
                switchTurn();
            } else {
                std::cout << "Invalid move! Try again.\n";
            }
        }
    }
    
    void switchTurn() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }
    
    bool isGameOver() {
        // Simplified checkmate logic - can be expanded
        return false;
    }
    
    bool makeMove(const Position& from, const Position& to) {
        // Validate bounds
        if (from.x < 0 || from.x >= 8 || from.y < 0 || from.y >= 8 ||
            to.x < 0 || to.x >= 8 || to.y < 0 || to.y >= 8) {
            return false;
        }
        
        auto piece = chessboard->getPiece(from);
        if (!piece) {
            std::cout << "No piece at starting position!\n";
            return false;
        }
        
        // Check if piece belongs to current player
        if (piece->color != currentPlayer->color) {
            std::cout << "Not your piece!\n";
            return false;
        }
        
        // Check if move is valid for this piece type
        if (!piece->isValidMove(from, to)) {
            std::cout << "Invalid move for this piece!\n";
            return false;
        }
        
        // Check if destination has friendly piece
        auto destPiece = chessboard->getPiece(to);
        if (destPiece && destPiece->color == currentPlayer->color) {
            std::cout << "Cannot capture your own piece!\n";
            return false;
        }
        
        // Make the move
        chessboard->getCell(to).setPiece(piece);
        chessboard->getCell(from).setPiece(nullptr);
        piece->position = to;
        
        return true;
    }
};

int main() {
    Player p1("Santosh", Color::WHITE);
    Player p2("Vijay", Color::BLACK);
    Game game(p1, p2);
    game.play();
    
    return 0;
}