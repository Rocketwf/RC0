#pragma once

class Span {
    public:
    const int _start_line;
    const int _start_col;
    const int _end_line;
    const int _end_col;
    Span(int start_line, int start_col, int end_line, int end_col): //TODO: Replace with position structs
        _start_line(start_line),
        _start_col(start_col),
        _end_line(end_line),
        _end_col(end_col) {}
};