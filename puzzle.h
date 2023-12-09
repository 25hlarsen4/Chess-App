/**
 * @file puzzle.h
 * @author teamname: The QT's
 *
 * @brief
 * CS 3505
 * Assignment Name: A9-An-Educational-App
 *
 * The puzzle class sets up puzzles in the application and allows users to interact with puzzles.
 *
 * @date 2023-12-08
 */
#ifndef PUZZLE_H
#define PUZZLE_H

#include "piece.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    enum PuzzleType
    {
        Puzzle1,
        Puzzle2,
        Puzzle3,
        Puzzle4,
        Puzzle5,
        Puzzle6
    };

    explicit Puzzle(QWidget *parent = nullptr);
    // correct moves, piece set up
    explicit Puzzle(PuzzleType, QWidget *parent = nullptr);
    PuzzleType puzzleType;

    /**
     * @brief Handles mouse press events from user.
     * @param e The mouse press event.
     */
    void mousePressEvent(QMouseEvent * e);

private:
    QImage background;

    QHash<QPair<int, int>, Piece::PieceType> boardSetUp;
    QHash<QPair<int, int>, Piece::PieceType> playerPieces;
//    QHash<QPushButton*, Piece*> spacePieceMap;
    QHash<QPair<int, int>, Piece*> piecePositions;
    QList<QPair<int, int>> correctClickSequence;
    QList<QPair<int, int>> potentialLocations;
    QList<QPair<int, int>> computerMoves;
    QList<QPushButton*> allButtons;

    QLabel* feedbackLabel;
    QPushButton* helpButton;

    int currSequenceIndex;
    int computerMovesIndex;
    bool correctMove;

    bool selecting;
    bool moving;

    Piece* selectedPiece;
    QPair<int, int> prevPiecePos;

    QGridLayout *layout;

    QLabel* revealedMove;
    QLabel* WhosTurnLabel;

    QList<PuzzleType> completedPuzzles;

    /**
     * @brief Handles paint events for drawing the puzzle.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Creates the puzzle page.
     */
    void createBoard();

    /**
     * @brief Sets a chess piece on a QPushButton with specific coordinate.
     * @param space The QPushButton with specific coordinate
     * @param piece The chess piece to set.
     */
    void setPiece(QPushButton *space, Piece*);

    /**
     * @brief Sets the background color of a button.
     * @param row The row of the button.
     * @param col The column of the button.
     * @param color The color to be set.
     */
    void setButtonBackgroundColor(int row, int col, QString color);

    // Set up the puzzles
    void setUpPuzzle1();
    void setUpPuzzle2();
    void setUpPuzzle3();
    void setUpPuzzle4();
    void setUpPuzzle5();
    void setUpPuzzle6();

    /**
     * @brief Get the title of the puzzle.
     * @return The puzzle title.
     */
    QString getPuzzleTitle();

    /**
     * @brief Sets up player's chess (white) pieces for the puzzle.
     */
    void setPlayerPieces();

    /**
     * @brief Resets the puzzle board.
     */
    void resetBoard();

    /**
     * @brief Handles the next move in the puzzle.
     */
    void nextMove();

    /**
     * @brief Saves the current game progress.
     */
    void savePuzzle();

signals:
    /**
     * @brief Emit signal when the "Go Back" button is clicked.
     */
    void goBackButtonClicked();

    /**
     * @brief Emit signal when a puzzle is completed.
     * @param puzzleIndex The index of the completed puzzle.
     */
    void puzzleComplete(int);

    /**
     * @brief Emit signal when the puzzle is loaded.
     * @param puzzleIndex The index of the loaded puzzle.
     */
    void fileLoaded(int);

public slots:
    /**
     * @brief Handles the selection of a chess space.
     */
    void selectSpace();

    /**
     * @brief Handles the "Go Back" button click.
     */
    void onGoBackButtonClicked();

    /**
     * @brief Handles the "Help" button click.
     */
    void onHelpButtonClicked();

    /**
     * @brief Loads a puzzle.
     */
    void loadPuzzle();

};

#endif // PUZZLE_H
