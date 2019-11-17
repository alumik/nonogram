#ifndef NONOGRAM_H
#define NONOGRAM_H

#include "src/core/nonogram_preview.h"
#include "src/core/nonogram_data.h"
#include "src/utils/util_pvector.h"

#include <QTableWidget>
#include <QVector>
#include <QLabel>
#include <QMouseEvent>

struct GameMove {
    PVector pos;
    QString old_text;
    QString new_text;
    QColor old_background_color;
    QColor new_background_color;
};

class Nonogram : public QTableWidget {
    Q_OBJECT

public:
    NonogramPreview* nonogram_preview;

    explicit Nonogram(QWidget* parent = nullptr);

    PVector getTableSize() const;
    void save() const;
    void load(std::ifstream& fin);
    bool isComplete() const;

private:
    static const int NO_HINT = 0;
    static const int SEPARATOR_HINT = -1;

    bool complete;
    bool mouse_pressed;

    int index;
    QString title;
    PVector game_grid;
    Hint hint;
    QVector<QVector<int> > hint_row_vector;
    QVector<QVector<int> > hint_column_vector;
    PVector table_size;
    PVector last_pos;
    PVector last_cross_highlighted_pos;
    PVector current_pos;
    PVector record_pos;
    PVector drag_size;

    QLabel* label_preview;
    QLabel* label_drag;
    QVector<GameMove> undos;
    QVector<GameMove> redos;

    bool canAct(PVector pos) const;
    bool crossHighlight(PVector pos);
    void eraseLastCrossHighlight();
    void areaHighlight();
    void eraseAreaHighlight();
    void record(PVector pos, const QColor& new_background_color, const QString& new_text);
    void checkCrossComplete(PVector pos);
    void checkGameComplete();
    void colorHintRow(int row, const QColor& color);
    void colorHintColumn(int column, const QColor& color);
    QVector<int> readRow(int row) const;
    QVector<int> readColumn(int column) const;
    QVector<int> readHintRow(int row);
    QVector<int> readHintColumn(int column);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void undo();
    void redo();
    void resetGame();

private slots:
    void getBlock(const QModelIndex& index);
};

#endif // NONOGRAM_H
