#pragma once

namespace sjtu {
    class CrossArray{
    private:
        int max_lines;           // capacity for number of arrays
        int current_lines;       // number of inserted arrays
        int **lines_ptrs;        // array of pointers to int arrays; nullptr if not set
        int *line_sizes;         // sizes of each line (0 if nullptr)

        // helper to count total elements
        int total_count() const {
            int sum = 0;
            for (int i = 0; i < max_lines; ++i) {
                if (lines_ptrs[i]) sum += line_sizes[i];
            }
            return sum;
        }

    public:
        explicit CrossArray(int lines)
            : max_lines(lines), current_lines(0) {
            if (max_lines < 0) max_lines = 0;
            lines_ptrs = new int*[max_lines];
            line_sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                lines_ptrs[i] = nullptr;
                line_sizes[i] = 0;
            }
        }

        CrossArray(const CrossArray & o)
            : max_lines(o.max_lines), current_lines(o.current_lines) {
            lines_ptrs = new int*[max_lines];
            line_sizes = new int[max_lines];
            for (int i = 0; i < max_lines; ++i) {
                line_sizes[i] = o.line_sizes[i];
                if (o.lines_ptrs[i]) {
                    lines_ptrs[i] = new int[line_sizes[i]];
                    for (int j = 0; j < line_sizes[i]; ++j) lines_ptrs[i][j] = o.lines_ptrs[i][j];
                } else {
                    lines_ptrs[i] = nullptr;
                }
            }
        }

        CrossArray & WhichGreater(CrossArray & o){
            int a = this->total_count();
            int b = o.total_count();
            return (a >= b) ? *this : o;
        }

        bool IsSame(const CrossArray & o){
            // Belong to the same memory space if they are the same object
            return this == &o;
        }

        bool InsertArrays(const int * Input, int size){
            if (current_lines >= max_lines) return false;
            int idx = current_lines;
            if (size < 0) size = 0;
            if (size == 0) {
                lines_ptrs[idx] = nullptr;
                line_sizes[idx] = 0;
            } else {
                int *arr = new int[size];
                for (int i = 0; i < size; ++i) arr[i] = Input[i];
                lines_ptrs[idx] = arr;
                line_sizes[idx] = size;
            }
            ++current_lines;
            return true;
        }

        void AppendArrays(const int * Input,int Line,int size){
            // Guaranteed Line is valid and already inserted
            int old_size = line_sizes[Line];
            int new_size = old_size + (size < 0 ? 0 : size);
            int *new_arr = new int[new_size];
            for (int i = 0; i < old_size; ++i) new_arr[i] = lines_ptrs[Line][i];
            for (int i = 0; i < size; ++i) new_arr[old_size + i] = Input[i];
            delete[] lines_ptrs[Line];
            lines_ptrs[Line] = new_arr;
            line_sizes[Line] = new_size;
        }

        void DoubleCrossLength(){
            int new_max = (max_lines == 0 ? 1 : max_lines * 2);
            int **new_lines = new int*[new_max];
            int *new_sizes = new int[new_max];
            // copy existing
            for (int i = 0; i < new_max; ++i) {
                if (i < max_lines) {
                    new_lines[i] = lines_ptrs[i];
                    new_sizes[i] = line_sizes[i];
                } else {
                    new_lines[i] = nullptr;
                    new_sizes[i] = 0;
                }
            }
            delete[] lines_ptrs;
            delete[] line_sizes;
            lines_ptrs = new_lines;
            line_sizes = new_sizes;
            max_lines = new_max;
        }

        const int * AtArray(int i){
            return lines_ptrs[i];
        }

        int & At(int i , int j){
            return lines_ptrs[i][j];
        }

        ~CrossArray(){
            for (int i = 0; i < max_lines; ++i) {
                delete[] lines_ptrs[i];
            }
            delete[] lines_ptrs;
            delete[] line_sizes;
        }

    };
}
