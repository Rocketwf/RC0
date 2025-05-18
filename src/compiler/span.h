#pragma once

class Position {
    public:
    Position(int line, int column):
        m_line(line),
        m_column(column) {};

    int line() const {
        return m_line;
    }
    int column() const {
        return m_column;
    }
    private:
    const int m_line;
    const int m_column;
};

class Span {
    public:
    const Position _start;
    const Position _end;
    Span(const Position start, const Position end):
        _start(start),
        _end(end) {};
    Position start() const {
        return _start;
    }
    Position end() const {
        return _end;
    }

    Span merge(Span later) const {
        return Span(_start, later._end);
    }
};